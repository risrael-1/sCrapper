#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Action {
    char *name;
    char *url;
    char *max_depth;
    char *versionning;
};

typedef struct Action Action;

struct Tache {
    char *name;
    int second;
    int minute;
    int hour;
    char **listeActions;
};

typedef struct Tache Tache;

void replaceAccolade(char *string) {
    char *place;
    place = strchr(string, '}');
    *place = '\0';
}

char *getInfos(char *line) {
    char *info;
    char *tmp;

    info = strchr(line, '>') + 2; //On récupère la valeur située derrière la ->
    replaceAccolade(info); // On enlève ce qu'il y a après l'accolade de fin

    tmp = malloc(sizeof(char) * 255);
    strcpy(tmp, info);

    return tmp;
}

int getValue(char *line) {
    char *info;

    info = strchr(line, '>') + 2; //On récupère la valeur située derrière la ->
    replaceAccolade(info);

    return atoi(info);
}

int main() {
    int totalActions = 0;
    int totalTaches = 0;
    int counterActions = -1;
    int counterTaches = -1;

    // Type de paramètre décrit dans le fichier :
    // 0 => Action
    // 1 => Tache
    int typeParam;

    // Liste des actions et des taches (commence par un a car Array)
    Action *aActions = malloc(sizeof(Action) * 10);
    Tache *aTaches = malloc(sizeof(Tache) * 10);

    char line[100];

    FILE *f = fopen("test.txt", "r");

    if (f != NULL) {
        // On parse une première fois pour compter le nb d'actions et de taches
        while (fgets(line, 255, f) != NULL) {
            if (strstr(line, "==") != NULL) {
                totalTaches++;
            } else if (strstr(line, "=") != NULL) {
                totalActions++;
            }
        }

        fseek(f, 0, SEEK_SET);

        while (fgets(line, 100, f) != NULL) {
            if (strstr(line, "==") != NULL) { // Si = on créé une tache
                typeParam = 1;
                counterTaches++;

                //On récupère les infos de l'action
                fgets(line, 100, f);
                aTaches[counterTaches].name = getInfos(line); // Name

            } else if (strstr(line, "=") != NULL) { // Si == on créé une action
                typeParam = 0;

                counterActions++;

                //On récupère les infos de l'action
                fgets(line, 100, f);
                aActions[counterActions].name = getInfos(line); // Name

                fgets(line, 100, f);
                aActions[counterActions].url = getInfos(line); // Url

            } else if (strstr(line, "+") != NULL) { // Si + on rajoute des options
                fgets(line, 100, f);
                if (strstr(line, "{") != NULL) { // Options d'une action
                    if (strstr(line, "max-depth") != NULL) { // Max-depth
                        aActions[counterActions].max_depth = getInfos(line);
                    } else if (strstr(line, "versionning") != NULL) { // Versionning
                        aActions[counterActions].versionning = getInfos(line);
                    }
                } else {
                    int i = 0;
                    char *info;
                    char *value;
                    char *sep;
                    value = malloc(sizeof(char) * 255);

                    info = strchr(line, '(') + 1;

                    aTaches[counterTaches].listeActions = malloc(sizeof(char *) * 10);

                    while (strchr(info, ',') != NULL) {
                        strcpy(value, info);
                        info = strchr(info, ',') + 1;
                        sep = strchr(value, ',');
                        *sep = '\0';
                        printf("%s", value);

                        aTaches[counterTaches].listeActions[i] = malloc(sizeof(char) * 255);
                        aTaches[counterTaches].listeActions[i] = value;

                        i++;
                    }
                    free(value);
                }
            } else if (strstr(line, "{") != NULL) { // Valeurs d'une tâche
                if (strstr(line, "second") != NULL) {
                    aTaches[counterTaches].second = getValue(line);
                } else if (strstr(line, "minute") != NULL) {
                    aTaches[counterTaches].minute = getValue(line);
                } else if (strstr(line, "hour") != NULL) {
                    aTaches[counterTaches].hour = getValue(line);
                }
            }
        }
        fclose(f);
    } else {
        printf("Fichier introuvable");
    }

    printf("%d", aTaches[1].second);
    printf("%d", aTaches[1].minute);
    printf("%s", aTaches[0].listeActions[0]);

    free(aActions);
    free(aTaches);

    return 0;
}