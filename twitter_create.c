//
// Created by Lili on 30/03/2022.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "twitter_create.h"

void create_twitter_system(twitter * twitter_system){
    // set of all users and tweets - change to linked lists later
    twitter_system->users[MAX_USERS];
    twitter_system->tweets[MAX_TWEETS];
    twitter_system->num_users = 0;
    twitter_system->num_tweets = 0;
}


user *New_user(twitter * twitter_system){ //Initializing a new user
    char username[USR_LENGHT];

    printf("%s %s\n", "Enter Username", "[press <ENTER> to end input]");

    // read username from console
    fgets(username, USR_LENGHT, stdin);

    // init new user
    user *usr = malloc(sizeof(user));

    strcpy(usr->username, username);

    usr->num_followers = 0;
    usr->num_following = 0;

    // add new user to twitter system
    twitter_system->users[twitter_system->num_users++] = *usr;


    return usr;
}


/* output user info
void print_info(user *user_data)
{
    printf("\nUsername: %s", user_data->username);
    printf("\nFollowers: %d", user_data->num_followers);
    printf("\nFollowing: %d", user_data->num_following);
    printf("\n\n");
}
 */