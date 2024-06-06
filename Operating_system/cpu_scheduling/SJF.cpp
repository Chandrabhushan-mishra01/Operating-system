#include <iostream>
#include <cstdlib>
#include <ctime>
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
    }

    cout << "\n";
    int time = 0;
    int *burst_times_clone = new int[n];
    for (int i = 0; i < n; i++) {
        burst_times_clone[i] = burst_times[i];
    }

    for (int i = 0; i < n; i++) {
        int min = 999;
        int min_idx = 0;
        for (int j = 0; j < n; j++) {
            if (burst_times_clone[j] < min && arrival_times[j] <= time) {
                min = burst_times_clone[j];
                min_idx = j;
            }
        }
        cout << "Process " << processes[min_idx] << " runs at time " << time << " for " << burst_times[min_idx] << " units of time\n";
        wait_times[min_idx] = time - arrival_times[min_idx];
        time += burst_times[min_idx];
        burst_times_clone[min_idx] = 999;
        completion_times[min_idx] = time;
        turnaround_times[min_idx] = completion_times[min_idx] - arrival_times[min_idx];
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

    // Free dynamically allocated memory
    delete[] processes;
    delete[] arrival_times;
    delete[] burst_times;
    delete[] wait_times;
    delete[] turnaround_times;
    delete[] completion_times;

    delete[] burst_times_clone;

    return 0;
}
