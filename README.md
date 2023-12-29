
# SAISIE INTUITIVE 2.0
## Table of contents
- [Prérequis](#Prérequis)
- [Exécution](#Exécution)
- [Description](#description)
- [Fpnctionnalités](#fonctionnalités)
- [License](#license)


## Prérequis
C compiler :
- **gcc**
  
Bibliothèques nécessaires :
- **gtk3**
- **pkg-config**
- **make**

Pour installer les paquets sur linux :
```bash
sudo apt install libgtk-3-dev pkg-config make gcc
```

## Prérequis
Pour compiler et run le programme se placer dans le dossier :
```bash
make main
./main
```

## Description
Ce programme permet d'avoir une saisie intuitile intelligente qui propose une autocomplétion des 
mots lorsqu'on est en train d'écrire sur un clavier.
Les mots utiliséd viennent d'un dictionnaire intrne mais l'utilisateur a le droit d'en ajouter.
Le programme presente une interface graphique compatible **GTK3**.

## Fonctionnnalités
### PARAMÈTRES
   On peut choisir le mode de prédiction qu'on préfère : fréquentiel qui sélectionne les mots les plus utilisés ou temporel qui choisit les derniers mots utilisés.

### INTERAGIR AVEC LES DICTIONNAIRES
  - L'utilisateur peut ajouter un dictionnaire personnel à celui déjà présent dans le programme. Pour 
  cela il suffit d'entrer le nom du fichier et d'appuyer sur le buton 'importer'. Le process se fait de manière
  automatique et une foi fini l'entrée texte s'effacera
   - Affciher dictionnaires personnel ou français : il faut appuyer sur exécuter et une fenêtre dialogue
  s'ouvrira.

<p style="color:red;">Attention :</p>
L'affichage du dictionnaire français met du temps à charger car très volumineux,
appuyer sur attendre à chque fois que l'application le demande 


### CHANGER LES DONNÉES
   - Ajouter un mot : en écrivant le mots dans la zone de texte et en appuyant sur ajouter ce mot sera 
   ajouté au dictionnaire personnel indépendamment de sa présence ou non dans le dictionnaire français
   - Supprimer un mot : le mot entré dans la zone de texte sera supprimé du dictionnaire personnel sous 
   résèrve d'existence
   - Modifier un mot : le entré dans la zone de texte du haut sera remplacé par le mot entré en deuxième

### ECRITURE INTUITIVE
   - Dans cette partie l'utilisateur peut écrire le message qu'il veut et automatiquement le programme 
   recupère le contenu et génère trois prédictions possibles.Ces prédictions se trouvent à l'intérieur de butons. 
   Si on appuie sur un buton le contenu du message sera automatiquement complété par la prédiction.
   - Une fois fini d'écrire en appuyant sur le buton "valider" chaque mot du message écris est extrait et soit il est 
   déjà présent dans le dictionnaire personnel et donc ses statistiques sont mises à jour soit il existe que dans le 
   dictionnaire français et est par conséquent ajouté au dictionnaire personnel.
  
  <p style="color:red;">Attention :</p>
  - si on écris entre un espace en premier caractère le programme crash
  - l'utilisation de caractères spéciaux peut mener au crash du programme
  - il se peut que certains mots atypiques fassent buguer le programme
 	 








































































 



