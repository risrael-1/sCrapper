//
// Created by Julien Guillan on 24/10/2019.
//

#ifndef SCRAPPER_SCRAPPER_H
#define SCRAPPER_SCRAPPER_H

#include <curl/curl.h>
#include <stdio.h>
#include <ntsid.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

//LIBCURL USEFULL METHODS
static size_t header_callback(char* buffer, size_t size, size_t nitems, void * userdata);
void get_header_data(char* url);
char* get_content_type(char*url);
char* get_content_page(char* url);
long get_response_code(char* url);
char* url_get_domain(char* url);
CURLcode perform_request(CURL* curl);

char* get_string_part(int start, char* line, char char1, char char2);
char** get_hyperlinks(char* URL);

char* write_file(char* URL);

//SCRAPPER METHODS
void scrapp(char* URL, char* type);

#endif //SCRAPPER_SCRAPPER_H
