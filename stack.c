//
// Created by markm on 26/04/2022.
//

#include "stack.h"
#include "twitter_create.h"
#include <stdlib.h>
#include <stdio.h>

void push(tweet *nTweet)
{
    struct node *link = (struct node*) malloc(sizeof(struct node));
    link->nTweet = *nTweet;
    link->next = head;
    head = link;
}
void pop(tweet *nTweet)
{
    struct node *tempLink = head;

    head = head->next;

    free(tempLink);
}
void printList()
{
    struct node *ptr = head;

    while(ptr != NULL)
    {
        printf("%s\n", ptr->nTweet.msg);
        ptr = ptr->next;
    }
}