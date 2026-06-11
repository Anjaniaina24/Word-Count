# wc - Compteur de lignes, mots et caractères

Une implémentation simplifiée et éducative de la commande `wc` (word count) en langage C.

---

## 📋 Description

Ce projet est une version maison de l'utilitaire `wc` sous Unix/Linux. Il permet de compter les lignes, les mots, les caractères et la longueur maximale des lignes dans un ou plusieurs fichiers.

Développé dans le cadre d'un exercice de programmation système en C (gestion de fichiers, arguments en ligne de commande, etc.).

## ✨ Fonctionnalités

- Comptage du nombre de **lignes** (`-l`)
- Comptage du nombre de **mots** (`-w`)
- Comptage du nombre de **caractères** (`-c` ou `-m`)
- Affichage de la **longueur de la ligne la plus longue** (`-L`)
- Mode `--files-form` pour afficher le contenu avec les fins de ligne visibles
- Support de plusieurs fichiers
- Options `--help` et `--version`
- Comportement par défaut (lignes + mots + caractères) quand aucune option n’est spécifiée

---

## 🛠️ Compilation

```bash
gcc main.c wc.c -o wc
