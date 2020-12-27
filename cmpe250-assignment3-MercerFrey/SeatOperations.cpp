/*
Notes: Anything you want to say about your code that will be helpful in the grading process.
Cool project
*/
#include "SeatOperations.h"
using namespace std;
int finder(int line , int seatNumber){
    int result=0;
    result = seatNumber % line;
    if (result == 0)
        return line;
    return result;
}


SeatOperations::SeatOperations(int N, int M){
    // IMPLEMENT ME!
    this->N=N;
    this->M=M;


    lines[0].resize((N));
    lines[1].resize(M);


}

void SeatOperations::addNewPerson(int personType, const string& ticketInfo){
    // IMPLEMENT ME!
    Person person;
    person.type=personType;
    person.line= ticketInfo[0] - 'A';
    person.seatNumber=stoi(ticketInfo.substr(1, ticketInfo.size() - 1));


    int lastLine=person.line;
    vector<Person> *ptrLastLine = &lines[lastLine];

    int lastSeat = finder(ptrLastLine->size(),person.seatNumber);

    swap(person, (*ptrLastLine)[lastSeat -1]);

    while (person.type!=0) {


        if (person.type == 1) {
            lastLine=(lastLine+1)%2;
            ptrLastLine = &lines[(lastLine)];
            lastSeat = finder(ptrLastLine->size(), person.seatNumber);
            swap(person, (*ptrLastLine)[lastSeat - 1]);
        }

        else if (person.type == 2) {

            if (lastSeat == ptrLastLine->size()){
                lastLine = (lastLine+1)%2;
                ptrLastLine= &lines[lastLine];
                lastSeat=1;
                swap(person,(*ptrLastLine)[lastSeat-1]);
            }
            else {
                lastSeat+=1;
                swap(person,(*ptrLastLine)[lastSeat-1]);
            }
        }
        else {
           person.type3LastOperation++;
           int distance = 2*person.type3LastOperation -1;
           distance%(N+M);
           for(int i=0; i<distance; i++){
               lastSeat++;
               if ( lastSeat == ptrLastLine->size()+1){
                   lastSeat=1;
                   lastLine=1-lastLine;
                   ptrLastLine=&lines[lastLine];
               }
           }
           swap(person, (*ptrLastLine)[lastSeat-1]);

        }
    }
}

void SeatOperations::printAllSeats(ofstream& outFile){
    // IMPLEMENT ME!

    for(int i=0; i<N; i++ ){
        if ( lines[0][i].type == 0){
            outFile << 0<< endl;
        }
        else {
            outFile <<  lines[0][i].type<<" " << (char)('A'+lines[0][i].line) <<lines[0][i].seatNumber<< endl;
        }
    }
    for (int i=0; i<M ; i++){
        if ( lines[1][i].type == 0){
            outFile << 0<< endl;
        }
        else {
            outFile <<  lines[1][i].type<<" " << (char)('A'+lines[1][i].line)<<lines[1][i].seatNumber << endl;
        }
    }

}

