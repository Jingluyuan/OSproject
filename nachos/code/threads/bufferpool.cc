#include "bufferpool.h"
#include "main.h"
#include "string.h"

BufferPool::BufferPool(){
	bufferPool = new List<MsgBuffer*>;
//initialize 20 buffers 
	/*
	for(int i = 0; i < 20; i++){
		MsgBuffer *mb = new MsgBuffer();
		bufferPool->Append(mb);
	}
	*/
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
BufferPool::FindNextToUse(string buffer_id){
	for(int i = 0; i < bufferPool->NumInList(); i++){
		MsgBuffer* mb = bufferPool->RemoveFront();
		bufferPool->Append(mb);
		if(!mb->getStatus()){
			mb->setId(buffer_id);
			return mb;
		}
	}
	MsgBuffer* nmb = new MsgBuffer();
	nmb->setId(buffer_id);
	bufferPool->Append(nmb);
	return nmb;
}

//----------------------------------------------------------------------
//	MsgBuffer* BufferPool::Search(char* buffer_id)
//	After kernel initialize the clean buffer, get this modified buffer		
//	based on its name.
//----------------------------------------------------------------------

MsgBuffer*
BufferPool::Search(string buffer_id){
	
	for(int i = 0; i < bufferPool->NumInList(); i++){
		MsgBuffer* mb = bufferPool->RemoveFront();
		string temp = mb->getId();
		bufferPool->Append(mb);
		if(buffer_id.compare(temp) == 0){
			return mb;
		}
	}
	return NULL;
}

//----------------------------------------------------------------------
//  Thread::reachLimit
//  Determine whether thread bufferpool is full 
//  TRUE is full, FALSE on the contary
//----------------------------------------------------------------------
 bool
BufferPool::reachLimit(){
    int size;
    size = 0;
  	for(int i = 0; i < bufferPool->NumInList(); i++){
		MsgBuffer* mb = bufferPool->RemoveFront();
		bufferPool->Append(mb);
		if(mb->getStatus()){
			size++;
		}
	}

	if(size >= 20){
		return TRUE;
	}else{
		return FALSE;
	}
 }



MsgBuffer*
BufferPool::SearchBySender(string sender_id){
	
	for(int i = 0; i < bufferPool->NumInList(); i++){
		MsgBuffer* mb = bufferPool->RemoveFront();
		string temp = mb->getSender();
		bufferPool->Append(mb);
		if(sender_id.compare(temp) == 0 && mb->getUsingStatus() == WAIT_MESSAGE){
			return mb;
		}
	}
	return NULL;
}


MsgBuffer*
BufferPool::SearchByReceiver(string receiver_id){
	
	for(int i = 0; i < bufferPool->NumInList(); i++){
		MsgBuffer* mb = bufferPool->RemoveFront();
		string temp = mb->getReceiver();
		bufferPool->Append(mb);
		if(receiver_id.compare(temp) == 0 && mb->getUsingStatus() == WAIT_ANSWER){
			return mb;
		}
	}
	return NULL;
}