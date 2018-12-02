/*** server.c ***/
//work as server
#include "syscall.h"
#include <iostream>
#include <string>

int main() {

	cout << "Prog server: server started \n"
	char *msg
	waitMessage("client", msg, "buffer1");
	if (msg == "SYN J") {
		sendAnswer("permit", "ACK J+1", "buffer1");
		sendMessage("client", "SYN K", "buffer2");
		char *res;
		char *ans;
		WaitAnswer(res, ans, "buffer2");
		if (res == "permit" && ans == "ACK K+1") {
			cout << "Prog server: connection success"
		}
	}

	Exit(0);
}