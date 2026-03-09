#include <stdio.h>      // Pour printf, perror
#include <stdlib.h>     // Pour exit, atoi
#include <string.h>     // Pour memset
#include <unistd.h>     // Pour close
#include <arpa/inet.h>  // Pour htons, inet_addr
#include <sys/types.h>  // Types système
#include <sys/socket.h> // Pour les sockets
#include <netinet/in.h> // Pour struct sockaddr_in

#define SERV_PORT 2222
#define BUFFER_SIZE 1024

int main() {
    // 1. Création du socket UDP
    int serverSocket;
    if ((serverSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Erreur socket");
        exit(1);
    }

    // 2. Configuration de l'adresse du serveur
    struct sockaddr_in serv_addr, cli_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    // 3. Liaison du socket avec l'adresse du serveur
    if (bind(serverSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Erreur bind");
        exit(1);
    }

    printf("Serveur UDP en attente de messages sur le port %d...\n", SERV_PORT);

    // 4. Attente des messages clients
    char buffer[BUFFER_SIZE];
    socklen_t cli_len = sizeof(cli_addr);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int n = recvfrom(serverSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&cli_addr, &cli_len);

        if (n < 0) {
            perror("Erreur recvfrom");
            continue;
        }

        printf("Message reçu : %s\n", buffer);

        // Réponse au client
        char response[] = "Message bien reçu";
        sendto(serverSocket, response, strlen(response), 0, (struct sockaddr *)&cli_addr, cli_len);
    }

    close(serverSocket);
    return 0;
}
