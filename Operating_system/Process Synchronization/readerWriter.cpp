#include <iostream>
#include <cstdlib>
#include <chrono>
#include <mutex>
#include <thread>
using namespace std;


mutex mtx;
mutex wrt;
int readcnt = 0;
int shared_resource = 0;


void reader(int reader_id){
    mtx.lock(); //To ensure that no two readers try to modify the readcnt variable simulatneously
    readcnt++;
    if(readcnt==1){
        wrt.lock(); //To ensure that no writer enters the critical section, once a reader has enetered or one or more readers has entered the critical section, this is done through this code which ensures that once the number of readers has increased to one,the wrt mutex is now in a locked state
    };
    mtx.unlock();
    cout<<"READER WITH READER ID: "<<reader_id<<" READING RESOURCE: "<<shared_resource<<endl;
    mtx.lock(); //To ensure that no two readers try to modify the readcnt variable simultaneously
    readcnt--;
    if(readcnt==0){    //If no more readers are in the critical section then writers should be allowed to access it and so should other readers if the number of readers has become zero
        wrt.unlock();
        mtx.unlock();
    }
}



void writer(int writer_id){
    wrt.lock();
    cout<<"WRITER WITH WRITER ID: "<<writer_id<<" WRITING ON THE RESOURCE: "<<shared_resource<<endl;
    wrt.unlock();
}


int main(){
    int r = 5;  //number of readers
    int w = 3;  //number of writers
    thread readers[r];
    thread writers[w];
    for(int i=0;i<r;i++){
        readers[i] = thread(reader, i);
    }
    for(int i=0;i<w;i++){
        writers[i] = thread(writer, i);
    }
    for(int i=0;i<r;i++){
        readers[i].join();
    }
    for(int i=0;i<w;i++){
        writers[i].join();
    }
}
