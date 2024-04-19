#include <iostream>
using namespace std;

void bestfit(int blockarray[], int m, int processesarray[], int n) {
    int allocation[n];
    fill_n(allocation, n, -1);

    for(int i = 0; i < n; i++) {
        int bestidx = -1;
        for(int j = 0; j < m; j++) {
            if(blockarray[j] >= processesarray[i]) {
                if (bestidx == -1) {
                    bestidx = j;
                }
                else if (blockarray[bestidx] > blockarray[j]) {
                    bestidx = j;
                }
            }
        }
        if (bestidx != -1) {
            allocation[i] = bestidx;
            blockarray[bestidx] -= processesarray[i];
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

    bestfit(blockarray, blocks, processarray, processes);

    return 0;
}
