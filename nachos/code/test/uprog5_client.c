#include "syscall.h"

int main() {
	OpenFileId output = ConsoleOutput;
	ThreadYield();
	SendMessage("uprog5_server1","Hello from client", "buffer1");
	Exit(0);
}