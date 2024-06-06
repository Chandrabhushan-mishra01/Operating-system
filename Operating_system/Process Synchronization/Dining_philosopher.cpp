#include <iostream>
#include <vector>

using namespace std;

#define thinking 1
#define hungry 2
#define eating 3

vector<int> chopsticks = {1, 1, 1, 1, 1};
vector<int> philosophers = {thinking, thinking, thinking, thinking, thinking};

int eat(int pos) {
    if (chopsticks[pos] == 1 && chopsticks[(pos + 1) % 5]) {
        chopsticks[pos] = 0;
        chopsticks[(pos + 1) % 5] = 0;
        philosophers[pos] = eating;
        cout << "Philosopher " << pos << " is eating" << endl;
        return 1;
    } else {
        philosophers[pos] = hungry;
        cout << "Philosopher " << pos << " was not able to eat, they are still hungry" << endl;
        return 0;
    }
}

void think(int pos) {
    philosophers[pos] = thinking;
    chopsticks[pos] = 1;
    chopsticks[(pos + 1) % 5] = 1;
    cout << "Philosopher " << pos << " is thinking" << endl;
    if (philosophers[(pos - 1) % 5] == hungry) {
        eat((pos - 1) % 5);
    } else if (philosophers[(pos + 1) % 5] == hungry) {
        eat((pos + 1) % 5);
    }
}

int main() {
    int run = 1;
    while (run) {
        cout << "\nChopsticks available: ";
        for (int i = 0; i < 5; i++) {
            if (chopsticks[i] == 1) {
                cout << i << " ";
            }
        }
        cout << "\n\nPhilosopher states - \n";
        for (int i = 0; i < 5; i++) {
            cout << "Philosopher " << i << " is ";
            if (philosophers[i] == thinking) {
                cout << "thinking" << endl;
            } else if (philosophers[i] == hungry) {
                cout << "hungry" << endl;
            } else if (philosophers[i] == eating) {
                cout << "eating" << endl;
            }
        }
        int philosopher;
        cout << "\n\nEnter philosopher no.: ";
        cin >> philosopher;
        int action;
        cout << "\nEnter action (1. eat, 2. think): ";
        cin >> action;
        if (action == 1) {
            eat(philosopher);
        } else if (action == 2) {
            think(philosopher);
        } else {
            cout << "Invalid Choice";
        }
        cout << "\nContinue? (1/0): ";
        cin >> run;
    }
    return 0;
}
