#include<iostream>
#include<algorithm>
#include<climits>
using namespace std;
struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnAroundTime;
    int completionTime;
    int remainingTime;
    bool completed;
};
bool compareArrival(Process a,Process b) {
    return a.arrivalTime<b.arrivalTime;
}
int findShortestIndex(Process processes[],int n,int currentTime) {
    int shortest=-1;
    int minRemaining=INT_MAX;
    for(int i=0;i<n;i++) 
        if(!processes[i].completed && processes[i].arrivalTime<=currentTime && processes[i].remainingTime<minRemaining) {
            minRemaining=processes[i].remainingTime;
            shortest=i;
        }
    return shortest;
}
void calculateTime(Process processes[],int n) {
    int currentTime=0;
    int completed=0;
    for(int i=0;i<n;i++) {
        processes[i].remainingTime=processes[i].burstTime;
        processes[i].completed=false;
    }
    while(completed!=n) {
        int shortest=findShortestIndex(processes,n,currentTime);
        if(shortest==-1) {
            currentTime++;
            continue;
        }
        processes[shortest].remainingTime--;
        currentTime++;
        if(processes[shortest].remainingTime==0) {
            processes[shortest].completionTime=currentTime;
            processes[shortest].turnAroundTime=processes[shortest].completionTime-processes[shortest].arrivalTime;
            processes[shortest].waitingTime=processes[shortest].turnAroundTime-processes[shortest].burstTime;
            completed++;
            processes[shortest].completed=true;
        }
    }
}
void printTable(Process processes[],int n) {
    int totalWaitingTime=0,totalTurnAroundTime=0;
    cout<<"P AT BT CT WT TAT"<<endl;
    for(int i=0;i<n;i++) {
        totalWaitingTime=totalWaitingTime+processes[i].waitingTime;
        totalTurnAroundTime=totalTurnAroundTime+processes[i].turnAroundTime;
        cout<<i+1<<" "<<processes[i].arrivalTime<<" "<<processes[i].burstTime<<" "<<processes[i].completionTime<<" "<<processes[i].waitingTime<<" "<<processes[i].turnAroundTime<<endl;
    }
    cout<<"Average waiting time is : "<<(float)totalWaitingTime/(float)n<<endl;
    cout<<"Average turn around time is : "<<(float)totalTurnAroundTime/(float)n<<endl;
}
int main() {
    int n;
    cout<<"Enter the number of processes : ";
    cin>>n;
    Process processes[n];
    cout<<"Enter the arrival time of all the processes : "<<endl;
    for(int i=0;i<n;i++) {
        cin>>processes[i].arrivalTime;
        processes[i].pid=i+1;
    }
    cout<<"Enter the burst time of all the processes : "<<endl;
    for(int i=0;i<n;i++)
        cin>>processes[i].burstTime;
    sort(processes,processes+n,compareArrival);
    calculateTime(processes,n);
    printTable(processes,n);
}