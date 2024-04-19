#include <iostream>
using namespace std;

int main() {
    int pagefaults = 0;
    int frames, pages;

    cout << "Enter number of pages: ";
    cin >> pages;

    int inpages[pages];
    cout << "Enter incoming pages: ";
    for (int i=0; i<pages; i++) {
        cin >> inpages[i];
    }
    
    cout << "Enter number of frames: ";
    cin >> frames;
    int temp[frames];
    for (int i=0; i<frames; i++) {
        temp[i] = -1;
    }

    cout << "Incoming\t\t";
    for (int i=0; i<frames; i++) {
        cout << "Frames " << i+1 << "\t\t";
    }

    for(int m=0; m<pages; m++) {
        int s = 0;
        for (int n = 0; n < frames; n++) {
            if (inpages[m] == temp[n]) {
                s++;
                pagefaults--;
            }
        }
        pagefaults++;
        if(pagefaults <= frames && s == 0) {
            temp[m] = inpages[m];
        }
        else if (s==0) {
            temp[(pagefaults-1) % frames] = inpages[m];
        }
        cout << endl;
        cout << inpages[m] << "\t\t\t";
        for (int n=0; n<frames; n++) {
            if (temp[n] != -1) {
                cout << temp[n] << "\t\t\t";
            }
            else {
                cout << "-1\t\t\t";
            }
        }
    }
    cout << "\n\nTotal Page Faults:\t" << pagefaults << endl;
    cout << "\nTotal Hits :\t" << pages - pagefaults << endl;
    return 0;
}