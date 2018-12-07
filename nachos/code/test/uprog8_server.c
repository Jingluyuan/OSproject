#include "syscall.h"


int main() {
	OpenFileId output = ConsoleOutput;
	char* msg;
	ThreadYield();
	WaitMessage("uprog8_client1", msg, "buffer1");
	SendAnswer("permit", "ACK J+1", "buffer1");
	Exit(0);
}