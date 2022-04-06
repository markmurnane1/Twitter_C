//
// Created by Lili on 30/03/2022.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "twitter_create.h"

void create_twitter_system(twitter * twitter_system){

    //to be completed

}

// create new user
user *New_user(char username[USR_LENGHT]) //Initializing a new user
{
    user *user1 = malloc(sizeof(user));

    strcpy(user1->username, username);

    user1->num_followers = 0;
    user1->num_following = 0;

    userList[numUsers] = user1;

    // record addition to user list
    numUsers++;

    return user1;
}


// output user info
void print_info(user *user_data)
{
    printf("\nUsername: %s", user_data->username);
    printf("\nFollowers: %d", user_data->num_followers);
    printf("\nFollowing: %d", user_data->num_following);
    printf("\n\n");
}