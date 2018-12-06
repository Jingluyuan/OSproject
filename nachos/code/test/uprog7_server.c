#include "syscall.h"


int main() {
	OpenFileId output = ConsoleOutput;
	char* msg;
	ThreadYield();
	WaitMessage("uprog7_client", msg, "buffer1");
	Exit(0);
}