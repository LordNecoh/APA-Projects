#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <fstream>

//Calcola il valore atteso dal file "MCByzantine.txt"

using namespace std;

int main(){
    ifstream file;
    file.open("MCByzantine.txt");
    if (!file.is_open()){
        cout << "Errore nell'apertura del file" << endl;
        return 1;
    }
    double sum = 0;
    double temp;
    int count = 0;
    while (file >> temp){
        sum += temp;
        count++;
    }
    cout << "Valore atteso: " << sum/count << endl;
    file.close();
    return 0;
}