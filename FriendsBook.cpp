/*
 * FriendsBook.cpp - Assignment 1
 * 
 * Class Description: Social network application.
 *
 * In this version, we use our MyADT to hold and modify profiles
 *
 *
 * Author: MH
 * Modified on: Sept. 28, 2023
 */

#include <iostream>
#include <string>
#include <cctype>
#include "Profile.h"
#include "MyADT.h"

using std::cout;
using std::ws;
using std::cin;
using std::endl;

//function that allows users to create a profile on FriendsBook
//username must not already be in use by other member -> will continue to ask user for
//new username if already taken
void join(MyADT & theMembers) {
   string username;
   string name;
   string email;
   string birthday;
   unsigned int nValue = 0;

   bool available = false;

   cout << "Enter your username, name, email, and birthday" << endl;
   cin >> username;
   cin >> name;
   cin >> email;
   cin >> birthday;
   for(char &c : username){
      c = tolower(c);
   }

   while (!available){
      Profile* user = new Profile(username, name, email, birthday);
      available = theMembers.insert(*user);
      if (!available){
         cout << "Please select a new username: " << endl;
         cin >> username;
         delete user;
      }
      cout<< "welcome to FriendsBook! " << username << endl;
      nValue = theMembers.getN();
      cout << "Number of profiles on network = " << nValue << endl;
   }
}

/*Removes users profile from FriendsBook
Username must be match a current FriendsBook user*/
void leave(MyADT & theMembers) {
   string userName;
   cout << "Enter username of profile to be deleted: " << endl;
   cin >> userName;
   for(char &c : userName){
      c = tolower(c);
   }
   cout << "Deleting profile..." << endl;

   Profile user(userName);
   Profile* current = theMembers.search(user);
      if (current != nullptr){
         theMembers.remove(*current);
         cout << "profile successfully deleted." << endl;
      }
}

/*Allows users to search for other FriendsBook members by username
Will either state that the profile is not found or that User is a FriendsBook member*/
void search(MyADT & theMembers) {
   string userName;
   cout << "Enter the username you wish to search for:" << endl;
   cin >> userName;
   for(char &c : userName){
      c = tolower(c);
   }
   Profile toSearch(userName);
   Profile* foundP = theMembers.search(toSearch);
   if (foundP != nullptr){
      cout << "User is a FriendsBook member." << endl;
   }
}

/*Allows user to modify their profile's name, birthday, or email after providing their username
Username must be associated with FriendsBook member*/
void modify(MyADT & theMembers) {
   string username;
   string toChange;
   cout << "enter your username: " << endl;
   cin >> username;
   cout << "What would you like to modify? Please enter: email, name, or birthday: " << endl;
   cin >> toChange;
   for(char &c : username){
      c = tolower(c);
   }
   Profile user(username);
   Profile* found = theMembers.search(user);
   if (found != nullptr){
      if (toChange == "email"){
         string email;
         cout << "Enter new email: " << endl;
         cin >> email;
         found->setEmail(email);
      }
      else if (toChange == "name"){
         string name;
         cout << "Enter new name: " << endl;
         cin >> name;
         found->setName(name);
      }
      else if (toChange == "birthday"){
         string birthday;
         cout << "Enter new birthday: " << endl;
         cin >> birthday;
         found->setBirthday(birthday);
      }
   }
}


void print(MyADT & theMembers) {
   theMembers.print();

}

int main() {

    // Variables declaration
    MyADT members = MyADT();  // Object MyADT on the stack, its arrays on the heap
    bool done = false;
    char input = 0;
        
    // Keep going until the user exits
    while (not done) {
        // Print menu to stdout
        cout << "\n----Welcome to FriendsBook!" << endl << endl;
        cout << endl << "Enter ..." << endl;
        cout << "j -> to join FriendsBook by creating a profile." << endl;
        cout << "l -> to leave FriendsBook." << endl;
        cout << "s -> to search for a friend on FriendsBook." << endl;
        cout << "m -> to modify your profile on FriendsBook." << endl;
        cout << "p -> to print all members on FriendsBook." << endl;
        cout << "x -> to exit FriendsBook." << endl << endl;


        cout << "Your choice: ";
        cin >> input;
        cout << endl;
        input = tolower(input);
        switch(input) {
            case 'j': join(members); break;
            case 'l': leave(members); break;
            case 's': search(members); break;
            case 'm': modify(members); break;
            case 'p': print(members); break;
            case 'x': cout << "\n----Bye!\n" << endl; 
                      done = true; break;
            default: cout << "Not sure what you mean! Please, try again!" << endl;
        }
    }

    return 0;
}
