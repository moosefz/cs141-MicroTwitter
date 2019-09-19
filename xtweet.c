//Name: Mustafa Fawaz
//Date: 8-5-19
//Purpose: Function file for micro-twitter program
//All functions to be placed in here

//Tweet structure
typedef struct microTweet{
  int id;
  char created_at[51];
  char text[141];
  char user[21];

  struct microTweet *next;
} tweetNode;

int countChar(char *char, char key){
  int count=0;

  while(*char){
    if(*char == key)
      count++;
      *char++;
  }
  return count;
}


//Header file structure
typedef struct tweetHeader{
  int count;
}Header;

//Create new tweet
tweetNode *createTweet(char username[], int size, int uniqueID){

  //UTC time function setup - pulled from time.h header
  time_t now = time(&now);
  struct tm *ptm = gmtime(&now);

  //Allocate memory for each stored tweet, size of tweetNode
  tweetNode *tweet = (tweetNode*)malloc(sizeof(tweetNode));

  //Assign ID to tweet
  tweet->id=uniqueID;

  //Assign user to tweet - this needs to be based on logged in user
  strcpy(tweet->user, username);

  printf("\nType a tweet (140 characters or less): \n");
  scanf(" %[^\n]s", tweet->text);
  //Assign UTC date and time for each tweet
  strcpy(tweet->created_at, asctime(ptm));

  tweet->next = NULL;

  return tweet;
}

//Function to create a new tweet, combined with createTweet
void insertTweetAtHead(tweetNode **head, char username[], int size, int uniqueID){

    tweetNode * tweetInfo = createTweet(username, size, uniqueID);
    //Assign head to values of productInfo IF it's the first value
    if(*head==NULL){
      *head = tweetInfo;
    }
    //Otherwise, make the current value the head (start) and store the value of the
    //next address.
    else{
      tweetInfo->next = *head;
      *head = tweetInfo;
    }
}

void searchTweet(tweetNode *head){
  //Search linked list tweets for keyword string, if match, display strings
  //strstr function handles this
  char key[20];
  char *search;
  tweetNode *current = head;
  int count=0;

  printf("\nPlease enter the search keyword: ");
  scanf("%s", key);

  printf("\nResults: \n");

  //Search for matching string/keyword
  while(current != NULL){
    search = strstr(current->text, key);
    if(search != NULL){
      printf("\n--------------------------");
      printf("\n%s\n@%s\n", current->user, current->user);
      printf("\n>> %s", current->text);
      printf("\n\nid: %d :: %s", current->id, current->created_at);
      count++;
    }
    current = current->next;
  }
  if(count==0)
    printf("\nNo matches found! Please try a different keyword.\n");
}

//Prints tweets from linkedlist
void printTweets(tweetNode *head){

  if(head==NULL)
    return;
  else{
      //Print all tweet criteria
      printf("\n--------------------------");
      printf("\n%s\n@%s\n", head->user, head->user);
      printf("\n>> %s", head->text);
      printf("\n\nid: %d :: %s", head->id, head->created_at);
      printTweets(head->next);
  }
}

//Count linked list size
int listSize(tweetNode *head){
  int count = 0;

  while(head != NULL){
    head = head->next;
    count+=1;
  }
  return count;
}

//Wipe linked list
void clearList(tweetNode **head){
  tweetNode *current = *head;

  while(current != NULL){
    current = current -> next;
    free(*head);
    *head = current;
  }
}

//Sorting linkedlist after loading to ensure they are stored in the correct order
//Descending with recent at top
void sortList(tweetNode *head){
  tweetNode *current;
  tweetNode *after;
  tweetNode temp;

  //Sort based on ID in descending order - newest first
  for(current = head; current -> next != NULL; current = current->next){
    for(after = current->next; after != NULL; after=after->next){
      if(current->id < after->id){
        temp->id=current->id;
        strcpy(temp.user,current->user);
        strcpy(temp.text,current->text);
        strcpy(temp.created_at,current->created_at);

        current->id=after->id;
        strcpy(current->user,after->user);
        strcpy(current->text,after->text);
        strcpy(current->created_at,after->created_at);

        after->id=temp.id;
        strcpy(after->user,temp.user);
        strcpy(after->text,temp.text);
        strcpy(after->created_at,temp.created_at);
      }
    }
  }
}

//ALL READ AND WRITE FUNCTIONS BELOW
//-----------------------------------------------

//Saving tweets to file
void writeToFile(tweetNode *head, Header fileHeader){

  char fileName[40];

  printf("\nEnter the desired filename: ");
  scanf("%s", fileName);

  FILE *fptr = fopen(fileName, "wb");
  int counter = 0;
  tweetNode *current = head;

  //Count the size of current linkedlist and save to file header
  fileHeader.count += listSize(head);
  //printf("%d", fileHeader.count);

  //Write the size of the header to the file
  fwrite(&fileHeader, sizeof(fileHeader),1, fptr);

  while(current != NULL){
    //Write each instance of current to file until NULL is reached
    fwrite(current, sizeof(tweetNode),1, fptr);
    current = current->next;
    counter++;
  }
  fclose(fptr);
  //Print how many tweets saved.
  printf("\n%d tweets saved successfully.\n", counter);
}


int loadFromFile(tweetNode **head, Header fileHeader){

  //Store filename
  char fileName[40];

  //Request filename
  printf("\nEnter the filename (incl extension). If local, enter filename only: ");
  scanf("%s", fileName);

  //Open file
  FILE *fptr = fopen(fileName, "rb");

  //If fptr is null, file is not found. Return and break.
  if(fptr == NULL){
    printf("%s not found. Please try another file name.\n", fileName);
    return 1;
  }
  else{
    printf("\nFile Opened Successfully.");

    //Clear any existing linkedlist - free heap
    clearList(head);

    //Read fileheader
    fread(&fileHeader, sizeof(Header),1, fptr);

    int size = fileHeader.count;
    printf("\nTweet count = %d\n", size);

    tweetNode p;
    tweetNode *ptr;

    //Clear any existing linkedlist - free heap
    clearList(head);

    //Begin writing file contents to local linkedlist
    for(int i=0; i<size; i++){

      fread(&p, sizeof(tweetNode),1, fptr);

      ptr = (tweetNode*)malloc(sizeof(tweetNode));
      ptr->id = p.id;
      strcpy(ptr->user, p.user);
      strcpy(ptr->text, p.text);
      strcpy(ptr->created_at, p.created_at);

      if(*head==NULL){
        *head = ptr;
      }else{
        ptr->next = *head;
        *head = ptr;
      }
    }
  }
  fclose(fptr);
  return 0;
}
