/*
cd "/Users/bibi/OneDrive - EPHEC asbl/OS"
gcc ex1.c -o ex1
./ex1
*/

//idées à éventuellement faire en + :arguement pour demander si on veut supprimer le contenue du fichier, nouveau fichier avec le path, mettre le chiffre ?, reprendre à partir

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>//important pour les processus fork
#include <sys/types.h>  // Inclure le fichier d'en-tête pour les types de données utilisés dans les appels système
#include <signal.h>     // Pour kill()
#include <fcntl.h>




FILE *bypassfopen(const char *pathname, const char *mode) {//définition de la fonction FILE avec ces 2 paramêtres(lePath,et le paramêtre)
    int fd;
    int wr = 0;

    

    if (strcmp(mode, "r+") == 0) {//vérication de l'argumemnt voulu
        wr = O_RDWR;
    } else if (strcmp(mode, "w+") == 0) {
        wr = O_RDWR | O_CREAT | O_TRUNC;
    } else {
    
        return NULL;
    }

    fd = open(pathname, wr, 0666);//ouverture
    if (fd == -1) {
        return NULL;
    }

    FILE *file = fdopen(fd, mode);
    if (file == NULL) {
        close(fd);
        return NULL;
    }

    return file;
}

    int showFunSh(void){// déclaration de ma fonction d'écran

        system("clear");
        printf(" ___               __       \n");
        printf("|__  |  | |\\ |    /__` |__| \n");
        printf("|    \\__/ | \\|    .__/ |  |  Scripts Editor & Runner\n");
        printf("\n");
        printf("\n");

        return 0;


    }



        void passeLigne(int hello){//j'ai fais ca plus pour tester les fonctions mais c'est utilse aussi j'immagine
        for (int i = 0 ;i<hello;i++){
            printf("\n");
        }
    }


    void afficherLeContenu(const char *fichierPath){//pour afficher le fichier avec un cat passé au systheme

        char commande[1024];
        snprintf(commande, sizeof(commande), "cat %s", fichierPath);//en gros ca concat un string comme ca on peut le jouer après psq j'ai pas trouvé comment faire autrement
        system(commande);//passe commande vers le terminal
        passeLigne(2);

        
    }


int main(int argc, char *argv[])// argc c'est le nombre d'argument passé, argv c'est la liste

{   
    
    showFunSh();

    FILE *fichier;//FILE représente un flux de donnés et est propre à stdlib je pense

    char fichierPath[30];

    strcpy(fichierPath,"funSh.txt");// non du fichier par défault

//boucle pour l'interpréation des options de type --
    for (int a = 1; a < argc; a++) {
        if (strcmp(argv[a], "--help") == 0) {



            printf("USAGE : %s [commande 1] [commande 2] [commande n] --file [NomFichier]\n", argv[0]);//std veut dire standart, normalement avec cette ligne on peut renommer le fichier et le message d'aide est adapté via la var
            //passeLigne(1);
            printf("OPTIONS : --help : affiche l'aide\n");
            printf("OPTIONS : --version : affiche la version\n");
            printf("OPTIONS : --file [nomDuFichier] : Ouvrir ou créer un fichier\n");
            printf("Le fichier par défault est 'funSh.txt'");
            passeLigne(2);
            exit(EXIT_SUCCESS);

        } if (strcmp(argv[a], "--version") == 0) {
            showFunSh();
            printf("Version 1.0 par Robin, Nathan & Gaspard\n");
            passeLigne(2);
            exit(EXIT_SUCCESS);
        } if (strcmp(argv[a], "--file") == 0){
            strcpy(fichierPath,argv[a+1]);
        }
        
    }




    fichier = bypassfopen(fichierPath,"r+");
    if (fichier == NULL) {
        fprintf (stdout,"aucun fichier '%s' trouvé, création d'un nouveau fichier à l'emplacement\n",fichierPath);
        fichier = bypassfopen(fichierPath,"w+");
            if(fichier == NULL){
                printf("Erreur dans la création du fichier, vérifiez les permissions");
                exit(EXIT_FAILURE);

            }
    }

    if (argc > 1 && strcmp(argv[1],"--count" )==0) {// c'est pour afficher le nombre de ligne à l'utilisateur
        fprintf(stdout,"USAGE : %s [commande 1] [commande 2] [commande 3] [commande n]\n",argv[0]);//std veut dire standart, normalement avec cette ligne on peut renommer le fichier et le message d'aide est adapté via la var
        exit(EXIT_SUCCESS);
    }

    char next[99];//nouvelle var de txt avec 99 taille max
    int choice;
    char buffer[1000];//c'est le nombre de caractre que fgets pourra lire en une fois sur le fichier par la suite
    int i = 1;
    int compteur = 1;
    char *temp;

    pid_t idPID;



    while (fgets(buffer, sizeof(buffer), fichier)) {//ce code sert à remettre la valeur du compteur en fct des lignes qui sont dans le fichier
        compteur++;  // Incrémente le compteur de lignes pour chaque ligne
    }



    //fprintf(fichier, "votre programme  %s fonctionne, féliciation tu as bien mis au moins un argument !", argv[0]);
    //fprintf(fichier, "vos agrument sont\n");
    
    //boucle pour les arguements du fichier
    for(i=1;i<argc;i++){

        if(strncmp(argv[i],"--",2) == 0){//2 est le nombre de lettre à comparer
        break;


        }
        
        printf("commande enregistrées --> %s \n", argv[i]);
        fprintf(fichier, "%d %s\n", compteur, argv[i]);

        compteur++;
        
    }

    passeLigne(1);
    printf("Utilisez %s --help au lancement pour afficher l'aide",argv[0]);
    passeLigne(2);








    while(1){
        //printf("entrez le prochain arguement à écrire dans le fichier \n");
        printf("entrez une commande, elle sera insrite dans le fichier '%s' !\n", fichierPath);
        passeLigne(1);
        printf("(pour sortir écrire 'exit')\n");
        printf("(pour afficher le menu 'menu')\n");
        passeLigne(1);
        printf("commande numéro %i : ",compteur);
        scanf(" %99[^\n]", next);//99 c'est le nombre de caractère que l'user peut taper '^' veut dire négation donc ne lie pas les "\n les crochets sont en gros les trucs qui sont accépté si l'u tape autre chose le c lit jusque là mais la c'est la négation avec le crochet "

        if (strcmp(next, "exit")== 0){// compare next la variable avec le exit
                fclose(fichier);//ferme le fichier 
                showFunSh();
                printf("vous quittez la boucle\n");
                printf("le fichier à bien été écrit!\n");
                passeLigne(2);
                //kill(0, SIGKILL);
                return 0;//retourne 0 donc pas d'erreur on est bon !

                
        }

        if (strcmp(next, "menu")== 0 || strcmp(next, "m")== 0){// compare next la variable avec le exit


            

            

            showFunSh();

            choice = 99;

            //printf("entrez un nombre (1-6)\n");
            printf("1: Affiche les commandes\n");
            printf("2: Exécuter le script\n");
            printf("3: Enregister et ouvrir un autre fichier\n");
            printf("4: Supprime le fichier %s\n", fichierPath);
            printf("5: Vider le fichier\n");
            printf("6: Compter le nombre de ligne\n");
            printf("7: Fermer le menu\n");
            printf("8: Enregistrer & quitter\n");
            printf("9: Enregister & rendre le fichier exécutable en dehors de FunSh\n");
        
            
            passeLigne(2);

            while (choice < 1 || choice > 9) {

                printf("Entrez votre choix (1-9) : ");
                if (scanf("%i", &choice)!= 1){
                    printf("Veillez entrer un nombre valide entre 1 et 9\n");
                    while (getchar() != '\n');//vider ce que l'utilisateur tape sinon ca fait une boucle infinie bizzard
                    choice = 0;
                    continue;
                }

                    if (choice > 9){
                        choice = 10;
                    }

                if (choice < 1 || choice > 9){
                    choice = 10;
                }

            }

            showFunSh();
            int compteur2 = 0;
            compteur2 = 0;
            

            

            //if(choice == 8){//demander à la prof comment fiare une fonction
            //}

            switch(choice) {

                char commande[100];
                char c[100];
                case 2:

                
                fclose(fichier);
                fichier = bypassfopen(fichierPath, "r+");
                if (fichier == NULL || compteur == 1) {
                    printf("Votre fichier %s est vide !\n", fichierPath);
                    passeLigne(2);
                    break;
                }

                int pipelist[2];//tableau pour socker les info de la pipe
                pipe(pipelist);  // Initialisation de la pipe

                passeLigne(4);

                while (fgets(buffer, sizeof(buffer), fichier)) {
                    char *temp = strchr(buffer, ' ');//ce code sert à prendre que ce qui est après l'espace ca prend dans le buffer le première fois ou il y a ' '
                    if (!temp) continue;
                    temp++;

                    char *liste[100];//pour chaque ligne par exemple 'cd pomme' via la boucle du dessus
                    int compteurArgu = 0;
                    
                    liste[compteurArgu] = strtok(temp, " \n");//stocker cd
                    while (liste[compteurArgu] != NULL) {//stocker les arguemnts dans un temp
                        compteurArgu++;//au augmente de 1 la liste
                        liste[compteurArgu] = strtok(NULL, " \n");
                    }

                    pid_t forkid = fork();//initiation de la fork

                    if (forkid == 0) {//si c'est un FILS
                        close(pipelist[0]);//ferme la lecture de la pipe je ne sais pas vraiment pourquoi on fait ca mais tt le monde le fait
                        
                        dup2(pipelist[1], STDOUT_FILENO);//redirection de la sortie terminal vers le pipe donc écriture
                        close(pipelist[1]);//fermeture de l'écriture

                        printf("------------EXECUTION--------------\n");
                        
                        
                        printf("La commande : %s retourne : ⬇️ ", temp);
                        //sleep(1);
                        //system(temp);
                        passeLigne(2);

                        execvp(liste[0], liste);//execution

                        
                        
                        exit(EXIT_FAILURE);//normalement ce code n'est pas joué
                    } else if (forkid > 0) {//CECI EST LE PERE
                        close(pipelist[1]);//fermeture de l'écriture psq c'est plus sécur i guess
                        char pipebuffer[1000];//declaration du buffer
                        while (read(pipelist[0], pipebuffer, sizeof(pipebuffer)-1) > 0) {//boucle pour print tt les lignes du buffers
                            printf("%s", pipebuffer);
                        }
                        close(pipelist[0]);//on ferme la lecture
                        printf("----------FIN-EXECUTION-----------");
                        //sleep(1);
                        wait(NULL);//on attend le fil
                        
                        passeLigne(2);
                    } else {
                        perror("le fork a raté");
                    }
                }

                
                break;

                case 3:


                fclose(fichier);//ferme le fichier 
                printf("le fichier à bien été écrit!\n");
                passeLigne(2);

                printf("Nom du fichier : ");
                scanf("%s",fichierPath);
                fichier = NULL;
                
                

                if (fichier == NULL) {

                    fprintf (stdout,"aucun fichier '%s' trouvé, création d'un nouveau fichier à l'emplacement\n",fichierPath);
                    fichier = bypassfopen(fichierPath,"w+");
                        if(fichier == NULL){

                            printf("Erreur dans la création du fichier, vérifiez les permissions");
                            exit(EXIT_FAILURE);

                        }
                }
                fichier = bypassfopen(fichierPath,"r+");
                compteur =1;
                break;
                
                
            


                case 8:
                    fclose(fichier);//ferme le fichier 
                    printf("le fichier à bien été écrit!\n");
                    passeLigne(2);
                    //kill(0, SIGKILL);
                    return 0;//retourne 0 donc pas d'erreur on est bon !

                case 1:
                    fclose(fichier);// on ferme comme ça le fichier peut se mettre à jour
                    afficherLeContenu(fichierPath);//appel à la fonction
                    fichier = bypassfopen(fichierPath,"r+");
                    // Variable pour stocker les caractères lus un à un
                    if (compteur == 1){
                        printf("Votre fichier %s est vide ! \n",fichierPath);
                        passeLigne(2);
                    }
                    break;
                case 7:
                    break;

                case 5:

                fclose(fichier);
                fichier = bypassfopen(fichierPath,"w+");
                printf("Le contenue du fichier %s à bien été supprimé !\n", fichierPath);
                passeLigne(2);
                compteur = 1;

                    break;
                case 4:


                fclose(fichier);//ferme le fichier 
                //char commande[1024];
                snprintf(commande, sizeof(commande), "rm %s", fichierPath);
                system(commande);
                printf("Le fichier %s à bien été supprimé !", fichierPath);
                passeLigne(2);
                return 0;//retourne 0 donc pas d'erreur on est bon !
                break;
                
                case 6:
                    compteur--;
                    printf("Le nombre de ligne est %i\n",compteur);
                    compteur++;
                    break;
                case 9:
                    fclose(fichier);
                    fichier = bypassfopen(fichierPath, "r+");
                    if (fichier == NULL || compteur == 1) {
                        printf("Votre fichier %s est vide !\n", fichierPath);
                        passeLigne(2);
                        break;
                    }


                    char *lines[100];//temp
                    int totalLines = 0;

                    while (fgets(buffer, sizeof(buffer), fichier)) {
                        char *temp = strchr(buffer, ' '); // Prendre ce qui est après l'espace
                        if (!temp) continue; // Si temp est rien continuer
                        temp++;

                         char *liste[100]; // pour chaque ligne, par exemple 'cd pomme'
                            int compteurArgu = 0;

                        liste[compteurArgu] = strtok(temp, " \n"); //sépa
                        while (liste[compteurArgu] != NULL) { // Stocker les arguments
                                compteurArgu++;
                            liste[compteurArgu] = strtok(NULL, " \n");
                        }


                        char lineBuffer[256] = "";
                        for (int i = 0; i < compteurArgu; i++) {
                            strcat(lineBuffer, liste[i]);
                            if (i < compteurArgu - 1) strcat(lineBuffer, " ");
                        }

                        lines[totalLines] = strdup(lineBuffer);
                        totalLines++;
                    }

                    fclose(fichier);

                    // ouvir le fichier & le vider avec w+
                    fichier = fopen(fichierPath, "w+");
                    if (fichier == NULL) {
                        printf("Erreur\n");//classique vérification
                        break;
                    }

                    // Écrire toutes les lignes dans le fichier
                    for (int i = 0; i < totalLines; i++) {
                        fprintf(fichier, "%s\n", lines[i]);
                    }

                    fclose(fichier); // Ferme le fichier
                    char commande2[100];
                    sprintf(commande2, "chmod 777 %s", fichierPath);
                    system(commande2);
                    printf("Votre fichier est maintenant exécutable en dehors de FunSh !\n");
                    passeLigne(2);
                    return 0; // Retourne 0 donc pas d'erreur




                    break;
                default:
                    showFunSh();
                    printf("Erreur, sortie\n");

            }
        

        }


        if (strcmp(next, "menu") != 0){

        fprintf(fichier, "%d %s\n", compteur, next);//on print dans le fichier
        compteur++;// on augmente de un le compteur
        showFunSh();
        printf("écriture réussie! \n");
        passeLigne(1);
        }


    }



    return 0;


};