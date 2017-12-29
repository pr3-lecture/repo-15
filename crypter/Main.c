#include <memory.h>
#include <stdio.h>
#include "crypto.h"
#include "regex.h"

//#define DEBUG

/**
 * Extrahiert aus dem Aufrufpfad den Modus
 * @param aufrufpfad Aufrufpfad
 * @return 0 (ENCRYPT) / 1 (DECRYPT)
 */
int getModus(char* aufrufpfad) {
    regex_t regex;
    int res;
    int ergebnis = -1;

    /* Encrypt */
    regcomp(&regex, "encrypt", 0);
    res = regexec(&regex, aufrufpfad, 0, NULL, 0);

    if (!res) {
        ergebnis = ENCRYPT;
    }

    /* Decrypt */
    regcomp(&regex, "decrypt", 0);
    res = regexec(&regex, aufrufpfad, 0, NULL, 0);

    if (!res) {
        ergebnis = DECRYPT;
    }

    regfree(&regex);
    return ergebnis;
}

int main(int args, char** argv) {
    KEY k;
    /* 1. Parameter: KEY */
    k.chars = argv[1];

    /* Wenn Key nicht vorhanden ist, wird die Routine abgebrochen */
    if (argv[1] == NULL) {
        printf("KEY fehlt!");
        return -1;
    }

    /* 2. Parameter vorhanden? */
    char eingabe[100];
    if (argv[2] != NULL) {
        FILE* f = fopen(argv[2], "r");

        if (f != NULL) {
            fgets(eingabe, 100, f);
            fclose(f);
        }
    } else {
        printf("Bitte Nachricht eingeben: ");
        scanf("%s", eingabe);
    }

    char ergebnis[strlen(eingabe)];

#ifdef DEBUG
    printf("Modus: %s\n", argv[0]);
#endif

    /* Modus bestimmen */
    int modus = getModus(argv[0]);

    if (modus == ENCRYPT) {
        if (encrypt(k, eingabe, ergebnis) == 0) {
            printf("Nachricht: %s\nKey: %s\nErgebnis: %s\n", eingabe, argv[1], ergebnis);
        }
    } else if (modus == DECRYPT) {
        if (decrypt(k, eingabe, ergebnis) == 0) {
            printf("Nachricht: %s\nKey: %s\nErgebnis: %s\n", eingabe, argv[1], ergebnis);
        }
    }

    return 0;
}