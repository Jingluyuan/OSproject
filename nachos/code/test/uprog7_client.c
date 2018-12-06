#include "syscall.h"

int main() {
	OpenFileId output = ConsoleOutput;
	char *res;
	char *ans;
	ThreadYield();
	SendMessage("uprog7_server","Hello From uprog7_client", "buffer1");
	WaitAnswer(res, ans, "buffer1");
	Exit(0);
}
