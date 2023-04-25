#include <stdio.h>
#include "rsa_fonctions.h"

int main() {
    char pub_key_file[] = "pub_key.txt";
    char pri_key_file[] = "pri_key.txt";

    creation_paire_cles(pub_key_file, pri_key_file);

    int p, q, d, n;
    FILE *pri_key = fopen(pri_key_file, "r");
    fscanf(pri_key, "%d%d%d%d", &p, &q, &d, &n);
    fclose(pri_key);

    char encrypted_file[] = "encrypted.txt";
    printf("Entrez le nom du fichier à déchiffrer : ");
    scanf("%s", encrypted_file);

    printf("Message déchiffré : ");
    dechiffrement_texte(p, q, d, encrypted_file);
    printf("\n");
    printf("Programme exécuté avec succès\n");
    return 0;
}
