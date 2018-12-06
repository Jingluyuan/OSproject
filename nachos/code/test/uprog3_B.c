#include "syscall.h"

int main() {
	OpenFileId output = ConsoleOutput;
	ThreadYield();
	SendMessage("uprog3_C","Hello From B by buffer8", "buffer8");
	SendMessage("uprog3_C","Hello From B by buffer9", "buffer9");
	SendMessage("uprog3_C","Hello From B by buffer10", "buffer10");
	SendMessage("uprog3_C","Hello From B by buffer11", "buffer11");
	SendMessage("uprog3_C","Hello From B by buffer12", "buffer12");
	SendMessage("uprog3_C","Hello From B by buffer13", "buffer13");
	SendMessage("uprog3_C","Hello From B by buffer14", "buffer14");
	Exit(0);
}
