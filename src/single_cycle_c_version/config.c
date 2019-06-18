#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#define BUFFER_SIZE 100

void init_config(struct core* cores, FILE *cfp){
    /* Parse the configuration file and store the data into a core structure*/
    /* Data to store: core id, core freq*/
    /* Sample input:
     * number_of_cores: 1
     * frequency: 0.5
     * */
    char buffer[BUFFER_SIZE];
    int count = 0;
    while(fgets(buffer, 100, cfp)){
        if(!count){
            char* token;
            char* rest = buffer;
            while(token = strtok_r(rest, ":", &rest)){
                               
            }
        }
        if(count == 1){
            printf("%s\n", buffer);
        }
        count++;
    }

}
