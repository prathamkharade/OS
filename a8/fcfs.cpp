#include <iostream>
#include <vector>
using namespace std;

int main() {
    int i, j, k, n, m, sum = 0, x, y, h;
    cout << "Enter size of disk: ";
    cin >> m;
    cout << "Enter number of requests: ";
    cin >> n;
    vector<int> a(n);
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

    int temp = h;
    cout << temp;
    for(i=0; i<n; i++) {
        cout << "->" << a[i] << "";
        sum = sum + abs(a[i] - temp);
        temp = a[i];
    }
    cout << endl;
    cout << "Total seek operations: " << sum << endl;
    return 0;
}