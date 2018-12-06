#include "syscall.h"

int main() {
	OpenFileId output = ConsoleOutput;
	int i = 0;
	ThreadYield();
	SendMessage("uprog5_server1","Hello from client", "buffer1");
	
	while (i++ < 20) {
		ThreadYield();
	}
	Exit(0);
}