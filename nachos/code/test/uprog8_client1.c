#include "syscall.h"

int main() {
	OpenFileId output = ConsoleOutput;
	ThreadYield();
	for(int i = 0; i < 20; i++){
		ThreadYield();
	}
	SendMessage("uprog8_server","Hello From uprog8_client1", "buffer1");
	
	Exit(0);
}
