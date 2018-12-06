/*** server.c ***/
//work as server
#include "syscall.h"


int main() {
	OpenFileId output = ConsoleOutput;
	char* str = "Prog server: server started \n";
	char* msg;
	char *res;
	char *ans;
	ThreadYield();
	Write(str, 30, output);
	
	WaitMessage("client", msg, "buffer1");
	Write(msg, 5, output);

	SendAnswer("permit", "ACK J+1", "buffer1");
	SendMessage("client", "SYN K", "buffer2");
		
	WaitAnswer(res, ans, "buffer2");
		


	Exit(0);
}