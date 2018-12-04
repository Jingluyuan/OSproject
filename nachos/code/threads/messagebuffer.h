#ifndef MESSAGEBUFFER_H
#define MESSAGEBUFFER_H


#include "copyright.h"
#include <iostream>
#include "string.h"

class MsgBuffer{
private:
	char* _sender;     	// sender thread's name
	char* _receiver;	//  resceiver thread's name
	char* _buffer_id;	//   buffer's identify id
	char* _message;		//  message input
	bool _used;			// the status of the buffer  true means currently being used; false means currently unused


public:
	MsgBuffer(){
		_used = false; 			// buffer's status is initialized to be false which means not being used by any process
	}

	char* getSender();
	void setSender(char* sender);
	char* getReceiver();
	void setReceiver(char* receiver);
	char* getId();
	void setId(char* id);
	char* getMessage();
	void setMessage(char* message);
	bool getStatus();
	void setStatus(bool status);
}


#endif