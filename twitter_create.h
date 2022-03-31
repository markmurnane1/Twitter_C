//
// Created by Lili on 30/03/2022.
//

#ifndef ASSIGNMENT2_TWITTER_CREATE_H
#define ASSIGNMENT2_TWITTER_CREATE_H

#endif //ASSIGNMENT2_TWITTER_CREATE_H

//Max length of a tweet
#define TWEET_LENGTH 270

//Max length of a username
#define USR_LENGHT 100

//Max num of a followers
#define MAX_FOLLOWERS 30

//Max num of following users
#define MAX_FOLLOWING 30

//Max num of tweets in the news feed
#define MAX_TWEETS 100

//Max num of users
#define MAX_USERS 100

typedef struct tweet{
    int id;
    char msg[TWEET_LENGTH];
    char user[USR_LENGHT];

}tweet;

typedef struct user{
    char username[USR_LENGHT];

    char followers[MAX_FOLLOWERS];
    int num_followers;

    char following[MAX_FOLLOWING];
    int num_following;
}user;

typedef struct twitter{
   // to be completed

   user user_list[MAX_USERS];
   tweet tweet_list[MAX_TWEETS];

} twitter;

void create_twitter_system(twitter * twitter_system);

user *New_user(char username[USR_LENGHT]);

void print_info(user *user_data);

static unsigned numUsers = 0;
static user *userList[MAX_USERS];