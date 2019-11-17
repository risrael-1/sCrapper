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
/**
 * Call called in get_header_data() function
 * @param buffer
 * @param size
 * @param nitems
 * @param userdata
 * @return
 */
static size_t header_callback(char* buffer, size_t size, size_t nitems, void * userdata);

/**
 * Get the data of header
 * @param url
 */
void get_header_data(char* url);

/**
 * Get the content type form MIME in HEADER
 * @param url
 * @return
 */
char* get_content_type(char*url);

char* get_content_page(char* url);
/**
 * Get HTTP response code
 * @param url
 * @return
 */
long get_response_code(char* url);

/**
 * Get only domain from URL
 * @param url
 * @return
 */
char* url_get_domain(char* url);

/**
 * Perform request of curl given in argument
 * @param curl
 * @return
 */
CURLcode perform_request(CURL* curl);

/**
 * Split string between two characters given in argument
 * @param start
 * @param line
 * @param char1
 * @param char2
 * @return
 */
char* get_string_part(int start, char* line, char char1, char char2);

/**
 * Create an array containing all the hyperlinks from a website
 * @param URL
 * @return
 */
char** get_hyperlinks(char* URL);

/**
 * Write into file website scrapped source code
 * @param URL
 * @return
 */
char* write_file(char* URL);

#endif //SCRAPPER_SCRAPPER_H
