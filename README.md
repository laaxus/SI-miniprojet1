# Projet 1 LINFO1252 - Antoine Demblon & Xavier de Liedekerke
![UCLouvain](https://upload.wikimedia.org/wikipedia/commons/thumb/2/21/UCLouvain_%C3%89cole_polytechnique_de_Louvain.svg/568px-UCLouvain_%C3%89cole_polytechnique_de_Louvain.svg.png)


Le code source est disponible sur [Github](https://github.com/laaxus/SI-miniprojet1).
La documentation est uploadée sur [Github Pages](https://laaxus.github.io/SI-miniprojet1/html/index.html).

Voici l'implémentation de notre solution pour le projet 1 de l'année 2020. Ce projet est constitué de 5 sous projet indépendant :
* Une implémentation du problème des philosophes,
* Une implémentation du problème des producers - consumers,
* Une implémentation du problème des readers - writers.
* Une implémentation du test and set,
* Une implémentation du test and test and set.

## Structure du projet
Le projet contient plusieurs dossier. Chaque implémentation d'un problème a son dossier et donc tous les dossier sont indépendant les uns des autres.
Voici les différent dossiers:
* philosophe, contenant l'implémentation du problème des philosophes,
* producer_consumer, contenant l'implémentation du problème des producers - consumers,
* reader_writer, contenant l'implémentation du problème des readers - writers.
* test_and_set, contenant l'implémentation du test and set,
* test_and_test_and_set, contenant l'implémentation du test and test and set.

mais aussi,

* Measures, 
* doc, contenant la documentation après l'avoir généré.

## Options en ligne de commande
Chaque implémentation affiche son usage si vous deviez utiliser une option incorrecte.
Par défault, ils utiliseront autant de threads que la machine a de coeurs.

## Compilation
Nous proposons les règles suivantes pour les sous projets :
* `rw`, pour le reader-writer avec version posix; 
* `ph`, pour les philosophes avec version posix;
* `pc`, pour le producer_consumer avec version posix;
* `ts`, pour le test and set;
* `tts`, pour le test and test and set.
* `rw2`, pour le reader-writer avec version test and test and set; 
* `ph2`, pour les philosophes avec version test and test and set; 
* `pc2`, pour le producer_consumer avec version test and test and set; 
* `rw3`, pour le reader-writer avec version test and set; 
* `ph3`, pour les philosophes avec version test and set; 
* `pc3`, pour le producer_consumer avec version test and set; 
 
`clean` nettoye les artéfacts de compilation. 

`test` lance le script bash pour créer les mesures et leur graphe correspondant.

Nous proposons aussi la règle `debug_("Une des règles de sous_projet")` permettant de créer un build sans optimisations et avec l'option `-g`.
Afin de pouvoir compiler, il est nécessaire d'avoir le compilateur GCC ainsi que les libraires pthread.
Il est aussi nécessaire que le système supporte l'interface POSIX `getopt`.

La documentation peut être générée à l'aide de `make doc` pour peu que Doxygen soit installé. Il faut ensuite ouvrir le fichier `index.html` dans le dossier docs. 
Si Doxygen n'est pas installé, vous pouvez quoi qu'il arrive trouver la doc sur [Github Pages](https://laaxus.github.io/SI-miniprojet1/html/index.html).


