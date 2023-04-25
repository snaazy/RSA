#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// TP2 et TP3 - RSA 
// FEKIH HASSEN Yassine 
// u32106510


/**
    Détermine si un entier est premier ou non.
    @param n : un entier à tester
    @return 1 si n est premier, 0 sinon
*/
int premier(int n) {
    if (n <= 1) { // 1 et les nombres negatifs ne sont pas premiers
        return 0;
    }
    // teste tous les entiers de 2 à racine carrée de n
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    
    return 1; // sinon n est premier
}

/**
    Calcule le PGCD de deux entiers a et b.
    @param a : un entier
    @param b : un entier
    @return le PGCD de a et b
*/
int pgcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/**
    Calcule l'inverse modulaire de a modulo m, c'est-à-dire l'entier d tel que a*d ≡ 1 (mod m)
    @param a : l'entier a
    @param m : l'entier m
    @return l'entier d tel que a*d ≡ 1 (mod m), s'il existe, sinon retourne -1
*/
int inverse_modulaire(int a, int m) {
    for (int d = 1; d < m; d++) {
        if ((a * d) % m == 1) {
            return d;
        }
    }
    return -1;
}

/**
    Calcule la clé privée pour un algorithme de chiffrement RSA à partir de la clé publique (e, p, q).
    @param e : un entier représentant la clé publique
    @param p : un entier premier
    @param q : un entier premier différent de p
    @return l'entier d représentant la clé privée si elle peut être calculée, -1 sinon
*/
int choix_cle_privee(int e, int p, int q) {
    int phi = (p - 1) * (q - 1);

    if (pgcd(e, phi) != 1) {
        return -1;
    }

    int d = inverse_modulaire(e, phi);
    return d;
}

/**
    Effectue le chiffrement RSA d'un message m avec une clé publique (e, n).
    @param e : un entier représentant la clé publique
    @param n : un entier représentant le produit de deux nombres premiers distincts
    @param m : un entier représentant le message à chiffrer
    @return l'entier chiffré correspondant à m
*/
int chiffrement(int e, int n, int m) {
    int c = (int) pow(m, e) % n;
    return c;
}

/**
    Effectue le déchiffrement RSA d'un message chiffré c avec une clé privée d et un modulo n.
    @param d : un entier représentant la clé privée
    @param n : un entier représentant le produit de deux nombres premiers distincts
    @param c : un entier représentant le message chiffré
    @return l'entier déchiffré correspondant à c
*/
int dechiffrement(int d, int n, int c) {
    int m = (int) pow(c, d) % n;
    return m;
}


/**
    Chiffre un texte contenu dans un fichier avec une clé publique (e, n) et enregistre le résultat dans un fichier de sortie.
    @param e : un entier représentant la clé publique
    @param n : un entier représentant le produit de deux nombres premiers distincts
    @param fich : une chaîne de caractères contenant le nom du fichier d'entrée à chiffrer
    @param res : une chaîne de caractères contenant le nom du fichier de sortie pour le résultat chiffré
*/
void chiffrement_texte(int e, int n, char fich[], char res[]) {
    FILE *input = fopen(fich, "r");
    FILE *output = fopen(res, "w");

    if (input == NULL || output == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    int c;
    while ((c = fgetc(input)) != EOF) {
        int m = c;
        int chiffre = chiffrement(e, n, m);
        fprintf(output, "%d\n", chiffre);
    }

    fclose(input);
    fclose(output);
}

/**
    Déchiffre un texte chiffré contenu dans un fichier avec une clé privée (p, q, d) et affiche le résultat à l'écran.
    @param p : un entier premier
    @param q : un entier premier différent de p
    @param d : un entier représentant la clé privée
    @param chiff : une chaîne de caractères contenant le nom du fichier contenant le texte chiffré
*/
void dechiffrement_texte(int p, int q, int d, char chiff[]) {
    int n = p * q;
    FILE *input = fopen(chiff, "r");

    if (input == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    int c;
    while (fscanf(input, "%d", &c) != EOF) { // lit chaque entier du fichier chiffré jusqu'à la fin de fichier (EOF)
        int m = dechiffrement(d, n, c);  // déchiffre l'entier avec la clé privée (p, q, d)
        printf("%c", (char) m); // affiche le caractère correspondant à l'entier déchiffré
    }

    fclose(input);
}

/**
    Crée une paire de clés RSA et enregistre les clés publiques et privées dans deux fichiers.
    @param fich_cle_pub : une chaîne de caractères contenant le nom du fichier pour la clé publique
    @param fich_cle_pri : une chaîne de caractères contenant le nom du fichier pour la clé privée
*/
void creation_paire_cles(char fich_cle_pub[], char fich_cle_pri[]) {
    srand(time(NULL));

    int p, q;
    do {
        p = rand() % 100 + 2;   // choisit un nombre premier aléatoire p entre 2 et 101
    } while (!premier(p));

    do {
        q = rand() % 100 + 2;
    } while (!premier(q));

    int n = p * q; // calcule le modulo n
    int phi = (p - 1) * (q - 1);  // calcule la valeur de l'indicatrice d'Euler de n
    int e;
    do {
        e = rand() % (phi - 2) + 2; // choisit un entier aléatoire e entre 2 et phi-1
    } while (pgcd(e, phi) != 1); // vérifie si e et phi sont premiers entre eux

    int d = choix_cle_privee(e, p, q);  // calcule la clé privée correspondant à e

    FILE *pub_key = fopen(fich_cle_pub, "w");
    FILE *pri_key = fopen(fich_cle_pri, "w");

    if (pub_key == NULL || pri_key == NULL) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    fprintf(pub_key, "%d\n%d", e, n); // écrit la clé publique (e, n) dans le fichier correspondant
    fprintf(pri_key, "%d\n%d\n%d\n%d", p, q, d, n); // écrit la clé privée (p, q, d, n) dans le fichier correspondant

    fclose(pub_key);
    fclose(pri_key);
}

/**
    Lit une clé publique RSA à partir d'un fichier et stocke les valeurs de e et n.
    @param nom_fichier : une chaîne de caractères contenant le nom du fichier pour la clé publique
    @param e : un pointeur vers un entier pour stocker la valeur de e
    @param n : un pointeur vers un entier pour stocker la valeur de n
*/
void lecture_cle_pub(char nom_fichier[], int *e, int *n) {
    FILE *input = fopen(nom_fichier, "r"); // ouvre le fichier contenant la clé publique en lecture

    if (input == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    fscanf(input, "%d%d", e, n); // lit les deux entiers (e et n) à partir du fichier
    fclose(input);
}
