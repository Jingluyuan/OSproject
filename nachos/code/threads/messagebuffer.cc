#include "copyright.h"
#include <iostream>
#include "string.h"
#include "MessageBuffer.h"

char*
MsgBuffer::getSender()
{
	return _sender;
}

void 
MsgBuffer::setSender(char* sender)
{
	_sender = sender;
}
	
char* 
MsgBuffer::getReceiver()
{
	return _receiver;
}
	
void 
MsgBuffer::setReceiver(char* receiver)
{
	_receiver = receiver;
}
	
char* 
MsgBuffer::getId()
{
	return _buffer_id;
}
	
void 
MsgBuffer::setId(char* id)
{
	_buffer_id = id;
}
	
char* 
MsgBuffer::getMessage()
{
	return _message;
}
	
void 
MsgBuffer::setMessage(char* message)
{
	_message = message;
}

bool 
MsgBuffer::getStatus()
{
	return _used;
}
	
void 
MsgBuffer::setStatus(bool status)
{
	_used = status;
}

char*
MsgBuffer::getResult()
{
	return _result;
}

void
MsgBuffer::setResult(char* result)
{
	_result = result;
}

char*
MsgBuffer::getAnswer()
{
	return _answer;
}

void
MsgBuffer::setAnswer(char* answer)
{
	_answer = answer;
}
