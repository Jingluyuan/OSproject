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
	
	WaitMessage("../test/client", msg, "buffer1");

	SendAnswer("permit", "ACK J+1", "buffer1");
	SendMessage("../test/client", "SYN K", "buffer2");
		
	WaitAnswer(res, ans, "buffer2");
		


	Exit(0);
}