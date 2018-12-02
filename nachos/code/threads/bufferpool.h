#ifndef BUFFERPOOL_H
#define BUFFERPOOL_H

#include "list.h"
#include "MessageBuffer"

class BufferPool{
	public:
		BufferPool();
		~BufferPool();

		MsgBuffer* FindNextToUse();


	private:
		List<MsgBuffer *> bufferPool;

		//int size;

}


#endif