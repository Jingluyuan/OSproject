#include "bufferpool.h"
#include "main.h"

BufferPool::BufferPool(){
	bufferPool = new List<MsgBuffer>;
//initialize 20 buffers 
	for(int i = 0; i < 20; i++){
		MsgBuffer *mb = new MsgBuffer();
		bufferPool.Append(mb);
	}
}

BufferPool::~BufferPool(){
	delete bufferPool;
}


MsgBuffer*
BufferPool::FindNextToUse(){
	for(int i = 0; i < 20; i++){
		MsgBuffer* mb = bufferPool->RemoveFront();
		if(mb->getStatus){
			break;
		}else{
			bufferPool.Append(mb);
		}
	}
//if there is no buffer to use, return NULL
	if(mb->getStatus){
		return NULL;
	}else{
		return mb;
	}
}