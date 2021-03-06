# cs141-MicroTwitter
Micro-Twitter - Mimics functionality of Twitter in the console. Use of File I/O, Linked Lists, Arrays, etc.

## Overview and Functionality

This *Micro-Twitter* was created during the S2019 semester in CS141 - Algorithms and Programming II at the University of Windsor. The program was created to demonstrate the use of linked list data structure along with file I/O in C. 

Once compiled, users are prompted to "log-in". There is no database with logins as this is simply for a name capture. Once "logged-in", users are prompted with the following options:
1. Create new Tweet
   - 140 character maximum tweet. Tweet is added to linked list with the username, date and time it was created.
2. Search Tweets
   - Searches the linked list for keywords relative to user input.
3. Display Tweets
   - Prints linked list to console in descending order.
4. Save tweets to file
   - Tweets are saved to a file (error checking is present)
5. Load tweets from file
   - Tweets are loaded from an existing file (error checking is present)
6. Exit
   - Close program.
