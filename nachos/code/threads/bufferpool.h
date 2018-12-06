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
		bool reachLimit();
		//List<MsgBuffer *> getPool() {return (bufferPool);};

	private:
		List<MsgBuffer *> *bufferPool;

		//int size;

};


#endif