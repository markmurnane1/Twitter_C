//
// Created by Mark Murnane & Elliot Brighton on 21/04/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "twitter_create.h"
#include "twitter_functionality.h"

//int x change to pointer to user
void menu(twitter * twitter_system, int x){
    int y = 0;
    void (*f[5])(twitter * twitter_system, int x) = {postTweet, getNewsFeed, follow, unfollow, delete};

    while(y >= 0 && y < 5){
        printf("\n%s %s\n", twitter_system->users[x].username, "is currently logged in");
        printf("%d followers; %d following\n\n", twitter_system->users[x].num_followers, twitter_system->users[x].num_following);
        printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n", "Enter 0 to post a tweet", "Enter 1 to view news feed", "Enter 2 to follow a user", "Enter 3 to unfollow a user", "Enter 4 to delete your account", "Enter 5 to end turn", "Enter 6 to end twitter");
        scanf("%d", &y);
        fflush(stdin);

        if(y == 5){
            if(twitter_system->num_users < 2){
                printf("%s\n", "There are no other users to switch to");
            } else {
                x = endTurn(twitter_system, x);
            }
        } else if(y == 6){
            endTwitter();
        } else if(y == 3 && twitter_system->users[x].num_following == 0){
            printf("%s\n", "You aren't following anyone");
        }else {
            (*f[y])(twitter_system, x);
        }

    }

    menu(twitter_system, x);
}

void getNewsFeed(twitter * twitter_system, int x){
//complete
}

void postTweet(twitter * twitter_system, int x){
    printf("%s\n", "enter your tweet [MAX 270 CHARACTERS]");
    char tw[TWEET_LENGTH];
    fgets(tw, TWEET_LENGTH, stdin);

    // add statement terminator
    if(tw[strlen(tw)-1]=='\n'){
        tw[strlen(tw)-1]='\0';
    }

    // add message to new tweet
    tweet *nTweet = malloc(sizeof(tweet));
    strcpy(nTweet->msg, tw);

    // give time stamp & user
    nTweet->id = twitter_system->num_tweets;
    strcpy(&nTweet->user, twitter_system->users[x].username);

    // add to news feed
    twitter_system->news_feed[twitter_system->num_tweets++] = *nTweet;

    puts("");

}

void follow(twitter * twitter_system, int x){
    bool matchFound = false;
    printf("%s\n", "Follow suggestions:");
    for(int i = 0; i < twitter_system->num_users; i++){
        if(strcmp(twitter_system->users[i].username, twitter_system->users[x].username) != 0){
            printf("%s\n", twitter_system->users[i].username);
        }
    }

    puts("");

    char username[USR_LENGTH];
    printf("%s\n", "Enter the username of the user you want to follow");

    fgets(username, USR_LENGTH, stdin);
    if(username[strlen(username)-1]=='\n'){
        username[strlen(username)-1]='\0';
    }

    //search for user in user array
    if(strcmp(username, twitter_system->users[x].username)==0){
        printf("%s\n\n", "You can't follow yourself");
    } else {
        for(int i = 0; i < twitter_system->num_users; i++){
            //search for username in users array, if they exist...
            if(strcmp(username, twitter_system->users[i].username)==0){
                int k = 0;
                // match found...
                while(k<twitter_system->users[x].num_following){
                    if(strcmp(username, twitter_system->users[x].following[k]) == 0){
                        printf("%s\n", "You already follow this person");
                        matchFound = true;
                    }
                    k++;
                }

                if(matchFound){
                    break;
                }

                //increment followers & following
                strncpy(twitter_system->users[i].followers[twitter_system->users[i].num_followers], twitter_system->users[x].username, strlen(twitter_system->users[x].username));
                twitter_system->users[i].num_followers++;

                strncpy(twitter_system->users[x].following[twitter_system->users[x].num_following], twitter_system->users[i].username, strlen(twitter_system->users[i].username));
                twitter_system->users[x].num_following++;

                printf("%s %s\n", username, "has been followed");


            }

            //made it to the end of the array without finding a match.
            if((twitter_system->num_users==i) && strcmp(username, twitter_system->users[i].username)!=0){
                printf("%s\n", "User not found");
            }
        }
    }

}

void unfollow(twitter * twitter_system, int x){
    printf("%s\n", "People you follow:");
    for(int i = 0; i < twitter_system->users[x].num_following; i++){
        printf("%s\n", twitter_system->users[x].following[i]);
    }

    puts("");

    char username[USR_LENGTH];
    printf("%s\n", "Enter the username of the user you want to unfollow");

    fgets(username, USR_LENGTH, stdin);
    if(username[strlen(username)-1]=='\n'){
        username[strlen(username)-1]='\0';
    }

    //search for user
    if(strcmp(username, twitter_system->users[x].username)==0){
        printf("%s\n", "You can't unfollow yourself");
    } else {
        for(int i = 0; i < twitter_system->users[x].num_following; i++){
            if(strcmp(username, twitter_system->users[x].following[i])==0){
                //number of users followed after this one in following list
                int k = (twitter_system->users[x].num_following - i);

                if(i == twitter_system->users[x].num_following-1){
                    twitter_system->users[x].num_following--;
                    break;
                } else if(k > 1){
                    for(int j = i; j < k; j++){
                        strcpy(twitter_system->users[x].following[j], twitter_system->users[x].following[j+1]);
                    }
                    twitter_system->users[x].num_following--;
                }


            }

            //made it to the end of the array without finding a match.
            if((twitter_system->num_users==i) && strcmp(username, twitter_system->users[i].username)!=0){
                printf("%s\n", "User not found");
            }

        }
    }
}

void delete(twitter * twitter_system, int x){
//complete
}

int endTurn(twitter * twitter_system, int x){
    printf("%s\n", "Users:");
    for(int i = 0; i < twitter_system->num_users; i++){
        printf("%s\n", twitter_system->users[i].username);
    }

    char username[USR_LENGTH];
    printf("%s\n", "Enter the username of the user to be signed in");

    fgets(username, USR_LENGTH, stdin);
    if(username[strlen(username)-1]=='\n'){
        username[strlen(username)-1]='\0';
    }

    //search for user in user array
    for(int i = 0; i < twitter_system->num_users; i++){
        if(strcmp(username, twitter_system->users[i].username)==0){
            //sign in new user
            return i;
        }

        //made it to the end of the array without finding a match.
        if((twitter_system->num_users==i) && strcmp(username, twitter_system->users[i].username)!=0){
            printf("%s\n", "User not found");
            //return control to original user
            return x;
        }
    }
}



void endTwitter(void){
    printf("Ending twitter...\n");
    exit(0);
}



