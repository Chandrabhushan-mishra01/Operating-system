#include <iostream>
using namespace std;

int main() {
    int arrival_upper = 10;
    int arrival_lower = 0;
    int burst_upper = 10;
    int burst_lower = 1;
    int time_quantum;

    int n;
    cout << "\nEnter the number of processes: ";
    cin >> n;
    cout << "\nEnter the time quantum: ";
    cin >> time_quantum;

    int *processes = new int[n];
    int *arrival_times = new int[n];
    int *burst_times = new int[n];
    int *wait_times = new int[n];
    int *turnaround_times = new int[n];
    int *completion_times = new int[n];
    int *remaining_burst_times = new int[n];

    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        cout << "\nEnter arrival time for process P" << processes[i] << ": ";
        cin >> arrival_times[i];
        cout << "Enter burst time for process P" << processes[i] << ": ";
        cin >> burst_times[i];
        remaining_burst_times[i] = burst_times[i];
    }

    cout << "\nProcesses, Arrival Times, Burst Times\n\n";
    for (int i = 0; i < n; i++) {
        cout << "P:" << processes[i] << " ";
        cout << "AT:" << arrival_times[i] << " ";
        cout << "BT:" << burst_times[i] << endl;
    }

    cout << endl;
    int time = 0;
    while (true) {
        int all_processes_completed = 1;
        for (int i = 0; i < n; i++) {
            if (remaining_burst_times[i] > 0 && arrival_times[i] <= time) {
                all_processes_completed = 0;
                if (remaining_burst_times[i] > time_quantum) {
                    cout << "Process " << processes[i] << " runs at time " << time << " for " << time_quantum << " units of time\n";
                    time += time_quantum;
                    remaining_burst_times[i] -= time_quantum;
                } else {
                    cout << "Process " << processes[i] << " runs at time " << time << " for " << remaining_burst_times[i] << " units of time\n";
                    time += remaining_burst_times[i];
                    remaining_burst_times[i] = 0;
                    completion_times[i] = time;
                    turnaround_times[i] = completion_times[i] - arrival_times[i];
                    wait_times[i] = turnaround_times[i] - burst_times[i];
                }
            }
        }
        if (all_processes_completed == 1) {
            break;
        }
    }

    cout << "\nProcess, Arrival Time, Burst Time, Wait Time, Turn Around Time, Completion Time\n\n";
    for (int i = 0; i < n; i++) {
        cout << "P:" << processes[i] << " ";
        cout << "AT:" << arrival_times[i] << " ";
        cout << "BT:" << burst_times[i] << " ";
        cout << "WT:" << wait_times[i] << " ";
        cout << "TAT:" << turnaround_times[i] << " ";
        cout << "CT:" << completion_times[i] << endl;
    }

    int total_wait = 0;
    for (int i = 0; i < n; i++) {
        total_wait += wait_times[i];
    }
    float avg_wait = (float)(total_wait) / n;
    cout << "\nAverage Waiting Time: " << avg_wait << endl;

    // Deallocate dynamically allocated memory
    delete[] processes;
    delete[] arrival_times;
    delete[] burst_times;
    delete[] wait_times;
    delete[] turnaround_times;
    delete[] completion_times;
    delete[] remaining_burst_times;

    return 0;
}
