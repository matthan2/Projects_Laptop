#pragma once
#include "LinkedList.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

/*name: readFile
Pre: Takes in a linked list by reference may or may not be empty
Post: Asks the user for file name. Tries to open the file and read the file
into a linked list. File may be any size. File contains int and string on each line
*/
void readFile(LinkedList &list);
/*
name: displayMessage
Pre: Requires a linked list (encrypted message)
Post: Displays the "raw" message - which has all the nodes still it in.
*/
void displayMessage(LinkedList &list);
/*
name: mainMenu
Pre: Requires a linked list (passed by reference)
Post: None
*/
void mainMenu(LinkedList &list);
/*
name: exitLinked
Pre: Requires a linked list (passed by reference) (to deallocate)
Post: list is deallocated and the application is exited.
*/
void exitLinked(LinkedList &list);
/*
name: displayEncrypt
Pre: Requires a linked list (an encrypted message)
Post: Displays only the decrypted message by creating a new linked list
and copying only the perfect squares and perfect cubes to it.
The new linked list with "real" clues is then sorted to display the message.
When this is done running the original message is still available in list.
The new linked list is deallocated.
*/
void displayEncrypt(LinkedList &list);


