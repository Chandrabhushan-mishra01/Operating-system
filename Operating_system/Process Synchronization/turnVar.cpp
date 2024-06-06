#include <iostream>
#include <thread>


using namespace std;

int shared = 0;
int turn = 0; // 0 implies no lock, 1 implies CS in use


void increment_shared_resource(){
    while(turn!=0); //While it's not the turn of this process, it will be spun into an infinite loop
    shared++; //Critical Section
    turn=1; //After this process finishes execution it will pass it's turn token to the next process
}



void decrement_shared_resource(){
    while(turn!=1); //While it's not the turn of this process, it will be spun into an infinite loop
    shared--; //Critical Section
    turn=0; ////After this process finishes execution it will pass it's turn token to the first process again
}





int main(){
    thread thread1(increment_shared_resource);
    thread thread2(decrement_shared_resource);

    thread1.join();
    thread2.join();

    cout<<"Final value: "<<shared<<endl;
}
