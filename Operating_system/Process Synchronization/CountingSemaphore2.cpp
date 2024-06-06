#include <iostream>
#include <thread>
using namespace std;

class Semaphore{
    public:
        Semaphore(int noOfInstancesOfResource){
            val = noOfInstancesOfResource;
        }
        void wait(){
            while(val<=0);
            val--;
        }
        void signal(){
            val++;
        }

    private:
        int val;
};


int shared_resource = 0;
Semaphore S(1);
int count1 =0;
int count2 =0;

void increment(int id){
    S.wait();
    shared_resource++;
    S.signal();
}


void decrement(int id){
    S.wait();
    shared_resource--;
    S.signal();
}



int main(){
    
    int n = 1000;
    // int m = 1000;
    
    
    thread inc[n];
    thread dec[n];
    
    for(int i=0;i<n;i++){
        inc[i] = thread(increment, i);
    }
    for(int i=0;i<n;i++){
        dec[i] = thread(decrement, i);
    }
    for(int i=0;i<n;i++){
        inc[i].join();
        dec[i].join();
    }
    
    cout<<"Final value of shared resource: "<<shared_resource<<endl;
}
