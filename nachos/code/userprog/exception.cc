// exception.cc
//  Entry point into the Nachos kernel from user programs.
//  There are two kinds of things that can cause control to
//  transfer back to here from user code:
//
//  syscall -- The user code explicitly requests to call a procedure
//  in the Nachos kernel.  Right now, the only function we support is
//  "Halt".
//
//  exceptions -- The user code does something that the CPU can't handle.
//  For instance, accessing memory that doesn't exist, arithmetic errors,
//  etc.
//
//  Interrupts (which can also cause control to transfer from user
//  code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
#include "string.h"
#include "thread.h"
#include "kernel.h"
#include "interrupt.h"
#include "machine.h"
#include "bufferpool.h"
#include "messagebuffer.h"


#include <stdlib.h>
#include <stdio.h>
#include <string> 
#include <string.h>
#include <sstream>
//----------------------------------------------------------------------
// ExceptionHandler
//  Entry point into the Nachos kernel.  Called when a user program
//  is executing, and either does a syscall, or generates an addressing
//  or arithmetic exception.
//
//  For system calls, the following is the calling convention:
//
//  system call code -- r2
//    arg1 -- r4
//    arg2 -- r5
//    arg3 -- r6
//    arg4 -- r7
//
//  The result of the system call, if any, must be put back into r2.
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//  "which" is the kind of exception.  The list of possible exceptions
//  is in machine.h.
//----------------------------------------------------------------------

//function to read from memory
string getStringInMem(int addr) {
  string name;
  int c;

  while (1) {
    if (!kernel->machine->ReadMem(addr,1,&c)) {
        kernel->machine->ReadMem(addr,1,&c);
    }
    if ((char)c != '\0') {
      name += char(c);
      addr++;
    }
    else {
      break;
    }
    
  }

  std::stringstream out;
  out << name;
  string s = out.str();

  return s;

}

//function to write to memory
void writeInToMen(string str, int ptr) {
  for (int i = ptr, j = 0; j < str.length(); i++, j++) {
    kernel->machine->WriteMem(i, 1, (int)str.at(j));
  }
}

void
ExceptionHandler(ExceptionType which)
{
  int type = kernel->machine->ReadRegister(2);
  
  DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");
  
  switch (which) {

    case SyscallException:
    {
      switch(type) {
        case SC_Halt:
          DEBUG(dbgSys, "Shutdown, initiated by user program.\n");
          
          SysHalt();
          break;
          
        case SC_Add:
          DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");
          
          /* Process SysAdd Systemcall*/
          int result;
          result = SysAdd(/* int op1 */(int)kernel->machine->ReadRegister(4),
                          /* int op2 */(int)kernel->machine->ReadRegister(5));
          
          DEBUG(dbgSys, "Add returning with " << result << "\n");
          /* Prepare Result */
          kernel->machine->WriteRegister(2, (int)result);
          
          
          break;

        case SC_ThreadYield: {
          kernel->currentThread->Yield();
          break;
        }

        //copy message into the first available buffer within the pool and delivers it in the queue of named receiver
        //activated the receiver who waiting on this message
        //if over the limit of receiver's queue, the message will not send to the receiver
        //if the buffer pool can not find a availabel buffer, the message will not send to the receiver
        //if the receiver dose not exist, print a error message.
        case SC_SendMessage:
        {
          IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff); 
          kernel->interrupt->SetLevel(IntOff);

          cout << "---------Sys call: sending message called by: " << kernel->currentThread->getName() << "-----------"  << endl;
          int receiverAddr = kernel->machine->ReadRegister(4);
          int msgAddr = kernel->machine->ReadRegister(5);
          int bufferAddr = kernel->machine->ReadRegister(6);
          string receiver = getStringInMem(receiverAddr);
          string message = getStringInMem(msgAddr);
          string bufferName = getStringInMem(bufferAddr);
          string sender = std::string(kernel->currentThread->getName());

          cout << "sender: " << sender << " ,receiver: " << receiver << " ,message: " << message << " ,bufferName: " << bufferName << endl;

          if (kernel->bufferPool->reachLimit()) {
            cout << "error! could not find available buffer in buffer pool" << endl;
            break;
          }

          if (kernel->isThreadExist(receiver) && kernel->getThread(receiver)->reachLimit()) {
            cout << "error! over receiver: "<< receiver << "\'s queue limitation" << endl;
            break;
          }

          if (kernel->isThreadExist(receiver) && kernel->bufferPool->Search(bufferName) != NULL) {
            MsgBuffer *buffer = kernel->bufferPool->Search(bufferName);
            buffer->setMessage(message);
            buffer->setStatus(true);
            buffer->setUsingStatus(SEND_MESSAGE);
            cout << "receiver: " << receiver << " is waiting for message in buffer: " << bufferName << " ,acitve receiver" << endl;

            kernel->scheduler->ReadyToRun(kernel->getThread(receiver));
                        
          }

          else if (kernel->isThreadExist(receiver)) {
            MsgBuffer *buffer = kernel->bufferPool->FindNextToUse(bufferName);
            buffer->setSender(sender);
            buffer->setReceiver(receiver);
            buffer->setId(bufferName);
            buffer->setMessage(message);
            buffer->setStatus(true);
            buffer->setUsingStatus(SEND_MESSAGE);
            
            cout << "delivers buffer: " << bufferName << " to receiver: " << receiver << endl;
            kernel->getThread(receiver)->addBuffer(buffer);
          }
          else {
            cout <<"reciver " << receiver << " not exist!" << endl;
          }

          kernel->interrupt->SetLevel(oldLevel);
          break;
        }

        //delay requesting process until a message arrives in the process's queue, may be a dummy message from system
        //if the message has already arrived, process it directly.
        //if sender does not exist, print a error message.
        //remove the buffer from queue.
        case SC_WaitMessage:
        {
          IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff); 
          kernel->interrupt->SetLevel(IntOff);

          cout << "---------Sys call waiting message called by: "<< kernel->currentThread->getName() << "-----------" << endl;
          int senderAddr = kernel->machine->ReadRegister(4);
          int msgAddr = kernel->machine->ReadRegister(5);
          int bufferAddr = kernel->machine->ReadRegister(6);
          string sender = getStringInMem(senderAddr);
          string bufferName = getStringInMem(bufferAddr);
          string receiver = std::string(kernel->currentThread->getName());

          cout << "sender: " << sender << " ,receiver: " << receiver << " ,bufferName: " << bufferName << endl;
          
          if (kernel->currentThread->contains(bufferName)) {
            MsgBuffer *buffer = kernel->bufferPool->Search(bufferName);
            cout << "buffer: " << bufferName << " has already in queue, message: " << buffer->getMessage() << " ,from sender: " << sender << endl;
            writeInToMen(buffer->getMessage(), msgAddr);
            cout << "remove buffer: " << bufferName << " from queue" << endl;
            kernel->currentThread->removeBuffer(bufferName);
          }
          else if (kernel->isThreadExist(sender)) {
            
            MsgBuffer *buffer = kernel->bufferPool->FindNextToUse(bufferName);
            buffer->setSender(sender);
            buffer->setReceiver(receiver);
            buffer->setId(bufferName);
            buffer->setStatus(true);
            buffer->setUsingStatus(WAIT_MESSAGE);

            //kernel->currentThread->addBuffer(buffer);

            cout << "buffer: " << bufferName << " not yet received from sender: " << sender << " ,delay until this message arrives" << endl;

            kernel->currentThread->Sleep(FALSE);

            cout << "-----------" << kernel->currentThread->getName() << " received waiting message---------" << endl;

            if (buffer->getMessage().compare("dummy message") == 0)
              cout << "message: " << buffer->getMessage() << " ,dummy message from system, due to waiting sender terminates" << endl;
            else 
              cout << "message: " << buffer->getMessage() << " ,from sender: " << sender << " ,in buffer : " << bufferName << " arrived" << endl;
 
            writeInToMen(buffer->getMessage(), msgAddr);
            
          }
          else {
            cout << "error! sender: " << sender << " dose not exist! write a dummy message back" << endl;
            writeInToMen("message from kerenl, sender dose not exist!", msgAddr);
            break;
          }
          
          kernel->interrupt->SetLevel(oldLevel);
          break;
        }

        //copy an answer in which message has been received
        //deliver it to queue of original sender 
        //the sender of the message is activated if it is waiting for the answer
        //if the buffer dose not in pool, print a error message
        //if origin sender terminated, print a error message and the answer will not send
        case SC_SendAnswer: //receiver and sender reverse
        {
          IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff); 
          kernel->interrupt->SetLevel(IntOff);

          cout << "---------Sys call sending answer called by: " << kernel->currentThread->getName() << "-----------"  << endl;
          int resAddr = kernel->machine->ReadRegister(4);
          int ansAddr = kernel->machine->ReadRegister(5);
          int bufferAddr = kernel->machine->ReadRegister(6);

          string result = getStringInMem(resAddr);
          string answer = getStringInMem(ansAddr);
          string bufferName = getStringInMem(bufferAddr);

          MsgBuffer *buffer = kernel->bufferPool->Search(bufferName);
          string sender = buffer->getSender();
          string receiver = buffer->getReceiver();
          
          

          cout << receiver << " send back result: " << result << " ,and answer: " << answer << " ,to " << sender << " ,using buffer: " << bufferName << endl;

          if (kernel->bufferPool->Search(bufferName) == NULL) {
            cout << "error! no buffer exits!" << endl;
            break;
          }

          buffer->setAnswer(answer);
          buffer->setResult(result);
          buffer->setUsingStatus(SEND_ANSWER);

          if (kernel->isThreadExist(sender) && kernel->bufferPool->Search(bufferName) != NULL) {
            
            cout << sender << " is waiting for answer in buffer: " << bufferName << " ,acitve original sender" << endl;
            kernel->scheduler->ReadyToRun(kernel->getThread(sender));

          }
          else if (kernel->isThreadExist(sender)) {
            if (kernel->getThread(sender)->reachLimit()) {
              cout << "erro! over original sender: "<< sender << "\'s queue limitation" << endl;
              break;
            }
            cout << receiver << " delivers answer in buffer: " << bufferName << " ,to original sender: " << sender << endl;
            kernel->getThread(sender)->addBuffer(buffer);
          }
          else {
            cout << "error, original sender dose not exist" << endl;
            buffer->setStatus(false);
          }
          kernel->interrupt->SetLevel(oldLevel);
          break;
        }

        //delays the requesting process until answer arrives in a given buffer
        //On arrival, the answer is copied into the process, and return the buffer to pool
        case SC_WaitAnswer:
        {
          IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff); 
          kernel->interrupt->SetLevel(IntOff);

          cout << "---------Sys call waiting answer called by: " << kernel->currentThread->getName() << "-----------"  << endl;
          

          int resAddr = kernel->machine->ReadRegister(4);
          int ansAddr = kernel->machine->ReadRegister(5);
          int bufferAddr = kernel->machine->ReadRegister(6);

          string bufferName = getStringInMem(bufferAddr);


          if (kernel->bufferPool->Search(bufferName) == NULL) {
            cout << "error! no buffer exits!" << endl;
            break;
          }

          MsgBuffer *buffer = kernel->bufferPool->Search(bufferName);
          if (kernel->currentThread->contains(bufferName)) {
            cout << "buffer: " << bufferName << " has already in queue, result: " << buffer->getResult() 
                      << " ,answer: " << buffer->getAnswer() << endl;
            writeInToMen(buffer->getAnswer(), ansAddr);
            writeInToMen(buffer->getResult(), resAddr);
            kernel->currentThread->removeBuffer(bufferName);
            cout << "remove buffer: " << bufferName << " from queue" << endl;
          }
          else if (kernel->isThreadExist(buffer->getReceiver())) {
 
            cout << "buffer: " << bufferName << " not yet received, delay until this buffer arrives" << endl;
            buffer->setUsingStatus(WAIT_ANSWER);
            kernel->currentThread->Sleep(FALSE);

            cout << "-----------" << kernel->currentThread->getName() << " received waiting message---------" << endl;
            
            if (buffer->getAnswer().compare("dummy message") == 0)
              cout << "answer: " << buffer->getAnswer() << " ,dummy answer from system, due to waiting sender terminates" << endl;
            else 
              cout << "buffer: " << bufferName << " received, result: " << buffer->getResult() 
                      << " ,answer: " << buffer->getAnswer() << endl;
            writeInToMen(buffer->getAnswer(), ansAddr);
            writeInToMen(buffer->getResult(), resAddr);
          }
          else {
            cout << "origin receiver: " << buffer->getReceiver() << " dose not exist! write a dummy message back" << endl;
            writeInToMen("message from kerenl, receiver dose not exist!", ansAddr);
          }

          cout << "buffer: " << bufferName << " returned to pool" << endl;

          buffer->setStatus(false);
          
          kernel->interrupt->SetLevel(oldLevel);
          break;
        }

        case SC_Write:
        {
          //printf("Write system call made by %s\n", kernel->currentThread->getName());
          int base = kernel->machine->ReadRegister(4);
          int number = kernel->machine->ReadRegister(5);
          int c;
          for (int i=0; i<number; i++) {
              if (!kernel->machine->ReadMem(base+i,1,&c)) {
                kernel->machine->ReadMem(base+i,1,&c);
              }
              cout<<char(c);
          }
        break;
        }

        case SC_Exit:
        {
          IntStatus oldLevel = kernel->interrupt->SetLevel(IntOff); 
          kernel->interrupt->SetLevel(IntOff);

          cout << "---------Sys call exit called by: " << kernel->currentThread->getName() << "-----------"  << endl;
          string sender = std::string(kernel->currentThread->getName());
          
          MsgBuffer* buffer = kernel->bufferPool->SearchBySender(sender);

          while (buffer != NULL) {
            
            string receiverTmp = buffer->getReceiver();
            buffer->setMessage("dummy message");
            buffer->setUsingStatus(SEND_MESSAGE);
            cout << "sending dummy message to receiver: " << receiverTmp << endl;
            kernel->scheduler->ReadyToRun(kernel->getThread(receiverTmp));
            
            buffer = kernel->bufferPool->SearchBySender(sender);
          }

          string receiver = std::string(kernel->currentThread->getName());

          buffer = kernel->bufferPool->SearchByReceiver(receiver);
          while (buffer != NULL) {
            string senderTmp = buffer->getSender();
            buffer->setAnswer("dummy message");
            buffer->setResult("dummy message");
            buffer->setUsingStatus(SEND_ANSWER);
            cout << "sending dummy answer to original sender: " << senderTmp << endl;
            kernel->scheduler->ReadyToRun(kernel->getThread(senderTmp));
            buffer = kernel->bufferPool->SearchByReceiver(receiver);
          }

          kernel->currentThread->Finish();
          kernel->interrupt->SetLevel(oldLevel);
          break;
        } 
        default:
          cerr << "Unexpected system call " << type << "\n";
          break;
      }
      break;
    }
    default:
      cerr << "Unexpected user mode exception" << (int)which << "\n";
      break;
  }
  
  /* Modify return point */
  {
    /* set previous programm counter (debugging only)*/
    kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));
    
    /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
    kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
    
    /* set next programm counter for brach execution */
    kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
  }
}
