#include<iostream>
using namespace std;

int main() {
    int arrival_upper = 10;
    int arrival_lower = 0;
    int burst_upper = 10;
    int burst_lower = 1;

    int n;
    cout << "\nEnter the number of processes: ";
    cin >> n;

    int *processes = new int[n];
    int *arrival_times = new int[n];
    int *burst_times = new int[n];
    int *wait_times = new int[n];
    int *turnaround_times = new int[n];
    int *completion_times = new int[n];
    int *remaining_burst = new int[n];

    cout << "\nEnter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        cout << "Process P" << processes[i] << ":\n";
        cout << "Arrival Time: ";
        cin >> arrival_times[i];
        cout << "Burst Time: ";
        cin >> burst_times[i];
    }

    cout << "\nProcesses, Arrival Times, Burst Times\n\n";
    for (int i = 0; i < n; i++) {
        cout << "P:" << processes[i] << " ";
        cout << "AT:" << arrival_times[i] << " ";
        cout << "BT:" << burst_times[i] << endl;
        remaining_burst[i] = burst_times[i];
    }

    cout << "\n";
    int time = 0;
    int completed = 0;
    while (completed < n) {
        int min = 999;
        int min_idx = -1;
        for (int i = 0; i < n; i++) {
            if (remaining_burst[i] < min && arrival_times[i] <= time && remaining_burst[i] > 0) {
                min = remaining_burst[i];
                min_idx = i;
            }
        }
        if (min_idx == -1) {
            time++;
            continue;
        }
        cout << "Process " << processes[min_idx] << " runs at time " << time << " for 1 unit of time\n";
        remaining_burst[min_idx]--;
        time++;
        if (remaining_burst[min_idx] == 0) {
            completion_times[min_idx] = time;
            turnaround_times[min_idx] = completion_times[min_idx] - arrival_times[min_idx];
            wait_times[min_idx] = turnaround_times[min_idx] - burst_times[min_idx];
            completed++;
        }
    }

    cout << "\nProcess, Arrival Time, Burst Time, Wait Time, Turnaround Time, Completion Time\n\n";
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
    delete[] remaining_burst;

    return 0;
}
