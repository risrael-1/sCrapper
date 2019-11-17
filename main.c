#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Action {
    char *name;
    char *url;
    int max_depth;
    char *versionning;
};

typedef struct Action Action;

struct Tache {
    char *name;
    int second;
    int minute;
    int hour;
    int nbActions;
    char **listeActions;
};

typedef struct Tache Tache;

void errorSyntaxeConfig(char *message) {
    int enter;
    printf("Error : %s \n", message);
    scanf("%d",&enter);
    exit(123);
}

void replaceAccolade(char *string) {
    char *place;
    place = strchr(string, '}');
    if (place == NULL) {
        errorSyntaxeConfig("Missing \'}\'");
    } else {
        *place = '\0';
    }
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

void initAction(Action * ActionN){
    ActionN->name = NULL;
    ActionN->url = NULL;
}

void initTache(Tache * tache){
    tache->name = NULL;
    tache->second = 0;
    tache->minute = 0;
    tache->hour = 0;
    tache->nbActions = 0;
}

void setParamTache(char * param, char * value, Tache * tache){
    if(strcmp(param,"name") == 0){
        tache->name = value;
    } else if (strcmp(param,"second") == 0){
        tache->second = (atoi(value));
    } else if (strcmp(param,"minute") == 0){
        tache->minute = (atoi(value));
    } else if (strcmp(param,"hour") == 0){
        tache->hour = (atoi(value));
    }
}

void setParamAction(char * param, char * value, Action * action){
    if(strcmp(param,"name") == 0){
        action->name = value;
    } else if (strcmp(param, "url") == 0){
        action->url = value;
    } else if (strcmp(param, "max-depth") == 0) { // Max-depth
        action->max_depth = atoi(value);
    } else if (strcmp(param, "versionning") == 0) { // Versionning
        action->versionning = value;
    }
}

void analyseLineTache(char * line, Tache * tache, Tache ** aTaches, int counterTaches){
    char * param;
    char * info;
    char * value;
    char * separateur;
    int counter;

    param = malloc(sizeof(char)*255);
    value = malloc(sizeof(char)*255);
    info = malloc(sizeof(char)*255);

    strcpy(info, line);
    if(strcmp(info,"\n") == 0){
        errorSyntaxeConfig("Retour a la ligne innatendu");
    }
    info = getInfos(info);
    for(counter = 0 ; counter < counterTaches ; counter ++){
        if(strcmp(aTaches[counter]->name, info) == 0){
            errorSyntaxeConfig("Same task names");
        }
    }

    strcpy(param, line);
    strcpy(value, line);
    param = strchr(param, '{')+1;
    separateur = strchr(param, ' ');
    *separateur = '\0';
    value = getInfos(line);

    setParamTache(param, value, tache);

}

void analyseLineAction(char * line, Action * action, Action ** aActions, int counterActions){
    char * param;
    char * value;
    char * info;
    char * separateur;
    int counter;

    param = malloc(sizeof(char)*255);
    value = malloc(sizeof(char)*255);
    info = malloc(sizeof(char)*255);

    strcpy(info, line);
    if(strcmp(info,"\n") == 0){
        errorSyntaxeConfig("Retour a la ligne innatendu");
    }
    info = getInfos(info);

    for(counter = 0 ; counter < counterActions ; counter ++){
        if(strcmp(aActions[counter]->name,info) == 0){
            errorSyntaxeConfig("Same action names");
        }
    }

    strcpy(param, line);
    strcpy(value, line);
    param = strchr(param, '{')+1;
    separateur = strchr( param, ' ');
    *separateur = '\0';
    value = getInfos(line);
    setParamAction(param, value, action);

}

int main() {
    int counterActions = -1;
    int counterTaches = -1;
    int counter;
    int type = -1; // indication si on traite une action ou une tache

    // Liste des actions et des taches (commence par un a car Array)
    Action *aActions = malloc(sizeof(Action) * 10);
    Tache *aTaches = malloc(sizeof(Tache) * 10);

    char line[100];

    FILE *f = fopen("test.txt", "r");

    if (f != NULL) {
        fseek(f, 0, SEEK_SET);

        while (fgets(line, 100, f) != NULL) {
            if (strstr(line, "==") != NULL) { // Si == on créé une tache
                type = 0;
                counterTaches++;

                initTache(&aTaches[counterTaches]);

                //On récupère les infos de la tache
                while(fgets(line, 100, f) != NULL && strstr(line,"{") != NULL){
                    analyseLineTache(line, &aTaches[counterTaches], &aTaches, counterTaches);
                }

                if(aTaches[counterTaches].name == NULL || (aTaches[counterTaches].second == 0 && aTaches[counterTaches].minute == 0 && aTaches[counterTaches].hour == 0)){
                    errorSyntaxeConfig("Parametre manquant dans une tache");
                }


            } else if (strstr(line, "=") != NULL) { // Si = on créé une action
                type = 1;
                counterActions++;

                initAction(&aActions[counterActions]); //On initialise l'action a NULL

                //On récupère les infos de l'action
                while(fgets(line, 100, f) != NULL && strstr(line,"{") != NULL){
                    analyseLineAction(line, &aActions[counterActions], &aActions, counterActions);
                }

                if(aActions[counterActions].name == NULL || aActions[counterActions].url == NULL){
                    errorSyntaxeConfig("Parametre manquant dans une action");
                }

            }

            if (strstr(line, "+") != NULL) { // Si + on rajoute des options
                while(fgets(line, 100, f) != NULL && strcmp(line,"\n") != 0){
                    if(type == 0){
                        int i = 0;
                        char *info;
                        char * actionToCopy;

                        if(strchr(line, '(') != NULL){ //Vérification de la présence de la liste des actions
                            info = strchr(line, '(') + 1;

                            aTaches[counterTaches].listeActions = malloc(sizeof(char *) * 10);

                            while (strchr(info, ',') != NULL && i <= 8) {
                                aTaches[counterTaches].listeActions[i] = malloc(sizeof(char) * 255);
                                actionToCopy = getValueBefore(info, ',');

                                for(counter = 0 ; counter <= counterActions ; counter++){
                                    if(strcmp(actionToCopy, aActions[counter].name) == 0){
                                        aTaches[counterTaches].listeActions[i] = actionToCopy;
                                        aTaches[counterTaches].nbActions++;
                                        info = strchr(info, ',') + 2;
                                    }
                                }

                                i++;
                            }
                            actionToCopy = getValueBefore(info, ')');
                            for(counter = 0 ; counter <= counterActions ; counter++){
                                if(strcmp(actionToCopy, aActions[counter].name) == 0){
                                    aTaches[counterTaches].listeActions[i] = actionToCopy;
                                    aTaches[counterTaches].nbActions++;
                                }
                            }

                        }

                    } else if(type == 1){
                        analyseLineAction(line, &aActions[counterActions], &aActions, counterActions);
                    }
                }
            }
        }
        fclose(f);
    } else {
        printf("Fichier introuvable");
    }

    int counter2;
    char * command;
    command = malloc(sizeof(char)*255);

    if(command != NULL){
        for(counter = 0 ; counter < counterTaches ; counter ++){
            for(counter2 = 0 ; counter2 < aTaches[counterTaches].nbActions ; counter2++){
                sprintf(command, "/sCrapper --url %s --max-depth %d",aActions[counter2].url, aActions[counter2].max_depth);
                system(command);
            }
        }
    }

    free(aActions);
    free(aTaches);

    return 0;
}