#include "syscall.h"

int main() {
	OpenFileId output = ConsoleOutput;
	ThreadYield();
	SendMessage("uprog3_A","Hello From C by buffer15", "buffer15");
	SendMessage("uprog3_A","Hello From C by buffer16", "buffer16");
	SendMessage("uprog3_A","Hello From C by buffer17", "buffer17");
	SendMessage("uprog3_A","Hello From C by buffer18", "buffer18");
	SendMessage("uprog3_A","Hello From C by buffer19", "buffer19");
	SendMessage("uprog3_A","Hello From C by buffer20", "buffer20");
	SendMessage("uprog3_A","Hello From C by buffer21", "buffer21");
	Exit(0);
}