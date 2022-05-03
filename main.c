/*
 * Created by Elliot Brighton & Mark Murnane
 * Twitter System
 */

#include <stdio.h>
#include "twitter_create.h"
#include "twitter_functionality.h"


int main() {

    twitter twitter_system;
    create_twitter_system(&twitter_system);

    //prompt user to create accounts
    unsigned int x = 0;
    while(x >= 0) {
        if(twitter_system.num_users<MAX_USERS){
            printf("%s\n", "Enter 1 to create new user; enter 2 to end user creation process");
            printf("%s", "?:");
            scanf("%u", &x);
            fflush(stdin);
        } else {
            menu(&twitter_system, 0);
        }

        switch (x) {
            case 1:
                create_new_user(&twitter_system);
                break;
            case 2:
                if(twitter_system.num_users<1){
                    printf("%s\n", "No users found, please create a user to continue");
                } else {
                    menu(&twitter_system, 0);
                }
                break;
            default:
                printf("%s\n", "Invalid input");
                break;
        }
    }

    return 0;
}