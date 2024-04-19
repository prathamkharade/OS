#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>
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
  int tq;
  struct process p[10];
  int totaltat = 0;
  int totalwt = 0;
  float avgtat;
  float avgwt;
  vector<int> Order_of_exec;
  vector<int> Time;
  int burst_remaining [10];
  
  cout << "Enter number of processes: ";
  cin >> n;
  cout << "Enter time quantum: ";
  cin >> tq;
  
  for (int i=0; i<n; i++) {
    cout << "\nEnter AT and BT for process " << i+1 << " : ";
    cin >> p[i].at >> p[i].bt;
    burst_remaining[i] = p[i].bt;
    p[i].pid = i+1;
  }
  
  sort(p, p+n, compareat);
  
  int current_time = 0;
  int completed = 0;
  int mark[10] = {0};
  queue<int> q;
  q.push(0);
  mark[0] = 1;
  
  while (completed != n) {
    int idx = q.front();
    q.pop();
    
    if (burst_remaining[idx] == p[idx].bt) {
      p[idx].st = max(current_time, p[idx].at);
      current_time = p[idx].st;
    }
    if (burst_remaining[idx] - tq > 0) {
      burst_remaining[idx] = burst_remaining[idx] - tq;
      Order_of_exec.push_back(p[idx].pid);
      Time.push_back(current_time);
      current_time = current_time + tq;
    }
    else {
      Order_of_exec.push_back(p[idx].pid);
        Time.push_back(current_time);
        current_time += burst_remaining[idx];
        burst_remaining[idx] = 0;
        completed++;
        if (completed == n) {
            Time.push_back(current_time);
        }

        p[idx].ct = current_time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        totaltat += p[idx].tat;
        totalwt += p[idx].wt;
      }

      for (int i = 1; i < n; i++) {
        if (burst_remaining[i] > 0 && p[i].at <= current_time && mark[i] == 0) {
            q.push(i);
            mark[i] = 1;
        }
      }

      if (burst_remaining[idx] > 0) {
        q.push(idx);
      }

      if (q.empty()) {
        for (int i = 1; i < n; i++) {
          if (burst_remaining[i] > 0) {
              q.push(i);
              mark[i] = 1;
              break;
          }
        }
      }
  }

  avgtat = (float)totaltat / n;
  avgwt = (float)totalwt / n;

  sort(p, p+n, compareID);
  
  cout << endl;
  cout << "#P\t" << "AT\t" << "BT\t" << "CT\t" << "TAT\t" << "WT\t" << endl;
  cout << "\nAverage Turnaround Time = " << avgtat << endl;
  cout << "Average Waiting Time = " << avgwt<< endl;
  cout << "" << endl;
  return 0;
}