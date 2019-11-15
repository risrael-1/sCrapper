#include "scrapper.h"
#include "Parser.h"

enum versioning {off = 0, on = 1};

int main() {
    //CONFIG EXTRACTOR EMULATION
    char* type_test = "image/jpeg";

    //printf("%s", get_content_type("https://img.lemde.fr/2019/04/22/0/191/1619/1079/688/0/60/0/e39da8d_2FIads9h8wB-0SwSgxVaVWsp.jpg"));
    //printf("%s\n", get_content_page("www.youtube.com"));
    write_file("https://www.example.com");
    run();

   /* int main() {
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
    }*/
}