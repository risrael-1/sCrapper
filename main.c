#include <stdio.h>
#include "scrapper.h"

enum versioning {off = 0, on = 1};

int main() {
    //CONFIG EXTRACTOR EMULATION
    char* type_test = "image/jpeg";

    //printf("%s", get_content_type("https://img.lemde.fr/2019/04/22/0/191/1619/1079/688/0/60/0/e39da8d_2FIads9h8wB-0SwSgxVaVWsp.jpg"));
    //printf("%s\n", get_content_page("www.youtube.com"));
    write_img("https://jsonplaceholder.typicode.com/posts/1");
}