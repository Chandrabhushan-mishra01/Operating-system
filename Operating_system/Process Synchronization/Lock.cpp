#include <iostream>
#include <thread>


using namespace std;

int shared = 0;
int lock = 0; // 0 implies no lock, 1 implies CS in use


void increment_shared_resource(){
    while(lock==1); //If CS is occupied then spin the process in an infinite loop
    lock = 1;
    shared++; //Critical Section
    lock=0;
}



void decrement_shared_resource(){
    while(lock==1); //If CS is occupied then spin the process in an infinite loop
    lock = 1;
    shared--; //Critical Section
    lock=0;
}





int main(){
    thread thread1(increment_shared_resource);
    thread thread2(decrement_shared_resource);

    thread1.join();
    thread2.join();

    cout<<"Final value: "<<shared<<endl;
}