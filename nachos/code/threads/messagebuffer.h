#ifndef MESSAGEBUFFER_H
#define MESSAGEBUFFER_H


#include "copyright.h"
#include <iostream>
#include "string.h"

class MsgBuffer{
private:
	char* _sender;
	char* _receiver;
	char* _buffer_id;
	char* _message;
	bool _used;


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