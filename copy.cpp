
#include <iostream>
#include "MyADT.h"
#include "Profile.h"

using std:: cout;
using std:: endl;

constexpr static unsigned int MAX_ALPHA = 26;   // 26 letters in the alphabet 
constexpr static unsigned int MAX_ELEMENTS = 5; // Small capacity so can test when data collection becomes full 

bool testInsert(MyADT& ADT, Profile &profile1, Profile &profile2, Profile &profile3, Profile &profile4, Profile &profile5);
bool testsearch(MyADT& ADT);
bool testGetElementCount(MyADT& ADT);
void testPrint(MyADT & ADT);
bool testRemove(MyADT& ADT);
bool testRemoveAll(MyADT& ADT);

int main(){
    Profile profile1("anna123","anna", "anna123@gmail.com", "12 Aug 2023");
    Profile profile2("anna123","anna", "anna123@gmail.com", "12 Aug 2023");
    Profile profile3("bob123","bob", "bob123@gmail.com", "13 jan 2023");
    Profile profile4("calum123","calum", "calum123@gmail.com", "20 Feb 2023");
    Profile profile5("caleb123","caleb", "caleb123@gmail.com", "20 Feb 2023");
    MyADT myObject; 
    bool insert = testInsert(myObject, profile1 , profile2, profile3, profile4, profile5);
    if (!insert) cout <<"ERROR: insert" <<endl;

    bool getECount = testGetElementCount(myObject);
    if(!getECount) cout << "ERROR: getElementCount"<< endl;

    testPrint(myObject);
    
    bool remove = testRemove(myObject);
    if(!remove) cout << "ERROR: remove" << endl;

    bool removeAll = testRemoveAll(myObject);
    if (!removeAll) cout <<"ERROR: removeAll" << endl;
    return 0;
}

bool testInsert(MyADT& ADT, Profile &profile1, Profile &profile2, Profile &profile3, Profile &profile4, Profile &profile5){
    cout<< "TEST 1: insert" << endl;
    
    if(ADT.insert(profile1)){
        cout<< "successfully inserted profile1" << endl;
    }
    if(ADT.insert(profile2)){
        return false;
    }
    if(ADT.insert(profile3)){
    cout<< "successfully inserted profile3" << endl;
    }
    if (ADT.insert(profile4)){
    cout<< "successfully inserted profile4" << endl;
    }
    if(ADT.insert(profile5)){
    cout <<"successfully inserted profile5" << endl;
    }
    cout << "End test insert" << endl << endl;
    return true;
}

bool testGetElementCount(MyADT& ADT){
    cout <<"TEST 2: getElementCount"<< endl;
    unsigned int elementCount = ADT.getElementCount();
    cout << "element count for ADT is: " << elementCount;
    if (elementCount != 4){
        return false;
    }
    cout <<"End test getElementCount" << endl << endl;
    return true;
}

bool testsearch(MyADT& ADT, Profile &profile){
    cout << "TEST 3; search"<< endl;
    Profile* found = ADT.search(profile);
    if (found != nullptr){
        cout <<"End test search" << endl << endl;
        return true;
    }
    return false;
}

void testPrint(MyADT & ADT){
    cout << "TEST 4: print" << endl;
    cout << "printing ADT" << endl;
    ADT.print();
    cout <<"End test print" << endl << endl;
}

bool testRemove(MyADT& ADT, Profile &profile){
    cout <<"Test 5: remove" << endl;
    if(!ADT.remove(profile)){
        return false;
    }
    Profile* found = ADT.search(profile);
    if (found != nullptr){
        return false;
    }
    return true;
}

bool testRemoveAll(MyADT& ADT){
    ADT.removeAll();
    unsigned int elementCount = ADT.getElementCount();
    if (elementCount != 0){
        return false;
    }
    return true;
}