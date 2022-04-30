//
// Created by markm on 26/04/2022.
//

#include "stack.h"
#include "twitter_create.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void push(tweetPtr *newTweet, tweetPtr *sPtr)
{
    tweetPtr prevPtr = NULL;
    tweetPtr currentPtr = *sPtr;

    // latest tweets appear at front of list
    while(currentPtr != NULL && (*newTweet)->id < currentPtr->id){
        prevPtr = currentPtr;
        currentPtr = currentPtr->nextPtr;
    }

    if(prevPtr == NULL){
        (*newTweet)->nextPtr = *sPtr;
        *sPtr = *newTweet;
    } else {
        prevPtr->nextPtr = *newTweet;
        (*newTweet)->nextPtr = currentPtr;
    }

}


int pop(tweetPtr *sPtr, user *x){
        // if tweet is at beginning of list
        if(strcmp(x->username, (*sPtr)->user)==0){
            tweetPtr temp = *sPtr;
            *sPtr = (*sPtr)->nextPtr;
            free(temp);
            return 1;
        } else {
            tweetPtr prevPtr = *sPtr;
            tweetPtr currentPtr = (*sPtr)->nextPtr;

            while(currentPtr != NULL && strcmp(x->username, currentPtr->user)!=0){
                prevPtr = currentPtr;
                currentPtr = currentPtr->nextPtr;
            }

            if(currentPtr!=NULL){
                tweetPtr temp = currentPtr;
                prevPtr->nextPtr = currentPtr->nextPtr;
                free(temp);
                return 1;
            }

        }

    return 0;

}


void printList(tweetPtr currentPtr, user *x)
{
    int j = 0;
    while(currentPtr != NULL && j <= 10)
    {
        for(int i = 0; i <= x->num_following; i++){
            if(strcmp(currentPtr->user, x->following[i])==0 || strcmp(currentPtr->user, x->username)==0){
                // print tweets by users followed by this user or posted by this user
                printf("%d.", currentPtr->id);
                printf("%s: ", currentPtr->user);
                printf("%s\n", currentPtr->msg);
                j++;
                i++;
            }
        }
        currentPtr = currentPtr->nextPtr;
    }
}


void reorder(tweetPtr sPtr, int x){
    // complete
}