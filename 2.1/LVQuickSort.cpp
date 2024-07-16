#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <time.h>
#include <cmath>

using namespace std;

int listDim = 10000;
int compCount = 0;
int const RunNumber = 100000;
string const outputFileName = "output.txt";

vector<int> generateList(){
    vector<int> list;
    for(int i = 0; i < listDim; ++i){
        list.push_back(rand() % listDim);
    }
    return list;
}

void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

void printList(vector<int> list){
    for(int i = 0; i < list.size(); ++i){
        cout << list[i] << " ";
    }
    cout << endl;
}

vector<int> LVQuickSort(vector<int> list){
    if(list.size() <= 1){
        return list;
    }
    int pivotIndex = rand() % list.size();
    int pivot = list[pivotIndex];
    vector<int> left;
    vector<int> right;
    for(int i = 0; i < list.size(); ++i){
        compCount++;
        if(i == pivotIndex){
            continue;
        }
        if(list[i] < pivot){
            left.push_back(list[i]);
        } else {
            right.push_back(list[i]);
        }
    }
    left = LVQuickSort(left);
    right = LVQuickSort(right);
    left.push_back(pivot);
    left.insert(left.end(), right.begin(), right.end());
    return left;
}

void ManySorts(vector <int> list){

    //Preparing output file
    ofstream outputFile(outputFileName);
    if(!outputFile.is_open()){
        cerr << "error opening Output file";
        return;
    }
    
    //Preparing list
    vector<int> backupList = list;

    for(int i=0; i < RunNumber; ++i){
        compCount = 0;
        list = LVQuickSort(list);
        outputFile << compCount << endl;
        list = backupList;
    }
}

float averageValue(){
    ifstream inputFile(outputFileName);
    if(!inputFile.is_open()){
        cerr << "error opening Output file";
        return -1;
    }
    float sum = 0;
    int temp;
    
    for(int i = 0; i < RunNumber; ++i){
        inputFile >> temp;
        sum += temp;
    }

    int avgVal = sum/RunNumber;

    ofstream outputFile("values.txt", ios::app);
    if(!outputFile.is_open()){
        cerr << "error opening Output file";
        return -1;
    }
    outputFile << "Average number of comparisons: " << avgVal << endl;
    return avgVal;
}

float empiricalVariance(float avgVal){
    ifstream inputFile(outputFileName);
    if(!inputFile.is_open()){
        cerr << "error opening Output file";
        return -1;
    }
    
    float sum = 0;
    int temp;
    for(int i = 0; i < RunNumber; ++i){
        inputFile >> temp;
        sum +=(temp - avgVal)*(temp - avgVal);
    }

    float empVariance = sum/(RunNumber-1);

    ofstream outputFile("values.txt", ios::app);
    if(!outputFile.is_open()){
        cerr << "error opening Output file";
        return -1;
    }
    outputFile << "Empirical variance: " << empVariance << endl;
    outputFile << "Standard Deviation: " << sqrt(empVariance) << endl;
    return empVariance;

}

int main(){
    srand(time(NULL));
    vector<int> list = generateList();
    cout << "Original List: ";
    printList(list);
    cout << endl;
    ManySorts(list);
    float avgVal = averageValue();
    cout << "Average number of comparisons: " << avgVal << endl;
    float empVar = empiricalVariance(avgVal);
    cout << "Empirical variance: " << empVar << endl;
}  