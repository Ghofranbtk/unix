#ifndef HANDLERS_SERV_H
#define HANDLERS_SERV_H

#include "serv_cli_fifo.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Handler pour le réveil du serveur suite à la réception du signal SIGUSR1
void hand_reveil(int sig) {
    printf("Le serveur a reçu le signal SIGUSR1.\n");
    
}

// Handler pour la fin du serveur suite à la réception d'un signal quelconque
void fin_serveur(int sig) {
    printf("Le serveur a reçu un signal de terminaison.\n");
    // Mettez ici le code à exécuter pour la fin du serveur
    // Ceci pourrait inclure la fermeture des tubes nommés, la libération de la mémoire allouée, etc.
    // Assurez-vous de nettoyer et de libérer les ressources correctement.
    exit(EXIT_SUCCESS);
}

#endif

