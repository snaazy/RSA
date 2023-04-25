#include <stdio.h>
#include "rsa_fonctions.h"

int main() {
    char pub_key_file[] = "pub_key.txt";
    int e, n;

    printf("Entrez le nom du fichier contenant la clé publique : ");
    scanf("%s", pub_key_file);
    lecture_cle_pub(pub_key_file, &e, &n);

    char input_file[] = "input.txt";
    printf("Entrez le nom du fichier à chiffrer : ");
    scanf("%s", input_file);

    char encrypted_file[] = "encrypted.txt";
    printf("Entrez le nom du fichier où sauvegarder le texte chiffré : ");
    scanf("%s", encrypted_file);

    chiffrement_texte(e, n, input_file, encrypted_file);
    printf("Programme exécuté avec succès\n");
    return 0;
}
