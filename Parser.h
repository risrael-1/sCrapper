//
// Created by Julien Guillan on 12/11/2019.
//

#ifndef SCRAPPER_PARSER_H
#define SCRAPPER_PARSER_H

#include <stdio.h>
#include <ntsid.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <string.h>

int run();

void replaceAccolade(char *string);

char *getInfos(char *line);

int getValue(char *line);

char *getValueBefore(char * info, char character);

#endif //SCRAPPER_PARSER_H
