#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>
#define buff_size 10




int generateRandomNumber(int min, int max) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    return min + std::rand() % (max - min + 1);
}

int i=0,j=1; //i for producer, j for consumer
bool flag[2] = {false, false};
int turn = 0;
int buffer[buff_size];
int in = 0;
int out = 0;
int count = 0;

void displayStats(){
    std::cout<<"BUFFER: ";
    for(int i=0;i<buff_size;i++){
        std::cout<<buffer[i]<<" ";
    }
    std::cout<<" IN:"<<in<<" OUT:"<<out<<" "<<" COUNT: "<<count<<"\n";
}
void producer(){
    flag[i] = true;
    turn = j;
    while(flag[j] && turn==j);
    
    // Critical Section Start
    if(count<buff_size){
        int x = generateRandomNumber(0,10);
        buffer[in] = x;
        in = (in+1)%buff_size;
        count++;
    }
    std::cout<<"PERFOMED PRODUCE OPERATION: ";
    displayStats();
        
    // Critical Section End

    flag[i] = false;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}


void consumer(){
    flag[j] = true;
    turn = i;
    while(flag[i] && turn==i);



    // Critical Section Start
    if(count>0){
        int x = buffer[out];
        buffer[out] = -1;
        out = (out+1)%10;
        count--;
    }
    std::cout<<"PERFORMED CONSUME OPERATION: ";
    displayStats();
    // Critical Section End


    flag[j] = false;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

}
void producer_code() {
    while (true) {
        producer();
    }
}

void consumer_code() {
    while (true) {
        consumer();
    }
}







int main(){
    std::thread producerThread(producer_code);
    std::thread  consumerThread(consumer_code);

    producerThread.join();
    consumerThread.join();
}
