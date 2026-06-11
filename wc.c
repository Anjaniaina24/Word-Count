#include "wc.h"

#define TAILLE_BUFFER 1024
#define VERSION "1.0.0"

// ==================== AFFICHAGE HELP & VERSION ====================

void afficher_help(const char *nom_programme)
{
    printf("Usage: %s [OPTION]... [FICHIER]...\n", nom_programme);
    printf("Compteur de lignes, mots et caractères (version simplifiée de wc).\n\n");
    printf("Options :\n");
    printf("  -l              afficher le nombre de lignes\n");
    printf("  -w              afficher le nombre de mots\n");
    printf("  -c, -m          afficher le nombre de caractères\n");
    printf("  -L              afficher la longueur de la ligne la plus longue\n");
    printf("  --files-form    afficher le contenu du fichier avec $ au niveau des \\n\n");
    printf("  --help          afficher ce message d'aide\n");
    printf("  --version       afficher la version du programme\n\n");
    printf("Si aucune option n'est spécifiée, affiche par défaut : lignes, mots, caractères.\n");
    printf("Vous pouvez combiner les options, ex: -lwc ou -lwL\n");
}

void afficher_version(void)
{
    printf("wc (version maison) %s\n", VERSION);
    printf("Développé en C pour un exercice de programmation système.\n");
}

// ==================== COMPTEURS ====================

void compteur_caracteres(FILE *fichier)
{
    int c;
    long count = 0;
    rewind(fichier);

    while ((c = fgetc(fichier)) != EOF) {
        count++;
    }
    printf("Nombre de caractères : %ld\n", count);
}

void compteur_lignes(FILE *fichier)
{
    char buffer[TAILLE_BUFFER];
    long count = 0;
    rewind(fichier);

    while (fgets(buffer, sizeof(buffer), fichier) != NULL) {
        count++;
    }
    printf("Nombre de lignes : %ld\n", count);
}

void compteur_mots(FILE *fichier)
{
    char buffer[TAILLE_BUFFER];
    long count = 0;
    rewind(fichier);

    while (fscanf(fichier, "%s", buffer) == 1) {
        count++;
    }
    printf("Nombre de mots : %ld\n", count);
}

void longueur_max_ligne(FILE *fichier)
{
    char buffer[TAILLE_BUFFER];
    long max_len = 0;
    rewind(fichier);

    while (fgets(buffer, sizeof(buffer), fichier) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            len--;                    
        }
        if (len > max_len) {
            max_len = len;
        }
    }
    printf("Longueur maximale de ligne : %ld\n", max_len);
}

void afficher_fichier_format(FILE *fichier)
{
    int c;
    rewind(fichier);

    while ((c = fgetc(fichier)) != EOF) {
        if (c == '\n') {
            printf("$\\n");
        } else {
            putchar(c);
        }
    }
}

// ==================== OPTION & ARGUMENTS ====================

void option(FILE *fichier, int argc, char *argv[], const char *nom_fichier)
{
    printf("==> %s <==\n", nom_fichier);

    if (argc == 1 || (argv[1][0] != '-')) {
        compteur_lignes(fichier);
        compteur_mots(fichier);
        compteur_caracteres(fichier);
    } 
    else {
        for (int i = 1; argv[1][i] != '\0'; i++) {
            switch (argv[1][i]) {
                case 'l':
                    compteur_lignes(fichier);
                    break;
                case 'w':
                    compteur_mots(fichier);
                    break;
                case 'c':
                case 'm':
                    compteur_caracteres(fichier);
                    break;
                case 'L':
                    longueur_max_ligne(fichier);
                    break;
                default:
                    fprintf(stderr, "Option inconnue : -%c\n", argv[1][i]);
                    break;
            }
        }
    }
    printf("\n");
}

void traiter_arguments(int argc, char *argv[])
{
    FILE *fichier = NULL;

    if (argc > 1) {
        if (strcmp(argv[1], "--help") == 0) {
            afficher_help(argv[0]);
            return;
        }
        if (strcmp(argv[1], "--version") == 0) {
            afficher_version();
            return;
        }
    }

    if (argc == 2) {
        fichier = fopen(argv[1], "r");
        if (fichier == NULL) {
            perror("Erreur d'ouverture du fichier");
            exit(1);
        }
        option(fichier, argc, argv, argv[1]);
        fclose(fichier);
    }
    else if (argc > 2) {
        int debut = (argv[1][0] == '-') ? 2 : 1;

        for (int i = debut; i < argc; i++) {
            fichier = fopen(argv[i], "r");
            if (fichier == NULL) {
                perror("Erreur d'ouverture du fichier");
                continue;
            }

            if (argc > 1 && strcmp(argv[1], "--files-form") == 0) {
                afficher_fichier_format(fichier);
            } else {
                option(fichier, argc, argv, argv[i]);
            }

            fclose(fichier);
        }
    }
    else {
        fprintf(stderr, "Usage: %s [OPTION]... [FICHIER]...\n", argv[0]);
        fprintf(stderr, "Essayez '%s --help' pour plus d'informations.\n", argv[0]);
    }
}
