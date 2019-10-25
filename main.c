#include <stdio.h>
#include "scrapper.h"

int main() {
    get_header_data("http://example.com");
    printf("%ld", get_response_code("https://www.youtube.com"));
    return 0;
}