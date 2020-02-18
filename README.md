# TechTheTide OpenCV

Le dépôt du code OpenCV de l'équipe TechTheTide

## OpenCV qu'est ce c'est ?

> (Du caca dans les raviolis)

OpenCV est une bibliothèque graphique libre implémentée pour faire du traitement d'images. Nous l'utilisons aussi bien pour faire du vrai traitement d'images que pour faire de la détection de tags arucos (ils aiment bien ça à la coupe ne les jugeons pas).
Bref, OpenCV c'est très complet, assez simple à manipuler, pas besoin d'être un dieu en C++ pour y arriver. Donc vous l'aurez compris c'est génial on aime bien ça mais il y a  disons un tout petit défaut.
Et oui après tout rien est totalement blanc ou noir, chaque chose a ses nuances de gris et OpenCV a, dirons nous, des ÉNORMES tâches grises au milieu de son petit minois tout blanc (oups je m'égare pardon...) : 
Opencv C'EST PUTAIN DE CANCER DU CUL À INSTALLER ET LA DOC EST BORDELIQUE AS FUCK comme dirais un certains personnage Intechien "juif" dont je ne citerais pas le nom ici, il risquerait d'être l'énorme tâche grise de ce magnifique README.
Et de la vient l'idée d'écrire ce Readme : faire en sorte que les 1A que vous êtes ne passent pas 3 mois a essayé d'intaller OpenCv sans succès pour terminer l'année en boule devant un psy...

Sur ceux je vous souhaite de réussir sans trop de dommages cérébraux :)

## Dépendances

> Tout est lié  
>
-- Une 1A fatiguée

Pour pouvoir compiler le projet, il est nécessaire d'avoir les bibliothèques suivantes d'installées:
 - OpenCV
 - Openexr
 - Dc1394
 - VTK
 
Sur les systèmes Ubuntu ou assimilés, ce sont donc les paquets `libopencv-core-dev`, `libopenexr-dev`, `libdc1394-dev` (potentiellement `libdc1394-22-dev`) qui doivent être installés.

### /!\
GCC doit être mis à jour *au moins* à la version 9.

###/!\
Sur les distribs Ubuntu il est possible qu'OpenCv ne trouve pas certains packages comme Aruco ou autres. Dans ce cas (et si toutes les méthodes décrites précedemments n'ont pas résolue le problème) il reste une méthode secrète (très shlag au passage) qui permet de régler le problème:
 - Dans usr/include COPIER (et pas couper) les fichiers OpenCV et OpenCV2
 - Les COLLER dans `usr/local/include`
 
Pour l'installation d'aruco/charuco, si OpenCv ne trouve pas et est (encore) perdu, il faut réutiliser une méthode de shlag pour arriver à ses fins:
 - Rechercher les fichiers `aruco.hpp`/`charuco.hpp`
 - Les COPIER et les COLLER dans `usr/include/opencv2`, `usr/include/opencv2/aruco`, `usr/local/include/opencv2`, `usr/local/include/opencv2/aruco`
 
 OU:
 
 - Prendre tous les fichiers libopenv (`libopencv_aruco.a`, `libopencv_aruco.so`, `libopencv_aruco.so.3.2`, `libopencv_aruco.so.3.2.0`)
 - Les mettre dans `usr/lib`, `usr/local/include`, `usr/local/lib`
 
 Ensuite, inchallah tout devrait fonctionner normalement.
 
 Vous êtes maintenant prêt à utiliser OpenCV et Aruco afin de faire du traitement d'image et de la détection de tag Aruco (voir même plus).
 
 ## Traitement d'Image
 
### Quand tout devient Matrice

Faire du traitement d'images concrètement qu'est ce que c'est ? Outre un truc qui sonne plutôt bien et qui fait styloche, faire du traitement d'images c'est travailler avec des matrices. Que ce soit une image static ou un flux vidéo, une image C'EST une matrice.
En travaillant avec OpenCV, vous allez travailler et trifouiller des matrices sans arrêts. Mais il faut savoir que toutes les matrices ne se valent pas ! Allez, c'est partit pour un petit aperçu de tous les types de matrices/vectors que vous rencontrerez sûrement !!

> Mat

Il s'agit du type Matrice par défaut pouvant contenir aussi bien des réels que des complexes, des coordonnées... Une image est représentée par une matrice, quelle soit en RVB, HSV ou en nuances de gris.
Pour construire une matrice quelconque sans taille imposée et sans type prédéfinis, on peut utiliser le constructeur `Mat maMatrice` pour initialiser la matrice maMatrice et ensuite travailler avec. Sinon c'est Matx.. qui nous intéresse.

> Matx...

Lorsque l'on veut créer une matrice d'une certaine taille ne contenant qu'un ceratain types d'éléments, on utilise Matx... . Avec Matx... on spécifie le nombre de lignes, le nombres de colonnes et le type d'éléments à l'intérieur (f pour float, d pour double, i pour int ...).Par exemple, quand on veut initier une matrice à 3 lignes 3 colonnes contenant que des doubles on initie la matrice maMatrice comme suit : `Matx33d maMatrice`. 
Le truc en plus par rapport à `Mat` ? Le type ne change à l'intérieur des éléments ne changes pas et est fixe alors qu'avec Mat, certains calculs vont de base convertir les float ou double contenue dans une matrice Mat en int... ce qui est pas cool quand on a absolument besoin de bosser avec autre chose que des entiers.


CE QUI FAUT RETENIR DE MAT ET MATX :

Mat c'est pour stocker des images : on ne sait pas forcément la taille c'est assez souple et c'est surtout fait pour ça.
Matx... c'est pour travailler sur des images avec des matrices spécifiques : des matrices exprimant la distorsion de la caméra par exemple.
Travailler avec une image c'est travailler avec une matrice et lui faire subir un bon nombre de transformations à coup de multiplications, transposition set inversions. Et pour ce faire, on a besoin de connaître exactement la gueule des matrices utilisées pour transformer notre image. On le précise donc en utilisant Matx... .

> Vector

Un vector est en fait un tableau dynamique i.e des tableaux dont la taille n'est pas fixe. Pas de panique, l'allocation en mémoire et autres histoires de pointeur sont gérées par le C++.
Les éléments d'un vector peuvent avoir plein de types bizzares et sogrenus : des int, des vector, des coordonnées d'un point en float (`Point2f`) , des matrices colonnes (`Vec4i` pour un matrice colonne avec 4 int) ...

> Moments

Pour trouver le centroide d'une figure on utilise la notion de moments d'une image. Un moment dans une image est une moyenne pondérée particulière des intensités des pixels d'une image. Un moment est un type à part (comme les float, int, double...). Il existe plusieurs moyens de calculer un moment dans une image :

 - le moment spatial `m` 
 - le moment centré `mu` qui fait intervenir le centre de masse d'une figure
 - le moment centré normmalisé `nu`

Le moment d'un contour est calculé en utilisant la formule de Green (https://en.wikipedia.org/wiki/Green%27s_theorem).
C'est en calculant tous les moments d'une figure délimitée par un contour que l'on peut ensuite trouver les coordonnées du centroïde de cette figure.
Mais qu'est ce qu'un centroïde ? C'est un peu comme un centre de masse mais version pixels. En fait, on regarde notre matrice (aka notre image) et on regarde par exemple tous les objets verts dans cette matrice. De ce fait, tous les objets verts prennent la valeur 1 et tout le reste prend la valeur 0. On travail alors avec une image bicolore et on calcul la moyenne des 1 dans notre matrice pour trouver là où il y a la plus forte concentration de 1 dans l'image. Ce point précis dans notre matrice c'est le centroïde.
Le centroïde d'une image est une notion assez interessante : on remplace un objet par un point. En terme de calcul, tout devient plus simple, si on connaît les dimensions de l'objet que l'on observe bien sûr !!
 
 Maintenant que les types spécifiques à OpenCV ont été présentés, interessons nous au différents header et aux différents constructeurs que l'on va être amenés à affronter
 
### Core

Cette bibliothèque permet de manipuler les structures de base, réaliser des opérations sur des matrices, dessiner sur des images, sauvegarder et charger des données dans des fichiers XML…
 
### Highgui

Highgui contient un certains nombres de fonctions permettant de réaliser des interfaces graphiques très simples, mais largement suffisantes pour tester nos programmes.

### Calib3d
 
Cette bibliothèque contient plein d'outils pour calibrer la caméra, estimer la distance caméra / objet filmé ..

### Videoio ou la gestion de la caméra

Videoio est une bibliothèque appartenant à OpenCV. En son sein (inside the titiz) on retrouve toutes les fonctions capables de gérer la caméra et le flux de données reçues. Parmis toutes les fonctionnalités proposées, certaines sont à connaître (car sans images il n'y a pas de traitement d'images)

> VideoCapture

Videocpature cap (int index) : ouvre une caméra pour capter ses frames. Index est le numéro de la caméra à ouvrir (par défaut, 0 est l'entrée vidéo du PC et 1 celle de la webcam branchée sur votre port USB). Cap est le fichier vidéo, on l'utilise et on travail avec ça (cap pour capture, c'est ce qui est capté par la caméra, les frames étant gérer par VideoCapture on ne s'intéressera pas ici à la gestion des frames par OpenCv)
### /!\
Sur le nuc, étant donné qu'il n'y a pas de caméra par défaut, 0 correspond à la caméra branchée.
### /!\
La méthode appelle `VideoCapture::release` avant d'ouvrir de nouveau la caméra : facilite la gestion des frames vidéo

> isOpen

Verifie deux fontions : 
- `open` : renvoie un bool si la caméra est ouverte ou non
- `destructor` : renvoie un bool si la caméra est fermée ou non

> release

Ferme toutes les caméras, nettoie la mémoire (les histoires de pointeurs en C tu connais...)

> Autres fonctions de videoio très cools à connaître

- `grab (int ou autre flag)` : permet de saisir les frames vidéo d'une caméra appélée via le paramètre d'entrée. La différence avec VideoCapture ? `grab` est très utile lorsque l'on travail avec plusieurs caméra qui n'on pas de hardware gérant la synchronisation.
- `retrieve(int ou autre flag)` : à utiliser après `grab` . Permet de décoder les frames envoyés par `grab`. Si rien est envoyé, la fonction retourne false.

Ces deux fonctions marchent de paires. On saisie un flux que l'on traite ensuite pour éviter la collision de frames dans le cas où plusieurs caméras marchent en même temps.
Étant donné que nous on utilise une seule caméra par programme, `VideoCapture` nous va très bien car il ne cherche pas plusieurs sources d'images et va beaucoup plus vite en temps de calcul que `grab ` et `retrieve` ensemble (et ça reste un outil très puissant ne le sous estimons pas non plus).
 
### Imgproc ou le traitement d'images en soi

Comme dit plus haut, lorsque l'on fait du traitement d'images, que ce soit une image fixe type jpeg ou un frame video, l'image que l'on traite à un instant t est une matrice (de type Mat). Ainsi faire du traitement d'images concrètement c'est jouer avec des matrices (vive l'algèbre et l'algérie française !!)
Et pour s'amuser avec des matrices, rien de mieux qu' imgproc, cette bibliothèque contient pas mal de fonctions pour bidouiller les images que l'on a en face.

> cvtColor

Permet de convertir une image d'un espace colorimétrique à un autre (de RVB à HSV par exemple)

>erode/dilate

Permet d'éroder/de dilater une image.

>Canny

Permet de détecter les bords des objets dans une image en utilisant un filtre de Canny (https://fr.wikipedia.org/wiki/Filtre_de_Canny) `Canny(InputArray, OutputArray, double, double, int, bool`

>findContours

Permet de trouvers les contours des objets dans une image bicolore. 
Concernant les arguments de la fonction :
- InputArray CannyImage : il s'agit d'une image codé sur 8 bit bicolore. Le mieux est de récupérer l'image obtenue avec Canny où toutes les bordures ont été détecté.
- vector<vector<Point>> contours : On stocke tous les contours trouvés dans ce vecteur. Un contour est un vecteur regroupant les points concernés par le contour
- vector<Vec4i> hierarchy : à chaque contour crée, on stocke dans `hierarchy` l'historique de ce contour (optionnel)
- RETR_TREE : mode d'implémentation du contour qui marche bien (tested and approved !!)
- CHAIN_APPROX_SIMPLE : mode d'approximation du contour
- Point(0, 0) : Point de départ pour tracer le contour, zéro de l'image

`findContours(InputArray CannyImage, vector<vector<Point>> contours, vector<Vec4i> hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0)))`

>moments

Permet de trouver les moments d'une figure délimité par un contour. Cette fonction renvoie... un Moment !!
`moments (vector<Point> contour[i], bool isImageBinary)`

Maintenant toutes les fonctions utilisées dans le projet TechTheTide sont présentée !! Vous êtes prêts pour faire la partire tag Aruco maintenant !!! (Vous inquiétez pas c'est plus simple)

 ## Aruco
 
 ### Et encore des bibliothèques....
 
 En plus de certaines des bibliothèques présentées précédemment, la détection de tag aruco requière l'utilisation de deux autres bibliothèques : 
 > aruco

Cette bibliothèque regroupe toutes les fonctions utiles pour travailler avec des tags aruco : détection du tag, orientation du tag dans l'espace...

> dictionnary

C'est la bibliothèque regroupant tous les dictionnaires aruco. Un dictionnaire aruco regroupe soit 50, 100 ou 250 tags aruco. Les tags sont différenciés par leur taille (4X4 ou 8X8 ou que sait-je...) et donc une bibliothèque regroupe un ensemble de tags ayant la même taille.
Dans un dictionnaire précis, chaque tag à un identifiant précis. Il est donc important de préciser dans quel dictionnaire l'on travail afin d'avoir l'id d'un tag et pouvoir l'appeler dans un programme.
 ## Envoie des données : petit point rapide
