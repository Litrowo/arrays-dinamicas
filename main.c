#include <stdio.h>
#include <stdlib.h>

struct tournament {
    char name;
    int *players;
};

//TODO Escribir la información de los torneos en un fichero

int main() {

    FILE * torneos = fopen("torneos.txt", "w");

    int selection;
    int n = 0;

    struct tournament *tournaments = malloc(sizeof(struct tournament));
    if (tournaments == NULL) {
        printf("Error dando memoria a torneos");
        exit(1);
    }

    printf("Quieres crear un torneo? (1 si, 0 no):\n");
    scanf("%d", &selection);

    if (selection == 1) {
        do {
            tournaments[n].players = malloc(sizeof(int));
            if (tournaments[n].players == NULL) {
                printf("Error dando memoria a jugadores");
            }
            int i = 0;
            printf("\nIntroduce el nombre del torneo:\n");
            scanf("%s", &tournaments[n].name);
            printf("Introduce el nombre de los participantes (0 para terminar):\n");
            do {
                int auxName;
                tournaments[n].players = realloc(tournaments[n].players, sizeof(tournaments[n].players) + sizeof(int));
                if (tournaments[n].players == NULL) {
                    printf("Erreur\n");
                    return 1;
                }
                scanf("%d", &auxName);
                tournaments[n].players[i] = auxName;
                if (auxName != 0) {
                    i++;
                }
            } while (tournaments[n].players[i] != 0);

            n++;

            printf("Quieres crear otro torneo?\n");
            scanf("%d", &selection);
            if (selection == 1) {
                tournaments = realloc(tournaments, (n + 1) * sizeof(struct tournament));
            }
        } while (selection == 1);
    } else return 0;

   // for (int i = 0; i < n; i++) {
    //    printTournaments(torneos, i, tournaments);
    //}

    for (int i = 0; i < n; i++) {
        free(tournaments[i].players);
    }
    free(tournaments);

    fclose(torneos);

    return 0;
}