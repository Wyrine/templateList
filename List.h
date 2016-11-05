#pragma once
template <typename T>
class List;

template <typename T>
class Node{
	friend class List<T>;
public:
	//default constructor with no initial vale
	Node() :next(NULL), prev(NULL){}
	//constructor with initial value and next
	Node(const T& item, Node<T>* nextNode = NULL, Node<T>* prevNode = NULL) : nodeItem(item), next(nextNode), prev(prevNode){}
private:
	T nodeItem;  //data held by Node
	Node<T> *next, *prev;
};

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

//copy constructor – deep copy
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

template <typename T>
List<T>::~List() {
	if (isEmpty()) return;
	do {
		head = head->next;
		delete head->prev;
		head->prev = NULL;
	} while (!isEmpty());
	head = head->next = NULL;
}

template <typename T>
void List<T>::insertFront(const T& newItem) {
	Node<T>* newNode;
	if (isEmpty()) {
		newNode = new Node<T>(newItem);
	}
	else {
		newNode = new Node<T>(newItem, head->next);
		newNode->next->prev = newNode;
	}
	head = newNode;
	size++;
}

template <typename T>
void List<T>::insertBack(const T& newItem) {
	size++;
	if (isEmpty()) {
		Node<T>* newNode = new Node<T>(newItem);
		head = newNode;
		return;
	}
	Node<T>* current = head;
	while (current->next != NULL) current = current->next;
	Node<T>* newNode = new Node<T>(newItem, NULL, current);
	newNode->prev->next = newNode;
}

template <typename T>
T  List<T>::removeFront() {
	if (isEmpty()) return NULL;
	T temp = head->nodeItem;
	head = head->next;
	delete head->prev;
	head->prev = NULL;
	size--;
	return temp;
}

template <typename T>
void List<T>::printList() {
	int i = 1;
	for (Node<T>* current = head; current != NULL; current = current->next,  i++) {
		cout << "Node " << i << "has the value: " << current->nodeItem << ".\n";
	}
}
