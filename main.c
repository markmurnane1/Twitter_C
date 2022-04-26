/*
 * Created by Mark Murnane & Elliot Brighton
 * Twitter System
 */

#include <stdio.h>
#include "twitter_create.h"
#include "twitter_functionality.h"


int main() {

    twitter twitter_system;
    create_twitter_system(&twitter_system);

    //prompt user to create accounts
    int x = 0;
    while(x<2){
        printf("%s\n", "Enter 1 to create new user; enter 2 to end input");

        //user choice
        scanf("%d", &x);
        fflush(stdin);

        if(x==1){
            create_new_user(&twitter_system);
        }

    }


    menu(&twitter_system, 0);


//    for(int i =0; i < twitter_system.num_users; i++){
//        user usr = twitter_system.users[i];
//        printf("User: %s\nFollowers: %d; Following: %d", usr.username, usr.num_followers, usr.num_followers);
//        puts("");
//    }


    return 0;
}