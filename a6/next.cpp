#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void nextfit(int blockarray[], int m, int processesarray[], int n) {
    int allocation[n];
    fill_n(allocation, n, -1);
    int start = 0;

    for(int i = 0; i < n; i++) {
        int j;
        for(j = start; j < m; j++) {
            if(blockarray[j] >= processesarray[i]) {
                allocation[i] = j;
                blockarray[j] -= processesarray[i];
                start = j+1;
                break;
            }
        }
        if (j == m) {
            start = 0;
        }
    }

    cout << endl << "Process No.\tProcess Size\tBlock no." << endl;
    for(int i = 0; i < n; i++) {
        cout << i+1 << "\t\t" << processesarray[i] << "\t\t";
        if(allocation[i] != -1) {
            cout << allocation[i] + 1 << endl;
        } else {
            cout << "Not allocated" << endl;
        }
    }
}


int main() {
    int blocks, processes;
    cout << "Enter number of blocks: ";
    cin >> blocks;
    cout << "Enter number of processes: ";
    cin >> processes;

    int blockarray[blocks];
    int processarray[processes];

    cout << "Enter sizes of blocks: ";
    for(int i=0; i<blocks; i++) {
        cin >> blockarray[i];
    }

    cout << "Enter sizes of processes: ";
    for(int i=0; i<processes; i++) {
        cin >> processarray[i];
    }

    int m = sizeof(blockarray)/ sizeof(blockarray[0]);
    int n = sizeof(processarray)/ sizeof(processarray[0]);

    nextfit(blockarray, blocks, processarray, processes);

    return 0;
}
