#include "scrapper.h"
#include "Parser.h"

int main(int argc, char **argv) {
    char* URL;
    int max_depth = 0;
    printf("%s\n", argv[2]);
    for(int i = 1 ; i < argc ; i++){
        if(strcmp(argv[i], "--url") == 0 || strcmp(argv[i], "-u") == 0) {
            URL = malloc(sizeof(char*) * strlen(argv[i + 1]));
            URL = argv[i + 1];
        }
        if (strcmp(argv[i], "--max-depth") == 0 || strcmp(argv[i], "-md") == 0) {
            max_depth = atoi(argv[i + 1]);
            printf("md -> %d\n", max_depth);
            char** hyperlinks = get_hyperlinks(write_file(URL));
            for(int i = 0 ; i < max_depth ; i++){
                if(strcmp(hyperlinks[i], URL) != 0 && hyperlinks[i] != NULL){
                    printf("URL I: %s \n", hyperlinks[i]);
                    get_hyperlinks(write_file(hyperlinks[i]));
                }
            }
        }
        if (strcmp(argv[i], "--type") == 0 || strcmp(argv[i], "-t") == 0) {
            char* type = get_content_type(URL);
            printf("TYPE -> %s\n", type);
        }
    }
}