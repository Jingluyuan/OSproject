/*** server.c ***/
//work as server
#include "syscall.h"
char data[2048];

int main() {
	OpenFileId output = ConsoleOutput;
	char* str = "Prog server: server started \n";
	char* msg;
	ThreadYield();
	Write(str, 30, output);
	
	WaitMessage("client", msg, "buffer1");
	if (msg == "SYN J") {
		char *res;
		char *ans;
		SendAnswer("permit", "ACK J+1", "buffer1");
		SendMessage("client", "SYN K", "buffer2");
		
		WaitAnswer(res, ans, "buffer2");
		if (res == "permit" && ans == "ACK K+1") {
			str = "Prog server: connection success\n";
			Write(str, 33, output);
		}
	}

	Exit(0);
}