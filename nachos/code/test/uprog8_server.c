#include "syscall.h"


int main() {
	OpenFileId output = ConsoleOutput;
	char* msg;
	ThreadYield();
	WaitMessage("uprog8_client1", msg, "buffer1");
	WaitMessage("uprog8_client2", msg, "buffer2");
	Exit(0);
}