#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <assert.h>
#include <fstream>
#include <time.h>

using namespace std;

#define ATTACK 1
#define RETREAT 0

const int RunNumber = 1024; //Numero di run
const int N = 4; //Numero di generali totali
const int T = 3; //Numero di generali affidabili
bool bellTower; //Variabile casuale comune

enum names {ARMANDO, BOB, CARL, DAVID};

struct general{
    names name;
    bool curr_decision; //b(j), la decisione che il generale intende prendere e che comunichera' al prossimo round
    
    //Le lettere ricevute dai generali
    bool letter_A; //La decisione comunicata dal generale A
    bool letter_B; //La decisione comunicata dal generale B
    bool letter_C; //La decisione comunicata dal generale C
    bool letter_D; //La decisione comunicata dal generale D
} Armando, Bob, Carl, David;

struct Tally{
    int A = 0;
    int B = 0;
    int C = 0;
};

struct Maj{
    bool A;
    bool B;
    bool C;
};

void broadcast_message(int decision, general from){    //Manda la decisione a tutti i generali (incluso se stesso)
    switch (from.name){
        case ARMANDO:
            Armando.letter_A = decision;
            Bob.letter_A = decision;
            Carl.letter_A = decision;
            David.letter_A = decision;
            break;
        case BOB:
            Armando.letter_B = decision;
            Bob.letter_B = decision;
            Carl.letter_B = decision;
            David.letter_B = decision;
            break;
        case CARL:
            Armando.letter_C = decision;
            Bob.letter_C = decision;
            Carl.letter_C = decision;
            David.letter_C = decision;
            break;
        case DAVID:
            Armando.letter_D = decision;
            Bob.letter_D = decision;
            Carl.letter_D = decision;
            David.letter_D = decision;
            break;
    }
}

void spyLetter(){
    //David e' il generale disonesto, la sua lettera e' ad ognuno 1- la propria decisione
    Armando.letter_D = 1 - Armando.curr_decision;
    Bob.letter_D = 1 - Bob.curr_decision;
    Carl.letter_D = 1 - Carl.curr_decision;
}

void evening(){
    //La sera, ognuno invia la propria decisione agli altri generali
    broadcast_message(Armando.curr_decision, Armando);
    broadcast_message(Bob.curr_decision, Bob);
    broadcast_message(Carl.curr_decision, Carl);
    spyLetter();
}



bool majNtally(general &me, int &tally){
    //Ritorna il valore maggioritario tra le lettere ricevute, e imposta tally al numero di volte in cui compare
    int attack = 0;
    int retreat = 0;
    if(me.letter_A == ATTACK) attack++;
    else retreat++;
    if(me.letter_B == ATTACK) attack++;
    else retreat++;
    if(me.letter_C == ATTACK) attack++;
    else retreat++;
    if(me.letter_D == ATTACK) attack++;
    else retreat++;
    if(attack > retreat) {
        tally = attack;
        return ATTACK;
    }
    tally = retreat;
    return RETREAT;
}

int MCByzantineGeneral(Maj& maj, Tally& tally){
    //Ritorna 1 se la decisione finale e' ATTACK, 0 se e' RETREAT, -1 se non si e' raggiunta una decisione
    
    int final_decision = -1;

    //Analisi Armando
    if(tally.A >= T){
        Armando.curr_decision = maj.A;
        if(maj.A == bellTower){
            assert( (tally.B < T || maj.B == maj.A )&& (tally.C < T || maj.C == maj.A) );
            final_decision = maj.A;
        }
    } else {
        Armando.curr_decision = bellTower;
    }

    //Analisi Bob
    if(tally.B >= T){
        Bob.curr_decision = maj.B;
        if(maj.B == bellTower){
            assert( (tally.A < T || maj.A == maj.B )&& (tally.C < T || maj.C == maj.B) );
            final_decision = maj.B;
        }
    }  else {
        Bob.curr_decision = bellTower;
    }

    //Analisi Carl
    if(tally.C >= T){
        Carl.curr_decision = maj.C;
        if(maj.C == bellTower){
            assert( (tally.A < T || maj.A == maj.C )&& (tally.B < T || maj.B == maj.C) );
            final_decision = maj.C;
        }
    } else {
        Carl.curr_decision = bellTower;
    }

    return final_decision;
}

int run(){
    //Inizializzazioni
    Armando.curr_decision = ATTACK;
    Bob.curr_decision = ATTACK;
    Carl.curr_decision = RETREAT;

    //Inizio algoritmo
    
    int finalDecision = -1;

    Maj maj;
    Tally tally;
    int round = 0;  
    while(finalDecision == -1){
        round++;
        //Trasmetti b(j) agli altri n-1 processi e
        //ricevi i valori spediti dagli altri n − 1 processi
        evening();
    
        //maj(j) ← valore maggioritario tra i ricevuti (incluso il proprio)
        //tally(j) ← numero dei valori uguali a maj(j)
        maj.A = majNtally(Armando, tally.A);
        maj.B = majNtally(Bob, tally.B);
        maj.C = majNtally(Carl, tally.C);

        bellTower = rand() % 2;

        finalDecision = MCByzantineGeneral(maj, tally);
    }

    return round;
}

int main(){
    

    //Inizializzazioni
    Armando.name = ARMANDO;
    Bob.name = BOB;
    Carl.name = CARL;
    David.name = DAVID;
    srand(time(NULL));

    ofstream output;
    output.open("MCByzantine.txt");
    for(int i = 0; i < RunNumber; i++){
        output << run() << endl;
    }
    output.close();
    
}
