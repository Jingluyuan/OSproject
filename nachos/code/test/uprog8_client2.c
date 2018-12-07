#include "syscall.h"

int main() {
	OpenFileId output = ConsoleOutput;
	
	ThreadYield();
	for(int i = 0; i < 5; i++){
		ThreadYield();
	}
	SendMessage("uprog8_server","Hello From uprog8_client2", "buffer2");
	
	Exit(0);
}
