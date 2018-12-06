#include "syscall.h"
int main() {
	OpenFileId output = ConsoleOutput;
	char* msg;
	ThreadYield();	
	WaitMessage("uprog5_client", msg, "buffer3");
	Exit(0);
}