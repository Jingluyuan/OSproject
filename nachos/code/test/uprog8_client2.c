#include "syscall.h"

int main() {
	OpenFileId output = ConsoleOutput;
	int i = 0;
	ThreadYield();

	while(i++ < 5){
		ThreadYield();
	}
	SendMessage("uprog8_server","Hello From uprog8_client2", "buffer2");
	
	Exit(0);
}
