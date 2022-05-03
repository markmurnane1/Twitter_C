//
// Created by ellc2 on 03/05/2022.
//

#ifndef COMP10050_ARRAY_H
#define COMP10050_ARRAY_H

#endif //COMP10050_ARRAY_H

#include "twitter_create.h"

// search user array
int search(char username[], user array[], int n);

// search follower/following array
int searchF(char username[], char array[][USR_LENGTH], int n);

// delete user from array
void overwrite(char array[][USR_LENGTH], int pos, int n);
