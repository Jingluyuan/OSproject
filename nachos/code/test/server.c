/*** server.c ***/
//work as server
#include "syscall.h"


int main() {
	OpenFileId output = ConsoleOutput;
	char* msg;
	char *res;
	char *ans;
	ThreadYield();
	
	WaitMessage("client", msg, "buffer1");

	SendAnswer("permit", "ACK J+1", "buffer1");
	SendMessage("client", "SYN K", "buffer2");
		
	WaitAnswer(res, ans, "buffer2");
		


	Exit(0);
}