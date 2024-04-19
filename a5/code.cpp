#include <iostream>
using namespace std;

int main() {
    int noofp, noofr;
    cout << "Enter number of processes: ";
    cin >> noofp;
    cout << "Enter number of resources: ";
    cin >> noofr;
    int max[noofp][noofr];
    int allocation[noofp][noofr];
    int remneed[noofp][noofr];
    int lasttable[noofp][noofr];
    int avail[noofp];
    int safeseq[noofr];

    cout << "Enter max limit" << endl;
    for(int i=0; i<noofp; i++) {
        cout << "Enter resource for process " << i << ": ";
        for(int j=0; j<noofr; j++) {
            cin >> max[i][j];
        }
    }
    cout << endl;
    cout << "#\t";
    for(int i=0; i<noofr; i++) {
        cout << "R" << i << "\t";
    }
    cout << endl;
    for(int i=0; i<noofp; i++) {
        cout << "P" << i << "\t";
        for(int j=0; j<noofr; j++) {
            cout << max[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Enter allocation" << endl;
    for(int i=0; i<noofp; i++) {
        cout << "Enter resource for process " << i << ": ";
        for(int j=0; j<noofr; j++) {
            cin >> allocation[i][j];
        }
    }
    cout << "#\t";
    for(int i=0; i<noofr; i++) {
        cout << "R" << i << "\t";
    }
    cout << endl;
    for(int i=0; i<noofp; i++) {
        cout << "P" << i << "\t";
        for(int j=0; j<noofr; j++) {
            cout << allocation[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;

    for(int i=0; i<noofp; i++) {
        for(int j=0; j<noofr; j++) {
            remneed[i][j] = max[i][j] - allocation[i][j];
        }
    }
    
    cout << "#\t";
    for(int i=0; i<noofr; i++) {
        cout << "R" << i << "\t";
    }
    cout << endl;
    for(int i=0; i<noofp; i++) {
        cout << "P" << i << "\t";
        for(int j=0; j<noofr; j++) {
            cout << remneed[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Enter available resources: ";
    for(int i=0; i<noofr; i++) {
        cin >> avail[i];
    }

    bool unsafe = false;
    for(int i=0; i<noofp; i++) {
        for(int j=0; j<noofr; j++) {
            if(remneed[i][j] < avail[j]) {
                unsafe = true;
            }
        }
    }
    if(unsafe) {
        cout << "Unsafe" << endl;
    }
    else {
        cout << "Safe" << endl;
    }

    bool visited[noofp];
    fill_n(visited, noofp, false);
    int count = 0;

    while(count < noofp) {
        bool found = false;
        for(int i=0; i<noofp; i++) {
            if(!visited[i]) {
                int j;
                for(j=0; j<noofr; j++) {
                    if(remneed[i][j] > avail[j]) {
                        break;
                    }
                }
                if(j == noofr) {
                    for(int k=0; k<noofr; k++) {
                        avail[k] = avail[k] + allocation[i][k];
                        visited[i] = true;
                        lasttable[i][k] = avail[k];
                    }
                    found = true;
                    safeseq[count++] = i;
                }
            }
        }
        if (!found) {
            cout << "System is in an unsafe state and no safe sequence found" << endl;
        }
    }

    cout << "Safe sequence is: ";
    for(int i=0; i<noofp; i++) {
        cout << "P" << safeseq[i] << "\t";
    }

    cout << endl;
    cout << "#\t";
    for(int i=0; i<noofr; i++) {
        cout << "R" << i << "\t";
    }
    cout << endl;
    for(int i=0; i<noofp; i++) {
        cout << "P" << i << "\t";
        for(int j=0; j<noofr; j++) {
            cout << lasttable[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;

}
