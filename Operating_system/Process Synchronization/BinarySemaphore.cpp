#include <iostream>
#include <thread>

class BinarySemaphore {
public:
    BinarySemaphore(bool state) : state_(state) {}

    void acquire() {
        while (!state_);
        state_ = false;
    }

    void release() {
        state_ = true;
    }

private:
    bool state_;
};

BinarySemaphore sem(true);
int sharedVariable = 0;

void incrementFunction(int id) {
    sem.acquire();
    sharedVariable++;
    sem.release();
}

void decrementFunction(int id) {
    sem.acquire();
    sharedVariable--;
    sem.release();
}

int main() {
    std::thread t1(incrementFunction, 1);
    std::thread t2(decrementFunction, 2);

    t1.join();
    t2.join();

    std::cout << "Final value of sharedVariable: " << sharedVariable << std::endl;

    return 0;
}

