#include "huffman.h"
#include <iostream>
#include<queue>
#include<string>
#include<cstdlib>

using namespace std;


HuffmanTree:: HuffmanTree()
	: numChars(0), built(false) {}

void HuffmanTree:: insert(char ch, int weight) {
/*
 *----- INSERTS A CHARACTER AND ITS ASSOCIATED WEIHT INTO A NODE OF THE HUFFMAN TREE -----
 */

    HNode newNode = {ch, weight, -1, -1}; 
    built = false;
    nodes.push_back(newNode);
    numChars++;

}

bool HuffmanTree:: inTree(char ch) {
/*
 *----- RETURNS A BOOLEAN VALUE INDICATING WHETHER A GIVEN CHARACTER IS STORED IN THE TREE -----
 */

	for(int i = 0; i < nodes.size(); i++){
		if(nodes[i].ch == ch){
			return true;
		}
	}	

	return false;

}

int HuffmanTree:: GetFrequency(char ch) {
/*
 *----- CALLS METHOD WITH INDEX OF WANTED CHARACTER-----
 */

	return GetFrequency(lookUp(ch));

}

int HuffmanTree:: GetFrequency(int i) {
/*
 *----- RETURNS THE WEIGHT OF A GIVEN CHARACTER -----
 */

	return nodes[i].weight;
	
}

int HuffmanTree:: lookUp(char ch) {
/*
 *----- USED BY GETCODE METHOD -----
 */

	for(int i = 0; i < nodes.size(); i++){
		if(nodes[i].ch == ch){
			return i;
		}
	}	


}

string HuffmanTree:: GetCode(char ch) {
/*
 *----- CALLS METHOD WITH INDEX OF WANTED CHARACTER -----
 */

	return GetCode(lookUp(ch));
}


string HuffmanTree:: GetCode(int i) {
/*
 *----- RETURNS COMPRESSED CODE OF A GIVEN CHARACTER IN THE TREE USING RECURSION
 */

	if(nodes[i].parent == 0)
		return "";
	else
		return (GetCode(nodes[i].parent) + (char)(nodes[i].childType+'0'));
}

void HuffmanTree:: PrintTable() {
/*
 *----- DISPLAYS HUFFMAN ENCODING TABLE USED IN COMPRESSION PROCESS -----
 */
	cout << endl;
	cout <<"\t## ENCODING TABLE FOR ZIP FILE ##" << endl;
	cout << endl;
	cout << "\tIndex\tChar\tWeight\tParent\tChildType" << endl;
	cout << endl;
	int count = 1;

	for(int i = 0; i < nodes.size(); i++){
		
		// print space
		if(nodes[i].ch == char(32)){
			cout << "\t" << i << "\t" << "sp" << "\t" << nodes[i].weight << "\t" << nodes[i].parent << "\t" << nodes[i].childType << endl;
		}
		// print newline
		else if(nodes[i].ch == char(10)){
	                cout << "\t" << i << "\t" << "nl" << "\t" << nodes[i].weight << "\t" << nodes[i].parent << "\t" << nodes[i].childType << endl;
                }
		// print root
		else if(i == (nodes.size() - 1)){
                        cout << "\t" << i << "\t" << "T" << count << "\t" << nodes[i].weight << "\t" << nodes[i].parent << "\t" << "N/A" << endl;
		}
		// print all T created nodes
		else if(nodes[i].ch == char(0)){
	                cout << "\t" << i << "\t" << "T" << count << "\t" << nodes[i].weight << "\t" << nodes[i].parent << "\t" << nodes[i].childType << endl;
			count++;
		}
		// print everything else which is just the characters
		else{		
			cout << "\t" << i << "\t" << nodes[i].ch << "\t" << nodes[i].weight << "\t" << nodes[i].parent << "\t" << nodes[i].childType << endl;
		}
	}

}

int HuffmanTree:: numNodes() {
/*
 *----- RETURNS THE NUMBER OF NODES CURRENTLY IN YOUR HUFFMAN TREE -----
 */

	return nodes.size();

}

void HuffmanTree:: build() {

/*
 *----- BUILDS HUFFMAN TREE -----
 */    

	// while built var has not been set to true
	while(!built){

		// initialize our two frequency variables
	        int greedyOne = -1;
        	int greedyTwo = -1;
        
		// iterate through
	       	for (int i = 0; i < numChars; i++) {
			// if we have not modified it and built it into our tree yet
			if (nodes[i].parent == -1) {
				// find our mins before we insert
                		if (greedyOne == -1 || nodes[i].weight < nodes[greedyOne].weight) {
                			greedyTwo = greedyOne;
                   			greedyOne = i;
                   
                		} else if (greedyTwo == -1 || nodes[i].weight < nodes[greedyTwo].weight) {
                    			greedyTwo = i;
                		}
            		}
        	}
         
		// insert our new node with null char and the combined weights
	        insert('\0', nodes[greedyOne].weight + nodes[greedyTwo].weight);

		// create var that will set the parent index for our next few lines of code
		int parent = numChars - 1;
      
		// set the parent and childType of each greedy variable
     		nodes[greedyOne].parent = parent;
		nodes[greedyTwo].parent = parent;
     		nodes[greedyOne].childType = 0;
        	nodes[greedyTwo].childType = 1;
	
	  
		// check how many parent indexes we have that are set to -1 still 
		// meaning they still need to be built into the tree
     		int numLeftToBuild = 0;
		for(int i = 0; i < numChars; i++){
			if(nodes[i].parent == -1){
				numLeftToBuild++;
			}
		}
		
		// if equal to one, we have our root node and are done building our tree
		if(numLeftToBuild == 1){
			built = true; // YAYYYY!
		}

    	}
 	
	// set our root parent to be 0 since it is the root   
	nodes[nodes.size() - 1].parent = 0;


	
}

