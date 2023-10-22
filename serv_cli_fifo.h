#ifndef SERV_CLI_FIFO_H
#define SERV_CLI_FIFO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define NMAX 100 // Valeur maximale pour le nombre aléatoire
#define FIFO1 "tmp/fifo1" // Nom du tube nommé pour la communication du serveur
#define FIFO2 "tmp/fifo2" // Nom du tube nommé pour la communication du client

// Structure pour représenter une question du client
typedef struct {
    int nombreAleatoire; // Nombre aléatoire à générer par le serveur
    pid_t numeroClient; // Numéro du client
} QuestionClient;

// Structure pour représenter une réponse du serveur
typedef struct {
    pid_t numeroClient; // Numéro du client
    int* nombresTires; // Tableau des nombres tirés au sort par le serveur
    int nombreTiresLen; // Nombre d'entiers tirés au sort
} ReponseServeur;

#endif
