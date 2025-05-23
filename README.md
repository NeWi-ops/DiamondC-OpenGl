Sur ce projet, on a commencé par dessiner une carte 50x50 en plaçant sur la carte un certain nombre de de pièges et d'ennemies. La position du joueur est trouver grace à un fonction qui trouve la position sur la carte oou la distance entre le joueur et le,plus proche ennemies et d'au moins 10.

Sur un second temps, on s'est lancé pour mettre en place les mouvements du joueur sur la carte. Il fallait prendre en compte les obstacles, la destruction des obstacles, les dégâts que subisse le joueur apres une attaque ou apres avoir touché un piège.

Les mouvement du joueur sont pour l'instant non fluide et demande à chaque fois d'appuyer sur entrée pour executer, mais le programme marche et le joueur est bloquer devant les obstacle. Le programme quitte lorsqu'on appuie sur 'a'

Avec les librairie <termios>,<unustd> et <stdio> on a reussi à avoir un mouvement du joueuer qui ne necessite pas d'appuyer à chaque fois sur entrer. Le seul soucis, c'est que ces bibliotheque ne marche que pour mac/linux. Pour le windows, il faut:
il faut utiliser _getch() de <conio.h>.


GROSSS probleme avec FORK, les git et tt sont emmeler, un grand bug 

Puis on mettra en place l'algorithme de "Dijkstra"  pour l'attaque des ennemis.
----> Amelioration à mettre en place: les ennemis bougent aléatoirement, il utilise l'algorithme pour attaquer que quand la distance qui leur sépare du joueur est < à 15.

