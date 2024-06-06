#include <iostream>
#include <thread>

class Semaphore {
public:
    Semaphore(int count) {
        count_ = count;
    }

    void acquire() {
        while (count_ == 0);
        count_--;
    }

    void release() {
        count_++;
    }

private:
    int count_;
};

Semaphore sem(1); // Initialize semaphore with count 1
int sharedVariable = 0; // Shared variable between threads

void incrementFunction(int id) {
    sem.acquire(); // Acquire semaphore
    std::cout << "Thread " << id << " is inside the increment critical section." << std::endl;
    // Incrementing the shared variable
    sharedVariable++;
    std::cout << "Thread " << id << " incremented sharedVariable to: " << sharedVariable << std::endl;
    // Simulating some work
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Thread " << id << " is outside the increment critical section." << std::endl;
    sem.release(); // Release semaphore
}

void decrementFunction(int id) {
    sem.acquire(); // Acquire semaphore
    std::cout << "Thread " << id << " is inside the decrement critical section." << std::endl;
    // Decrementing the shared variable
    sharedVariable--;
    std::cout << "Thread " << id << " decremented sharedVariable to: " << sharedVariable << std::endl;
    // Simulating some work
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Thread " << id << " is outside the decrement critical section." << std::endl;
    sem.release(); // Release semaphore
}

int main() {
    std::thread t1(incrementFunction, 1);
    std::thread t2(decrementFunction, 2);

    t1.join();
    t2.join();

    std::cout << "Final value of sharedVariable: " << sharedVariable << std::endl;

    return 0;
}

