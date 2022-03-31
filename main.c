#include <stdio.h>
#include "twitter_create.h"


int main() {

    twitter twitter_system;
    create_twitter_system(&twitter_system);



    //implement here the code to print the users
    // for each user you need to print the username, the number of followers and the number of users that the current user is following
    printf("Enter your username");
    char name[USR_LENGHT];
    scanf("%s", name);

    user *user1 = New_user(name);

    printf("Printing user number %d", numUsers);

    print_info(user1);

    printf("%d", numUsers);

    return 0;
}
