//Name: Mustafa Fawaz
//Date: 8-5-19
//Purpose: Interactive microtwitter with linked lists. 10 tweets max.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "xtweet.c"

int main()
{
  int selection, uniqueID, sizeLoad, loadRes;
  char username[21];

  tweetNode *head;
  Header fileHeader;

  //Unique ID handled outside the function
  uniqueID = 1;

  fileHeader.count = 0;

  //Create empty linked list.
  head = NULL;

  //User Login
  printf("\nWelcome to micro-twitter! Please login below.");

  printf("\nUsername: ");
  scanf("%[^\n]s", username);

  printf("\nWelcome back %s!\n", username);
  printf("______________________________\n");

  printf("\nMain Menu:");

  while(selection != 6){
    printf("\n1: Create new tweet");
    printf("\n2: Search tweets");
    printf("\n3: Display tweets");
    printf("\n4: Save tweets to file");
    printf("\n5: Load tweets from file");
    printf("\n6: Exit\n");

    scanf("%d", &selection);

    switch(selection)
    {
      case 1: {
          insertTweetAtHead(&head, username, 21, uniqueID);
          //Increment UniqueID for next tweet
          uniqueID++;
        } break;
      case 2: {
        searchTweet(head);
      } break;
      case 3: {
        printTweets(head);
      } break;
      case 4: {
        //ALL TWEETS DELETE AFTER SAVING EXCEPT 1
        writeToFile(head, fileHeader);
      } break;
      case 5: {
        //Load file
        loadRes = loadFromFile(&head, fileHeader);
        //Check to see if file is found. Break to menu if not.
        if(loadRes == 1){
          break;
        }else{
          //Sort for proper order -- could use add node from tail
          sortList(head);
          printTweets(head);
          //Gather size of new tweets
          sizeLoad = listSize(head);
          //Pick up ID where it left off after loading
          uniqueID = sizeLoad+1;
        }
      } break;
      case 6: break; //End program
      default: printf("\nInvalid selection! Please select a valid menu item.\n");
    }
  }
  return 0;
}
