//
// Created by markm on 26/04/2022.
//



#ifndef SEP2_2022_STACK_H
#define SEP2_2022_STACK_H


#endif //SEP2_2022_STACK_H

#include "twitter_create.h"

struct node
{
    tweet nTweet;
    struct node* next;
};

struct node *head;

void push(tweet *nTweet);//insert new node
void pop(tweet *nTweet); //maybe dont need this function because idk if we allow deleting tweets
void printList();