#include <iostream>
#include <iomanip>
#include <algorithm> // for sort function

using namespace std;

struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int remaining;  // Remaining burst time
    int completion; // Completion time
    int turnaround; // Turnaround time
    int waiting;    // Waiting time
    bool inQueue;   // Whether process is in ready queue
    bool completed; // Whether process has completed
};

// Comparison function for sorting processes by arrival time
bool compareArrival(const Process &a, const Process &b) {
    return a.arrival < b.arrival;
}

void roundRobinScheduling(Process processes[], int n, int quantum) {
    // First sort processes by arrival time
    sort(processes, processes + n, compareArrival);
    
    int currentTime = 0;
    int completed = 0;
    
    // Initialize process data
    for (int i = 0; i < n; i++) {
        processes[i].remaining = processes[i].burst;
        processes[i].inQueue = false;
        processes[i].completed = false;
    }
    
    while (completed < n) {
        bool executed = false;
        
        // Execute each process in round-robin fashion
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrival <= currentTime) {
                executed = true;
                
                // Execute for quantum or remaining time, whichever is smaller
                int executionTime = min(quantum, processes[i].remaining);
                processes[i].remaining -= executionTime;
                currentTime += executionTime;
                
                // Check if process completed
                if (processes[i].remaining == 0) {
                    processes[i].completion = currentTime;
                    processes[i].turnaround = processes[i].completion - processes[i].arrival;
                    processes[i].waiting = processes[i].turnaround - processes[i].burst;
                    processes[i].completed = true;
                    completed++;
                }
                
                // Check for newly arrived processes after each time quantum
                for (int j = 0; j < n; j++) {
                    if (!processes[j].completed && 
                        processes[j].arrival <= currentTime && 
                        !processes[j].inQueue && 
                        j != i) {
                        processes[j].inQueue = true;
                    }
                }
            }
        }
        
        // If no process was executed in this cycle, increment time
        if (!executed) {
            currentTime++;
        }
    }
}

void printResults(Process processes[], int n) {
    cout << "\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    float totalTurnaround = 0, totalWaiting = 0;
    
    for (int i = 0; i < n; i++) {
        cout << processes[i].pid << "\t" 
             << processes[i].arrival << "\t" 
             << processes[i].burst << "\t"
             << processes[i].completion << "\t\t" 
             << processes[i].turnaround << "\t\t" 
             << processes[i].waiting << endl;
        
        totalTurnaround += processes[i].turnaround;
        totalWaiting += processes[i].waiting;
    }
    
    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << totalTurnaround / n << endl;
    cout << "Average Waiting Time: " << totalWaiting / n << endl;
}

int main() {
    int n, quantum;
    
    cout << "Enter number of processes: ";
    cin >> n;
    
    cout << "Enter time quantum: ";
    cin >> quantum;
    
    Process processes[n];
    
    for (int i = 0; i < n; i++) {
        cout << "\nEnter details for process " << i + 1 << ":\n";
        processes[i].pid = i + 1;
        cout << "Arrival time: ";
        cin >> processes[i].arrival;
        cout << "Burst time: ";
        cin >> processes[i].burst;
    }
    
    roundRobinScheduling(processes, n, quantum);
    printResults(processes, n);
    
    return 0;
}