#include <stdio.h>
#include "twitter_create.h"


int main() {

    twitter twitter_system;
    create_twitter_system(&twitter_system);

    // create & record addition to user list
    for(int i = 0; i<3; i++){
        New_user(&twitter_system);
    }


    // print user details
    for(int i = 0; i < twitter_system.num_users; i++){
        user usr = twitter_system.users[i];
        printf("\nUser: %sFollowers: %d; Following: %d", usr.username, usr.num_followers, usr.num_followers );
    }

    puts("");

    return 0;

}
