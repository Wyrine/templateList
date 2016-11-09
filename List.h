//Kirolos Shahat List.h

#pragma once
#include <iostream>

using namespace std;

//class prototype for the Node class to friend
template <typename T>
class List;

//Node class. Added a prev pointer to implement a doubly-linked list
template <typename T>
class Node{
	friend class List<T>;
public:
	//default constructor with no initial value
	Node() :next(NULL), prev(NULL){}
	//constructor with initial value, next, and prev
	Node(const T& item, Node<T>* nextNode = NULL, Node<T>* prevNode = NULL)
	: nodeItem(item), next(nextNode), prev(prevNode){}
private:
	T nodeItem;  //data held by Node
	Node<T> *next, *prev;
};

//List class definition
template <typename T>
class List{
public:
	// constructors and destructor:
	List();
	List(const List<T>& obj);  // copy constructor for List
	~List();  //destructor

			  // list operations:
	void insertFront(const T& newItem);  //insert a new Node at the front
	void insertBack(const T& newItem);  //insert a new Node at the back
	T  removeFront();//remove a Node from the front and return Node value
	void printList();  //print linked list

					   //operator overload   : assignment operator
	List<T>& operator=(const List<T>& aList);

private:
	//is list empty
	bool isEmpty() const { return (head == NULL) ? true : false; }
	int size;       // number of items in list
	Node<T> *head; // pointer to linked list of items

}; // end class

   //implementation starts here
template <typename T>
List<T>::List() { //creates list with start and end as NULL
	head = NULL;
	size = 0;
}

//copy constructor � deep copy
template <typename T>
List<T>::List(const List<T>& aList) { // copy constructor for List lista=listb   or function parameter
	size = aList.size;
	if (aList.head == NULL)
		head = NULL; // original list is empty
	else {  // copy first Node
		head = new Node<T>;
		head->nodeItem = aList.head->nodeItem;
		// copy rest of list
		Node<T> *newPtr = head; // new list pointer
		for (Node<T> *origPtr = aList.head->next; origPtr != NULL; origPtr = origPtr->next){
			newPtr->next = new Node<T>;
			newPtr = newPtr->next;
			newPtr->nodeItem = origPtr->nodeItem;
		} // end for
		newPtr->next = NULL;
	} // end if
} // end copy constructor


template <typename T>
List<T>& List<T>::operator=(const List<T>& aList) {  // = operator overloading
	if (this != &aList){  //self?
		size = aList.size;
		if (aList.isEmpty())
			head = NULL; // original list is empty
		else {  // copy first Node
			head = new Node<T>;
			head->nodeItem = aList.head->nodeItem;
			// copy rest of list
			Node<T> *newPtr = head; // new list pointer
			for (Node<T> *origPtr = aList.head->next; origPtr != NULL;  origPtr = origPtr->next) {
				newPtr->next = new Node<T>;
				newPtr = newPtr->next;
				newPtr->nodeItem = origPtr->nodeItem;
			} // end for
			newPtr->next = NULL;
		} // end if
	}
	return *this;
}   //assignment operator overloading for list1=list2

//a function that takes a T item and inserts it at the front of the list
template <typename T>
void List<T>::insertFront(const T& newItem) {
	Node<T>* newNode;
	//if the list is empty allocate the new node with null pointers to left and right
	if (isEmpty()) newNode = new Node<T>(newItem);
	else {
		//otherwise allocate a new node with a next pointer to the current head location
		newNode = new Node<T>(newItem, head);
		//set's the next node's previous pointer to be the current head
		newNode->next->prev = head;
	}
	//update head and size
	head = newNode;
	size++;
}

//insert back function takes a T item and pushes it to the back of the linked list
template <typename T>
void List<T>::insertBack(const T& newItem) {
	//increment the size
	size++;
	//if the list is empty, put it in the front
	if (isEmpty()) {
		Node<T>* newNode = new Node<T>(newItem);
		head = newNode;
		return;
	}
	//otherwise, put it in the back of the while
	Node<T>* current = head;
	//iterate till you find the end of the list
	while (current->next != NULL) current = current->next;
	//do the assignments
	Node<T>* newNode = new Node<T>(newItem, NULL, current);
	newNode->prev->next = newNode;
}

//removeFront removes the first node from the front of the list and
//returns that data member. If the list is empty, returns -1
template <typename T>
T  List<T>::removeFront() {
	//if list is empty, return -1
	if (isEmpty()) return -1;
	//create a temp item to return which is the data member of the current head
	T temp = head->nodeItem;
	//if that's the only node in the list, set head's next and prev to NULL
	if(head->next != NULL){
		head = head->next;
		//delete the current head
		head->prev = NULL;
		delete head->prev;
	}
	else{
		//otherwise, move forward and delete the previous node
		head->prev = NULL;
		delete head;
	}
	//decrement the size
	size--;
	return temp;
}

//printList iterates and prints the value of head node in the list
template <typename T>
void List<T>::printList() {
	int i = 1;
	for (Node<T>* current = head; current != NULL; current = current->next,  i++)
		cout << "Node " << i << " has the value: " << current->nodeItem << ".\n";
}

//destructor which deallocates all memory that was in the list
template <typename T>
List<T>::~List() {
	while (!isEmpty()){
		if(head->next != NULL){
			head = head->next;
			head->prev = NULL;
			delete head->prev;
		}
		else{
			head = NULL;
			delete head;
		}
		size--;
	}
}
