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

//----------------------------------------------------------------------
//	MsgBuffer* BufferPool::FindNextToUse()
//	Find next clean buffer to use 		
//	If there is no clean buffer, return NULL
//----------------------------------------------------------------------

MsgBuffer*
BufferPool::FindNextToUse(){
	for(int i = 0; i < 20; i++){
		MsgBuffer* mb = bufferPool->RemoveFront();
		if(!mb->getStatus){
			break;
		}else{
			bufferPool.Append(mb);
		}
	}
//if there is no buffer to use, return NULL
	if(!mb->getStatus){
		return NULL;
	}else{
		return mb;
	}
}

//----------------------------------------------------------------------
//	MsgBuffer* BufferPool::Search(char* buffer_id)
//	After kernel initialize the clean buffer, get this modified buffer		
//	based on its name.
//----------------------------------------------------------------------

MsgBuffer*
BufferPool::Search(char* buffer_id){

}

//----------------------------------------------------------------------
//	void BufferPool::Clean(MsgBuffer* msgbuffer)
//	Clean the buffer, if it is not used anymore		
//	Just modfied buffer status
//----------------------------------------------------------------------

void
BufferPool::Clean(MsgBuffer* msgbuffer){

}