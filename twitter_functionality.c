//
// Created by Elliot Brighton & Mark Murnane on 21/04/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "twitter_create.h"
#include "twitter_functionality.h"
#include "stack.h"


void menu(twitter * twitter_system, int x){
    tweetPtr sPtr = NULL;
    unsigned int y = 0;
    instructions();

    while(y >= 0){
        printf("\n%s %s\n", twitter_system->users[x].username, "is currently logged in");
        printf("%d followers; %d following\n\n", twitter_system->users[x].num_followers, twitter_system->users[x].num_following);
        printf("%s", "?:");
        scanf("%u", &y);
        fflush(stdin);

        switch(y){
            case 0:
                instructions();
                break;
            case 1:
                postTweet(twitter_system, x, &sPtr);
                break;
            case 2:
                if(twitter_system->num_tweets<1){
                    printf("%s\n", "No tweets have been posted yet");
                } else {
                    printList(sPtr, &twitter_system->users[x]);
                }
                break;
            case 3:
                if(twitter_system->num_users < 2){
                    printf("%s\n", "There are no other users to follow");
                } else {
                    follow(twitter_system, x);
                }
                break;
            case 4:
                if(twitter_system->users[x].num_following == 0){
                    printf("%s\n", "Following list empty");
                } else {
                    unfollow(twitter_system, x);
                }
                break;
            case 5:
                if(twitter_system->num_users < 2){
                    printf("%s\n", "There are no other users to switch to");
                } else {
                    x = endTurn(twitter_system, x);
                    instructions();
                }
                break;
            case 6:
                x = delete(&sPtr, twitter_system, x);
                break;
            case 7:
                endTwitter();
                break;
            default:
                printf("%s\n\n", "Invalid entry");
                instructions();
                break;
        }

    }

}

void instructions(void){
    printf("\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
           "Enter 0 to view instructions",
           "Enter 1 to post a tweet",
           "Enter 2 to view news feed",
           "Enter 3 to follow a user",
           "Enter 4 to unfollow a user",
           "Enter 5 to end turn",
           "Enter 6 to delete your account",
           "Enter 7 to end program");
}

void postTweet(twitter * twitter_system, int x, tweetPtr *sPtr){
    printf("%s\n", "enter your tweet [MAX 270 CHARACTERS]");
    char tw[TWEET_LENGTH];
    fgets(tw, TWEET_LENGTH, stdin);
    // add statement terminator
    if(tw[strlen(tw)-1]=='\n'){
        tw[strlen(tw)-1]='\0';
    }

    // add message to new tweet
    tweetPtr newTweet = malloc(sizeof(Tweet));
    if(newTweet != NULL){
        // copy from string
        strcpy(newTweet->msg, tw);
        // give time stamp & user
        newTweet->id = (twitter_system->num_tweets++)+1;
        strcpy(newTweet->user, twitter_system->users[x].username);

        // add to linked list
        push(&newTweet, sPtr);

    } else {
        printf("%s\n", "Failed to create tweet, no memory available");
    }

}

void follow(twitter * twitter_system, int x){
    bool matchFound = false, isAlreadyFollowing = false;
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
                        isAlreadyFollowing = true;
                    }
                    k++;
                }

                matchFound = true;
                if(isAlreadyFollowing){
                    break;
                }

                //increment followers & following
                strncpy(twitter_system->users[i].followers[twitter_system->users[i].num_followers], twitter_system->users[x].username, strlen(twitter_system->users[x].username));
                twitter_system->users[i].num_followers++;

                strncpy(twitter_system->users[x].following[twitter_system->users[x].num_following], twitter_system->users[i].username, strlen(twitter_system->users[i].username));
                twitter_system->users[x].num_following++;

                printf("%s %s\n", username, "has been followed");


            }
        }
            //made it to the end of the array without finding a match.
            if(!matchFound){
                printf("%s\n", "User not found");
            }
    }

}

void unfollow(twitter * twitter_system, int x){
    bool matchFound = false;
    printf("%s\n", "People you follow:");
    for(int i = 0; i < twitter_system->users[x].num_following; i++){
        printf("%s\n", twitter_system->users[x].following[i]);
    }

    puts("");

    char username[USR_LENGTH];
    printf("%s\n", "Enter the username of the user you want to unfollow");

    fgets(username, USR_LENGTH, stdin);
    fflush(stdin);

    if(username[strlen(username)-1]=='\n'){
        username[strlen(username)-1]='\0';
    }

    //search for user
    if(strcmp(username, twitter_system->users[x].username)==0){
        printf("%s\n", "You can't unfollow yourself");
    } else {
        for(int i = 0; i < twitter_system->users[x].num_following; i++){
            if(strcmp(username, twitter_system->users[x].following[i])==0){
                matchFound = true;
                //number of users followed after this one in following list
                int k = (twitter_system->users[x].num_following - i);

                if(i == twitter_system->users[x].num_following-1){
                    printf("%s %s\n", username, "has been unfollowed");
                    twitter_system->users[x].num_following--;
                    break;
                } else if(k > 1){
                    for(int j = i; j < k; j++){
                        strcpy(twitter_system->users[x].following[j], twitter_system->users[x].following[j+1]);
                    }
                    printf("%s %s\n", username, "has been unfollowed");
                    twitter_system->users[x].num_following--;
                }

            }
        }
        //made it to the end of the array without finding a match.
        if(!matchFound){
            printf("%s\n", "User not found");
        }

    }
}

int delete(tweetPtr *sPtr , twitter * twitter_system, int x){
    int y=0;

    printf("%s\n%s\n", "Are you sure you want to delete your account? This action cannot be undone", "1 to continue; 2 to cancel");

    scanf("%d", &y);
    fflush(stdin);

    while(y != 2){
        if(y == 1){
            for(int i = 0; i < twitter_system->num_users; i++){
                // loop through user array
                for(int j = 0; j < twitter_system->users[i].num_followers; j++){
                    // if this user is found on another user's follower list
                    if(strcmp(twitter_system->users[x].username, twitter_system->users[i].followers[j])==0){
                        // overwrite this user
                        for(int k = j; k < twitter_system->users[i].num_followers-1; k++){
                            strcpy(twitter_system->users[i].followers[k], twitter_system->users[i].followers[k + 1]);
                        }
                        twitter_system->users[i].num_followers--;
                        break;
                    }
                }

                for(int j = 0; j < twitter_system->users[i].num_following; j++){
                    // if this user is found on another user's following list
                    if(strcmp(twitter_system->users[x].username, twitter_system->users[i].following[j])==0){
                        // overwrite this user
                        for(int k = j; k < twitter_system->users[i].num_following-1; k++){
                            strcpy(twitter_system->users[i].following[k], twitter_system->users[i].following[k + 1]);
                        }
                        twitter_system->users[i].num_following--;
                        break;
                    }
                }

            }

            // remove user tweets from linked list
            while(twitter_system->num_tweets>0){
                int n = pop(sPtr, &twitter_system->users[x]);
                if(n==0){
                    break;
                } else {
                    twitter_system->num_tweets -= n;
                }
            }

            // remove from user list
            if(twitter_system->num_users>1){
                for(int i = x; i < twitter_system->num_users; i++) {
                    twitter_system->users[i] = twitter_system->users[i+1];
                }
            }

            // decrement number of users
            twitter_system->num_users--;

            // sign in next user or end program
            if(twitter_system->num_users==0){
                printf("%s\n", "No users left to switch to");
                endTwitter();
            } else {
                printf("%s\n", "Account deleted. Signing in next user...");
                return 0;
            }

        } else if (y != 2) {
            printf("%s\n%s\n", "Invalid input. Please try again", "1 to continue; 2 to cancel");
            scanf("%d", &y);
            fflush(stdin);
        }
    }

    return x;

}

int endTurn(twitter * twitter_system, int x){
    printf("%s\n", "Users:");
    for(int i = 0; i < twitter_system->num_users; i++){
        printf("%s\n", twitter_system->users[i].username);
    }

    puts("");

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

    }
    //made it to the end of the array without finding a match.
    printf("%s\n", "User not found");
    //return control to original user
    return x;

}

void endTwitter(void){
    printf("Ending twitter...\n");
    exit(0);
}



