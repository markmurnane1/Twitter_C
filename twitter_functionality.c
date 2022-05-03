//
// Created by Elliot Brighton & Mark Murnane on 21/04/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "twitter_create.h"
#include "twitter_functionality.h"
#include "array.h"
#include "stack.h"


void menu(twitter * twitter_system, int x){
    tweetPtr sPtr = NULL;
    unsigned int y = 0;
    displayStats(twitter_system);
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
                displayStats(twitter_system);
                break;
            case 2:
                postTweet(twitter_system, x, &sPtr);
                break;
            case 3:
                if(twitter_system->num_tweets<1){
                    printf("%s\n", "No tweets have been posted");
                } else {
                    getNewsFeed(twitter_system, sPtr, x);
                }
                break;
            case 4:
                if(twitter_system->num_users < 2){
                    printf("%s\n", "There are no other users to follow");
                } else {
                    follow(twitter_system, x);
                }
                break;
            case 5:
                if(twitter_system->users[x].num_following == 0){
                    printf("%s\n", "You do not follow any accounts");
                } else {
                    unfollow(twitter_system, x);
                }
                break;
            case 6:
                if(twitter_system->num_users < 2){
                    printf("%s\n", "There are no other users to switch to");
                } else {
                    x = endTurn(twitter_system, x);
                    instructions();
                }
                break;
            case 7:
                x = delete(&sPtr, twitter_system, x);
                instructions();
                break;
            case 8:
                endTwitter();
                break;
            default:
                printf("%s\n\n", "Invalid entry");
                instructions();
                break;
        }

    }

}

// display menu options
void instructions(void){
    printf("\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
           "Enter 0 to view instructions",
           "Enter 1 to view all user statistics",
           "Enter 2 to post a tweet",
           "Enter 3 to view news feed",
           "Enter 4 to follow a user",
           "Enter 5 to unfollow a user",
           "Enter 6 to end turn",
           "Enter 7 to delete your account",
           "Enter 8 to end program");
}

void displayStats(twitter * twitter_system){
    puts("");
    for(int i = 0; i < twitter_system->num_users; i++){
        printf("%s: %s; %s: %d; %s: %d\n", "Username", twitter_system->users[i].username, "Following", twitter_system->users[i].num_following, "Followers", twitter_system->users[i].num_followers);
    }
}


// display tweets posted by signed-in user or users they follow
void getNewsFeed(twitter * twitter_system, tweetPtr sPtr, int x){
    printf("%s\n", "Latest tweets");
    printList(sPtr, &twitter_system->users[x]);
}

// create tweet
void postTweet(twitter * twitter_system, int x, tweetPtr *sPtr){
    printf("%s\n", "enter your tweet [MAX 270 CHARACTERS]");
    char msg[TWEET_LENGTH];
    fgets(msg, TWEET_LENGTH, stdin);

    while(strcmp(msg, "\n")==0){
        printf("%s\n", "No tweet entered, please try again");
        fgets(msg, TWEET_LENGTH, stdin);
    }

    // add statement terminator
    if(msg[strlen(msg)-1]=='\n'){
        msg[strlen(msg)-1]='\0';
    }

    // add message to new tweet
    tweetPtr newTweet = malloc(sizeof(Tweet));
    if(newTweet != NULL){
        // copy from string
        strcpy(newTweet->msg, msg);
        // give time stamp & user
        newTweet->id = (twitter_system->num_tweets++)+1;
        strcpy(newTweet->user, twitter_system->users[x].username);

        // add to linked list
        push(&newTweet, sPtr);

    } else {
        printf("%s\n", "Failed to create tweet, no memory available");
    }

}

// add new user to this user's following list
void follow(twitter * twitter_system, int x){
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
        printf("%s\n", "You can't follow yourself");
    } else {
        int k = search(username, twitter_system->users, twitter_system->num_users);
        if (k == -1) {
            printf("%s\n", "User not found");
        } else {
            int j = searchF(username, twitter_system->users[x].following, twitter_system->users[x].num_following);
            if (j != -1) {
                printf("%s\n", "You already follow this account");
            } else {
                // increment followers & following
                strncpy(twitter_system->users[k].followers[twitter_system->users[k].num_followers],
                        twitter_system->users[x].username, strlen(twitter_system->users[x].username));
                twitter_system->users[k].num_followers++;
                strncpy(twitter_system->users[x].following[twitter_system->users[x].num_following],
                        twitter_system->users[k].username, strlen(twitter_system->users[k].username));
                twitter_system->users[x].num_following++;

                printf("%s %s\n", username, "has been followed");
            }

        }
    }
}

// remove user from this user's following list
void unfollow(twitter * twitter_system, int x){
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

    // search for user
    if(strcmp(username, twitter_system->users[x].username)==0){
        printf("%s\n", "You can't unfollow yourself");
    } else {
        int i = searchF(username, twitter_system->users[x].following, twitter_system->users[x].num_following);
        if(i != -1){
            // find position of soon-to-be-unfollowed user in user array
            int k = search(username, twitter_system->users, twitter_system->num_users);
            if(twitter_system->users[x].num_following>=1){
                overwrite(twitter_system->users[x].following, i, twitter_system->users[x].num_following);
            }
            if(twitter_system->users[k].num_followers>=1){
                // find position of user x in follower array
                int j = searchF(twitter_system->users[x].username, twitter_system->users[k].followers, twitter_system->users[k].num_followers);
                overwrite(twitter_system->users[k].followers, j, twitter_system->users[k].num_followers);
            }

            twitter_system->users[x].num_following--;
            twitter_system->users[k].num_followers--;

            printf("%s %s\n", username, "has been unfollowed");

        } else {
            printf("%s\n", "User not found");
        }
    }
}

// remove this user from system
int delete(tweetPtr *sPtr , twitter * twitter_system, int x){
    int y=0;
    printf("%s\n%s\n", "Are you sure you want to delete your account? This action cannot be undone", "1 to continue; 2 to cancel");
    scanf("%d", &y);
    fflush(stdin);

    while(y != 2){
        if(y == 1){
            // loop through user array to check each user's follower list
            for(int i = 0; i < twitter_system->num_users; i++){
                // check if this user is following anyone, remove from follower lists
                if(twitter_system->users[x].num_following!=0){
                    int j = searchF(twitter_system->users[x].username, twitter_system->users[i].followers, twitter_system->users[i].num_followers);
                    if(j!=-1){
                        overwrite(twitter_system->users[i].followers, j, twitter_system->users[i].num_followers);
                        twitter_system->users[i].num_followers--;
                        twitter_system->users[x].num_following--;
                    }
                }

                // check if this user is followed by anyone, remove from following lists
                if(twitter_system->users[x].num_followers!=0){
                    int j = searchF(twitter_system->users[x].username, twitter_system->users[i].following, twitter_system->users[i].num_following);
                    if(j!=-1){
                        overwrite(twitter_system->users[i].following, j, twitter_system->users[i].num_following);
                        twitter_system->users[i].num_following--;
                        twitter_system->users[x].num_followers--;
                    }
                }
            }

            // remove user tweets from linked list
            while(twitter_system->num_tweets>0){
                int n = pop(sPtr, &twitter_system->users[x]);
                // continue until no more tweets by this user are found in linked list
                if(n==0){
                    //if tweets were removed from the linked list then the id's of each tweet need to be reordered
                    reorder(*sPtr, twitter_system->num_tweets);
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

// sign in different user
int endTurn(twitter * twitter_system, int x){
    int j = -1;

    printf("%s\n", "Users:");
    for(int i = 0; i < twitter_system->num_users; i++){
        printf("%s\n", twitter_system->users[i].username);
    }

    puts("");

    while(j == -1) {
        char username[USR_LENGTH];
        printf("%s\n", "Enter the username of the user to be signed in");
        fgets(username, USR_LENGTH, stdin);
        if (username[strlen(username) - 1] == '\n') {
            username[strlen(username) - 1] = '\0';
        }

        // search for user
        if((j = (search(username, twitter_system->users, twitter_system->num_users)))==-1){
            printf("%s\n\n", "User not found");
        } else {
            // sign in new user
            x = j;
        }

    }
    // give control to new user
    return x;
}

// end program
void endTwitter(void){
    printf("\n%s\n", "Ending twitter...");
    exit(0);
}



