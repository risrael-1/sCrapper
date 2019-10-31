#include <stdio.h>
#include "scrapper.h"

enum versioning {off = 0, on = 1};

int main() {
    //CONFIG EXTRACTOR EMULATION
    int max_depth = 2;
    int _versioning = off;
    char* type[3][100] = {"video", "jpeg", "png"};
    char* type_test = "image/jpeg";

    //SCRAPPER TEST
    /*for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 100 ; j++){
            printf("%s", type[i][j]);
        }
    }*/
    //get_header_data("https://img.lemde.fr/2019/04/22/0/191/1619/1079/688/0/60/0/e39da8d_2FIads9h8wB-0SwSgxVaVWsp.jpg");

    printf("%s", get_content_type("https://img.lemde.fr/2019/04/22/0/191/1619/1079/688/0/60/0/e39da8d_2FIads9h8wB-0SwSgxVaVWsp.jpg"));

}