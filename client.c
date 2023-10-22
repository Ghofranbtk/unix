#include "serv_cli_fifo.h"
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


    /* Initialisation du générateur de nombres aléatoires */
    srand(getpid());

    /* Ouverture du tube nommé fifo1 pour l'écriture */
    fifo1_fd = open(FIFO1, O_WRONLY);
    if (fifo1_fd == -1) {
        perror("Erreur lors de l'ouverture du tube nommé fifo1");
        exit(EXIT_FAILURE);
    }
	int pid = getpid();
    /* Construction de la question du client */
    question.numeroClient = pid;
    question.nombreAleatoire = rand() % NMAX + 1;


    /* Envoi de la question au serveur */
    write(fifo1_fd, &question, sizeof(QuestionClient));
    close(fifo1_fd);

    /* Ouverture du tube nommé fifo2 pour la lecture de la réponse */
    fifo2_fd = open(FIFO2, O_RDONLY);
    if (fifo2_fd == -1) {
        perror("Erreur lors de l'ouverture du tube nommé fifo2");
        exit(EXIT_FAILURE);
    }



    /* Lecture de la réponse du serveur */
    read(fifo2_fd, &reponse, sizeof(ReponseServeur));
 
 int n = reponse.nombreTiresLen;
 int *tab = (int *)malloc(n * sizeof(int));
 tab =reponse.nombresTires ;
 
 
 //printf("test de reponse %p \n",  &reponse.nombresTires[0]);
    /* Traitement de la réponse */
    printf("Client %d: \nVoici les nombres tirés au sort par le serveur:\n", pid);
     
   
     int *ptr = tab[0] ;
    for (int i = 0; i < n; i++)  {
    printf("test de reponse %d \n",  *ptr);
      //  printf("test de reponse %d ", reponse.nombresTires[i]);
         printf("test de reponse  %d",i);
    }

    printf("\n");

    /* Fermeture du tube nommé fifo2 */
    close(fifo2_fd);

    /* Envoi du signal SIGUSR1 au serveur pour indiquer que la réponse a été lue */
    kill(pid, SIGUSR1);

    return 0;
}
