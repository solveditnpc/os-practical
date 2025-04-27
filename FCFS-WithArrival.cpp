#include <iostream>
#include <iomanip>

using namespace std;

void calculateFCFS(int n, int arrivalTime[], int burstTime[], int completionTime[], 
                   int turnaroundTime[], int waitingTime[]) {
    int currentTime = 0;
    
    for (int i = 0; i < n; i++) {
        // If process arrives after current time, update current time
        if (arrivalTime[i] > currentTime) {
            currentTime = arrivalTime[i];
        }
        
        // Calculate completion time
        completionTime[i] = currentTime + burstTime[i];
        
        // Calculate turnaround time
        turnaroundTime[i] = completionTime[i] - arrivalTime[i];
        
        // Calculate waiting time
        waitingTime[i] = turnaroundTime[i] - burstTime[i];
        
        // Update current time
        currentTime = completionTime[i];
    }
}

void printResults(int n, int arrivalTime[], int burstTime[], int completionTime[],
                 int turnaroundTime[], int waitingTime[]) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    
    cout << "\nProcess ID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time\n";
    cout << "----------------------------------------------------------------------------------------\n";
    
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
        
        cout << setw(10) << i+1 << " | "
             << setw(12) << arrivalTime[i] << " | "
             << setw(10) << burstTime[i] << " | "
             << setw(15) << completionTime[i] << " | "
             << setw(15) << turnaroundTime[i] << " | "
             << setw(12) << waitingTime[i] << "\n";
    }
    
    cout << "\nAverage Waiting Time: " << (float)totalWaitingTime / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / n << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    
    int arrivalTime[n];
    int burstTime[n];
    int completionTime[n];
    int turnaroundTime[n];
    int waitingTime[n];
    
    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i+1 << " arrival time: ";
        cin >> arrivalTime[i];
        cout << "Process " << i+1 << " burst time: ";
        cin >> burstTime[i];
    }
    
    calculateFCFS(n, arrivalTime, burstTime, completionTime, turnaroundTime, waitingTime);
    printResults(n, arrivalTime, burstTime, completionTime, turnaroundTime, waitingTime);
    
    return 0;
}