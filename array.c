//
// Created by Elliot Brighton
//

#include <string.h>
#include "array.h"
#include "twitter_create.h"

int search(char username[], user array[], int n){
    for(int i = 0; i < n; i++){
        if(strcmp(username, array[i].username)==0){
            return i;
        }
    }
    // user not found
    return -1;
}

int searchF(char username[], char array[][USR_LENGTH], int n){
    for(int i = 0; i < n; i++){
        if(strcmp(username, array[i])==0){
            return i;
        }
    }
    return -1;
}

void overwrite(char array[][USR_LENGTH], int pos, int n){
    for(int i = pos; i < n; i++){
        strcpy(array[i], array[i+1]);
    }
}

