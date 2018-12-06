#include "syscall.h"

//server will keep alive to receive all the messages from the uprog2_client
// which will eventually beyond the scoop of the server's messgae queue
int main() {
	while(1)
	{
		ThreadYield();
	}
}