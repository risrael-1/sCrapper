//
// Created by Julien Guillan on 24/10/2019.
//

#include "scrapper.h"

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
                fprintf(stderr, "%s", _error_buff);
            } else {
                fprintf(stderr, "%s\n", curl_easy_strerror(_res));
            }
        }
    }
    return _res;
}

static size_t header_callback(char* buffer, size_t size, size_t nitems, void * userdata){
    printf("%s", buffer );
    return nitems * size;
}

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

void scrapp(char* URL, char* type){

}

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

char* get_content_page(char* URL){
    CURL* curl = curl_easy_init();
    char* response_code;
    if(curl){
        CURLcode _res;
        curl_easy_setopt(curl, CURLOPT_URL, URL);
        perform_request(curl);
    }
}

//TODO USE DOMAIN NAME TO PUT FILE INTO DIRECTORY NAMED BY URL DOMAIN (mkdir DOMAIN_NAME/FILE_NAME)
void write_file(char* URL){
    FILE* img_file;
    CURL* curl = curl_easy_init();
    char* directory_name = url_get_domain(URL);
    printf("%s", directory_name);
    int mkdir_status;
    char* _file_name = "tmp_file";
    char* _type = get_content_type(URL);
    int sep_pos = 0;
    int size = 0;
    //GETTING THE POSITION OF "/" OF THE MIME CONTENT TYPE
    //end of the extension in case of multiple content type
    int end = 0;
    for(int i = 0 ; i < strlen(_type) ; i++){
        if(_type[i] == 59){
            end = i;
            break;
        }
        if(_type[i] == 47){
            sep_pos = i;
            size = strlen(_type) - i;
        }
    }

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
    //_file_name =
    url_get_domain(URL);
    char* full_file_name = malloc(sizeof(char*) * strlen(_file_name) + sizeof(char*) * 2 + sizeof(char*) * strlen(img_type) + sizeof(char*) * strlen(directory_name));
    strcpy(full_file_name, directory_name);
    strcat(full_file_name, "/");
    strcat(full_file_name, _file_name);
    strcat(full_file_name, ".");
    strcat(full_file_name, img_type);

    //CREATING DIRECTORY TO SAVE SCRAPPED CONTENT
    mkdir(directory_name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    //WRITE DATA INTO FILE
    img_file = fopen(full_file_name, "wb");
    if(img_file != NULL && curl){
        curl_easy_setopt(curl, CURLOPT_URL, URL);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, img_file);
        CURLcode _res = perform_request(curl);
        if(_res){
            printf("%d", _res);
        }
    }
    curl_easy_cleanup(curl);
    fclose(img_file);
}

char* url_get_domain(char* URL){
    printf("%s", URL);
    int slash_pos = 0;
    int end_slash_pos = 0;
    int domain_size = 0;
    char* domain;
    for(int i = 0 ; i < strlen(URL) ; i++){
        //ASCII 47 -> /
        if(URL[i] == 47 && URL[i + 1] == 47){
            slash_pos = i;
        } else if (URL[i] == 47 && URL[i + 1] != 47 && URL [i - 1] != 47) {
            end_slash_pos = i;
            break;
        }
    }
    for (int i = slash_pos + 2 ; i < end_slash_pos; i++){
        domain_size++;
    }
    domain = malloc(sizeof(char* ) * domain_size - 2);
    int j = 0;
    for(int i = slash_pos + 2; i < end_slash_pos; i++){
        domain[j] = URL[i];
        j++;
    }
    printf("%s", domain);
    return domain;
}






