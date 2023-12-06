# RogerEnzoLIFAPC

## Conception

Conception avec FigJam : [Lien FigmJam](https://www.figma.com/file/HxI14LNnPssUnBXXEPSnBu/diagrame_des_classes?type=whiteboard&node-id=0%3A1&t=zAzpCbIxr9VF0aRo-1)

![Exemple d'un graphe qui représente une image pgm](https://i.imgur.com/Qc11KIv.png)

### Diagramme des classes

![Aperçu du Diagramme des classes](https://i.imgur.com/F0myJYt.png)

## Compilation

### Étape 1 : Ouvrir un terminal et se rendre dans le dossier du projet

### Étape 2 : Vous devez être dans la racine du projet

- Tester avec :
  
```bash
pwd
```

### Étape 3 : Entrez la commande make pour build le projet (Vous devez être dans la racine du projet, c'est important)

```bash
make clean && make
```

### Étape 4 : Lancement du projet (exécution)

```bash
./bin/MonProgramme
```

### Étape 5 : Voir le résultats

- Ouvrez votre explorateur de fichiers
- Rendez-vous dans le dossier du projet
- Cliquez-droit sur 'imagePgmInitial'
- Ouvrez-le avec GIMP ou un autre lecteur d'images
- Retournez dans votre explorateur de fichiers
- Cliquez-droit sur 'imagePgmBin'
- Ouvrez-le avec GIMP ou un autre lecteur d'images
- Comparez les résultats

### Explication du makefile

- Création des dossiers 'bin' et 'obj' (s'ils n'existent pas)
- Construction du fichier objet 'noeud' stocké dans 'obj'
- Construction du fichier objet 'graphe' stocké dans 'obj'
- Construction du fichier objet 'main' stocké dans 'obj'
- Construction de l'exécutable à partir des fichiers objet, qui est stocké dans le dossier 'bin'

Tips : la commande make clean supprime les fichiers obj et l'éxecutable
  
## Collaborator

Delgado Roger p2208393
Thiebaud Enzo p2207446
