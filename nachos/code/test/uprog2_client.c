#include "syscall.h"

//Designed to send 11 message to the same receiver
// which has the limitation of 10 message.
// In this situation, an error will be return
int main() {
	OpenFileId output = ConsoleOutput;
	ThreadYield();
	SendMessage("uprog2_server","message message 1", "buffer1");
	SendMessage("uprog2_server","message message 2", "buffer2");
	SendMessage("uprog2_server","message message 3", "buffer3");
	SendMessage("uprog2_server","message message 4", "buffer4");
	SendMessage("uprog2_server","message message 5", "buffer5");
	SendMessage("uprog2_server","message message 6", "buffer6");
	SendMessage("uprog2_server","message message 7", "buffer7");
	SendMessage("uprog2_server","message message 8", "buffer8");
	SendMessage("uprog2_server","message message 9", "buffer9");
	SendMessage("uprog2_server","message message 10", "buffer10");
	SendMessage("uprog2_server","message message 11", "buffer11");
	Exit(0);
}
