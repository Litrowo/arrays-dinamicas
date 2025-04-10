#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

struct players {
    char name[10];
    int score;
};

struct tournament {
    char name[100];
    struct players *players;
};

void shortPlayers(int n, struct tournament *tournament) {
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (strcmp(tournament[i].players[j].name, "stop") != 0) {
            j++;
        }
        for (int k = 0; k < j; k++) {
            for (int l = k + 1; l < j; l++) {
                if (tournament[i].players[k].score < tournament[i].players[l].score) {
                    char auxName[10];
                    int auxShort = tournament[i].players[k].score;
                    tournament[i].players[k].score = tournament[i].players[l].score;
                    tournament[i].players[l].score = auxShort;
                    strcpy(auxName, tournament[i].players[k].name);
                    strcpy(tournament[i].players[k].name, tournament[i].players[l].name),
                    strcpy(tournament[i].players[l].name, auxName);
                }
            }
        }
    }
}

void printTournaments(FILE * torneos, int n, struct tournament *tournament) {
    for (int i = 0; i < n; i++) {
        fprintf(torneos,"El nombre del torneo %d es: ", i + 1);
        fprintf(torneos, "%s\n", tournament[i].name);
        fprintf(torneos,"Los jugadores del torneo son:\n");
        shortPlayers(n, tournament);
        int j = 0;
        while (strcmp(tournament[i].players[j].name, "stop") != 0) {
            fprintf(torneos,"Nombre: %s Puntuación: %d\n", tournament[i].players[j].name, tournament[i].players[j].score);
            j++;
        }
        fprintf(torneos,"\n");
    }
}


void printData(FILE * data, int n, struct tournament *tournament) {
    for (int i = 0; i < n; i++) {
        fprintf(data,"%s\n\n", tournament[i].name);
        int j = 0;
        while (strcmp(tournament[i].players[j].name, "stop") != 0) {
            fprintf(data, "%s\n\n", tournament[i].players[j].name);
            fprintf(data, "%d\n\n", tournament[i].players[j].score);
            j++;
        }
        fprintf(data,"\n\n");
    }
}

void readData(FILE * data, int *i, struct tournament *tournament) {
    bool keepReading = true;
    int blanc = 0;
    int n = *i;
    //printf("Test 0\n");
    tournament[n].players = malloc(sizeof(struct players));
    if (tournament[n].players == NULL) {
        printf("Error");
        exit(1);
    }

    do {
        //printf("Test 1\n");
        blanc++;
        char auxLineChange[2];
        tournament = realloc(tournament, (n + 1) * sizeof(struct tournament));
        fgets(tournament[n].name, 100, data);
        //fscanf(data, "%s", &tournament[n].name);
        //printf("%s\n", tournament[n].name);
        //fgets(auxLineChange, 2, data);
        //printf("Test 2\n");
        int j = 0;
        while (strcmp(fgets(auxLineChange, 2, data), "\n") != 0) {
            tournament[n].players = realloc(tournament[n].players, (j + 1) * sizeof(struct players));
            fscanf(data, "%s", &tournament[n].players[j].name);
            //printf("%s\n", tournament[n].players[j].name);
            //tournament[n].players[j].name = auxPlayerName;
            fscanf(data, "%d", &tournament[n].players[j].score);

            //printf("Test 3\n");
            blanc = 0;
            j++;
        }
        n++;
        //printf("Test 3'\n");
        if (blanc > 2) {
            //printf("Test 5\n");
            keepReading = false;
        }
    } while (keepReading);
    //printf("Test 4\n");
    *i = n - 1;
}

int main() {

    int selection;
    int n = 0;

    struct tournament *tournaments = malloc(sizeof(struct tournament));
    if (tournaments == NULL) {
        printf("Error dando memoria a torneos");
        exit(1);
    }


    srand(time(NULL));

    FILE * dataRead = fopen("data.txt", "r");

    readData(dataRead, &n, &tournaments[0]);
    fclose(dataRead);

    printf("%d\n", n);

    printf("Quieres crear un torneo? (1 si, 0 no):\n");
    scanf("%d", &selection);

    if (selection == 1) {
        //tournaments = realloc(tournaments, (n + 1) * sizeof(struct tournament));
        if (tournaments == NULL) {
            printf("Error");
        }
        do {
            tournaments[n].players = malloc(sizeof(struct players));
            if (tournaments[n].players == NULL) {
                printf("Error dando memoria a jugadores");
            }
            int i = 0;
            printf("\nIntroduce el nombre del torneo:\n");
            scanf("%s", &tournaments[n].name);
            //printf("%s\n", tournaments[n].name);
            printf("Introduce el nombre de los participantes ('stop' para terminar):\n");
            do {
                printf("Test 2\n");
                tournaments[n].players = realloc(tournaments[n].players, (i + 1) * sizeof(struct players));
                if (tournaments[n].players == NULL) {
                    printf("Errorasd\n");
                    exit(1);
                }
                scanf("%s", &tournaments[n].players[i].name);
                tournaments[n].players[i].score = rand() % 1000;

                if (strcmp("stop", tournaments[n].players[i].name) != 0) {
                    i++;
                }
            } while (strcmp("stop", tournaments[n].players[i].name) != 0);

            n++;

            printf("Quieres crear otro torneo?\n");
            scanf("%d", &selection);
            //printf("Test2 %d", selection);
            if (selection == 1) {
                tournaments = realloc(tournaments, (n + 1) * sizeof(struct tournament));
                if (tournaments == NULL) {
                    printf("Error\n");
                }
            }
        } while (selection == 1);
    }

    printf("test1");


    FILE * torneos = fopen("torneos.txt", "w");

    //printTournaments(torneos, n, tournaments);

    fclose(torneos);

    FILE * data = fopen("data.txt", "w");

    //printData(data, n, tournaments);

    fclose(data);


    for (int i = 0; i < n; i++) {
        free(tournaments[i].players);
    }
    free(tournaments);

    return 0;
}

//TODO leer info de torneos y no borrarlos cada vez que se use
//crear el struct players con nombre y puntuación
//TODO crear funcion que permita modificar información de torneos
//ordenar los jugadores de cada torneo por puntuación
