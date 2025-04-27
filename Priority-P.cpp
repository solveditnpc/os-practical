#include<iostream>
#include<climits>
#include<algorithm>
using namespace std;
struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
    int remainingTime;
    bool executed;
};
bool compareArrival(Process a, Process b) {
    return a.arrivalTime<b.arrivalTime;
}
int findProcess(Process processes[],int n,int currentTime) {
    int highestPriority=INT_MAX;
    int nextProcess=-1;
    for(int i=0;i<n;i++)
        if(!processes[i].executed && processes[i].arrivalTime<=currentTime) {
            if(processes[i].priority<highestPriority) {
                highestPriority=processes[i].priority;
                nextProcess=i;
            }
        }
    return nextProcess;
}
void calculateTimes(Process processes[],int n) {
    sort(processes,processes+n,compareArrival);
    for(int i=0;i<n;i++) {
        processes[i].remainingTime=processes[i].burstTime;
        processes[i].executed=false;
    }
    int completedProcess=0,currentTime=0;
    while(completedProcess!=n) {
        int nextProcess=findProcess(processes,n,currentTime);
        if(nextProcess==-1) {
            currentTime++;
            continue;
        }
        processes[nextProcess].remainingTime--;
        currentTime++;
        if(processes[nextProcess].remainingTime==0) {
            processes[nextProcess].completionTime=currentTime;
            processes[nextProcess].turnAroundTime=processes[nextProcess].completionTime-processes[nextProcess].arrivalTime;
            processes[nextProcess].waitingTime=processes[nextProcess].turnAroundTime-processes[nextProcess].burstTime;
            completedProcess++;
            processes[nextProcess].executed=true;
        }
    }
}
void printTable(Process processes[],int n) {
    int totalWaitingTime=0,totalTurnAroundTime=0;
    cout<<"P AT BT Pri CT WT TAT"<<endl;
    for(int i=0;i<n;i++) {
        totalWaitingTime=totalWaitingTime+processes[i].waitingTime;
        totalTurnAroundTime=totalTurnAroundTime+processes[i].turnAroundTime;
        cout<<i+1<<" "<<processes[i].arrivalTime<<" "<<processes[i].burstTime<<" "<<processes[i].priority<<" "<<processes[i].completionTime<<" "<<processes[i].waitingTime<<" "<<processes[i].turnAroundTime<<endl;
    }
    cout<<"Average waiting time is : "<<(float)totalWaitingTime/n<<endl;
    cout<<"Average turn around time is : "<<(float)totalTurnAroundTime/n<<endl;
}
int main() {
    int n;
    cout<<"Enter the number of processes : ";
    cin>>n;
    Process processes[n];
    cout<<"Enter the arrival time of the processes : "<<endl;
    for(int i=0;i<n;i++) {
        cin>>processes[i].arrivalTime;
        processes[i].pid=i+1;
    }
    cout<<"Enter the burst time of the processes : "<<endl;
    for(int i=0;i<n;i++)
        cin>>processes[i].burstTime;
    cout<<"Enter the priority of the processes : "<<endl;
    for(int i=0;i<n;i++)
        cin>>processes[i].priority;
    calculateTimes(processes,n);
    printTable(processes,n);
}