#include<iostream>
#include<algorithm>
#include<climits>
using namespace std;
struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
    bool completed;
};
bool compareArrival(Process a,Process b) {
    return a.arrivalTime<b.arrivalTime;
}
int findShortestIndex(Process processes[],int n,int currentTime) {
    int shortest=-1;
    int minBurst=INT_MAX;
    for(int i=0;i<n;i++)
        if(!processes[i].completed && processes[i].arrivalTime<=currentTime && processes[i].burstTime<minBurst) {
            minBurst=processes[i].burstTime;
            shortest=i;
        }
    return shortest;
}
void calculateTimes(Process processes[],int n) {
    sort(processes,processes+n,compareArrival);
    int currentTime=0;
    int completed=0;
    for(int i=0;i<n;i++)
        processes[i].completed=false;
    while(completed!=n) {
        int shortest=findShortestIndex(processes,n,currentTime);
        if(shortest==-1) {
            currentTime++;
            continue;
        }
        processes[shortest].completionTime=currentTime+processes[shortest].burstTime;
        processes[shortest].turnAroundTime=processes[shortest].completionTime-processes[shortest].arrivalTime;
        processes[shortest].waitingTime=processes[shortest].turnAroundTime-processes[shortest].burstTime;
        currentTime=processes[shortest].completionTime;
        //turn around time = completion - arrival;
        // waiting time = turn around time - burst time;
        processes[shortest].completed=true;
        completed++;
    }
} 
void printTable(Process processes[],int n) {
    int totalWaitingTime=0,totalTurnAroundTime=0;
    cout<<"P AT BT CT WT TAT"<<endl;
    for(int i=0;i<n;i++) {
        totalWaitingTime=totalWaitingTime+processes[i].waitingTime;
        totalTurnAroundTime=totalTurnAroundTime+processes[i].turnAroundTime;
        cout<<processes[i].pid<<" "<<processes[i].arrivalTime<<" "<<processes[i].burstTime<<" "<<processes[i].completionTime<<" "<<processes[i].waitingTime<<" "<<processes[i].turnAroundTime<<endl;
    }
    cout<<"Average waiting time is : "<<(float)totalWaitingTime/(float)n<<endl;
    cout<<"Average turn around time is : "<<(float)totalTurnAroundTime/(float)n<<endl;
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
    calculateTimes(processes,n);
    printTable(processes,n);
}