# Makefile pour compiler les programmes alice.c, bob.c et les fonctions RSA dans rsa_fonctions.c

# Définition des variables du compilateur
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Liste des fichiers objets nécessaires pour chaque cible
OBJS = alice.o bob.o rsa_fonctions.o

# Liste des cibles à compiler
TARGETS = alice bob

# Règle pour générer toutes les cibles
all: $(TARGETS)

# Règle pour générer le programme alice
alice: alice.o rsa_fonctions.o
	$(CC) $(CFLAGS) -o alice alice.o rsa_fonctions.o

# Règle pour générer le programme bob
bob: bob.o rsa_fonctions.o
	$(CC) $(CFLAGS) -o bob bob.o rsa_fonctions.o

# Règles pour générer les fichiers objets
alice.o: alice.c rsa_fonctions.h
	$(CC) $(CFLAGS) -c alice.c

bob.o: bob.c rsa_fonctions.h
	$(CC) $(CFLAGS) -c bob.c

rsa_fonctions.o: rsa_fonctions.c rsa_fonctions.h
	$(CC) $(CFLAGS) -c rsa_fonctions.c

# Règle pour nettoyer les fichiers objets
clean:
	rm -f $(OBJS)

# Règle pour nettoyer les fichiers objets et les cibles
distclean: clean
	rm -f $(TARGETS)
