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

//LIBCURL USEFULL METHODS
static size_t header_callback(char* buffer, size_t size, size_t nitems, void * userdata);
void get_header_data(char* url);
char* get_content_type(char*url);
char* get_content_page(char* url);
long get_response_code(char* url);
CURLcode perform_request(CURL* curl);
void write_img();

//SCRAPPER METHODS
void scrapp(char* URL, char* type);

#endif //SCRAPPER_SCRAPPER_H
