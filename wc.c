#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wc.h"

void compteurcaractere(FILE *fichier) 
{

    int caractere = 0;
    int nbrcaractere = 0;
    rewind(fichier);
    while((caractere = fgetc(fichier)) != EOF)
    {
        nbrcaractere++;
    }
    printf("Nombre de caractere : %d\n", nbrcaractere);

}

void compteurligne(FILE *fichier) 
{

    char *chaine = NULL;
    chaine = malloc(300*sizeof(char));
    int nbrligne = 0;
    rewind(fichier);
    while((fgets(chaine, 300, fichier)) != NULL)
    {
        nbrligne++;
    }
    free(chaine);
    printf("Nombre de ligne : %d\n", nbrligne);

}

void compteurmot(FILE *fichier) 
{

    char *chaine = NULL;
    chaine = malloc(300*sizeof(char));
    int nbrmot = -1;
    rewind(fichier);
    while(!feof(fichier))
    {
        fscanf(fichier, "%s", chaine);
        nbrmot++;
    }
    free(chaine);
    printf("Nombre de mot : %d\n", nbrmot);

}

void longueurmax(FILE *fichier) 
{

    char *chaine = NULL;
    chaine = malloc(300*sizeof(char));
    int longueur = 0;
    rewind(fichier);
    fgets(chaine, 300, fichier);
    longueur = strlen(chaine);
    rewind(fichier);
    while((fgets(chaine, 300, fichier)) != NULL)
    {
        if(longueur < strlen(chaine))
        {
            longueur = strlen(chaine);
        }
    }
    longueur--;
    free(chaine);
    printf("Longueur maximal de ligne : %d\n", longueur);

}

void filesfrom(FILE *fichier) 
{

    int caractere = 0;
    rewind(fichier);
    while((caractere = fgetc(fichier)) != EOF)
    {
        if(caractere != '\n')
        {
            printf("%c", caractere);
        }
        else
        {
            printf("'$''\\n'");
        }    
    }

}

void option(FILE *fichier, int argc, char *argv[], char *chemin) 
{

    int i = 0;
    printf("==> %s <==\n", chemin);
    if(argc == 1)
    {
        printf("Manque d'argument\n");
    }
    if(argv[1][0] != '-')
    {
        compteurcaractere(fichier);
        compteurligne(fichier);
        compteurmot(fichier);
    }
    else
    {
        for(i = 1; i < strlen(argv[1]); i++)
        {
            switch(argv[1][i])
            {
                case 'L':
                    longueurmax(fichier); 
                    break;
                case 'c':
                    compteurcaractere(fichier);
                    break;
                case 'm':
                    compteurcaractere(fichier);
                    break;
                case 'w':
                    compteurmot(fichier);
                    break;
                case 'l':
                    compteurligne(fichier);
                    break;    
            }
        }
        
    }   
    printf("\n");
    
}

void argument(int argc, char *argv[])
{

    FILE* fichier = NULL;
    int i = 0;

    if(strcmp(argv[1], "--help") == 0)
    {
        exit(0);
    }
    else if(strcmp(argv[1], "--version") == 0)
    {
        exit(0);
    }
    if(argc == 2) 
    {
        fichier = fopen(argv[1], "r");
        if(fichier == NULL)
        {
            printf("Erreur d'ouverture du fichier");
            exit(1);
        }
        option(fichier, argc, argv, argv[1]);
        fclose(fichier);
    }
    else if(argc > 2)
    {
        for(i = (argv[1][0] == '-' ? 2 : 1); i < argc; i++) 
        {
            fichier = fopen(argv[i], "r");
            if(fichier == NULL)
            {
                printf("Erreur d'ouverture du fichier");
                exit(1);
            }
            if(strcmp(argv[1], "--files-form") == 0)
            {
                filesfrom(fichier);
                exit(0);
            }
            else {
                option(fichier, argc, argv, argv[i]);
            }
            fclose(fichier);
        }
    }

}