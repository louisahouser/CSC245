#include<iostream>
#include<climits>
#include "graph.h"
#include<string>
#include<queue>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<algorithm>
#include<sstream>
#include<iomanip>
using namespace std;

bool isCYCLE(vector<string> from, Graph<string>& myGraph, string& startingVertex, vector<bool>& visited, Queue<string> myQ);
void printCycle(Graph<string> myGraph, vector<string>& v, string& startingVertex, Queue<string> myQ, vector<string>& to, vector<string>& from, vector<int>& dist);
void sortAndPrint(vector<string>& v);
void getStartingVertex(string& startingVertex, bool& exists, vector<string>& v);
int numElemQueue(Queue<string> myQ);
void dijkstraTable(string& startingVertex, vector<string>& v, Graph<string>& myGraph, Queue<string>& myQ, vector<string>& from, vector<string>& to, vector<bool>& marked, vector<int>& dist);
void fillVectors(vector<string>& v, vector<string>& from, vector<string>& to, vector<bool>& marked, vector<int>& dist);
void buildGraph(Graph<string>& myGraph, ifstream& readFile, vector<int> dist, vector<string> to, vector<string> from, vector<string>& v);
bool checkIfExists(string& startingVertex, vector<string> v);
bool validVertex(string& phrase, vector<string>& from);
bool DPScycle(Graph<string> myGraph, string& vertex, Queue<string> myQ, vector<bool>& visited, vector<string> from);
/////// STRING RADIX SORT
int indexValOfString(string& phrase, vector<string>& from);
int maxElemLength(const vector<string>& v);
char GetDigit(string word, int k);
vector<queue<string> > ItemsToQueues(const vector<string>& L, int k);
vector<string> QueuesToArray(vector<queue<string> >& QA, int numVals);
void RadixSort(vector<string>& L, int numDigits);
void PrintVector(const vector<string>& L);
void pad(string& word, const vector<string>& L);
void unpad(string& word, const vector<string>& L);

int main(int argc, char** argv){

	Graph<string> myGraph(50);
	Queue<string> myQ(50);
	vector<string> from;
	vector<bool> marks;
	vector<int> dist;
	vector<string> to;
	string startingVertex = "";						// starting vertex variable
	bool exists = false;							// cycle bool var

	ifstream readFile;
	readFile.open(argv[1]);
	if(!readFile.good()){
		cout << "	Bad Filename Entered on Command Line -- Now Aborting." << endl;
		return 0;
	}
	
	vector<string> v;		
	buildGraph(myGraph, readFile, dist, to, from, v);			// build graph
	readFile.close();							// close file
	readFile.open(argv[1]);							// open file
	sortAndPrint(v);							// sort and print 
	fillVectors(v, from, to, marks, dist); 					// fill vectors with arbitrary fillers
	getStartingVertex(startingVertex, exists, v);
	dijkstraTable(startingVertex, v, myGraph, myQ, from, to, marks, dist);
	printCycle(myGraph, v, startingVertex, myQ, to, from, dist);
	readFile.close();
	return 0;
}

void printCycle(Graph<string> myGraph, vector<string>& v, string& startingVertex, Queue<string> myQ, vector<string>& to, vector<string>& from, vector<int>& dist){	
/*
 * CALLS ON DPSCYCLE WHICH CALLS ON ISCYCLE -- FINDS IF THERE OCCURS A CYCLE AND THEN PRINTS RESULT
 */
	for(int i = 0; i < to.size(); i++){
		cout << right << setw(15)<< to[i] << right << setw(15) << dist[i] << right << setw(15) << from[i] << endl;
	}
	vector<bool> visited;
	bool cycle = false;
	cycle = DPScycle(myGraph, startingVertex, myQ, visited, v);

	cout << endl;
	cout << "------------------------------------------------------------------------------" << endl;
	cout << endl;
	if(cycle){
		cout << right << setw(40) << "The graph contains a cycle" << endl;	
	}else{
		cout << right << setw(40) << "The graph does not contain a cycle" << endl;
	}
	
	cout << endl;
}

void sortAndPrint(vector<string>& v){
/*
 * SORTS V AND THEN PRINTS IT
 */
	int numDigits = maxElemLength(v);	
	RadixSort(v, numDigits);
	PrintVector(v);
}

void getStartingVertex(string& startingVertex, bool& exists, vector<string>& v){
/*
 * FINDS STARTING VERTEX IN THE VECTOR
 */
	while(!exists){
		cout << "Please input your starting vertex: " ;
		getline(cin, startingVertex);
		exists = checkIfExists(startingVertex, v);
		if(!exists){
			cout << "Vertex Does Not Exist, Please Try Again: " << endl;
		}	
	}
	cout << "------------------------------------------------------------------------------" << endl;
	cout << right << setw(15)<< "Vertex" << right << setw(15) << "Distance" << right << setw(15) << "Previous" << endl;
	cout << endl;
}


int numElemQueue(Queue<string> myQ){
/*
 * FINDS SIZE OF QUEUE
 */ 
	int count = 0;
	string disregard = "";
	Queue<string> q2 = myQ;
	while(!q2.isEmpty()){
		disregard = q2.dequeue();
		count++;	
	}
	return count;
}

void dijkstraTable(string& startingVertex, vector<string>& v, Graph<string>& myGraph, Queue<string>& myQ, vector<string>& from, vector<string>& to, vector<bool>& marked, vector<int>& dist){
/*
 * SORTS THE DISTANCES AND THEN GETS GREEDY!
 */	
	bool finished = false;
	int start = 0;
	int sizeOfQ = 0;
	int min = INT_MAX;
	int weight;
	string tempTWO = "";
	string minString = "";
	int indexOf = 0;
	int distPrev = 0;
	int distNOW = 0;
	int count = 0;
	int counting = 0;
	int tempTHREE = 0;
	
	/*
 	 *	SET STARTING VERTEX TO 0-DIST AND N/A-PREV AND TRUE-MARK
  	 */
	start = indexValOfString(startingVertex, v);	// GET INDEX OF STARTING STRING
	string tempONE = v[start];			// tempONE holds startingVertex
	marked[start] = true;				// set mark = true
	dist[start] = 0;				// set dist = 0
	from[start] = "N/A";				// set from = N/A

	while(!finished){
		myGraph.GetToVertices(tempONE, myQ);	// get vertices tempONE can reach and add them to myQ
		sizeOfQ = numElemQueue(myQ);		// get the size of the queue
		for(int i = 0; i < dist.size(); i++){	// find out how many distances still need to be set
			if(dist[i] == 0){
				count++;
			}	
		}	
		if(count > 1){				// while more than the starting vertex has a distance of 0, run
			for(int i = 0; i < sizeOfQ; i++){
						
				tempTWO = myQ.dequeue();				 // get the top of the queue and pop it off
				distPrev = indexValOfString(tempONE, v);		 // get index of the "parent" vertice
				indexOf = indexValOfString(tempTWO, v);			 // get index of the "child" vertice
				if(marked[indexOf] == false){				 // if the "child" vertice is false, handle it
					weight = myGraph.WeightIs(v[distPrev], tempTWO); // get weight of "parent" vertice to "child" vertice
					distNOW = dist[distPrev] + weight;		 // add weight of "parent" to dist between "parent" and "child"
					dist[indexOf] = distNOW;			 // set dist of "child" to combined weight
					from[indexOf] = tempONE;			 // set from of "child" to "parent"
				}
			}
		}

		for(int i = 0; i < dist.size(); i++){					 // find min of distances that are not 0 and are not marked
			if((dist[i] <= min) && (dist[i] > 0) && (marked[i] == false)){
				min = dist[i];
				minString = v[i];
			}

		}	
		
		tempTHREE = indexValOfString(minString, v);				 // get index of smallest string that is not 0 and not marked
		marked[tempTHREE] = true;						 // set mark to true
		tempONE = minString;
		to[tempTHREE] = tempONE;
		

		counting++;
		if(counting == (v.size() - 1)){
			finished = true;
		}

		min = INT_MAX;
		count = 0;
	}


} 


void fillVectors(vector<string>& v, vector<string>& from, vector<string>& to, vector<bool>& marked, vector<int>& dist){
/*
 * FILLS VECTORS SO THEY ARE THE SAME SIZE AS V
 */
	for(int i = 0; i < v.size(); i++){		
		from.push_back("");;
		to.push_back(v[i]);
		marked.push_back(false);
		dist.push_back(0);
	}

}

void buildGraph(Graph<string>& myGraph, ifstream& readFile, vector<int> dist, vector<string> to, vector<string> from, vector<string>& v){
/*
 * USES PASS BY VALUE TO BE ABLE TO BUILD THE GRAPH AND READ THE FILE AT THE SAME TIME WITHOUT ACTUALLY FILLING THE OG VECTORS
 * (EXCEPT V WHICH IS PASS BY REFERENCE)
 */
	
	string line = "";
	string temp = "";
	string tempTwo = "";
	int pos = 0;
	int weight;
	bool exists = false;
	int count = 0;
	while(readFile){
		/*
		* READS FILE AND ADDS THE VALUES TO THEIR RESPECTIVE VECTORS
  		*/
		getline(readFile, line);
		pos = line.find(";");

		if(pos == -1){
			break;
		}

       		temp = line.substr(0, pos);
	        line = line.substr(pos + 1);
	        pos = line.find(";");
	        tempTwo = line.substr(0, pos);
	        line = line.substr(pos + 1);

		for(int i = 0; i < from.size(); i++){
			if(temp == from[i]){
				exists = true;
			}
		}
		
		from.push_back(temp);
		to.push_back(tempTwo);
		weight = atoi(line.c_str());
		dist.push_back(weight);

		if(!exists){
			v.push_back(temp);
			myGraph.AddVertex(temp);
		}
		exists = false;
		count++;
	}
	
	/*
	* SEE IF THERE ARE VERTICES THAT ARE UNREACHABLE AND ADD THEM TO V
 	*/
	v.resize(from.size());
	bool FROMinV = false;
	bool TOinV = false;
	for(int i = 0; i < from.size(); i++){
		for(int j = 0; j < v.size(); j++){
			if(v[j] == from[i]){
				FROMinV = true;
			}
			if(v[j] == to[i]){
				TOinV = true;
			}
		}
		if(!FROMinV){			
			v.push_back(from[i]);
		}
		if(!TOinV){
			v.push_back(to[i]);
		}
		FROMinV = false;
		TOinV = false;
	}

	// ERASE ANY ELEMENTS THAT ARE BLANK FROM RESIZING
	for(int i = 0; i < from.size(); i++){
		if(v[i] == ""){
			v.erase(v.begin() + i);
		}
	}

/*
 * THE ADDEDGE CAUSES A SEG FAULT ON GINFILE2, GINFILE4, AND GINFILE5. I WAS NEVER ABLE TO UNDERSTAND WHY, THUS NEVER ABLE TO FIX IT.
 */ 

	// ADD EDGES FOR EACH ELEMENT IN THE VECTORS
	for(int i = 0; i < dist.size(); i++){
		myGraph.AddEdge(from[i], to[i], dist[i]);
	}

	cout << endl;

}


bool checkIfExists(string& startingVertex, vector<string> v){
/*
 * CHECK IF A VERTEX EXISTS IN V
 */
	bool exists = false;

	for(int i = 0; i < v. size(); i++){
		if(v[i] == startingVertex){
			exists = true;
		}
	}

	return exists;

}

int indexValOfString(string& phrase, vector<string>& v){
/*
 *FIND THE INDEX VAL OF A STRING IN V
 */
	for(int i = 0; i < v.size(); i++){
		if(v[i] == phrase){
			return i;
		}
	}

	return -1;

}

bool validVertex(string& phrase, vector<string>& from){
/*
 * CHECK IF A VERTEX EXISTS IN FROM
 */
	for(int i = 0; i < from.size(); i++){
		if(from[i] == phrase){
			return true;
		}
	
	}

	return false;

}

bool DPScycle(Graph<string> myGraph, string& vertex, Queue<string> myQ, vector<bool>& visited, vector<string> from){
/*
 * RECURSIVELY GO THROUGH DPS TO FIND IF THERE IS A CYCLE
 */

	for(int i = 0; i < from.size(); i++){
		visited.push_back(false);
	}

	for(int i = 0; i < visited.size(); i++){
		if(!visited[i]){
			if(isCYCLE(from, myGraph, vertex, visited, myQ)){
				return true;
			}
		}
	}
	return false;

}

bool isCYCLE(vector<string> from, Graph<string>& myGraph, string& startingVertex, vector<bool>& visited, Queue<string> myQ){
/*
 * CHECK IF A VERTICE WAS ALREADY MARKED AS TRUE
 */
	
	myGraph.GetToVertices(startingVertex, myQ);
	int sizeOfQ = numElemQueue(myQ);
	int indexOf = indexValOfString(startingVertex, from);		
	visited[indexOf] = true;

	for(int i = 0; i < sizeOfQ; i++){
		startingVertex = myQ.dequeue();
		int indexOf2 = indexValOfString(startingVertex, from);
		if(!visited[indexOf2]){
			if(isCYCLE(from, myGraph, startingVertex, visited, myQ)){
				return true;
			}
		}
	}
	return false;
}



////------------------------------------------
////----------STRING RADIX SORT---------------
////------------------------------------------

int maxElemLength(const vector<string>& v){
        string current = "";
        int max = -999;
        int length = 0;
        for(int i = 0; i < v.size(); i++){
                current = v[i];
                length = current.length();
                if(length > max){
                        max = current.length();
                }
        }

        return max;

}

char GetDigit(string word, int k){
        char count = '\0';
        reverse(word.begin(), word.end());
        count = word[k];
        return count;

}

void pad(string& word, const vector<string>& L){

        int padding = maxElemLength(L);
        padding -= word.length();

        for(int i = 0; i < padding; i++){

                word += " ";

        }


}

void unpad(string& word, const vector<string>& L){

        int count = 0;

        for(int i = 0; i < word.length(); i++){
		if(i != (word.length() - 1)){
	                if((word[i] == 32) && (word[i - 1] != 32) && (word[i + 1] != 32)){
				continue;
               		}else if(word[i] == 32){
				count++;
			}
		}else if(word[i] == 32){
			count++;
		}
        }

        word.erase((word.length() - count));

}

vector<queue<string> > ItemsToQueues(const vector<string>& L, int k){
        vector<queue<string> > QA(128);

        char digitOne = '\0';
        int digitTwo = 0;
        int convertToNum;

        for(int i = 0; i < L.size(); i++){
                string word = L[i];
                pad(word, L);
                digitOne = GetDigit(word, k);
                digitTwo = int(digitOne);
                QA[digitTwo].push(word);

        }

        return QA;

}

vector<string> QueuesToArray(vector<queue<string> >& QA, int numVals){
        vector<string> L;

        string front = "";
        for(int i = 0; i < QA.size(); i++){
                while(!QA[i].empty()){
                        front = QA[i].front();
                        QA[i].pop();
                        unpad(front, L);
                        L.push_back(front);
                }
        }

        return L;

}

void RadixSort(vector<string>& L, int numDigits){

        vector<queue<string> > QA(128);
        for(int k = 0; k < numDigits; k++){
                QA = ItemsToQueues(L, k);
                L = QueuesToArray(QA, L.size());
        }

}

void PrintVector(const vector<string>& L){
	cout << "^^^^^^^^^^^^^^^^  DIJKSTRA'S ALGORITHM ^^^^^^^^^^^^^^^^" << endl;
	int count = 1;
        for(int i = 0; i < L.size(); i++){
                cout << right << setw(15) <<  L[i] ;
		if(count % 3 == 0){
			cout << endl;
		}
		count++;
        }

        cout << endl;
	cout << endl;
}


