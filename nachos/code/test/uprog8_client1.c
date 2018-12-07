#include "syscall.h"

int main() {
	OpenFileId output = ConsoleOutput;
	char *res;
	char *ans;
	ThreadYield();
	SendMessage("uprog8_server","Hello From uprog8_client1", "buffer1");
	WaitAnswer(res, ans, "buffer1");
	Exit(0);
}
