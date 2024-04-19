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

bool compareID (process p1, process p2) {
  return p1.pid < p2.pid;
}

int main() {
  int n;
  int totaltat = 0;
  int totalwt = 0;
  float avgtat;
  float avgwt;
  struct process p[10];
  int iscompleted[10]; 
  fill_n(iscompleted, 10, 0);
  
  vector<int> Order_of_exec;
  
  cout << "Enter number of processes: ";
  cin >> n;
  
  for(int i=0; i<n; i++) {
    cout << "\nEnter AT and BT for process " << i+1 << " : ";
    cin >> p[i].at >> p[i].bt;
    p[i].pid = i+1;
  }
  
  int current_time = 0;
  int completed = 0;
  
  while (completed != n) {
    int idx = -1;
    int mn = 100000;
    for (int i=0; i<n; i++) {
      if (p[i].at <= current_time && iscompleted[i] == 0) {
        if (p[i].bt < mn) {
          mn = p[i].bt;
          idx = i;
        }
        if (p[i].bt == mn) {
          if (p[i].at < p[idx].at) {
            idx = i;
          }
        }
      }
    }
    if(idx != -1) {
      p[idx].st = current_time;
      p[idx].ct = p[idx].st + p[idx].bt;
      p[idx].tat = p[idx].ct - p[idx].at;
      p[idx].wt = p[idx].tat - p[idx].bt;
      totaltat = totaltat + p[idx].tat;
      totalwt = totalwt + p[idx].wt;
      iscompleted[idx] = 1;
      completed++;
      Order_of_exec.push_back(p[idx].pid);
      current_time = p[idx].ct;
    }
    else {
      current_time++;
    }
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
