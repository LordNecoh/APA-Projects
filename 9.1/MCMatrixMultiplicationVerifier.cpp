#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

const int N = 100;
const int IndexToChange = 5;
const int Runs = 100;

const int matrixNumbers[5] = {-2, -1, 0, 1, 2};

vector<vector<int>> matrixBuilder(int n){
    vector<vector<int>> matrix(N, vector<int>(n, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix[i][j] = matrixNumbers[rand() % 5];
        }
    }
    return matrix;
}

vector<vector<int>> matrixMultiplier(vector<vector<int>> A, vector<vector<int>> B){
    vector<vector<int>> C(N, vector<int>(N, 0));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

vector<int> randomVector(int n){
    vector<int> v = vector<int>(n, 0);
    for(int i = 0; i < n; i++){
        v[i] = rand() % 2;
    }
    return v;
}

vector<int> matrixVectorMultiplier(vector<vector<int>> A, vector<int> v){
    vector<int> result = vector<int>(N, 0);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            result[i] += A[i][j] * v[j];
        }
    }
    return result;
}

//Returns true if probabily C = AB, false otherwise
bool MCMatrixMultiplicationVerifier(vector<vector<int>> A, vector<vector<int>> B, vector<vector<int>> C, int k){
    for(  int i=0; i < k; i++){
        //Inizilazing vectors r, s, t, u
        vector<int> r = randomVector(N);
        vector<int> s = matrixVectorMultiplier(B, r);
        vector<int> t = matrixVectorMultiplier(A, s);
        vector<int> u = matrixVectorMultiplier(C, r);
        
       if (t != u) return false;    //If t != u, it is certanly false, 
                                    //Otherwise could be true so we check again for another r
    }
    return true;
}
    



vector<bool> singleRun(vector<vector<int>> A){

    //Inizializing matrixes, C = AB, A and B are made of random integer numbers from -2 to 2
    vector<vector<int>> B = matrixBuilder(N);
    vector<vector<int>> C = matrixMultiplier(A, B);

    vector<bool>returnVector = vector<bool>(3, false);

    C[IndexToChange][IndexToChange]++;

    for(int k = 5; k <= 20; k*=2){   //Running the test with k = 5, 10, 20
        bool result = MCMatrixMultiplicationVerifier(A, B, C, k);

        //Writing the result on a file
        ofstream file;
        file.open("MCMatrixMultiplicationVerifier.txt", ios::app);
        file << '\t' << "k = " << k << ": " << result << endl;
        if(k == 20) file << endl;   //Adding a new line at the end of the run
        file.close();

        switch(k){
            case 5:
                returnVector[0] = result;
                break;
            case 10:
                returnVector[1] = result;
                break;
            case 20:
                returnVector[2] = result;
                break;
        }
    }
    return returnVector;
}


int main(){
    srand(time(NULL));
    vector<vector<int>> A = matrixBuilder(N);

    //Variables to store result distribution
    int r000 = 0;
    int r001 = 0;
    int r010 = 0;
    int r011 = 0;
    int r100 = 0;
    int r101 = 0;
    int r110 = 0;
    int r111 = 0;

    ofstream file;
    file.open("MCMatrixMultiplicationVerifier.txt", ios::app);

    for(int i = 0; i < Runs; i++){      //Running the test 100 times
        
        
        //Writing the result on a file
        file << "Run n. " << i << ": " << endl;
        vector<bool> result = singleRun(A);

        //updating the result distribution
        if(result[0] && result[1] && result[2]) r111++;
        if(result[0] && result[1] && !result[2]) r110++;
        if(result[0] && !result[1] && result[2]) r101++;
        if(result[0] && !result[1] && !result[2]) r100++;
        if(!result[0] && result[1] && result[2]) r011++;
        if(!result[0] && result[1] && !result[2]) r010++;
        if(!result[0] && !result[1] && result[2]) r001++;
        if(!result[0] && !result[1] && !result[2]) r000++;
        
        
    }
    

    //Writing the result distribution  file in order from r000 to r111, three on each line

    file << endl << "Result distribution: " << endl;
    file << "r000: " << r000 << " r001: " << r001 << " r010: " << r010 << endl;
    file << "r011: " << r011 << " r100: " << r100 << " r101: " << r101 << endl;
    file << "r110: " << r110 << " r111: " << r111 << endl;
}