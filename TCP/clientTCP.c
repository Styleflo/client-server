#include <stdio.h>      // Pour printf, perror
#include <stdlib.h>     // Pour exit, atoi
#include <string.h>     // Pour memset
#include <strings.h>    // Pour bzero
#include <unistd.h>     // Pour close
#include <arpa/inet.h>  // Pour htons, inet_addr
#include <sys/types.h>  // Types système
#include <sys/socket.h> // Pour les sockets
#include <netinet/in.h> // Pour struct sockaddr_in


#define SERVER_IP "127.0.0.1" // Adresse du serveur (localhost ici)
#define SERVER_PORT 2222      // Même port que le serveur
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int clientSocket;
    struct sockaddr_in serv_addr;

    // 1. Création du socket
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Erreur lors de la création de la socket");
        exit(1);
    }

    // 2. Configuration de l'adresse du serveur
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);
    
    
    //3. Demande de connection
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons((ushort) atoi(argv[2]));
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(clientSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("cliecho : erreur connect");
        exit(1);
    }

    char buff[BUFFER_SIZE];  
    ssize_t bytes_received = recv(clientSocket, buff, sizeof(buff) - 1, 0);
    if (bytes_received < 0) {
        perror("Erreur lors de la réception");
    } else {
        buff[bytes_received] = '\0';
        printf("%s\n", buff);
    }

    system("clear");

    while (1)
    {
        printf("Client: ");
        fflush(stdout);
        if (fgets(buff, BUFFER_SIZE, stdin) == NULL) {
            break;
        }

        // Supprimer le saut de ligne
        buff[strcspn(buff, "\n")] = 0;

        // Vérifier si l'utilisateur veut quitter
        if (strcmp(buff, "exit") == 0) {
            printf("Déconnexion...\n");
            send(clientSocket, buff, strlen(buff), 0);
            break;
        }
        send(clientSocket, buff, strlen(buff), 0);

        ssize_t bytes_received = recv(clientSocket, buff, sizeof(buff) - 1, 0);
        if (bytes_received < 0) {
            perror("Erreur lors de la réception");
        } else {
            buff[bytes_received] = '\0';
            printf("Serveur : %s", buff);
        }

    }
    
    close(clientSocket);
    return 0;
}