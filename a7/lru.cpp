#include <iostream>
using namespace std;

int main() {
    int pagefaults = 0;
    int position;
    int totalframes, totalpages;

    cout << "Enter number of pages: ";
    cin >> totalpages;

    int pages[totalpages];
    cout << "Enter incoming pages: ";
    for (int i=0; i<totalpages; i++) {
        cin >> pages[i];
    }
    
    cout << "Enter number of frames: ";
    cin >> totalframes;
    int frames[totalframes];
    int temp[totalframes];
    for (int i=0; i<totalframes; i++) {
        frames[i] = -1;
    }

    cout << "Incoming\t\t";
    for (int i=0; i<totalframes; i++) {
        cout << "Frames " << i+1 << "\t\t";
    }

    for(int m=0; m<totalpages; m++) {
        int a = 0;
        int b = 0;
        for (int n = 0; n < totalframes; n++) {
            if (pages[m] == frames[n]) {
                a = 1;
                b = 1;
                break;
            }
        }
        if(a == 0) {
            for (int n=0; n < totalframes; n++) {
                if(frames[n] == -1) {
                    frames[n] = pages[m];
                    b = 1;
                    pagefaults++;
                    break;
                }
            }
        }
        if(b == 0) {
            for (int n = 0; n<totalframes; n++) {
                temp[n] = 0;
            }
            for (int k = m-1, l = 1; l <= totalframes-1; l++, k--) {
                for (int n=0; n<totalframes; n++) {
                    if(frames[n] == pages[k]) {
                        temp[n] = 1;
                    }
                }
            }
            for (int n=0; n<totalframes; n++) {
                if (temp[m] == 0) {
                    position = n;
                    break;
                }
            }
            frames[position] = pages[m];
            pagefaults++;
        }
        cout << endl;
        cout << pages[m] << "\t\t\t";
        for (int n=0; n<totalframes; n++) {
            cout << frames[n] << "\t\t\t";
        }
    }
    cout << "\n\nTotal Page Faults:\t" << pagefaults << endl;
    cout << "\nTotal Hits :\t" << totalpages - pagefaults << endl;
    return 0;
}