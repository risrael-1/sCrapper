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
        if(curl) {
            CURLcode _res;
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
            _res = perform_request(curl);
            if (_res == CURLE_OK) {
                long response_code;
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
                return response_code;
            }
            curl_easy_cleanup(curl);
            return _res;
        }
    return 0;
}


