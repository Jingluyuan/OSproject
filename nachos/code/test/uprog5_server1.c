#include "syscall.h"


int main() {
	OpenFileId output = ConsoleOutput;
	char* msg;
	ThreadYield();	
	WaitMessage("uprog5_client", msg, "buffer1");
	Exit(0);
}