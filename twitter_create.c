//
// Created by Lili on 30/03/2022.
//

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "twitter_create.h"
#include "stack.h"

void create_twitter_system(twitter * twitter_system){
    //initialise all values in twitter struct

    twitter_system->news_feed[MAX_TWEETS];
    twitter_system->users[MAX_USERS];
    twitter_system->num_tweets = 0;
    twitter_system->num_users = 0;
}

// create new user
void create_new_user(twitter * twitter_system){
    char username[USR_LENGTH];
    puts("Enter Username: [press <ENTER> to end input]");

    // read username from console and initialise new user w/username + default values
    fflush(stdin);
    //fgets(username, USR_LENGTH, stdin);

    scanf("%s*[^\n]", username); //*[^\n] will ignore the newline char

    //remove newline character
    if(username[strlen(username)-1]=='\n'){
        username[strlen(username)-1]='\0';
    }

    // check if username is free
    if((twitter_system->num_users)>0){
        for(int i = 0; i < twitter_system->num_users; i++){
            // loop through user records, don't let user progress until they enter a username that does not already exist
            if(strcmp(username, twitter_system->users[i].username) == 0){
                while(strcmp(username, twitter_system->users[i].username) == 0){
                    printf("%s\n", "Username taken: please enter a different username");
                    //fgets(username, USR_LENGTH, stdin);
                    scanf("%s*[^\n]", username);
                    if(username[strlen(username)-1]=='\n'){
                        username[strlen(username)-1]='\0';
                    }
                }
            }
        }
    }

    // create user struct
    user *usr = malloc(sizeof(user));
    strcpy(usr->username, username);
    usr->num_followers = 0;
    usr->num_following = 0;

    // add new user to twitter system
    twitter_system->users[twitter_system->num_users++] = *usr;

}