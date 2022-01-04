# 📖 - Mode d’emploi

## Prérequis

Vous devez posséder les outils suivants sur la machine qui compile :

- Compilateur C++ (gcc, g++)
- CMake

## Compilation

Pour compiler le projet, commencez par cloner le projet sur Github à l’adresse suivante : 

[https://github.com/leodlplq/IMACraft](https://github.com/leodlplq/IMACraft)

Une fois téléchargé rendez-vous à la racine de ce projet et créez un fichier build et entrez à l’intérieur.

```bash
mkdir build
cd build
```

Une fois à l’intérieur de ce fichier, vous allez pouvoir compiler le projet avec les commandes suivantes : 

```bash
cmake ..
make
```

Ces deux commandes doivent ainsi vous créer de nouveaux dossiers / fichiers.

## Lancement du jeu

Vous pouvez maintenant lancer le jeu avec cette commande, toujours depuis le dossier build.

```bash
../bin/IMACraft
```

<aside>
🔴 Si vous avez des problèmes pour compiler, vous pouvez également utiliser un IDE qui compilera le projet à votre place.

</aside>

# 🎯 But du jeu et déroulement d’une partie:

**IMACraft** est un Temple Run Like dans l’univers de Minecraft. Le joueur incarne Steve, un villageois poursuivit par ses pires ennemis. Pour leur échapper, le joueur va devoir parcourir un chemin semé d’obstacles. 

### 🔰Début de partie:

Pour lancer une partie après le lancement du jeu, il suffit d’appuyer sur le bouton “Lauch game”.

Le but du jeu est d’arriver jusqu’à la fin du niveau sans mourir tout en essayant d’obtenir le meilleur score. Pour se faire, le joueur peut ramasser différents collectables le long du parcours: 

- Le diamant bleu : +10 points de score
- Le diamant rouge: +50 points de score
- La pomme: +1 point de vie si le joueur n’a pas sa vie au maximum

### 🏁 Fin de partie

Si le joueur ne parvient pas à éviter un obstacle ou à tourner à temps, il perd un point de vie.

A chaque point de vie perdu, les ennemis se rapprochent un peu plus de Steve. Quand il n’a plus aucun point de vie, les ennemis sautent sur Steve et tuent ce dernier. Le joueur perd ainsi la partie.

De même si le joueur saute en dehors du parcours, Steve meurt instantanément .

Si le joueur perd la partie en cours, il a la possibilité de relancer une nouvelle partie ou de quitter le jeu.

Si le joueur parvient à atteindre l’arrivée sain et sauf, son score ainsi que le tableau des meilleurs scores s’affichent au milieu de l’écran. De plus, si son score est supérieur à un des scores du top 3, il peut l’enregistrer définitivement en entrant son pseudo. Il peut ensuite choisir de relancer une partie ou de quitter le jeu en cliquant sur les boutons correspondants.

### 🔃 En cours de partie:

Durant la partie le joueur peut mettre le jeu en pause. A partir du menu Pause, il peut choisir d’afficher les meilleurs score, de relancer une nouvelle partie ou bien évidement, reprendre la partie en cours.

Le joueur a la possibilité de changer de point de vu tout le long de la partie. Il peut soit choisir une vue FPS, plus immersive, soit une vue TPS, plus globale (vue par défaut). 

Il a aussi la possibilité de débloquer l’angle de la caméra pour observer le monde autour de lui (restreint dans la vue FPS pour plus d’immersion).

# 🎮 - Commandes du jeu

- Z - Sauter
- Q - Se déplacer à gauche | Dans un virage permet de tourner à gauche
- S - Glisser
- D - Se déplacer à droite | Dans un virage permet de tourner à droite
- C - Change la vue du joueur entre vue FPS et vue TPS
- L - Bloque/Débloque la caméra
- Echap - Met le jeu en pause

*En fin de partie, si le joueur gagne et obtient un des meilleurs scores : Utilisation du clavier pour entrer son pseudo.*

Navigation entre les différents menus (Principal / Pause / Score / Game Over) via des boutons cliquables.

# Remerciements
Nous remercions les personnes qui nous ont aidés lors de la réalisation : 
- Jules (merci merci)
- Théo
<3
