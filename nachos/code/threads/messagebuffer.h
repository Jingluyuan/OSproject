#ifndef MESSAGEBUFFER_H
#define MESSAGEBUFFER_H


#include "copyright.h"
#include <iostream>
#include "string.h"

using namespace std;

enum BufferStatus {JUST_CREATED,SEND_MESSAGE,WAIT_MESSAGE,SEND_ANSWER,WAIT_ANSWER};
class MsgBuffer{
private:
	string _sender;     	// sender thread's name
	string _receiver;	//  resceiver thread's name
	string _buffer_id;	//   buffer's identify id
	string _message;		//  message input
	bool _used;			// the status of the buffer  true means currently being used; false means currently unused
	BufferStatus _using_status; // the status of a used buffer; just create, send message, wait message, send answer, wait answer
	string _result;
	string _answer;


public:
	MsgBuffer(){
		_used = false; 			// buffer's status is initialized to be false which means not being used by any process
	}

	string getSender();
	void setSender(string sender);
	string getReceiver();
	void setReceiver(string receiver);
	string getId();
	void setId(string id);
	string getMessage();
	void setMessage(string message);
	bool getStatus();
	void setStatus(bool status);
	string getResult();
	void setResult(string result);
	string getAnswer();
	void setAnswer(string answer);
	BufferStatus getUsingStatus();
	void setUsingStatus(BufferStatus bufferStatus);
};


#endif