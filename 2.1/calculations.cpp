#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <time.h>
#include <cmath>

using namespace std;
int const RunNumber = 100000;
string const outputFileName = "output.txt";

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

    ofstream outputFile("values.txt");
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
    float avgVal = averageValue();
    cout << "Average number of comparisons: " << avgVal << endl;
    float empVar = empiricalVariance(avgVal);
    cout << "Empirical variance: " << empVar << endl;
}