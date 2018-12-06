#include "copyright.h"
#include <iostream>
#include "string.h"
#include "messagebuffer.h"

string
MsgBuffer::getSender()
{
	return _sender;
}

void 
MsgBuffer::setSender(string sender)
{
	_sender = sender;
}
	
string 
MsgBuffer::getReceiver()
{
	return _receiver;
}
	
void 
MsgBuffer::setReceiver(string receiver)
{
	_receiver = receiver;
}
	
string 
MsgBuffer::getId()
{
	return _buffer_id;
}
	
void 
MsgBuffer::setId(string id)
{
	_buffer_id = id;
}
	
string 
MsgBuffer::getMessage()
{
	return _message;
}
	
void 
MsgBuffer::setMessage(string message)
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

string
MsgBuffer::getResult()
{
	return _result;
}

void
MsgBuffer::setResult(string result)
{
	_result = result;
}

string
MsgBuffer::getAnswer()
{
	return _answer;
}

void
MsgBuffer::setAnswer(string answer)
{
	_answer = answer;
}

BufferStatus 
MsgBuffer::getUsingStatus()
{
	return _using_status;
}
void 
MsgBuffer::setUsingStatus(BufferStatus bufferStatus)
{
	_using_status = bufferStatus;
}

