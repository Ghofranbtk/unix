#include "serv_cli_fifo.h"
#include "Handlers_Serv.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    /* Déclarations */
    int fifo1_fd, fifo2_fd;
    QuestionClient question;
    ReponseServeur reponse;
  

    /* Création des tubes nommés */
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    /* Initialisation du générateur de nombres aléatoires */
    srand(getpid());

    /* Ouverture du tube nommé fifo1 pour la lecture des questions */
    fifo1_fd = open(FIFO1, O_RDONLY);
    if (fifo1_fd == -1) {
        perror("Erreur lors de l'ouverture du tube nommé fifo1");
        exit(EXIT_FAILURE);
    }

    /* Installation des Handlers */
    signal(SIGUSR1, hand_reveil);
    signal(SIGINT, fin_serveur);

    while (1) {
  
        /* Lecture d'une question */
        if (read(fifo1_fd, &question, sizeof(QuestionClient)) > 0) {
            /* Construction de la réponse */
            int n = question.nombreAleatoire;
            int *nombresTires = (int *)malloc(n * sizeof(int));
            for (int i = 0; i < n; i++) {
                nombresTires[i] = rand() % NMAX + 1;
               
            }

            /* Préparation de la réponse du serveur */
            reponse.numeroClient = question.numeroClient;
            reponse.nombresTires = nombresTires;
            reponse.nombreTiresLen = n;
           
           
 printf("test de reponse %p ", (void *) &reponse.nombresTires[n]);
            /* Envoi de la réponse */
            fifo2_fd = open(FIFO2, O_WRONLY);
            if (fifo2_fd == -1) {
                perror("Erreur lors de l'ouverture du tube nommé fifo2");
                exit(EXIT_FAILURE);
            }
            write(fifo2_fd, &reponse, sizeof(ReponseServeur));
            
            close(fifo2_fd);

            /* Envoi du signal SIGUSR1 au client concerné */
          // kill(question.numeroClient, SIGUSR1);
        }
    }

    /* Fermeture du tube nommé fifo1 et suppression des tubes nommés */
    close(fifo1_fd);
    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}
