//
// Created by Julien Guillan on 12/11/2019.
//

#include "Parser.h"

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

char *getValueBefore(char * info, char character) {
    char *value;
    char *separateur;
    value = malloc(sizeof(char) * 255);
    if (value != NULL) {
        strcpy(value, info);
        separateur = strchr(value, character);
        *separateur = '\0';
    }
    return value;
}

int run(){
    int counterActions = -1;
    int counterTaches = -1;

    // Liste des actions et des taches (commence par un a car Array)
    Action *aActions = malloc(sizeof(Action) * 10);
    Tache *aTaches = malloc(sizeof(Tache) * 10);

    char line[100];

    printf("Bienvenue dans Scrapper\n\n");
    char fic[255];
    printf("Veuillez saisir un fichier de configuration\n");
    scanf("%s", fic);
    printf("Votre fichier de configuration : %s va être traite", fic);

    FILE *f = fopen(fic, "r");

    if (f != NULL) {
        fseek(f, 0, SEEK_SET);

        while (fgets(line, 100, f) != NULL) {
            if (strstr(line, "==") != NULL) { // Si == on créé une tache
                counterTaches++;

                //On récupère les infos de la tache
                fgets(line, 100, f);
                aTaches[counterTaches].name = getInfos(line); // Name

            } else if (strstr(line, "=") != NULL) { // Si = on créé une action
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
                    } // DO TO : option type -> (type1, type2, type3)
                } else { // Actions d'une tache
                    int i = 0;
                    char *info;

                    info = strchr(line, '(') + 1;

                    aTaches[counterTaches].listeActions = malloc(sizeof(char *) * 10);

                    while (strchr(info, ',') != NULL && i <= 8) {
                        aTaches[counterTaches].listeActions[i] = malloc(sizeof(char) * 255);
                        strcpy(aTaches[counterTaches].listeActions[i], getValueBefore(info, ','));
                        info = strchr(info, ',') + 1;

                        i++;
                    }
                    aTaches[counterTaches].listeActions[i] = malloc(sizeof(char) * 255);
                    strcpy(aTaches[counterTaches].listeActions[i], getValueBefore(info, ')'));

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
    printf(" %d", aTaches[1].minute);
    printf("\n%s", aTaches[0].listeActions[1]);
    printf("\n%s", aTaches[1].listeActions[0]);

    free(aActions);
    free(aTaches);

    return 0;
}


