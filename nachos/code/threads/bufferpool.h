#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#include "list.h"
#include "messagebuffer.h"

class BufferPool{
	public:
		BufferPool();
		~BufferPool();

		MsgBuffer* FindNextToUse(); //find next clean buffer
		MsgBuffer* Search(char* buffer_id); //find specific buffer based on buffer id
		
		//List<MsgBuffer *> getPool() {return (bufferPool);};

	private:
		List<MsgBuffer *> *bufferPool;

		//int size;

}


#endif