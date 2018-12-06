#include "syscall.h"

//just keep a live in order to allow the server creates enough message buffer to cause the over buffer pool's size problem
int main() {
	while(1)
	{
		ThreadYield();
	}
}