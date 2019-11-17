//
// Created by Julien Guillan on 24/10/2019.
//

#include "scrapper.h"

/**
 * Perform request of a curl passed as argument
 * @param curl
 * @return
 */
CURLcode perform_request(CURL* curl){
    CURLcode _res = 0;
    char* _error_buff = malloc(sizeof(char*) * CURL_ERROR_SIZE);
    *(_error_buff) = 0;
    if(curl){
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, _error_buff);
        _res = curl_easy_perform(curl);
        if(_res != CURLE_OK){
            size_t _err_len = strlen(_error_buff);
            if(_err_len){
                fprintf(stderr, "%s\n", _error_buff);
            } else {
                fprintf(stderr, "%s\n", curl_easy_strerror(_res));
            }
        }
    }
    return _res;
}

/**
 * Cakkback called from get_header_data() function
 * @param buffer
 * @param size
 * @param nitems
 * @param userdata
 * @return
 */
static size_t header_callback(char* buffer, size_t size, size_t nitems, void * userdata){
    printf("%s", buffer );
    return nitems * size;
}

/**
 * Get header data
 * @param url
 */
void get_header_data(char* url){
    CURL *curl = curl_easy_init();
    CURLcode _res = 0;
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        perform_request(curl);
    }
}

/**
 * Get HTTP response code
 * @param url
 * @return
 */
long get_response_code(char* url){
    CURL *curl = curl_easy_init();
    long response_code = 0;
        if(curl) {
            CURLcode _res;
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
            curl_easy_setopt(curl, CURLOPT_FAILONERROR, &response_code);
            _res = perform_request(curl);
            if (_res == CURLE_OK) {
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
                return response_code;
            }
            curl_easy_cleanup(curl);
            return response_code;
        }
    return 0;
}

/**
 * Get content type of page from MIME in HEADER
 * @param URL
 * @return
 */
char* get_content_type(char* URL){
    CURL *curl = curl_easy_init();
    char* response_code;
    if(curl){
        CURLcode _res;
        curl_easy_setopt(curl, CURLOPT_URL, URL);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        curl_easy_setopt(curl, CURLOPT_FAILONERROR, &response_code);
        _res = perform_request(curl);
        if(_res == CURLE_OK){
            curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &response_code);
            return response_code;
        }
        curl_easy_cleanup(curl);
    }
    return NULL;
}
/**
 * Get content of page -> UNUSED
 * @param URL
 * @return
 */
char* get_content_page(char* URL){
    CURL* curl = curl_easy_init();
    char* response_code;
    if(curl){
        CURLcode _res;
        curl_easy_setopt(curl, CURLOPT_URL, URL);
        perform_request(curl);
    }
    return NULL;
}
/**
 * Get part of string between two characters passed as arguments
 * @param start
 * @param line
 * @param char1
 * @param char2
 * @return
 */
char* get_string_part(int start, char* line, char char1, char char2){
    start = 0;
    char* buffer = malloc(sizeof(char) * 255);
    //34 ASCII for "
    while(line[start] != char1) {
        start += 1;
    }

    int fin = start + 1;
    while(line[fin] != char2) {
        fin += 1;
    }

    strncat(buffer, &line[start + 1], (fin - start - 1));
    return buffer;
}

/**
 * Create a table containing all hyperlinks found on scrapped website
 * @param file
 * @return
 */
char** get_hyperlinks(char* file){
    printf("\nDEBUG - get_hyperlinks BEGIN\n");
    char* array_link[255];
    int array_size = 0;
    FILE* scrapped_site;
    scrapped_site = fopen(file, "r");
    if(scrapped_site != NULL){
        int buf_length = 255;
        char* buffer = malloc(sizeof(char*) * 255);
        int i = 0;
        while(fgets(buffer, buf_length, scrapped_site) != NULL){
            char* tmp_link = strstr(buffer, "<a href=");
            if(tmp_link != NULL){
                //printf("DEBUG - get_string_part() -> %s\n \n", get_string_part(0, tmp_link));
                char* tmp = get_string_part(0, tmp_link, '"', '"');
                char* link = strstr(tmp, "http");
                if(link != NULL){
                    array_link[i] = link;
                    printf("-> %s\n", array_link[i]);
                    array_size++;
                    i++;
                }
            }
        }
    } else {
        fprintf(stderr, "get_hyperlinks() -> Error: Cannot open %s. Exiting...\n", file);
        exit(1);
    }
    printf("\nDEBUG - get_hyperlinks END\n");
    return array_link;
}

/**
 * Create file with website source code
 * @param URL
 * @return
 */
//TODO USE DOMAIN NAME TO PUT FILE INTO DIRECTORY NAMED BY URL DOMAIN (mkdir DOMAIN_NAME/FILE_NAME)
char* write_file(char* URL){
    printf("\nwrite_file() BEGIN\n");
    printf("URL -> %s\n", URL);
    FILE* tmp_file;
    CURL* curl = curl_easy_init();
    char* directory_name = url_get_domain(URL);
    printf("\nDirectory name: %s\n", directory_name);
    int mkdir_status;
    char* _file_name = "tmp_file";
    char* _type = get_content_type(URL);
    int sep_pos = 0;
    int size = 0;
    //GETTING THE POSITION OF "/" OF THE MIME CONTENT TYPE
    //end of the extension in case of multiple content type
    int end = 0;
    for(int i = 0 ; i < strlen(_type) ; i++){
        //59 -> ;
        if(_type[i] == 59){
            end = i;
            break;
        }
        //47 -> /
        if(_type[i] == 47){
            sep_pos = i;
            //TODO DYNAMIC SIZE
            size = 4;
        }
    }
    printf("ICI %d\n", size);
    //SPLITTING THE MIME CONTENT TYPE TO ONLY GET THE SECOND PART AFTER "/"
    char* img_type = malloc(sizeof(char) * size - 1);
    if(size > 0){
        int j = 0;
        for(int i = sep_pos + 1; i < end ; i++){
            img_type[j] = _type[i];
            j++;
        }
    }
    //CREATE FULL FILE NAME WITH THE A NAME + "." + EXTENSION

    char* full_file_name = malloc(sizeof(char) * strlen(_file_name) + sizeof(char) * 2 + sizeof(char) * strlen(img_type) + sizeof(char) * strlen(directory_name));
    strcpy(full_file_name, directory_name);
    strcat(full_file_name, "/");
    strcat(full_file_name, _file_name);
    strcat(full_file_name, ".");
    if(strlen(img_type) == 0){
        img_type = "html";
    }
    strcat(full_file_name, img_type);

    printf("\nFULLFILENAME -> %s", img_type);

    //CREATING DIRECTORY TO SAVE SCRAPPED CONTENT
    mkdir(directory_name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    //WRITE DATA INTO FILE
    tmp_file = fopen(full_file_name, "wb");
    if(tmp_file != NULL && curl){
        curl_easy_setopt(curl, CURLOPT_URL, URL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, tmp_file);
        CURLcode _res = perform_request(curl);
        if(!_res){
            printf("\nRES -> %d\n", _res);
        } else {
            fclose(tmp_file);
            return NULL;
        }//TODO: _res ERROR not treated
    }
    curl_easy_cleanup(curl);
    fclose(tmp_file);
    printf("\nFULL FILE NAME: %s\n", full_file_name);
    return full_file_name;
}

/**
 * Get onnfly domain name of URL
 * @param URL
 * @return
 */
char* url_get_domain(char* URL){
    printf("URL[i] -> %s\n", URL);
    int slash_pos = 0;
    int end_slash_pos = 0;
    int domain_size = 0;
    char* domain;
    for(int i = 0 ; i < strlen(URL) ; i++){
        //ASCII 47 -> /
        if(URL[i] == 47 && URL[i + 1] == 47){
            slash_pos = i;
        } else if ((URL[i] == 47 && URL[i + 1] != 47 && URL [i - 1] != 47) || (URL [i] == 'm' && URL[i - 1] == 'o' && URL [ i - 2] == 'c')) {
            end_slash_pos = i;
            break;
        }
    }
    for (int i = slash_pos + 2 ; i < end_slash_pos; i++){
        if(URL[i] >= 97 && URL[i] <= 122){
            domain_size++;
        }
    }
    printf("DOMAINE SIZE -> %d\n", domain_size);
    domain = malloc(sizeof(char) * domain_size - 4);
    int j = 0;
    for(int i = slash_pos + 2; i < end_slash_pos; i++){
        if(URL[i] >= 97 && URL[i] <= 122){
            domain[j] = URL[i];
            j++;
        }
    }
    printf("DOMAINE SIZE domain -> %lu\n", strlen(domain));
    printf("DOMAIN : %s", domain);
    return domain;
}






