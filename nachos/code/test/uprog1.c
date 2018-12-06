#include "syscall.h"

//Designed with only onew Send Message call 
// In this situation, sender will send a message to an unexist receiver 
// which will be feedback a error message
int main() {
	OpenFileId output = ConsoleOutput;
	ThreadYield();
	SendMessage("sayhi","hello reveiver!", "buffer1");
	Exit(0);
}