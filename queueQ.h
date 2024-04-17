// queue.h -- class template for the linked list implementation of a queue
// note:  use of the copy constructor, overloaded assignment operator, or enqueue function
// can cause an exception to be thrown when heap memory is exhausted
using namespace std;
template <class DataType>
struct Node {
	DataType info;
	Node<DataType> *next;
};

template <class DataType>
class Queue
{
public:
	Queue( );
	Queue( const Queue<DataType> & apqueue );
	~Queue( );
	Queue<DataType> & operator =( const Queue<DataType> & rqueue );
	void enqueue( const DataType & element );

	// dequeues element and returns it in deqElement
	// returns false if called on an empty queue; otherwise returns true
	bool dequeue( DataType & deqElement );
	// returns element at the front of the queue into frontElement without removing it
	// returns false if called on an empty queue; otherwise returns true
	bool peek( DataType & frontElement );
	bool isEmpty( ) const;// returns true if queue is empty
	void makeEmpty( );
	void print( );
	bool contains(const DataType &element) const;
	bool replace(const DataType &newValue);
	bool remove(const DataType &value);
private:
	Node<DataType> *front;
	Node<DataType> *back;
	Node<DataType> header;
	inline void deepCopy( const Queue<DataType> & original );
};

template <class DataType>
void Queue<DataType>::print( )
{
Node<DataType> *ptr = front;
while(ptr!=back)
{
cout<<ptr->next->info<<endl;
ptr = ptr->next;
}

}

template <class DataType>
Queue<DataType>::Queue( )
{
	front = back = &header;
}

template <class DataType>
Queue<DataType>::Queue( const Queue<DataType> & apqueue )
{
	deepCopy( apqueue );
}

template <class DataType>
Queue<DataType>::~Queue( )
{
	makeEmpty( );
}

template <class DataType>
Queue<DataType> & Queue<DataType>::operator =( const Queue<DataType> & rqueue )
{
	if ( this == &rqueue )
		return *this;
	makeEmpty( );
	deepCopy( rqueue );
	return *this;
}

template <class DataType>
void Queue<DataType>::enqueue( const DataType & element )
{
	Node<DataType> *ptr = new Node<DataType>;
	ptr->info = element;
	back->next = ptr;
	back = ptr;
}


// dequeues element and returns it in deqElement
// returns false if called on an empty queue; otherwise returns true
template <class DataType>
bool Queue<DataType>::dequeue( DataType & deqElement )
{
	if ( front == back )
		return false;

	Node<DataType> *ptr = front->next;
	deqElement = ptr->info;
	front->next = ptr->next;
	if ( back == ptr )
		back = front;
	delete ptr;

	return true;
}
// returns element at the front of the queue into frontElement without removing it
// returns false if called on an empty queue; otherwise returns true
template <class DataType>
bool Queue<DataType>::peek( DataType & frontElement )
{
	if ( front == back )
		return false;
	frontElement = front->next->info;
	return true;
}

template <class DataType>
bool Queue<DataType>::isEmpty( ) const
{
   	 return front == back;
}

template <class DataType>
void Queue<DataType>::makeEmpty( )
{
   	DataType temp;
	while ( dequeue( temp ) );
}

template <class DataType>
inline void Queue<DataType>::deepCopy( const Queue<DataType> & original )
{
	Node<DataType> *copyptr = front = &header;
	Node<DataType> *originalptr = original.front;
	while ( originalptr != original.back ) {
		originalptr = originalptr->next;
		copyptr->next = new Node<DataType>;
		copyptr = copyptr->next;
		copyptr->info = originalptr->info;
	}
	back = copyptr;
}

template <class DataType>
bool Queue<DataType>::contains(const DataType &element) const {
    Node<DataType> *current = front->next;
    while (current != nullptr) { //Iterate through the list checking if
        if(current->info == element)// Each element is equal to the element you passed it
            return true;
        current = current->next;
    }
    return false;
}

template <class DataType>
bool Queue<DataType>::replace(const DataType &newValue) {
    Node<DataType> *current = front;
    while (current != nullptr) {
        if (current->info == newValue) { //If current's element is == to the new value
            current->info = newValue;//Set currents element equal to the new value to update it
            return true;
        }
        current = current->next;
    }
    return false;
}

template <class DataType>
bool Queue<DataType>::remove(const DataType & oldValue) {
    Node<DataType> *current = front->next;
    Node<DataType> *previous = nullptr;

    while (current != nullptr){
        if(current->info == oldValue) {
            if(current == front){ //if its the first element u have to remove set it equal to what currents next is pointing at and then delete the current element.
                front = current->next;
                delete current;
                return true;
            }
            if (current == back){ //if the element u need to remove is the last element change it to the previous node and have it point to nullptr.
                back = previous;
                back->next = nullptr;
                delete current;
                return true;
            }
            //If you have to remove an element in the middle
            previous->next = current->next; //Set the element before current to point at currents next pointer then delete current
            delete current;
            return true;
        }
        //Move to next node
        previous = current;
        current = current->next;
    }
    //Element not found
    return false;
}

