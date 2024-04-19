#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {
  pid_t pid;
  int status;
  
  pid = fork();
  if (pid < 0) {
    cout << "Fork failed";
    exit(1);
  }
  else if (pid == 0) {
    cout << "Child process (PID: " << getpid() << " executing cp command" << endl;
    execl("/bin/cp", "cp", "source.txt", "dest.txt", NULL);
    exit(1);
  }
  else {
    wait(&status);
    if (WIFEXITED(status)) {
      cout << "Child process (PID: " << pid << " executed sucessfully" << endl;
    }
    else {
      cout << "Child process (PID: " << pid << " terminated" << endl;
    }
  }
  
  pid = fork();
  if (pid < 0) {
    cout << "Fork failed";
    exit(1);
  }
  else if (pid == 0) {
    cout << "Child process (PID: " << getpid() << " executing grep command" << endl;
    execl("/bin/grep", "grep", "Hi", "dest.txt", NULL);
    exit(1);
  }
  else {
    wait(&status);
    if (WIFEXITED(status)) {
      cout << "Child process (PID: " << pid << " executed sucessfully" << endl;
    }
    else {
      cout << "Child process (PID: " << pid << " terminated" << endl;
    }
  }
  
  return 0;
}
