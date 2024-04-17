#include<iostream>
#include "hashtable.h"
#include <fstream>
using namespace std;

struct Profile {
    string name;
    string state;
    // Overload the == operator to compare profile names to see if equivalent
    bool operator==(const Profile& other) const{
        return name == other.name;
    }
};

// HashFunction - converts Profile into a key 0-6
int hashFunction(const Profile& profile) {
    int sum = 0;
    for (char c : profile.name) {
        sum += c; // this adds the ASCII value of the character to the sum
    }
    int key = sum % 7; // this mods the total sum by 7
    return key; // returns a value from 0 to 6 for the hash table index
}


// Overload the << operator for profile have it cout the name and state strings
ostream& operator << (ostream& out, const Profile& data){
    out << data.name << endl;
    out << data.state << endl;
    return out;
}

// Smart Park
int main() {
    int tableSize = 7;
    HashTable<Profile> hashtable_profile(hashFunction, tableSize); // Create HashTable object with Profile as its datatype

    ifstream infile;
    infile.open("presidentsWstates.txt"); // Parse the text file
    string name;
    string state;


    getline (infile,name,'\t');
    while(infile){
        getline (infile,state);
        getline (infile,name,'\t');{ //Splits the text file into names and states
        Profile profileStruct; // Create the profile struct
        profileStruct.name = name; // Stores name as a string in the struct
        profileStruct.state = state; // Stores state as a string in the struct
        hashtable_profile.insert(profileStruct);// Call insert function to insert into hashtable
    }
    }
    infile.close(); // Stop parsing text



    // Get all of the profiles for ALL parking locations
    for (int i = 0; i < tableSize; i++) {// Uses getQueueSize function from hashtable class
        cout << "Parking lot " << i << " has " << hashtable_profile.getQueueSize(i) << " cars in it." << endl;
    }



    // Find President
    // New profile with the name of president that is trying to be found
    string presidentToRetrieve = "Barack Obama";
    Profile profileToRetrieve;
    profileToRetrieve.name = presidentToRetrieve;
    if (hashtable_profile.find(profileToRetrieve)) { // Calls the find function to look for another profile with that name
        int z = hashFunction(profileToRetrieve); //Used to show what parking lot we are in
        cout << "\nBarack Obama's car is in parking lot " << z << std::endl;
    } else {
        cout << "\nBarack Obama's car is no longer in the lot!" << endl;
    }



    // Call the retrieve function to find the first president in the row
    cout << "\nThe first car in " << presidentToRetrieve << " parking lot belongs to: \n";
    Profile retrievedProfile; //New profile
    retrievedProfile.name = presidentToRetrieve; //Set profiles name = to the string we are looking to use the retrieve function on
    if (hashtable_profile.retrieve(retrievedProfile)) {
        cout << retrievedProfile << endl;
    } else {
        cout << " Sorry there is nobody in that parking lot!\n";
    }
    cout << "\n";



    // Display final configuration
    for (int i = 0; i < tableSize; i++) {
        cout << "Parking lot " << i << "\n";
        Queue<Profile> queueCopy;
        queueCopy = hashtable_profile.getQueue(i); // Deep copy the queue
        while (!queueCopy.isEmpty()) { //Dequeue elements one by one until its empty
            Profile profile;
            queueCopy.dequeue(profile);
            cout << profile;
        }
        cout << endl;
    }



    // Remove a Car/President
    Profile profileToRemove; // New Profile
    string removePres = "Ronald Reagan";
    profileToRemove.name = removePres;
    if (hashtable_profile.remove(profileToRemove)) { //Calls the remove function and depending on what it returns cout back to user
        std::cout << " \nRemoval is a success!\n" << removePres << " Car was removed from parking lot " << hashFunction(profileToRemove) << std::endl;
    } else {
        std::cout << "\n Removal was a failure, car was not found\n" << std::endl;
    }
        int x = hashFunction(profileToRemove);
        Queue<Profile> queueCopy;
        queueCopy = hashtable_profile.getQueue(x); // Deep copy the queue
        while (!queueCopy.isEmpty()) {
            Profile profile;
            queueCopy.dequeue(profile);
            cout << profile;
        }
        cout << endl;

    // Update
    // Creating a profile that is going to be updated
    Profile updatedProfile;
    string updatePres = "William J. Clinton";
    updatedProfile.name = updatePres;
    updatedProfile.state = "MI";

    if (hashtable_profile.update(updatedProfile)) { //Calls update function to update a profiles data for example they could change there state
        std::cout << "\nUpdate was a success, William J. Clinton's  state was changed to MI\nHis car is located in ";
    } else {
        std::cout << "\nUpdate was a failure\n";
    }
    Profile profileToUpdate;
    int j = hashFunction(updatedProfile);
   std::cout << "Parking lot " << j << "\n";
        Queue<Profile> queueCopy1;
        queueCopy1 = hashtable_profile.getQueue(j); // Deep copy the queue
        while (!queueCopy1.isEmpty()) {
            Profile profile;
            queueCopy1.dequeue(profile);
            cout << profile;
        }


    return 0;
}
