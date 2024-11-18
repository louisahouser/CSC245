#include <iostream>
#include "dlist.h"

// prototypes for functions
void PrintMenu(char& sel);
void HeadInsert(DList<int>& list);
void TailInsert(DList<int>& list);
bool AccessItem(DList<int>& list);
void Delete(DList<int>& list);
void PrintList(const DList<int>& list);
void PrintLength(const DList<int>& list); 
void FindandMove(DList<int>& list, int num);

using namespace std;

int main(){

	DList<int> list;
	char sel;

	do{

		PrintMenu(sel);
		switch(toupper(sel)){
			case 'H' :   HeadInsert(list);  break;
			case 'T' :   TailInsert(list);  break;
			case 'A' :   AccessItem(list);  break;
			case 'D' :   Delete(list);  break;
			case 'P' :   PrintList(list);  break;
			case 'L' :   PrintLength(list);  break;
			case 'Q' :   cout << "\tExiting Program...\n";  break;
			default  :   cout << "\tError. Try Again." << endl;
		}	

	} while (toupper(sel) != 'Q');	


	return 0;

}

void PrintMenu(char& sel) {
// prints the menu for user to choose from	
	cout << "-----------------------------------------" << endl;
	cout << "|\t\t\t\t\t|" << endl;
        cout << "|\t\t\t\t\t|" << endl;        
	cout << "|    |\\    /| | ̅ ̅ ̅ ̅ ̅ |\\    | |     |    |" << endl;
	cout << "|    | \\  / | |      | \\   | |     |    |" << endl;
	cout << "|    |  \\/  | |_____ |  \\  | |     |    |" << endl;
	cout << "|    |      | |      |   \\ | |     |    |" << endl;
	cout << "|    |      | |_____ |    \\| |_____|    |" << endl;
	cout << "|\t\t\t\t\t|" << endl;
        cout << "|\t\t\t\t\t|" << endl;	
	cout << "|	 H :   Insert Head\t\t|" << endl;
	cout << "|	 T :   Insert Tail\t\t|" << endl;
	cout << "|	 A :   Access Item\t\t|" << endl;
	cout << "|	 D :   Delete \t\t\t|" << endl;
	cout << "|	 P :   Print List\t\t|" << endl;
	cout << "|	 L :   Print Length of List\t|" << endl;
	cout << "|	 Q :   Exit Program\t\t|" << endl;
        cout << "|\t\t\t\t\t|" << endl;
	cout << "-----------------------------------------" << endl;
	
	cin >> sel;
	
}

void HeadInsert(DList<int>& list){
// should alert user if they try to add a duplicate item to the list	
	int num;
	cout << "What value would you like to add? ";
	cin >> num;

	// alert user of duplicate and give option to choose new number
	if(list.inList(num)){
		int correct = 0;
		cout << "You are entering a duplicate value." << endl;
		cout << "Is this correct? 0 for NO, 1 for YES: ";
		cin >> correct;
		if(correct == 0){
			cout << "Here is the current list: " << endl;
			list.print();
			cout << "Please enter another value not currently in the list: ";
			cin >> num;
		}
	}

	list.insertHead(num); // inserts item to head
}
void TailInsert(DList<int>& list){
// should alert user if they try to add a duplicate item to the list 
	int num;
	cout << "What value would you like to add? ";
	cin >> num;
	
	// alert user of duplicate and give option to choose new number
	if(list.inList(num)){
                int correct = 0;
                cout << "You are entering a duplicate value." << endl;
                cout << "Is this correct? 0 for NO, 1 for YES: ";
                cin >> correct;
                if(correct == 0){
                        cout << "Here is the current list: " << endl;
			list.print();
                        cout << "Please enter another value not currently in the list: ";
                        cin >> num;
                }
		
	}	
	
	list.appendTail(num); // appends item to tail
}
bool AccessItem(DList<int>& list){
// call FindandMove to see if item is in the list and then move it to the front if it is
	int num;
	cout << "What value would you like to access? ";
	cin >> num;
	
	if(list.inList(num)){	
		FindandMove(list, num); // will item to head after checking its existence and deleting its location
	}else{
		cout << "Value is not found in the list." << endl;
	}	


	// lets user know if list is empty or not
	string empty = "False";
	if(list.isEmpty()){
		empty = "True";
	}

	return cout << "List is empty: " << empty << endl; 
	
}
void Delete(DList<int>& list){
// should inform user if item they are attempting to delete is not found in the list	
	if(list.isEmpty()){
		cout << "List is empty" << endl; // if list is empty does not give user option to delete any value
	}else{	
		int num;
		cout << "What value would you like to delete? ";
		cin >> num;
		if(!list.inList(num)){
			cout << "Value not found in list" << endl;
		}else{
			list.deleteItem(num); // delete item
		}
	}
}

void PrintList(const DList<int>& list){
// immutable; calls on public print method that will print the info stored in each node
	if(list.lengthIs() == 0){
		cout << "List is empty" << endl;
	}else{
		cout << "Current list: ";
		list.print();
		cout << endl;
	}
}
void PrintLength(const DList<int>& list){
// immutable; prints length of string
	int num = list.lengthIs();
	cout << "The length of the list is: " << num;
	cout << endl;
}
void FindandMove(DList<int>& list, int num){
// checks if item being accessed in the list and then moves it to the front if it is
	if(list.inList(num)){
		list.deleteItem(num);
		list.insertHead(num);
	}	
}

