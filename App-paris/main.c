#include <stdio.h>
#include <winsock2.h>
#include <winsock.h>
#include <mysql.h>
#include <curl/curl.h>

int main() {
    MYSQL *mysql;
    mysql = mysql_init(NULL);
    char *q;
    int end = 0;

    //printf("\nClient Version curl: %s\n", curl_version());
    printf("\n");

    if (mysql_real_connect(mysql, "localhost", "root", "root", "app-pari", 0, NULL, 0)) {
        unsigned int i = 0;
        unsigned int num_champs = 0;
        char query[255];
        char pseudo[255];
        char mail[255];
        char password[255];
        unsigned int age;
        char ages[20];
        //Déclaration des pointeurs de structure
        MYSQL_RES *result = NULL;
        MYSQL_ROW row = NULL;

        printf("Connexion r%cussie\n", 130);

    while(!end) {
        int c;

        /* affichage menu */
        printf("\n1\\Ins%crer des donn%ces.\n"
               "2\\Nombre d'utilisateur.\n"
               "3\\Descriptions des utilisateurs.\n"
               "4\\Quitter!\n"
               "Votre choix:"
               , 130, 130);

        c = getchar();

        /* suppression des caracteres dans stdin */
        if(c != '\n' && c != EOF) {
            int d;
            while((d = getchar()) != '\n' && d != EOF);
        }
        switch(c) {
            case '1':

                // Pseudo
                printf("Pseudo:\n");
                scanf("%s", &pseudo);

                // Email
                printf("E-mail:\n");
                scanf("%s", &mail);

                // Password
                printf("Password:\n");
                scanf("%s", &password);

                // Age
                printf("Age:\n");
                scanf("%d", &age);

                strcpy (query, "INSERT INTO user (pseudo, email, password, age) VALUES (");
                strcat (query, "'");
                strcat (query, pseudo);
                strcat (query, "','");
                strcat (query, mail);
                strcat (query, "','");
                strcat (query, password);
                strcat (query, "','");
                sprintf(ages, "%d", age);
                strcat (query, ages);
                strcat (query, "');");
                printf("QUERY : %s\n", query);
                if (!mysql_real_query(mysql, query, strlen(query))) {
                    printf("Insertion r%cussi\n", 130);
                } else {
                    printf("Insertion failed!\n");
                }

                break;

            case '2':

                //Requête qui sélectionne tout dans ma table
                mysql_query(mysql, "SELECT * FROM user");
                //On met le jeu de résultat dans le pointeur result
                result = mysql_use_result(mysql);
                //Tant qu il y a encore un résultat ...
                while ((row = mysql_fetch_row(result))) {
                    i++;
                }
                printf("\nNombre d'utilisateurs: %d\n", i);
                i = 0;
                //Libération du jeu de résultat
                mysql_free_result(result);

            break;

            case '3':

                // Cette fois, on va lire les données
                //à nouveau la requête qui sélectionne tout dans ma table
                mysql_query(mysql, "SELECT * FROM user");
                result = mysql_use_result(mysql);
                //On récupère le nombre de champs
                num_champs = mysql_num_fields(result);
                printf("\n");
                printf("----------------------------------------------------------------");
                printf("\n");
                while ((row = mysql_fetch_row(result))) {
                    //On déclare un pointeur long non signé pour y stocker la taille des valeurs
                    unsigned long *lengths;
                    //On stocke cette taille dans le pointeur
                    lengths = mysql_fetch_lengths(result);
                    //On fait une boucle pour avoir la valeur de chaque champs
                    for (i = 0; i < num_champs; i++) {
                        //On ecrit toutes les valeurs
                        printf("[%.*s]", (int) lengths[i], row[i] ? row[i] : "NULL");
                    }
                    printf("\n");
                }
                printf("----------------------------------------------------------------");
                printf("\n");
                //Fermeture de MySQL
                mysql_close(mysql);

            break;

            case '4':

                end = 1;

            break;

        }
    }

    } else {
        printf("Une erreur s'est produite lors de la connexion a la base de donnee");
    }

    return 0;

}
