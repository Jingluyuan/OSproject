#ifndef MESSAGEBUFFER_H
#define MESSAGEBUFFER_H


#include "copyright.h"
#include <iostream>
#include "string.h"

using namespace std;
class MsgBuffer{
private:
	string _sender;     	// sender thread's name
	string _receiver;	//  resceiver thread's name
	string _buffer_id;	//   buffer's identify id
	string _message;		//  message input
	bool _used;			// the status of the buffer  true means currently being used; false means currently unused
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
};


#endif