/*** client.c ***/
//work as client
#include "syscall.h"
#include <iostream>
#include <string>
int main() {
	char *res;
	char *ans;
	SendMessage("server","SYN J", "buffer1");
	WaitAnswer(res, ans, "buffer1");
	if (res != "permit") {
		Exit(0);
	}

	if (ans == "ACK J+1") {
		char* msg;
		WaitMessage("server", msg, "buffer2");
		if (msg == "SYN K") {
			SendAnswer("permit", "ACK K+1", "buffer2");
		}
		else {
			cout << "connect failed"
			Exit(0);
		}
	}


	Exit(0);
}
