# Projet Client-Serveur

Ce projet a pour but la création de deux couples client-serveur en TCP et UDP

## Client-Serveur TCP

### Explication

Le serveur TCP créer un socket et se lie à l'adresse ip 127.0.0.1 au port 2222 
Le serveur attend ensuite la connection d'un client sur cette adresse et ce port.

Le client TCP se connecte au port 2222 et le serveur envoie un bonjour.
À partir de là, une communication peut se faire, le client peut écrire au serveur et le serveur peut répondre.

### Mise en place

Pour commencer il faut se rendre dans le dossier TCP
```
cd ./TCP
```

Une fois dans le dossier TCP, on doit compiler les fichiers .c pour obtenir des fichiers executables.
```
clang [Nom_du_fichier].c -o Nom_du_fichier
```

Pour lancer ces deux executables, le mieux et de lancer le serveur :
```
./serveurTCP
```
Puis de lancer dans un autre terminal :
```
./clientTCP '127.0.0.1' 2222
```


## Client-Serveur UDP

### Explication

Le serveur UDP créer un socket et se lie à l'adresse ip 127.0.0.1 au port 2222
Le serveur attend ensuite la connection d'un client sur cette adresse et ce port.

Le client UDP envoie une information au serveur qui peut acquitter de la bonne reception de ce dernier
en envoyant à son tour un message au client.

### Mise en place

Pour commencer il faut se rendre dans le dossier UDP
```
cd ./UDP
```

Une fois dans le dossier UDP, on doit compiler les fichiers .c pour obtenir des fichiers executables.
```
clang [Nom_du_fichier].c -o Nom_du_fichier
```

Pour lancer ces deux executables, le mieux et de lancer le serveur :
```
./serveurUDP
```
Puis de lancer dans un autre terminal :
```
./clientUDP '127.0.0.1' 2222
```