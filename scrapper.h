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

static size_t header_callback(char* buffer, size_t size, size_t nitems, void * userdata);
void get_header_data(char* url);
long get_response_code(char* url);
#endif //SCRAPPER_SCRAPPER_H
