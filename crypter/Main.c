#include <memory.h>
#include <stdio.h>
#include "crypto.h"

int main(int args, char** argv) {
    KEY k;
    // 1. Parameter: KEY
    k.chars = argv[1];

    // Wenn Key nicht vorhanden ist, wird die Routine abgebrochen
    if (argv[1] == NULL) {
        printf("KEY fehlt!");
        return -1;
    }

    // 2. Parameter vorhanden?
    char eingabe[100];
    if (argv[2] != NULL) {
        FILE* f = fopen(argv[2], "r");

        if (f != NULL) {
            //fscanf(f,"%[^\n]", eingabe);
            fgets(eingabe, 100, f);
            fclose(f);
        }
    } else {
        printf("Bitte Nachricht eingeben: ");
        scanf("%s", eingabe);
    }

    char ergebnis[strlen(eingabe)];

    //argv[0] = "encrypt";
    if (strcmp(argv[0], "encrypt") == 0) {
    //k.type = 2;
    //if (k.type == 1) {
        if (encrypt(k, eingabe, ergebnis) == 0) {
            printf("Nachricht: %s\nKey: %s\nErgebnis: %s\n", eingabe, argv[1], ergebnis);
        }
    } else {
        if (decrypt(k, eingabe, ergebnis) == 0) {
            printf("Nachricht: %s\nKey: %s\nErgebnis: %s\n", eingabe, argv[1], ergebnis);
        }
    }

    return 0;
}