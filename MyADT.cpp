/*
 * MyADT.cpp
 * 
 * Class Description: A linear data collection ADT.
 * Class Invariant: Data collection with the following characteristics:
 *                   - Each element is unique (no duplicates).
 *                   - This is a value-oriented data collection: the elements are kept in 
 *                     ascending sort order of search key. 
 *                   - Its data structure is not expandable, i.e., resizable. 
 *
 * Author: AL
 * Last modified on: Sept. 2023
 */


#include <iostream>
#include <cctype>
#include "MyADT.h"  // Header file
#include "Profile.h"
#include <stdbool.h>
#include <cmath>
using std::cout;
using std::endl;


    
// Default constructor.
MyADT::MyADT() {
   for (unsigned int i = 0 ; i < MAX_ALPHA; i ++){
       elements[i] = new Profile [MAX_ELEMENTS];
   }
   for (unsigned int i = 0; i < MAX_ALPHA; i++){
      elementCount[i] = 0;
   }
   n = 0;
}  // end default constructor


// Copy constructor - Covered in Lab 3
MyADT::MyADT(const MyADT& rhs) {
   for (unsigned int i = 0; i < MAX_ALPHA; i ++){
      for (unsigned int j = 0; j < MAX_ELEMENTS; j++){
         this->elements[i][j] = rhs.elements[i][j];
      }
   }
   for (unsigned int i = 0 ; i < MAX_ALPHA ; i ++){
      this->elementCount[i] = rhs.elementCount[i];
   }
   this->n = rhs.n;
}  // end copy constructor


// Destructor
// Description: Destruct this object, releasing heap-allocated memory.
MyADT::~MyADT() {
   for (unsigned int i = 0; i < MAX_ALPHA; i ++){
      delete []elements[i];
   }
} // end destructor

// Description: Returns the total element count of elements currently stored in MyADT.
unsigned int MyADT::getElementCount() const {
   return n;
}  // end getElementCount


// Description: Inserts an element.
// Precondition: newElement must not already be in data collection.  
// Postcondition: newElement inserted and the appropriate elementCount has been incremented.
//                Returns "true" when the insertion is successfull,
//                otherwise "false".
bool MyADT::insert(const Profile& newElement) {
   int firstletter = newElement.getUserName()[0] - 'a';
   unsigned int insertPos = 0;
   
   if (elementCount[firstletter] == MAX_ELEMENTS){
      cout << "ERROR: Too many elements. No space for new profile" << endl;
      return false;
   }
   else if (elementCount[firstletter] == 0){
      elements[firstletter][0] = newElement;
      elementCount[firstletter] ++;
      n++;
      return true;
   }
   while (insertPos < (elementCount[firstletter]) && (elements[firstletter][insertPos] < newElement || elements[firstletter][insertPos] == newElement)){
      if (elements[firstletter][insertPos] == newElement){
         cout << "Username already taken." << endl;
         return false;
      }
      insertPos++;
   }
   for (unsigned int i = elementCount[firstletter]-1; i >= insertPos; i --){
      elements[firstletter][i + 1] = elements[firstletter][i];
   }
   elements[firstletter][insertPos] = newElement;

  //increment number of elements with firstletter//
   elementCount[firstletter] ++;
   n++;
   return true;
}  // end insert


// Description: Search for target element. 
//              Returns a pointer to the element if found,
//              otherwise, returns nullptr.
Profile* MyADT::search(const Profile& target) {
   Profile *searched = nullptr;
   int index = target.getUserName()[0] - 'a';

   if (elementCount[index] == 0){
      cout << "Profile not found." << endl;
      return nullptr;
   }
   
   int left = 0;
   int right = elementCount[index]-1;
   int middle = std::floor(elementCount[index]/2);

   while (left <= right){
      if (elements[index][middle] == target){
         searched = &elements[index][middle];
         return searched;
      }
      else if (elements[index][middle] < target){
         left = middle + 1;
      }
      else if (elements[index][middle] > target){
         right = middle -1;
      }
      else left++;
      middle = std::floor((right + left) /2);
   }
   if (searched == nullptr) cout << "searched is nullptr profile wasn't found" << endl;
   return searched;
}  // end of search

// Description: Remove an element. 
// Postcondition: toBeRemoved is removed and the appropriate elementCount has been decremented.
//                Returns "true" when the removal is successfull,
//                otherwise "false".
bool MyADT::remove(const Profile& toBeRemoved) {
   int letterIndex = toBeRemoved.getUserName()[0] - 'a';
   int elementNum = elementCount[letterIndex];
   Profile* remove = this->search(toBeRemoved);
   if (remove == nullptr){
      return false;
   }
   else {
      for ( int i = 0 ; i < elementNum; i ++){
         if (elements[letterIndex][i] == *remove){
            for (int j = i; j < elementNum; j++){
               elements[letterIndex][j] = elements[letterIndex][j+1];
            }
         }  
      }
      n--;
      elementCount[letterIndex] --;
      return true;
   }
}
// end remove


// Description: Remove all elements.
void MyADT::removeAll() {
   unsigned int removed = 0;
   for (unsigned int i = 0; i < MAX_ALPHA && removed < n; i++){
      for (unsigned int j = 0 ; j < elementCount[i]; j++){
         remove(elements[i][j]);
         removed ++;
      }
   }
}  // end removeAll


void MyADT::print() {
   cout << "PRINT CALLED" << endl;
   unsigned int printed = 0;
   if (this->getElementCount == 0){
      cout << "No profiles to print" << endl;
      return;
   }
   for (unsigned int i = 0 ; i < MAX_ALPHA && printed < n; i++){
      for (unsigned int j = 0; j < elementCount[i]; j ++){
         cout << elements[i][j].getUserName() << endl;
         cout << elements[i][j].getName() << endl; 
         cout << elements[i][j].getEmail() << endl;
         cout << elements[i][j].getBirthday() << endl;
         printed ++;
      }
   }
}

unsigned int MyADT::getIndexElementCount(int index){
   return this->elementCount[index];
}



//  End of implementation file
