#include "syscall.h"

int main() {
	OpenFileId output = ConsoleOutput;
	int i = 0;
	ThreadYield();

	while(i++ < 20){
		ThreadYield();
	}
	
	SendMessage("uprog8_server","Hello From uprog8_client1", "buffer1");
	
	Exit(0);
}
