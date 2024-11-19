#include "huffman.h"

#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<cmath>
#include<cstdlib>

using namespace std;


// prototypes for our main
void insertThenBuild(double& countChars, HuffmanTree& HT, ifstream& unzipFile, ofstream& zipFile, map<char, int>& m);
void writeIntoZip(bool& table, bool& help, double& countChars, HuffmanTree& HT, ifstream& unzipFile, ofstream& zipFile, map<char, int>& m);
void getFileIndex(bool& exitValue, bool& table, bool& help, int& fileIndex, int& argc, char**& argv);

int main(int argc, char** argv){
	HuffmanTree HT;				// initialize huffman tree object
	/*
	 * account for if --t or --h was given
	 */
	bool table = false;
	bool help = false;
	int fileIndex = 1;
	bool exitValue = false;		

	getFileIndex(exitValue, table, help, fileIndex, argc, argv);
	if(exitValue)
		return 0;	
	// initialize unzipFile and open input file	
	ifstream unzipFile;
	unzipFile.open(argv[fileIndex]);
	if(!unzipFile.good()){
                cout << "        Bad Filename Entered On Command Line -- Now Aborting." << endl;
		return 0;
	}
	// create new file with the input file name plus .zip
	string fileName = argv[fileIndex];
	fileName.c_str();
	string removeName = "rm " + fileName;
	fileName += ".zip";
	ofstream zipFile(fileName.c_str());

	// create map that will carry character and frequency; create double var for compression later
        map<char, int> m;
	double countChars = 0;

	// call methods to read file, build tree, and then write into zippedfile
	insertThenBuild(countChars, HT, unzipFile, zipFile, m);
        unzipFile.close();
        unzipFile.open(argv[fileIndex]);
	writeIntoZip(table, help, countChars, HT, unzipFile, zipFile, m);

	// close files and exit
	unzipFile.close();
	zipFile.close();
	system(removeName.c_str());
	return 0;

}

void getFileIndex(bool& exitValue, bool& table, bool& help, int& fileIndex, int& argc, char**& argv){

	// account for --t or --help
        string fileName = argv[fileIndex];
        fileName.c_str();
        if(fileName == "--t"){
                fileIndex = 2;
                table = true;
        }else if(fileName == "--help"){
                help = true;
                fileIndex = 2;
        }
        // exit and send message if second arg exists and first wasnt help or table
        else if(argc > 2){
                cout << "ZIP: Invalid format. \nTry `ZIP --help' for more information." << endl;
                exitValue = true;
        }                                                
}



void insertThenBuild(double& countChars, HuffmanTree& HT, ifstream& unzipFile, ofstream& zipFile, map<char,int>& m){
	
	/*
 	* READ FILE AND CREATE MAP THAT COUNTS FREQUENCIES
	*/
	char ch;
	while(unzipFile){
		unzipFile.get(ch);
		/*
 		* LOOK TO SEE IF IT EXISTS IN THE MAP ALREADY; IF IT DOES THEN INCREASE ITS VALUE,
 		* IF IT DOES NOT THEN ADD IT TO MAP AND SET ITS VALUE BY ONE.
  		*/
	        if(m.find(ch) == m.end()){
			m[ch] = 1;
			countChars++;		// increase countChars by one so we can use later in program
		}else{
			m[ch] += 1;	
		}
		
	}

	m['\n'] -= 1;

	/*
 	* ITERATE THROUGH CHARS AND IF WE HAVE A FREQUCNY FOR IT GREATER THAN OR EQUAL TO 1, INSERT TO TREE
  	*/
	for(char ch = char(0); ch <= char(126); ch++){

		if(m[ch] >= 1){
			HT.insert(ch, m[ch]);
		}
	
	}

	HT.build(); 				// BUILD TREE now that we have inserted all of our nodes



}

void writeIntoZip(bool& table, bool& help, double& countChars, HuffmanTree& HT, ifstream& unzipFile, ofstream& zipFile, map<char,int>& m){

	// insert number of chars to the first line of our zipped file
	zipFile << countChars << endl;

	/*
 	* FOR LOOP TO CHECK IF CHARACTER IS IN OUR TREE. IF IT IS THEN
 	* STORE ITS ASCII VALUE AND THEN WRITE IT INTO OUR ZIPFILE AS WELL 
 	* AS ITS GETCODE RETURNED VALUE 	
  	*/
	for(char ch = char(1); ch <= char(126); ch++){

		if(HT.inTree(ch)){
			int ascii = int(ch);
			zipFile << ascii << " " << HT.GetCode(ch) << endl;
		}
	}

	char ch;			      // ch will be used to read input file
	int bits = 0; 			      // var to keep track of bits ; will be used for compression ratio
	int countTotalChars = 0;	      // count number of chars and how many times they are printed; will be used for compression ratio

	/*
 	* READ FILE AND WRITE INTO OUR ZIPPED FILE THE GETCODE FOR EACH
 	* CHARACTER WE GET; INCREASE COUNTTOTALCHARS AS WE WRITE INTO
 	* AND COUNT NUMBER OF 0'S AND 1'S WE ADD WHICH ARE OUR BITS	 	
  	*/
	while(unzipFile.get(ch)){
		string code = HT.GetCode(ch);
		zipFile << HT.GetCode(ch);
		countTotalChars++;
		for(int i = 0; i < code.length(); i++){
			bits++;
		}
	}
	
	
	/*
 	* IF TABLE OR HELP HAS BEEN SET TO TRUE THEN PRINT THEIR RESPECTIVE INFO
 	*/ 
	if(table){
		HT.PrintTable();
	}else if(help){

		cout << "Usage: ZIP [OPTION]... [FILE]..." << endl;
		cout << "Compress a text file using Huffman encoding." << endl;
		cout << endl;
		cout << "  --t              Display the Huffman encoding table." << endl;
 		cout << " --help           Provide help on command." << endl;

	}

	// CREATE COMPRESSION RATIO
	double compressionRatio = floor((1 - (double(bits)/(double(countTotalChars) * 8.0))) * 10000) / 100;

	// let user know we successfully compressed to however many bits and the compression ratio
	cout << "File Successfully Compressed To " << bits << " Bits (" << compressionRatio << "% Less)." << endl;

		
}


