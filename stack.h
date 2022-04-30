//
// Created by markm on 26/04/2022.
//



#ifndef SEP2_2022_STACK_H
#define SEP2_2022_STACK_H


#endif //SEP2_2022_STACK_H

#include "twitter_create.h"

void push(tweetPtr *newTweet, tweetPtr *sPtr);//insert new node
int pop(tweetPtr *sPtr, user *x); // delete all tweets by this user
void printList(tweetPtr currentPtr, user *x);