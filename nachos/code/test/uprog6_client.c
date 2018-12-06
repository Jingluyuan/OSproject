#include "syscall.h"

int main() {
	OpenFileId output = ConsoleOutput;
	ThreadYield();
	SendMessage("uprog6_erver","Hello from uprog6_client", "buffer1");
	Exit(0);
}
