// bufferpool.h
// Date structure for storing MessageBuffers and managing MessageBuffers
// It was relized by List in Nachos System, the default size of buffer
// pool is 20. Buffer pool will  supply a clean MessageBuffer when  
// kernel or userprogram need. In addition, it supply interface to 
// exception handler to help exception handler manage Message Buffer.

#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#include "list.h"
#include "messagebuffer.h"
#include "string.h"

class BufferPool{
	public:
		BufferPool();
		~BufferPool();

		MsgBuffer* FindNextToUse(string buffer_id); //find next clean buffer
		MsgBuffer* Search(string buffer_id); //find specific buffer based on buffer id
		MsgBuffer* SearchBySender(string sender_id); //find specifiac buffer based on buffer sender;
		MsgBuffer* SearchByReceiver(string receiver_id); //find specifiac buffer based on buffer receiver;
		bool reachLimit(); //check whether the bufferpool is full, the size of pool is 20.

		//List<MsgBuffer *> getPool() {return (bufferPool);};

	private:
		List<MsgBuffer *> *bufferPool;

		//int size;

};


#endif