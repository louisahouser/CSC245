#include <cstddef> 
#include <iostream>
using namespace std;

template<class ItemType>
struct NodeType
{
	ItemType info;
	NodeType<ItemType>*	next;
	NodeType<ItemType>*	back;
};

template <class ItemType>		
DList<ItemType>::DList()		// Class constructor
{
    length = 0;
    head = NULL;
}

template <class ItemType>
DList<ItemType>::~DList   ()		
{
	// Post: List is empty; All items have been deallocated.
	makeEmpty(); // deconstructor function that will only run when object is out of scope
}

template <class ItemType>
void DList<ItemType>::makeEmpty()
{
    // Post: List is empty; all items have been deallocated.
	
	NodeType<ItemType>* newNode; // node to keep track of where we are
	NodeType<ItemType>* currentNode = head; // node we can delete

	if(head == NULL){
		cout << "List is already empty"<< endl;
	}else{
		while(currentNode != NULL){

			newNode = currentNode -> next; // set newNode to the next node
			delete currentNode;
			currentNode = newNode; // reassign currentNode after having deallocating memory
		}
	}
	
	head = NULL;
	
}

template <class ItemType>
void DList<ItemType>::deleteItem (ItemType item)	
{
	//  Pre :  item to be deleted is passed in via parameter 
        // Post :  item is deleted if it exists in list 
		
	

	if(!(inList(item))){
		cout << "List is empty" << endl;
	}else{
		deleteLocation(location(item));
	}

}

template <class ItemType>
bool DList<ItemType>::inList (ItemType item) const
{
	//  Pre :  item to be located is passed in via parameter 
        // Post :  function returns bool value if item is found 

	return (location(item) != NULL);
	
}

template <class ItemType>
bool DList<ItemType>::isEmpty() const		
{
	// Post : function returns true if list is empty, false otherwise

	return (head == NULL);
	
}

template <class ItemType>
void DList<ItemType>::print() const	
{
	// Pre  : List is not empty 
	// Post : Items in List have been printed to screen	

	NodeType <ItemType>* newNode = head;

	// while loop to make sure we do not iterate past head again
	while(newNode -> next != head){

		cout << newNode -> info << " ";
		
		if(newNode -> next == NULL){
			break; // break if we reach end of list
		}else{
			newNode = newNode -> next; 
		}		
	
	}

	cout << endl;

}
	
template <class ItemType>
void DList<ItemType>::insertHead(ItemType item)	
{
	//  Pre : item to be inserted is passed in via parameter
        // Post : item is inserted at head of list;  Former first node is 
        //        linked back to this new one via double link;
        //        Length incremented;  Special case handled if list is empty 

	NodeType <ItemType>* newNode = new NodeType<ItemType>;
	newNode -> info = item;
	newNode -> back = NULL;
	if(head == NULL){
		newNode -> next = NULL;
	}else{
		head -> back = newNode; // link the old 1st item to the new 1st item
		newNode -> next = head; // link the new 1st item to the old 1st item
	}


	head = newNode; length++; // set new head to newNode and increase length
	
	
}

template <class ItemType>
void DList<ItemType>::appendTail(ItemType item)
{
	//  Pre :  item to be inserted is passed in via parameter
        // Post :  item is added to tail of list; Former last node
        //         is linked to this new one via double link 

	NodeType<ItemType>* newNode = new NodeType<ItemType>; // node to set new tail
	NodeType<ItemType>* lastNode = last(); // node to keep track of tail
	newNode -> info = item;
	newNode -> next = NULL;
	if(head == NULL){
		head = newNode;
		head -> back = NULL;		
	}else{ 
		newNode -> back = lastNode;
		lastNode -> next = newNode;
	}

	length++; // increase length
}


template <class ItemType>
int DList<ItemType>::lengthIs() const	
{
	// Post : Function returns current length of list  

	int count = 0; // initialize length counter
	NodeType<ItemType>* newNode = head;
	
	
	if (head == NULL){
		count = 0;
	}else{
		while(newNode -> next != head){
			// if next equal NULL, then increase count but break	
			if(newNode -> next == NULL){
				count++;
				break;						
			}else{ // else increase count and continue iterating
				count++;
				newNode = newNode -> next;	
			}
		}
	
	}
	return count; // return count variable;

}

template <class ItemType>
NodeType<ItemType>* DList<ItemType>::location(ItemType item) const	
{
	//  Pre : item to be located is passed in via parameter 
        // Post : function returns address of item being searched for --
        //        if not found, NULL is returned  

	NodeType<ItemType>* newNode = newNode = head;
	
	// returns newNode if item matches info	
	while(newNode != NULL){
		if(newNode -> info == item){
			return newNode;				
		}else{
			newNode = newNode -> next;
		}
	}

	return NULL; // returns NULL otherwise

}

template <class ItemType>
NodeType<ItemType>* DList<ItemType>::last() const	
{
	// Post : Function returns location of current last item in list

	NodeType<ItemType>* newNode = newNode = head;

	// iterates through to the last item in list
	if(head == NULL){
		newNode = NULL;
	}else{
		while(newNode -> next != NULL){
			newNode = newNode -> next;
		}
	}
	return (newNode); // returns location of last item
	
}	

template <class ItemType>
void DList<ItemType>::deleteLocation (NodeType<ItemType>* delPtr)	
{

	//  Pre : Item to be deleted exits in list and its location
        //        is passed in via parameter
                   
	// Post : Location passed in is removed from list;  Length
        //        is decremented, and location is deallocated 

        // Special Cases Handled for Deleting Only One Item in List,
        // The Head Item of List, and the Tail Item of List
        //


// checks if deleting head item
	if((delPtr -> back == NULL) && (delPtr -> next != NULL)){
		delPtr -> next -> back = NULL;	// set new head's back to NULL
		head = delPtr -> next; // sets new head to delPtr next
		delete delPtr;
		head -> back = NULL;
		length--;
	
// checks if deleting tail item
	}else if((delPtr -> next == NULL) && (delPtr -> back != NULL)){
		delPtr -> back -> next = NULL; // set next of back of delPtr to NULL since it will be new tail
		delete delPtr;
		length--;

// checks if deleting middle position item
	}else if((delPtr -> next != NULL) && (delPtr -> back != NULL)){
		delPtr -> back -> next = delPtr -> next; // link next of back to the node after delPtr 
		delPtr -> next -> back = delPtr -> back; // link back of next to the node before delPtr
		delete delPtr;
		length--;

// checks if deleting list with only one item in list
        }else if((delPtr -> next == NULL) && (delPtr -> back == NULL)){
		delete delPtr;
		head = NULL;
		length--;
	}


 
		


}
