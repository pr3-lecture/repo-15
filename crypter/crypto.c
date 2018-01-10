#include <stdio.h>
#include <memory.h>
#include "crypto.h"

//#define DEBUG

/**
 * Gibt die Stelle eines Buchstaben in einem uebergebenen Alphabet zurueck
 * @param x Buchstabe
 * @param alphabet Alphabet
 * @return Stelle des Buchstabens im Alphabet
 */
int stelleImAlphabet(char x, const char* alphabet) {
    for (int i = 0; i < strlen(alphabet); i++) {
        if (alphabet[i] == x) {
            return i;
        }
    }
    return -1;
}

/**
 * Prueft, ob eine Zeichenkennte nur erlaubet Zeichen enthaelt
 * @param modus 0: encrypt, 1: decrypt
 * @param message zu pruefende Nachricht
 * @param zeichen erlaubte Zeichen
 * @return 0 wenn ungueltige Zeichen vorkommen, ansonsten 1
 */
int pruefeGueltigeZeichen(int modus, const char* message) {
    char* alphabet;

    if (modus == 0) {
        alphabet = MESSAGE_CHARACTERS;
    } else {
        alphabet = CYPHER_CHARACTERS;
    }

    for (int i = 0; i < strlen(message); i++) {
        char zeichen = message[i];
        int ok = 0;

        for (int j = 0; j < strlen(alphabet); j++) {
            if (zeichen == alphabet[j]) {
                ok = 1;
                break;
            }
        }

        if (ok == 0) {
            return 0;
        }
    }

    return 1;
}

/**
 * Prueft, ob Key und Message bzw. Cypher in Ordnung sind
 * @param k Key
 * @param input Message
 * @param modus 0: encrypt, 1: decrypt
 * @return 0 wenn alles ok, ansonsten Fehlercode
 */
int inputUndKeyPruefen(KEY k, char* input, int modus) {
    /* Laenge des Keys pruefen */
    if (strlen(k.chars) < 1) {
        fprintf(stderr, "Key zu kurz\n");
        return E_KEY_TOO_SHORT;
    }

    /* Encrypt */
    if (modus == ENCRYPT) {
        /* Inhalt der Nachricht pruefen */
        if (pruefeGueltigeZeichen(ENCRYPT, input) == 0) {
            fprintf(stderr, "Ungueltige Zeichen in der Nachricht\n");
            return E_MESSAGE_ILLEGAL_CHAR;
        }

        if (pruefeGueltigeZeichen(ENCRYPT, k.chars) == 0) {
            fprintf(stderr, "Ungueltige Zeichen im Key\n");
            return E_KEY_ILLEGAL_CHAR;
        }
    } else {
        /* Decrypt */
        /* Inhalt des Inputs pruefen */
        if (pruefeGueltigeZeichen(DECRYPT, input) == 0) {
            fprintf(stderr, "Ungueltige Zeichen im Cypher Text\n");
            return E_CYPHER_ILLEGAL_CHAR;
        }

        /* Inhalt des Keys pruefen */
        if (pruefeGueltigeZeichen(DECRYPT, k.chars) == 0) {
            fprintf(stderr, "Ungueltige Zeichen im Key\n");
            return E_KEY_ILLEGAL_CHAR;
        }
    }

    return 0;
}

/**
 * Wendet die XOR-Funktion an
 * @param key Key zum Verschluesseln / Entschluesseln
 * @param input Nachricht
 * @param output Ergebnis
 * @param modus 0: encrypt, 1: decrypt
 * @param len Laenge der Nachricht
 */
void crypt(KEY key, const char* input, char* output, int modus, int len) {
    for (int i = 0; i < len; i++) {
        /* Position im Key anpassen, da Key kuerzer sein kann als Message */
        int korrigiertePosition = (int) (i % strlen(key.chars));
        int positionKey = stelleImAlphabet(key.chars[korrigiertePosition], KEY_CHARACTERS) + 1;
        int positionMessage = 0;

#ifdef DEBUG
        printf("Zaehler: %d, Position in Key: %d\n", i, korrigiertePosition);
#endif

        /* Encrypt */
        if (modus == ENCRYPT) {
            positionMessage = stelleImAlphabet(input[i], MESSAGE_CHARACTERS) + 1;
        } else {
            /* Decrypt */
            positionMessage= stelleImAlphabet(input[i], CYPHER_CHARACTERS);
        }

#ifdef DEBUG
        printf("Message: %c (%d), Key: %c (%d), Neuer Char: %c\n", input[i], positionMessage, key.chars[korrigiertePosition], positionKey, CYPHER_CHARACTERS[positionMessage ^ positionKey]);
#endif

        if (modus == ENCRYPT) {
            output[i] = CYPHER_CHARACTERS[positionMessage ^ positionKey];
        } else {
            output[i] = MESSAGE_CHARACTERS[(positionMessage ^ positionKey) - 1];
        }
    }

    /* '\0' anhaengen */
    output[strlen(input)] = '\0';
}

/**
 * Verschluesselt eine Nachricht
 * @param key Key zum Verschluesseln
 * @param input Nachricht in Klartext
 * @param output Verschluesselte Nachricht
 * @return 0 wenn alles ok, ansonsten Fehlercode
 */
int encrypt(KEY key, const char* input, char* output) {
    int pruefung = inputUndKeyPruefen(key, (char *) input, ENCRYPT);

    if (pruefung == 0) {
#ifdef DEBUG
        printf("Key: %s\n", key.chars);
#endif

        crypt(key, input, output, ENCRYPT, (int) strlen(input));

        return 0;
    } else {
        return pruefung;
    }
}

/**
 * Entschluesselt eine nachricht
 * @param key Key zum Entschluesseln
 * @param cypherText Verschluesselte Nachricht
 * @param output Nachricht in Klartext
 * @return 0 wenn alles ok, ansonsten Fehlercode
 */
int decrypt(KEY key, const char* cypherText, char* output) {
    int pruefung = inputUndKeyPruefen(key, (char *) cypherText, DECRYPT);

    if (pruefung == 0) {
#ifdef DEBUG
        printf("Key: %s\n", key.chars);
#endif

        crypt(key, cypherText, output, DECRYPT, (int) strlen(cypherText));

        return 0;
    } else {
        return pruefung;
    }
}