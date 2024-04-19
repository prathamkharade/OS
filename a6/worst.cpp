#include <iostream>
using namespace std;

void worstfit(int blockarray[], int m, int processesarray[], int n) {
    int allocation[n];
    fill_n(allocation, n, -1);

    for(int i = 0; i < n; i++) {
        int worstidx = -1;
        for(int j = 0; j < m; j++) {
            if(blockarray[j] >= processesarray[i]) {
                if (worstidx == -1) {
                    worstidx = j;
                }
                else if (blockarray[worstidx] < blockarray[j]) {
                    worstidx = j;
                }
            }
        }
        if (worstidx != -1) {
            allocation[i] = worstidx;
            blockarray[worstidx] -= processesarray[i];
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

    worstfit(blockarray, blocks, processarray, processes);

    return 0;
}
