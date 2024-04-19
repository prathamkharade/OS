#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
    int pipe1[2], pipe2[2];
    int pid;
    char pipe1msg[20];
    char pipe2msg[20];
    char readmsg[20];
    pipe(pipe1);
    pipe(pipe2);
    
    pid = fork();

    if (pid != 0) {
        close(pipe1[0]);
        close(pipe2[1]);
        cout << "Enter Parent msg to Child: ";
        cin >> pipe1msg;
        cout << "Parent writes msg to pipe1: " << pipe1msg << endl;
        write(pipe1[1], pipe1msg, sizeof(pipe1msg));
        read(pipe2[0], readmsg, sizeof(readmsg));
        cout << "Parent reading msg from pipe2: " << readmsg << endl;
    }
    else {
        close(pipe1[1]);
        close(pipe2[0]);
        read(pipe1[0], readmsg, sizeof(readmsg));
        cout << "Child reading msg from pipe1: " << readmsg << endl;
        cout << "Enter Child msg to Parent: ";
        cin >> pipe2msg;
        cout << "Child writing to pipe2: " << pipe2msg << endl;
        write(pipe2[1], pipe2msg, sizeof(pipe2msg));
    }

    return 0;
}