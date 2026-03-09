#include <stdio.h>      // Pour printf, perror
#include <stdlib.h>     // Pour exit, atoi
#include <string.h>     // Pour memset et bzero
#include <unistd.h>     // Pour close
#include <arpa/inet.h>  // Pour htons, inet_addr
#include <sys/types.h>  // Types système
#include <sys/socket.h> // Pour les sockets
#include <netinet/in.h>
#include <fcntl.h>

#define SERV_PORT 2222
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {

    // 1. Creation du socket serveur
    int serverSocket;
    if ((serverSocket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("erreur socket");
        exit(1);
    }

    // 2. Configuration de l'adresse du serveur
    struct sockaddr_in serv_addr;

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    if (bind(serverSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("servecho: erreur bind\n");
        exit(1);
    }

    system("clear");
    
    if (listen(serverSocket, SOMAXCONN) < 0)
    {
        perror("servecho: erreur listen\n");
        exit(1);
    }

    int dialogSocket;
    int clilen;
    struct sockaddr_in cli_addr;
    clilen = sizeof(cli_addr);
    
    dialogSocket = accept(serverSocket,(struct sockaddr *)&cli_addr,(socklen_t *)&clilen);
    
    if (dialogSocket < 0) {
        perror("servecho : erreur accep\n");
        exit(1);
    }

    printf("Connexion acceptée d'un client \n");

    char buff[BUFFER_SIZE] = "Bonjour !";
    send(dialogSocket, buff, strlen(buff), 0);

    while (1) {
        // Réception d'un message du client
        memset(buff, 0, sizeof(buff));
        ssize_t bytes_received = recv(dialogSocket, buff, sizeof(buff) - 1, 0);
        if (bytes_received < 0) {
            perror("Erreur lors de la réception");
            break;
        }
        
        if (strcmp(buff, "exit") == 0)
        {
            printf("deconnection du client...\n");
            printf("deconnection du serveur...\n");
            break;
        }
        
        printf("Client: %s\n", buff);

        // Envoi d'une réponse
        printf("Serveur: ");
        fgets(buff, sizeof(buff), stdin);
        send(dialogSocket, buff, strlen(buff), 0);
    }

    close(dialogSocket);
    close(serverSocket);
    
    exit(0);
}
