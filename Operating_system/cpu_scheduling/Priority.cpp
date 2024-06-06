#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_PROCESS 50

// Making a struct to hold the given input 
struct Process {
    int at, bt, pr, pno;
};

Process proc[MAX_PROCESS];

// Writing comparator function to sort according to priority if arrival time is the same 
bool comp(Process a, Process b) {
    if (a.at == b.at) {
        return a.pr < b.pr;
    } else {
        return a.at < b.at;
    }
}

// Function to get input from the user
void get_input(int n) {
    cout << "Enter Arrival Time, Burst Time, and Priority for each process:\n";
    for (int i = 0; i < n; ++i) {
        cout << "For Process " << i + 1 << ":\n";
        cout << "Arrival Time: ";
        cin >> proc[i].at;
        cout << "Burst Time: ";
        cin >> proc[i].bt;
        cout << "Priority: ";
        cin >> proc[i].pr;
        proc[i].pno = i + 1;
    }
}

// Function to calculate waiting time using FCFS Algorithm
void get_wt_time(int wt[], int n) {
    int service[MAX_PROCESS];
    service[0] = proc[0].at;
    wt[0] = 0;

    for (int i = 1; i < n; i++) {
        service[i] = proc[i - 1].bt + service[i - 1];
        wt[i] = service[i] - proc[i].at;
        if (wt[i] < 0) {
            wt[i] = 0;
        }
    }
}

// Function to calculate turnaround time
void get_tat_time(int tat[], int wt[], int n) {
    for (int i = 0; i < n; i++) {
        tat[i] = proc[i].bt + wt[i];
    }
}

// Function to find Gantt Chart
void findgc(int n) {
    int wt[MAX_PROCESS], tat[MAX_PROCESS];
    double wavg = 0, tavg = 0;

    get_wt_time(wt, n);
    get_tat_time(tat, wt, n);

    int stime[MAX_PROCESS], ctime[MAX_PROCESS];

    stime[0] = proc[0].at;
    ctime[0] = stime[0] + tat[0];

    for (int i = 1; i < n; i++) {
        stime[i] = ctime[i - 1];
        ctime[i] = stime[i] + tat[i] - wt[i];
    }

    cout << "Process_no\tStart_time\tComplete_time\tTurn_Around_Time\tWaiting_Time\n";

    for (int i = 0; i < n; i++) {
        wavg += wt[i];
        tavg += tat[i];

        cout << proc[i].pno << "\t\t" << stime[i] << "\t\t" << ctime[i] << "\t\t" << tat[i] << "\t\t\t" << wt[i] << endl;
    }

    cout << "Average waiting time is : " << wavg / (double)n << endl;
    cout << "Average turnaround time : " << tavg / (double)n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    get_input(n);

    sort(proc, proc + n, comp);

    findgc(n);

    return 0;
}
