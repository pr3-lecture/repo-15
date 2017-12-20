#include <stdio.h>
#include <memory.h>
#include "crypto.h"

#define ENCRYPT 0
#define DECRYPT 1

int stelleImAlphabet(char x, const char* alphabet) {
    for (int i = 0; i < *alphabet; i++) {
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

int encrypt(KEY key, const char* input, char* output) {
    // Laenge des Schluessel pruefen
    if (strlen(key.chars) < 2) {
        printf("Key zu kurz");
        return E_KEY_TOO_SHORT;
    }

    // Inhalt des Inputs pruefen
    if (pruefeGueltigeZeichen(ENCRYPT, input) == 0) {
        printf("Ungueltige Zeichen in der Nachricht");
        return E_MESSAGE_ILLEGAL_CHAR;
    }

    // Inhalt des Keys pruefen
    if (pruefeGueltigeZeichen(ENCRYPT, key.chars) == 0) {
        printf("Ungueltige Zeichen im Key");
        return E_KEY_ILLEGAL_CHAR;
    }

    // Verschuesseln
#ifdef DEBUG
    printf("Key: %s\n", key.chars);
#endif
    for (int i = 0; i < strlen(input); i++) {
        // Position im Key anpassen, da Key kuerzer sein kann als Message
        int korrigiertePosition = (int) (i % strlen(key.chars));
        int positionMessage = stelleImAlphabet(input[i], MESSAGE_CHARACTERS) + 1;
#ifdef DEBUG
        printf("Zaehler: %d, Position in Key: %d\n", i, korrigiertePosition);
#endif
        int positionKey = stelleImAlphabet(key.chars[korrigiertePosition], KEY_CHARACTERS) + 1;
#ifdef DEBUG
        printf("Message: %c (%d), Key: %c (%d)\n", input[i], positionMessage, key.chars[korrigiertePosition], positionKey);
#endif
        output[i] = CYPHER_CHARACTERS[positionMessage ^ positionKey];
    }

    // '\0' anhaengen
    output[strlen(input)] = '\0';

    return 0;
}

int decrypt(KEY key, const char* cypherText, char* output) {
    // Geht eigentlich so wie encrypt, bis auf MESSAGE_CHARACTERS und CYPHER_CHARACTERS
    //return encrypt(key, cypherText, output);

    // Laenge des Schluessel pruefen
    if (strlen(key.chars) < 2) {
        printf("Key zu kurz");
        return E_KEY_TOO_SHORT;
    }

    // Inhalt des Inputs pruefen
    if (pruefeGueltigeZeichen(DECRYPT, cypherText) == 0) {
        printf("Ungueltige Zeichen in der Nachricht");
        return E_CYPHER_ILLEGAL_CHAR;
    }

    // Inhalt des Keys pruefen
    if (pruefeGueltigeZeichen(DECRYPT, key.chars) == 0) {
        printf("Ungueltige Zeichen im Key");
        return E_KEY_ILLEGAL_CHAR;
    }

    // Entschuesseln
#ifdef DEBUG
    printf("Key: %s\n", key.chars);
#endif
    for (int i = 0; i < strlen(cypherText); i++) {
        // Position im Key anpassen, da Key kuerzer sein kann als Message
        int korrigiertePosition = (int) (i % strlen(key.chars));
        int positionCypher = stelleImAlphabet(cypherText[i], CYPHER_CHARACTERS);
#ifdef DEBUG
        printf("Zaehler: %d, Position in Key: %d\n", i, korrigiertePosition);
#endif
        int positionKey = stelleImAlphabet(key.chars[korrigiertePosition], KEY_CHARACTERS) + 1;
#ifdef DEBUG
        printf("Message: %c (%d), Key: %c (%d)\n", cypherText[i], positionCypher, key.chars[korrigiertePosition], positionKey);
#endif
        output[i] = MESSAGE_CHARACTERS[(positionCypher ^ positionKey) - 1];
    }

    // '\0' anhaengen
    output[strlen(cypherText)] = '\0';

    return 0;
}