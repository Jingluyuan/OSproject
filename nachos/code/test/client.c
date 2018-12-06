/*** client.c ***/
//work as client
#include "syscall.h"

int main() {
	OpenFileId output = ConsoleOutput;
	char *res;
	char *ans;
	char* msg;
	ThreadYield();
	SendMessage("server","SYN J", "buffer1");
	WaitAnswer(res, ans, "buffer1");

	WaitMessage("server", msg, "buffer2");
	SendAnswer("permit", "ACK K+1", "buffer2");

	


	Exit(0);
}
