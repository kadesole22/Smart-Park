#include "queueQ.h"
#include <iostream>


template <class DataType>
class HashTable
{
private:
   static const int tableSize = 7; // Size of the array
   Queue<DataType> table[tableSize]; // Array of Queue DataTypes
   int(*hashfunc)(const DataType &); // Function Pointer
   int queueSizes[tableSize] = {0}; // Array that can store the size of each queue

public:
    // HashTable Constructor
    HashTable(int(*hf)(const DataType &), int s) {
        hashfunc = hf;
        for (int i = 0; i < tableSize; i++) {
            table[i] = Queue<DataType>();
            queueSizes[i] = 0;
        }
    }

    // Function to insert value at location into the hashtable
    // If there is already 4 elements dequeue the element taking the spot
    // Once space is open then enqueue
    bool insert(const DataType & newObject) {
        int location = hashfunc( newObject);
        if( location < 0 || location >= tableSize) // If out of scope
            return false;
        if(queueSizes[location] >=4){ // If Queue already have 4 elements we need to dequeue
            DataType dequeuedItem;
            if(table[location].dequeue(dequeuedItem)){
                cout << dequeuedItem << "Needs to leave the parking lot.\n " << endl;
                queueSizes[location]--; // To keep track of total elements in the each queue
            }
        }
        table[location].enqueue( newObject );
        queueSizes[location]++; // Because we are inserting we have to keep track of size
        return true;
    }


    // Function to remove a value given the name
    bool remove(DataType & removed){
        int location = hashfunc(removed);
        if( location < 0 || location >= tableSize) // Out of scope
            return false;
        if(!table[location].remove(removed)) // Call the remove function from the Queue class
            return false;

        return true;
    }


    // Function to update the value of the object
    bool update(DataType & updateObject){
        int location = hashfunc( updateObject);
        if( location < 0 || location >= tableSize)// Out of scope
            return false;
        if(!table[location].contains(updateObject))// If it doesnt contain the object you cant update it
            return false;
        table[location].replace(updateObject); // Replace object with updated object
        return true;
    }

     // Function to make hashtable empty
    void makeEmpty(){
        for ( int i = 0; i < tableSize; i++)
            table[i].makeEmpty();
            }


    // Function to find if value exist given the location
    bool find(const DataType & object) {
        int location = hashfunc(object);
        if(location < 0 || location >= tableSize) // Out of scope
            return false;
        return table[location].contains(object);// Calls contains function from queue class
        }


    // Function to retrieve the first element in the queue given the location
    bool retrieve(DataType &object){
        int location = hashfunc( object );
        if( location < 0 || location >= tableSize)// Out of scope
            return false;
        return table[location].peek(object); //Call the peek function from the Queue class

    }
    // Function to get the size of the Queue
    int getQueueSize(int index) {
        if (index < 0 || index >= tableSize)
            return false;
        return queueSizes[index];
        }

    // Function get the entire queue
    Queue<DataType>& getQueue(int index) {
        if(index < 0 || index >= tableSize){
            cout << "Out of scope!";
        }
        return table[index];
        }
};
