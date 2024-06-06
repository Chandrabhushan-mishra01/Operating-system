#include <iostream>
#include <vector>
using namespace std;

int FCFS(vector<int> requests, int head){
    int n = requests.size();
    int dist = 0;
    int noOfTurns = 0;
    int totalDist = 0;
    int start = head;
    for(int i=0;i<n;i++){
        dist = requests[i] - start;
        if(dist<0){
            dist *= -1;
            // noOfTurns++;
        }
        start = requests[i];
        totalDist += dist;
    }
    return totalDist;
}


int main(){
    vector<int> v{ 176, 79, 34, 60, 92, 11, 41, 114 };
    int head = 50;
    printf("%d ", FCFS(v, head));
}