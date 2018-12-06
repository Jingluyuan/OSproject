#include "syscall.h"

//In this test case, a receiver will wait a non-exist sender
int main() {
	
	char* msg;
	ThreadYield();
	WaitMessage("client", msg, "buffer1");
	Exit(0);
}