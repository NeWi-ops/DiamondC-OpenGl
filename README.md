Sur ce projet, on a commencé par dessiner une carte 50x50 en plaçant sur la carte un certain nombre de de pièges et d'ennemies. La position du joueur est trouver grace à un fonction qui trouve la position sur la carte oou la distance entre le joueur et le,plus proche ennemies et d'au moins 10.

Sur un second temps, on s'est lancé pour mettre en place les mouvements du joueur sur la carte. Il fallait prendre en compte les obstacles, la destruction des obstacles, les dégâts que subisse le joueur apres une attaque ou apres avoir touché un piège.

Les mouvement du joueur sont pour l'instant non fluide et demande à chaque fois d'appuyer sur entrée pour executer, mais le programme marche et le joueur est bloquer devant les obstacle. Le programme quitte lorsqu'on appuie sur 'a'

Avec les librairie <termios>,<unustd> et <stdio> on a reussi à avoir un mouvement du joueuer qui ne necessite pas d'appuyer à chaque fois sur entrer. Le seul soucis, c'est que ces bibliotheque ne marche que pour mac/linux. Pour le windows, il faut:
il faut utiliser _getch() de <conio.h>.

On a mis en place les fins de jeu en fonction de l'etat du jeu:
Victoire :  si le nombre de gemme total est collecter
Defete : si le niveau de vie est nulle


GROSSS probleme avec FORK, les git et tt sont emmeler, un grand bug 

Puis on mettra en place l'algorithme de "Dijkstra"  pour l'attaque des ennemis.
----> Amelioration à mettre en place: les ennemis bougent aléatoirement, il utilise l'algorithme pour attaquer que quand la distance qui leur sépare du joueur est < à 15.




IDEE THEME:
theme: sous la mer
obstacle: dune, ile... fausses, bateaux...
ennemis: requins
gemmes: piece d'or / trésor...
joueur: plongeur (+: niveau d'O2 qui baisse)

Pour l'instant ce que le code en C++ fait:

Génération de la carte
Placement des ennemis, pièges, gemmes
Déplacement du joueur
Déplacement automatique des ennemis vers le joueur (avec flow field)
Détection et gestion de l’attaque des ennemis (la vie du joueur baisse bien si un ennemi arrive sur sa case)

