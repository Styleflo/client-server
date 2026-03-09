#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <IP> <PORT>\n", argv[0]);
        exit(1);
    }

    // Récupérer l'IP et le port depuis les arguments
    char *server_ip = argv[1];
    int server_port = atoi(argv[2]);

    // 1. Création du socket UDP
    int clientSocket;
    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Erreur socket");
        exit(1);
    }

    // 2. Configuration de l'adresse du serveur
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);
    serv_addr.sin_addr.s_addr = inet_addr(server_ip);

    // 3. Envoi du message au serveur
    char message[] = "Hello, serveur UDP !";
    if (sendto(clientSocket, message, strlen(message), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Erreur sendto");
        exit(1);
    }

    printf("Message envoyé au serveur %s:%d\n", server_ip, server_port);

    // 4. Réception de la réponse du serveur
    char buffer[BUFFER_SIZE];
    socklen_t serv_len = sizeof(serv_addr);
    int n = recvfrom(clientSocket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serv_addr, &serv_len);

    if (n < 0) {
        perror("Erreur recvfrom");
        exit(1);
    }

    buffer[n] = '\0';
    printf("Réponse du serveur : %s\n", buffer);

    // 5. Fermeture du socket
    close(clientSocket);
    return 0;
}
