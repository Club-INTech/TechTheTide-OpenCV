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
 
 ## Aruco