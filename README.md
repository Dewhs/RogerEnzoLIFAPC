# RogerEnzoLIFAPC

## Conception

Conception avec Figjam :
<https://www.figma.com/file/HxI14LNnPssUnBXXEPSnBu/diagrame_des_classes?type=whiteboard&node-id=0%3A1&t=zAzpCbIxr9VF0aRo-1>

- Exemple (avec des valeurs réels)
- Diagramme des classes
  
### Diagramme des classes
![Preview Diagramme des classes](https://i.imgur.com/F0myJYt.png)

## Compilation
 ### Étape 1 : Ouvrir un terminal et se rendre dans le dossier du projet

 ### Étape 2 : Vous devez être dans la racine du projet
 - Tester avec :
 ```bash
pwd
```
### Étape 3 : Entrez la commande make pour build le projet (Vous devez être dans la racine du projet important)
```bash
make clean && make
```
### Étape 4 : lancement du projet (éxecution)
```bash
./bin/MonProgramme
```
### Étape 5 : Voir le résultats 
- Ouvrir votre explorateur de fichier
- Rendez-vous dans le dossier du projet
- clique droit sur 'imagePgmInitial'
- l'ouvrir avec gimp ou autre lecteur d'image
- retourner dans votre explorateur de fichier
- clique droit sur 'imagePgmBin'
- l'ouvrir avec gimp ou autre lecteur d'image
- comparer les résultats

### Explication du makefile
- Création des dossiers bin et obj (si il n'existe pas)
- On construit le fichier obj de noeud stocker dans obj
- On construit le fichier obj de graphe stocker dans obj
- On construit le fichier obj de main stocker dans obj
- On construit l'éxecutable à partir des fichiers obj qui est stocker dans le dossier bin

Tips : la commande make clean supprime les fichiers obj et l'éxecutable
  
## Collaborator
Delgado Roger p2208393
Thiebaud Enzo p2207446
