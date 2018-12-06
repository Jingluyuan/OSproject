#include "syscall.h"

// In the design of system call WaitMessage, a buffer will be created first and added to the kernel's buffer poll.
// Designing a server sends 21 times WaitMessage syscall to the kernel while the size of the kernel's buffer pool.
// In this situation, buffer pool won't be enough for the total WaitMessage system calls which will be returned an error message
int main() {
	OpenFileId output = ConsoleOutput;
	char* msg;
	ThreadYield();
	WaitMessage("uprog3_client", msg, "buffer1");
	WaitMessage("uprog3_client", msg, "buffer2");
	WaitMessage("uprog3_client", msg, "buffer3");
	WaitMessage("uprog3_client", msg, "buffer4");
	WaitMessage("uprog3_client", msg, "buffer5");
	WaitMessage("uprog3_client", msg, "buffer6");
	WaitMessage("uprog3_client", msg, "buffer7");
	WaitMessage("uprog3_client", msg, "buffer8");
	WaitMessage("uprog3_client", msg, "buffer9");
	WaitMessage("uprog3_client", msg, "buffer10");
	WaitMessage("uprog3_client", msg, "buffer11");
	WaitMessage("uprog3_client", msg, "buffer12");
	WaitMessage("uprog3_client", msg, "buffer13");
	WaitMessage("uprog3_client", msg, "buffer14");
	WaitMessage("uprog3_client", msg, "buffer15");
	WaitMessage("uprog3_client", msg, "buffer16");
	WaitMessage("uprog3_client", msg, "buffer17");
	WaitMessage("uprog3_client", msg, "buffer18");
	WaitMessage("uprog3_client", msg, "buffer19");
	WaitMessage("uprog3_client", msg, "buffer20");
	WaitMessage("uprog3_client", msg, "buffer21");
	Exit(0);
}