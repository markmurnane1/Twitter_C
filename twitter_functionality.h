//
// Created by Elliot Brighton & Mark Murnane on 21/04/2022.
//

#ifndef COMP10050_TWITTER_FUNCTIONALITY_H
#define COMP10050_TWITTER_FUNCTIONALITY_H

#endif //COMP10050_TWITTER_FUNCTIONALITY_H

void menu(twitter * twitter_system, int x);

void getNewsFeed(twitter * twitter_system, int x, tweetPtr currentPtr);
void postTweet(twitter * twitter_system, int x, tweetPtr *sPtr);

void follow(twitter * twitter_system, int x);
void unfollow(twitter * twitter_system, int x);

int delete(tweetPtr *sPtr, twitter * twitter_system, int x);
int endTurn(twitter * twitter_system, int x);

void instructions(void);
void endTwitter(void);
