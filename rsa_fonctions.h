#ifndef RSA_FONCTIONS_H
#define RSA_FONCTIONS_H


int premier(int n);
int pgcd(int a, int b);
int choix_cle_privee(int e, int p, int q);
int chiffrement(int e, int n, int m);
int dechiffrement(int d, int n, int c);
void chiffrement_texte(int e, int n, char fich[], char res[]);
void dechiffrement_texte(int p, int q, int d, char chiff[]);
void creation_paire_cles(char fich_cle_pub[], char fich_cle_pri[]);
void lecture_cle_pub(char nom_fichier[], int *e, int *n);

#endif 
