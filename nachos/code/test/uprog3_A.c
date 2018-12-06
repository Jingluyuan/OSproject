#include "syscall.h"

int main() {
	OpenFileId output = ConsoleOutput;
	ThreadYield();
	SendMessage("uprog3_B","Hello From A by buffer1", "buffer1");
	SendMessage("uprog3_B","Hello From A by buffer2", "buffer2");
	SendMessage("uprog3_B","Hello From A by buffer3", "buffer3");
	SendMessage("uprog3_B","Hello From A by buffer4", "buffer4");
	SendMessage("uprog3_B","Hello From A by buffer5", "buffer5");
	SendMessage("uprog3_B","Hello From A by buffer6", "buffer6");
	SendMessage("uprog3_B","Hello From A by buffer7", "buffer7");
	Exit(0);
}
