#include<iostream>
using namespace std;
void calculateTime(int arrivalTime[],int burstTime[],int waitingTime[],int turnAroundTime[],int completionTime[],int n) {
    int currentTime=0;
    for(int i=0;i<n;i++) {
        if(arrivalTime[i]>currentTime)
            currentTime=arrivalTime[i];
        completionTime[i]=currentTime+burstTime[i];
        turnAroundTime[i]=completionTime[i]-arrivalTime[i];
        waitingTime[i]=turnAroundTime[i]-burstTime[i];
        currentTime=completionTime[i];
    }
}
void printTable(int arrivalTime[],int burstTime[],int waitingTime[],int turnAroundTime[],int completionTime[],int n) {
    int totalWaitingTime=0,totalTurnAroundTime=0;
    cout<<"P BT AT CT WT TAT"<<endl;
    for(int i=0;i<n;i++) {
        totalWaitingTime=totalWaitingTime+waitingTime[i];
        totalTurnAroundTime=totalTurnAroundTime+turnAroundTime[i];
        cout<<i+1<<" "<<burstTime[i]<<" "<<arrivalTime[i]<<" "<<completionTime[i]<<" "<<waitingTime[i]<<" "<<turnAroundTime[i]<<endl;
    }
    cout<<"Average waiting time is : "<<(float)totalWaitingTime/(float)n<<endl;
    cout<<"Average turn around time is : "<<(float)totalTurnAroundTime/(float)n<<endl;
}
int main() {
    int n;
    cout<<"Enter the number of processes : ";
    cin>>n;
    int arrivalTime[n];
    int burstTime[n];
    int waitingTime[n];
    int turnAroundTime[n];
    int completionTime[n];
    cout<<"Enter the arrival time of the processes : "<<endl;
    for(int i=0;i<n;i++)
        cin>>arrivalTime[i];
    cout<<"Enter the burst time of the processes : "<<endl;
    for(int i=0;i<n;i++)
        cin>>burstTime[i];
    calculateTime(arrivalTime,burstTime,waitingTime,turnAroundTime,completionTime,n);
    printTable(arrivalTime,burstTime,waitingTime,turnAroundTime,completionTime,n);
}