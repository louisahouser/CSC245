#include<iostream>
#include<map>
#include<string>
#include<fstream>
#include<cstdlib>

using namespace std;

// prototypes for two methods
void fillMap(map<string, int>& myMap, ifstream& zipFile, int& numOfLines, string& line);
void compareAndFillUnzipped(map<string, int>& myMap, ofstream& unzipFile, string& line);

int main(int argc, char** argv){

	ifstream zipFile;				// initialize zippedFile object of type ifstream (input)
	zipFile.open(argv[1]); 				// open inputted file to zippedFile object

	// get a substring of the inputted file name so we can create the unzipped version
	string fileName = argv[1];
	int pos = fileName.find(".");

	// handle if file given does not have .zip
	if(!zipFile.good()){
		cout << "        Bad Filename Entered On Command Line -- Now Aborting." << endl;
		return 0;
	}else if(pos == -1){
		cout << "        File Entered Is Not A Zip File -- Now Aborting. " << endl;
		return 0;
	}
	string newFileName = fileName.substr(0, pos);
	ofstream unzipFile(newFileName.c_str());	// initialize unzipped file of type ofstream (output) that we will write into

	// string vars -> numOfChars will hold first line of file which is num of characters; line will hold each line we read using getline
	string numOfChars = "";			
	string line = "";			

	map<string, int> myMap;				// create map with string and char parameters
	getline(zipFile, numOfChars);			// get the first line of input (num of characters in unzipped)

	int numOfLines = atoi(numOfChars.c_str());	// int representation of numOfChars

	// 2 method calls -> read file and fill map; compare map to last line and fill unzipped file
	fillMap(myMap, zipFile, numOfLines, line);
	compareAndFillUnzipped(myMap, unzipFile, line);

	// close files, let user know file was unzipped, and then return 0
	zipFile.close();
	unzipFile.close();
	cout << "File Successfully Inflated Back to Original" << endl;
	return 0;

}



void compareAndFillUnzipped(map<string, int>& myMap, ofstream& unzipFile, string& line){

/*
 * Iterate through the last line of the file and build a compare string. If/when the compare string equals a value in the map,
 * convert the int to a character value and then add it to the unzipped file, and then set the compare string to empty for
 * the next value found.
 */

        string compare = "";
        for(int i = 0; i < line.length(); i++){
                compare += line[i];
                if(myMap.find(compare) != myMap.end()){	 
			char letter = char(myMap[compare]);
                        unzipFile << letter;
                        compare = "";
                }
        }

}

void fillMap(map<string, int>& myMap, ifstream& zipFile, int& numOfLines, string& line){

/*
 * WHILE ZIPFILE HAS NEXT LINE: getline and store in line variable. if still
 * looking at characters and their path code, substring line into its ascii
 * value and its path and then add to map and decrement numOfLines 
 */

        while(zipFile){
                getline(zipFile, line);
		// we do not want to add the last line to the map so we use conditional statement to check if we are at last line or not
		if(numOfLines > 0){
			int pos = line.find(" ");
			string tempKey = line.substr(0, pos);
			int key = atoi(tempKey.c_str());
			string value = line.substr(pos + 1);
                        myMap[value] = key;
                        numOfLines -= 1;
                }
        }

}


