#include<iostream>
#include<cstdlib>
#include<cctype>
#include "stack.h"

using namespace std;

/*
 * PROTOTYPES
 */
void PrintTop(Stack<int>& s);
void PrintAndPopTop(Stack<int>& s);
void PrintStack(Stack<int>& s);
void MakeStackEmpty(Stack<int>& s);
void DuplicateTop(Stack<int>& s);
void ReverseTopTwo(Stack<int>& s);
void PopAddAndPushTwo(Stack<int>& s);
void PopSubAndPushTwo(Stack<int>& s);
void PopMultAndPushTwo(Stack<int>& s);
void PopDivideAndPushTwo(Stack<int>& s);
void PopRemainAndPushTwo(Stack<int>& s);



/*
 * MAIN METHOD ---------------------------------------------------------------
 */ 

int main(){


	Stack<int> s;	
	string myInput;

	do{
		try{

			getline(cin, myInput);				// getline to keep track of order of input
			for(int i = 0; i < myInput.size(); i++){	// for loop to iterate through the input

				bool negative;		// keep track of if a negative marker was given				
				string operators;	// string that will hold only the operators inputted
				string numbers;		// string that will hold only the numbers inputted	
				int ascii = int(myInput[i]);				

				// set bool to true if negative marker is the input
				if(myInput[i] == '_'){ 		  
					negative = true;
				}

				// add input to operators string if input is a letter
				if(isalpha(myInput[i]) != 0){	
					operators += myInput[i];
				
				// add input to numbers string if input is a number 	   
				}else if(isdigit(myInput[i]) != 0){
				
					// add '-' to numbers string if boolean was set to true above
					if(negative){		  			
						numbers += '-';
						negative = false; // set bool to false so next number won't be negative as well
					}
				
					/*
 					*   ----- HANDLE LARGER THAN SINGLE DIGIT: -----	 
					*/
					
                                        numbers += myInput[i];

					if(i < myInput.size()){
						while((isdigit(myInput[i + 1]) != 0)){
							numbers += myInput[i + 1];
							i++;
							if(i >= myInput.size()){
								break;
							}
						}
					}						
		

					int num = atoi(numbers.c_str());
					s.push(num);
					

				// continue if element is a whitespace
				}else if(isspace(myInput[i]) != 0){						
					continue;
				
				// add input to operators string if ascii code of input is equal to specific special characters
				}else if((42 <= ascii <=  43) || (ascii == 45) || (ascii == 47) || (ascii == 37)){
					operators += myInput[i];
				}	
				 	
		
	
				// for each element of the operators string, call method based off of letter
			   	for(int k = 0; k < operators.length(); k++){
			   
					if(operators[k] == 'p'){
					        PrintTop(s);			
					}else if(operators[k] == 'n'){
						PrintAndPopTop(s);   
					}else if(operators[k] == 'f'){
						PrintStack(s);
					}else if(operators[k] == 'c'){
						MakeStackEmpty(s);			
					}else if(operators[k] == 'd'){
						DuplicateTop(s);
					}else if(operators[k] == 'r'){
						ReverseTopTwo(s);
					}else if(operators[k] == '+'){
						PopAddAndPushTwo(s);
					}else if(operators[k] == '-'){
						PopSubAndPushTwo(s);
					}else if(operators[k] == '*'){
						PopMultAndPushTwo(s);
					}else if(operators[k] == '/'){
						PopDivideAndPushTwo(s);
					}else if(operators[k] == '%'){
						PopRemainAndPushTwo(s);
					}
					
					// shorten operators string so the next loop looks at the next letter	
					operators = operators.substr(1, operators.length());   				
				}
			}
                	if(! cin){
                        	throw DataError();
                	}

                	if(myInput.c_str() == 0){
                       		throw DivisionByZero();
                	}


		}

       		/*
 		* EXCEPTION HANDLING
 		*/
		catch(DataError exc){
			cerr << "You have not entered any input!\n";
		}
		catch(DivisionByZero exc){
			cerr << "Division by zero not allowed -- Re-enter input. \n";
       		}
		catch(Underflow exc){
			cerr << "Exception--You're Trying to Pop An Empty Stack! \n";
		}
		catch(Overflow exc){
			cerr << "Exception--Your Stack is Full! " << endl;
		}

	   	
	}while(cin);

	
	return 0;
}

/*
 * FUNCTIONS FOR OPERATIONS --------------------------------------------------
 */

void PrintTop(Stack<int>& s){

/*
 * Prints the value on the top of the stack, without altering the stack.
 * A newline is printed after each value
 */

	int top = s.top();
	cout << top << endl;	
}

void PrintAndPopTop(Stack<int>& s){

/*
 * Prints the value on the top of the stack, pops it off,
 * and does not print a newline after.
 */

	int top = s.top();
	cout << top << endl;
	s.pop();
}

void PrintStack(Stack<int>& s){

/*
 * Prints the entire contents of the stack without altering anything.
 * A newline is printed after each value
 */

	Stack<int> tempS; 	     // temporary stack so we can print the stack in correct order
	while(!(s.isEmpty())){
		int pos = s.top();
		cout << pos << endl; // print the stack 
		tempS.push(pos);
		s.pop();
	}
	while(!(tempS.isEmpty())){
		int pos =  tempS.top();
		s.push(pos);	     // refill s with temp stack	
		tempS.pop();		
	
	}
		

}

void MakeStackEmpty(Stack<int>& s){

/*
 * Clears the stack, rendering it empty.
 */

	s.makeEmpty();
	
}

void DuplicateTop(Stack<int>& s){

/*
 * Duplicates the value on the top of the stack, pushing another copy of it.
 */

	int top = s.top();
	s.push(top);

}

void ReverseTopTwo(Stack<int>& s){

/*
 * Reverses the order of (swaps) the top two values on the stack.
 */

	int top = s.top();
	s.pop();
	int second = s.top();
	s.pop();
	s.push(top);
	s.push(second);

}

void PopAddAndPushTwo(Stack<int>& s){

/*
 * Pops two values off the stack, adds them, and pushes the result.
 */

	int sum = s.top();
	s.pop();
	sum += s.top();
	s.pop();
	s.push(sum);

}

void PopSubAndPushTwo(Stack<int>& s){

/*
 * Pops two values, subtracts the first one popped from the second one popped,
 * and pushes the result.
 */

	int num1 = s.top();
	s.pop();
	int num2 = s.top();
	s.pop();
	num2 -= num1;
	s.push(num2);

}

void PopMultAndPushTwo(Stack<int>& s){

/*
 * Pops two values, multiplies them, and pushes the result
 */

        int mult = s.top();
        s.pop();
        mult *= s.top();
        s.pop();
        s.push(mult);

}

void PopDivideAndPushTwo(Stack<int>& s){

/*
 * Pops two values, divides the second one popped from the first one popped,
 * and pushes the result
 */

        int num1 = s.top();
        s.pop();
        int num2 = s.top();
        s.pop();
        num2 = num2 / num1;
        s.push(num2);	

}

void PopRemainAndPushTwo(Stack<int>& s){

/*
 * Pops two values, computes the remainder of the division
 * that the / command would do, and pushes that.
 */

	int num1 = s.top();
        s.pop();
        int num2 = s.top();
        s.pop();
        num2 = num2 % num1;
        s.push(num2);
	

}


