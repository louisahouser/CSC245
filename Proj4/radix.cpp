#include<iostream>
#include<cstdlib>
#include<vector>
#include<queue>
#include<sstream>
#include<string>
#include<algorithm>

using namespace std;

int maxElemLength(const vector<int>& v);
int GetDigit(int number, int k);
vector<queue<int> > ItemsToQueues(const vector<int>& L, int k);
vector<int> QueuesToArray(vector<queue<int> >& QA, int numVals);
void RadixSort(vector<int>& L, int numDigits);
void PrintVector(const vector<int>& L);

int main(){

        vector<int> L;  // list to be sorted

        L.push_back(380);
        L.push_back(95);
        L.push_back(345);
        L.push_back(382);
        L.push_back(260);
        L.push_back(100);
        L.push_back(492);

        vector<queue<int> > QA(10);     // vector of queues indexed 0-9

        int numDigits = maxElemLength(L); // store maxElemLength of L

        RadixSort(L, numDigits);        // sort!!!!

        PrintVector(L);                 // print sorted vector!!

        return 0;
}

int maxElemLength(const vector<int>& v){

        int current = 0;
        int max = -999;
        string convertToString;
        for(int i = 0; i < v.size(); i++){
                current = v[i];
                if(current > max){
                        max = current;
                }
        }

        ostringstream str1;
        str1 << max;
        convertToString = str1.str();

        return convertToString.length();

}

int GetDigit(int number, int k){
        ostringstream str1;
        str1 << number;
        string convertToString = str1.str();
        reverse(convertToString.begin(), convertToString.end());

        int digit = 0;
        string str = "";
        str = convertToString[k];
        digit = atoi(str.c_str());

        return digit;

}

vector<queue<int> > ItemsToQueues(const vector<int>& L, int k){
        vector<queue<int> > QA(10);

        int digitOne = 0;
        int convertToNum;
        for(int i = 0; i < L.size(); i++){

                digitOne = GetDigit(L[i], k);
                QA[digitOne].push(L[i]);
        }

        return QA;

}

vector<int> QueuesToArray(vector<queue<int> >& QA, int numVals){
        vector<int> L;

        int front = 0;
        for(int i = 0; i < QA.size(); i++){
                while(!QA[i].empty()){
                        front = QA[i].front();
                        QA[i].pop();
                        L.push_back(front);
                }

        }

        return L;

}

void RadixSort(vector<int>& L, int numDigits){

        vector<queue<int> > QA(10);
        for(int k = 0; k < numDigits; k++){
                QA = ItemsToQueues(L, k);
                L = QueuesToArray(QA, L.size());
        }

}

void PrintVector(const vector<int>& L){
        for(int i = 0; i < L.size(); i++){
                cout << L[i] << " ";
        }

        cout << endl;
}

