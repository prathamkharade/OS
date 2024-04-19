#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <algorithm>
#include <vector>
using namespace std;

struct process {
  int pid;
  int at;
  int bt;
  int ct;
  int st;
  int tat;
  int wt;
};

bool compareat (process p1, process p2) {
  return p1.at < p2.at;
}

bool compareID (process p1, process p2) {
  return p1.pid < p2.pid;
}

int main() {
  int n;
  struct process p[10];
  int totaltat = 0;
  int totalwt = 0;
  float avgtat;
  float avgwt;
  vector<int> Order_of_exec;
  
  cout << "Enter number of processes: ";
  cin >> n;
  
  for(int i=0; i<n; i++) {
    cout << "\nEnter AT and BT for process " << i+1 << " : ";
    cin >> p[i].at >> p[i].bt;
    p[i].pid = i+1;
  }
  
  sort(p, p+n, compareat);
  
  for(int i=0; i<n; i++) {
    if (i==0) {
      p[i].st = p[i].at;
    }
    else {
      p[i].st = max(p[i-1].ct, p[i].at);
    }
    p[i].ct = p[i].st + p[i].bt;
    p[i].tat = p[i].ct - p[i].at;
    p[i].wt = p[i].tat - p[i].bt;
    totaltat = totaltat + p[i].tat;
    totalwt = totalwt + p[i].wt;
    Order_of_exec.push_back(p[i].pid);
  }
  
  avgtat = (float) totaltat / n;
  avgwt = (float) totalwt / n;
  
  sort(p, p+n, compareID);
  
  cout << endl;
  cout << "#P\t" << "AT\t" << "BT\t" << "CT\t" << "TAT\t" << "WT\t" << endl;
  cout << "\nAverage Turnaround Time = " << avgtat << endl;
  cout << "Average Waiting Time = " << avgwt<< endl;
  cout << "" << endl;
  
  return 0;
}
