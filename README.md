# Projet 3 EPL 2020 - Groupe E5
![UCLouvain](https://upload.wikimedia.org/wikipedia/commons/thumb/2/21/UCLouvain_%C3%89cole_polytechnique_de_Louvain.svg/568px-UCLouvain_%C3%89cole_polytechnique_de_Louvain.svg.png)

Voici l'implémentation de la solution du groupe E5 pour le projet 3 de l'année 2020: un programme pour factoriser rapidement des nombres en facteurs premiers.
Le code source est disponible sur [Gitlab](https://forge.uclouvain.be/bploumhans/lepl1503-2020-groupe-E5).
La documentation est régulièrement uploadée sur [Github Pages](https://technici4n.github.io/lepl1503/index.html).

## Structure du programme
Le programme est réparti en plusieurs threads:
* Un thread de lecture du fichier d'entrée,
* N threads de factorisation des nombres,
* Un thread d'écriture du fichier de sortie.

Ces threads communiquent entre eux à l'aide d'une queue multithreadée bornée, c'est-à-dire que si un producteur essaye d'insérer dans une queue pleine, il va bloquer jusqu'à ce qu'une place se libère dans la queue. Plus précisément, le thread de lecture communique avec les threads de factorisation, qui eux-mêmes communiquent avec le thread d'écriture.

Nous proposons deux algorithmes de factorisation, le choix de l'algorithme se faisant via les options en ligne de commande:
* Un rapide basé sur la recherche de facteur rho de Pollard ainsi que le test de primalité de Rabin-Miller,
* Un lent basé sur la méthode des divisions successives.

## Options en ligne de commande
```
Usage: fact [-N NUMBER_OF_THREADS] [other options] INPUT_FILE OUTPUT_FILE

 -N NUMBER_OF_THREADS  Specify how many threads the program should use.
                       The argument should be a positive integer.
                       By default, the program will use all available
                       cores on the machine.
 -f  Use the fast algorithm.
 -s  Use the slow algorithm. This is enabled by default.
 INPUT_FILE  A file containing arbitrarily-long positive integers to
             be processed by the program.
 OUTPUT_FILE  The output file. For every integer in INPUT_FILE, a line
              will be written in OUTPUT_FILE. This line will contain,
              space-separated:
              - the integer that was factored,
              - its prime factors, in increasing order, excluding
                the number itself.
              The ordering of the lines in the output may not match
              the ordering of the numbers in the input.
```

## Compilation
Nous proposons les règles `fact`, `test` ainsi que `clean` afin de compiler, tester et nettoyer les artéfacts de compilation respectivement. Nous proposons aussi la règle `debug` permettant de créer un build sans optimisations et avec l'option `-g`. Afin de pouvoir compiler, il est nécessaire d'avoir le compilateur GCC ainsi que les libraires pthread, CUnit et GMP. Il est aussi nécessaire que le système supporte l'interface POSIX `getopt`.

La documentation peut être générée à l'aide de `make doc` pour peu que Doxygen soit installé.

## Structure du code
Les fichiers source suivants se trouvent dans le dossier `c`:
* `alloc.c` et `alloc.h` contiennent une fonction d'allocation qui arrête le programme si l'allocation échoue.
* `factorize.c` et `factorize.h` contiennent les deux algorithmes de factorisation implémentés.
* `main.c` contient la fonction principale responsable de la lecture des arguments ainsi que de l'exécution des différents threads.
* `queue.c` et `queue.h` contiennent l'implémentation de notre queue bornée.
* `threads.c` et `threads.h` contiennent les différents threads de notre programme ainsi que l'infrastructure nécessaire à leur communication.
Dans le dossier `input`, nous retrouvons les divers fichiers d'entrée que nous avons utilisés pour nos tests de performances.

Nous disposons en plus d'une infrastructure de tests:
* `c/test.c` contient des tests unitaires implémentés à l'aide de CUnit.
* `tests/test.sh` est un script bash permettant de tester notre programme sur des fichiers entiers.

Un exemple d'entrée et de sortie est donné dans les fichiers `exemple.in` et `exemple.out`.
