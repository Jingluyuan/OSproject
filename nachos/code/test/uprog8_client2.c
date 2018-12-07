#include "syscall.h"

int main() {
	OpenFileId output = ConsoleOutput;
	char *res;
	char *ans;
	ThreadYield();
	SendMessage("uprog8_server","Hello From uprog8_client2", "buffer2");
	WaitAnswer(res, ans, "buffer2");
	Exit(0);
}
