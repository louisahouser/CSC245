#include<iostream>
#include<cstdlib>
#include<vector>
#include<queue>
#include<sstream>
#include<string>
#include<algorithm>

using namespace std;

int maxElemLength(const vector<string>& v);
char GetDigit(string word, int k);
vector<queue<string> > ItemsToQueues(const vector<string>& L, int k);
vector<string> QueuesToArray(vector<queue<string> >& QA, int numVals);
void RadixSort(vector<string>& L, int numDigits);
void PrintVector(const vector<string>& L);
void pad(string& word, const vector<string>& L);
void unpad(string& word, const vector<string>& L);

int main(){

        vector<string> L;       // list to be sorted

        L.push_back("zebra");
        L.push_back("apple");
        L.push_back("orange");
        L.push_back("can");
        L.push_back("candy");
        L.push_back("a");
        L.push_back("top");
        L.push_back("pumpkin");
        L.push_back("today");
        L.push_back("parade");

        vector<queue<string> > QA(128); // vector of queues indexed 0-9

        int numDigits = maxElemLength(L); // store maxElemLength of L

        RadixSort(L, numDigits);        // sort!!!!

        PrintVector(L);                 // print sorted vector!!

        return 0;
}

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
                if(word[i] == 32){
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
        for(int i = 0; i < L.size(); i++){
                cout << L[i] << " ";
        }

        cout << endl;
}

