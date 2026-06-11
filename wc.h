#ifndef WC_H
#define WC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compteur_caracteres(FILE *fichier);
void compteur_lignes(FILE *fichier);
void compteur_mots(FILE *fichier);
void longueur_max_ligne(FILE *fichier);
void afficher_fichier_format(FILE *fichier);

void option(FILE *fichier, int argc, char *argv[], const char *nom_fichier);
void traiter_arguments(int argc, char *argv[]);

#endif
