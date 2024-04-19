#include <iostream>
#include <vector>
using namespace std;

void calculateddifference(int request[], int head, int diff[][2], int n) {
    for (int i=0; i<n; i++) {
        diff[i][0] = abs(head - request[i]);
    }
}

int findMIN(int diff[][2], int n) {
    int index = -1;
    int minimum = 1e9;
    for(int i=0; i<n; i++) {
        if(!diff[i][1] && minimum > diff[i][0]) {
            minimum = diff[i][0];
            index = i;
        }
    }
    return index;
}

void shortestseektimefirst(int request[], int head, int n) {
    if (n == 0) {
        return;
    }
    int diff[n][2] = {{0,0}};
    int seekcount = 0;
    int seeksequence[n+1] = {0};
    for(int i=0; i<n; i++) {
        seeksequence[i] = head;
        calculateddifference(request, head, diff, n);
        int index = findMIN(diff, n);
        diff[index][1] = 1;
        seekcount = seekcount + diff[index][0];
        head = request[index];
    }
    seeksequence[n] = head;
    
    cout << "Seek sequence is: ";
    for (int i=0; i<=n; i++) {
        cout << seeksequence[i] << "\t";
    }
    cout << endl;
    cout << "Total number of seek operations: " << seekcount << endl;
}

int main() {
    int i, j, k, n, m, sum = 0, x, y, h;
    cout << "Enter size of disk: ";
    cin >> m;
    cout << "Enter number of requests: ";
    cin >> n;
    int a[n];
    cout << "Enter the requests: ";
    for (i=0; i<n ; i++) {
        cin >> a[i];
    }
    for (i=0; i<n; i++) {
        if (a[i] > m) {
            cout << "Error, unknown position" << a[i] << endl;
            return 0;
        }
    }
    cout << "Enter the head position: ";
    cin >> h;

    shortestseektimefirst(a, h, n);
    return 0;
}