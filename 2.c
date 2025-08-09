#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
    #include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// Déclaration des fonctions utiles

int showFunSh(void) { // Déclaration de ma fonction d'écran
    char *t[] = {"clear", NULL};

    int pid = fork();



    if (pid == 0) {
        if (execvp(t[0], t) == -1) {
            perror("execvp");
        }
        exit(0); 
    }

    wait(NULL);

    printf("     ___               __       \n");
    printf("    |__  |  | |\\ |    /__` |__| \n");
    printf("(un)|    \\__/ | \\|    .__/ |  |  Light Scripts Editor & Runner without fopen, fclose and others !\n");
    printf("\n");
    printf("\n");

        return 0;

}

void writer(const char *cara) {
    int fichier = open("UnFunSh.command", O_WRONLY | O_CREAT | O_APPEND, 0777);



    if (fichier == -1) {
            perror("Erreur ouverture du fichier");
        return;
    }

    write(fichier, cara, strlen(cara));
    write(fichier, " ", 1);


    close(fichier);
}

int compta() {
    int fichier = open("compta", O_RDWR | O_CREAT, 0777);



    if (fichier == -1) {
        perror("Erreur ouverture du fichier");
            return -1;
    }

    char nbr;
    int aa = read(fichier, &nbr, 1);


    if (aa == -1) {
        perror("Erreur lecture du fichier");
        close(fichier);
        return -1;
    }



    if (aa == 0) {
        // Fichier vide, initialiser à 1
        nbr = '1';
    write(fichier, &nbr, 1);
        close(fichier);
        return 1;
    }





    int num = (nbr - '0') + 1;
    char new_num = num + '0';

    lseek(fichier, 0, SEEK_SET);
    write(fichier, &new_num, 1);


    close(fichier);

    return nbr - '0';
}

int compta2() {
    int fichier = open("compta", O_RDWR | O_CREAT, 0777);

    if (fichier == -1) {
        perror("Erreu");
        return -1;
    }

    char nbr;

    int aa = read(fichier, &nbr, 1);

    if (aa == -1) {
        perror("Erreur");
        close(fichier);
        return -1;
    }

    if (aa == 0) {
        // Fichier vide, initialiser à 1
        nbr = '1';
        write(fichier, &nbr, 1);
        close(fichier);
        return 1;
    }



    int num = (nbr - '0');
    close(fichier);
    return num;
}

void show() {
    int fichier = open("UnFunSh.command", O_RDONLY | O_CREAT, 0777);

    if (fichier == -1) {
        perror("Erreur ouverture du fichier");
        return;
    }


    char aff[1024];
    int br = read(fichier, aff, sizeof(aff) - 1);



    if (br == -1) {
        perror("Erreur");
        close(fichier);
        return;
    }


    if (br == 0) {
        printf("Fichier vide !\n");
        close(fichier);
        return;
        }

    aff[br] = '\0'; // Ajouter un caractère nul pour éviter des problèmes d'affichage
    printf("%s", aff);
    close(fichier);}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [commande] [argument 1] [argument n]\n", argv[0]);
        return 1;
    }

    char *liste[50];
    int compteur = 0;

    showFunSh();


    if ((strcmp(argv[1], "--help") == 0) || (strcmp(argv[1], "help") == 0)) {
        printf("Vider le fichier & quitter: %s redo\n", argv[0]);
        printf("Afficher le fichier & quitter: %s dp\n", argv[0]);
        printf("Afficher l'aide & quitter: %s help\n", argv[0]);
        printf("Jouer les commandes: ./UnFunSh.command\n");
        printf("\n");

        printf("Usage: une commande à la fois à chaque démarrage du programme\n");
        printf("Toutes les commandes sont sauvées dans UnFunSh.command\n");
        printf("Usage: %s [commande] [argument 1] [argument n]\n", argv[0]);
        return 0;



    }

    if ((strcmp(argv[1], "--redo") == 0) || (strcmp(argv[1], "redo") == 0)) {
        int file = open("UnFunSh.command", O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (file == -1) {
            printf("erruer");
        } else {


                close(file);
        }

        file = open("compta", O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (file == -1) {
        printf("erruer compta");
        } else {

            close(file);
        }

        printf("Fichiers vidés !\n");
        return 0;
    }

    if ((strcmp(argv[1], "--dp") == 0) || (strcmp(argv[1], "dp") == 0)) {
        int nbrC = compta2();
        nbrC--;

        printf("Vous avez un total de %i commande \n\n", nbrC);
        show();
        return 0;
    }



    int nbrC = compta();

    for (int i = 1; i < argc; i++) {
        if (i == 1) {

            printf("Votre commande numéro %i : %s\n\n", nbrC, argv[i]);
        } else {
            printf("Argument %i de votre commande : %s\n", i - 1, argv[i]);
        }
        writer(argv[i]);
        liste[compteur] = argv[i];
        compteur++;
    }

    liste[compteur] = NULL;



    writer("\n");

    int initp[2];

    if (pipe(initp) == -1) {


        perror("pipe");
        return 1;
    }

    int idf = fork();



    if (idf == 0) {
        //fils

        close(initp[0]);
        dup2(initp[1], STDOUT_FILENO);
        close(initp[1]);
        printf("\n\nRésultat de la commande: \n");
        execvp(liste[0], liste);
        perror("execvp");
        exit(1);
    } else if (idf > 0) {
        close(initp[1]);
        wait(NULL);




        char buffer[1024];
        int lecteur;
        while ((lecteur = read(initp[0], buffer, sizeof(buffer) - 1)) > 0) {
            printf("%s", buffer);
                }
        close(initp[0]);




    } else {
        return 1;}

    return 0;
}
