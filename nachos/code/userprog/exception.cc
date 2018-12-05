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
char * getStringInMem(int addr) {
  string name;
  int c;

  while (1) {
    if (!kernel->machine->ReadMem(base+i,1,&c)) {
        kernel->machine->ReadMem(base+i,1,&c);
    }
    if ((char)val != '\0') {
      name += char(c);
      addr++;
    }
    else {
      break;
    }
    
  }

  std::stringstream out;
  out << name;
  s = out.str();
  return (char*)s.c_str();
}

void writeInToMen(char *str, int ptr) {
  for (int i = ptr, j = 0; j < strlen(str); i++, j++) {
    kernel->machine->WriteMem(i, 1, (int)*(str+j));
  }
}

void
ExceptionHandler(ExceptionType which)
{
  int type = kernel->machine->ReadRegister(2);
  
  DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");
  
  switch (which) {
    case PageFaultException:
    {
      //cout<<"page fault\n";
      kernel->currentThread->space->PageFaultHandler();
      return;
      
    break;
    }
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

        case SC_SendMessage:
        {
          
          int receiverAddr = kernel->machine->ReadRegister(4);
          int msgAddr = kernel->machine->ReadRegister(5);
          int bufferAddr = kernel->machine->ReadRegister(6);
          char *receiver = getStringInMem(receiverAddr);
          char *message = getStringInMem(msgAddr);
          char *bufferName = getStringInMem(bufferAddr);
          char *sender = kernel->currentThread->getName();

          //to do --contains(bufferName)
          if (kernel->isThreadExist(receiver) && kernel->getThread(receiver)->contains(bufferName)) {
            MsgBuffer *buffer = kernel->bufferpool->Search(bufferName);
            buffer->setMessage(message);
            buffer->setStatus(true);

            kernel->scheduler->ReadyToRun(kernel->getThread(receiver));
          }

          else if (kernel->isThreadExist(receiver)) {
            MsgBuffer *buffer = kernel->bufferPool->FindNextToUse();
            buffer->setSender(sender);
            buffer->setReceiver(receiver);
            buffer->setId(bufferName);
            buffer->setMessage(message);
            buffer->setStatus(true);
            ///to do
            kernel->getThread(receiver)->addBuffer(buffer);
          }
          else {
            cout <<"reciver " << receiver << "not exist!" << endl;
          }

          break;
        }

        case SC_WaitMessage:
        {
          int senderAddr = kernel->machine->ReadRegister(4);
          int msgAddr = kernel->machine->ReadRegister(5);
          int bufferAddr = kernel->machine->ReadRegister(6);
          char *sender = getStringInMem(senderAddr);
          char *bufferName = getStringInMem(bufferAddr);
          char *receiver = kernel->currentThread->getName();
          
          if (kernel->currentThread->contains(bufferName)) {
            MsgBuffer *buffer = kernel->bufferpool->Search(bufferName);
            writeInToMen(buffer->getMessage(), msgAddr);
          }
          else if (kernel->isThreadExist(sender)) {
            MsgBuffer *buffer = kernel->bufferPool->FindNextToUse();
            buffer->setSender(sender);
            buffer->setReceiver(receiver);
            buffer->setId(bufferName);
            buffer->setStatus(true);

            kernel->currentThread->addBuffer(buffer);

            kernel->currentThread->Sleep();

            writeInToMen(buffer->getMessage(), msgAddr);
            
          }
          else {
            cout << "sender: " << sender << " dose not exist!" << endl;
            writeInToMen("message from kerenl, sender dose not exist!", msgAddr);
          }
          kernel->currentThread->removeBuffer(bufferName);
          break;
        }

        case SC_SendAnswer: //receiver and sender reverse
        {
          int resAddr = kernel->machine->ReadRegister(4);
          int ansAddr = kernel->machine->ReadRegister(5);
          int bufferAddr = kernel->machine->ReadRegister(6);

          char *result = getStringInMem(resAddr);
          char *answer = getStringInMem(ansAddr);
          char *bufferName = getStringInMem(bufferAddr);

          MsgBuffer *buffer = kernel->bufferpool->Search(bufferName);
          char *sender = buffer->getSender();
          char *reciver = buffer->getReceiver();
          
          buffer->setAnswer(answer);
          buffer->setResult(result);

          if (kernel->isThreadExist(sender) && kernel->getThread(sender)->contains(bufferName)) {
            
            kernel->scheduler->ReadyToRun(kernel->getThread(sender));
          }
          else if (kernel->isThreadExist(sender)) {
            ///to do
            kernel->getThread(sender)->addBuffer(buffer);
          }
          else {
            cout << "error" << endl;
          }
          break;
        }

        case SC_WaitAnswer:
        {
          int resAddr = kernel->machine->ReadRegister(4);
          int ansAddr = kernel->machine->ReadRegister(5);
          int bufferAddr = kernel->machine->ReadRegister(6);

          char *bufferName = getStringInMem(bufferAddr);

          if (kernel->bufferpool->Search(bufferName) == NULL) {
            cout << "error! no buffer exits!" << endl;
            break;
          }

          MsgBuffer *buffer = kernel->bufferpool->Search(bufferName);
          if (kernel->currentThread->contains(bufferName)) {
            
            writeInToMen(buffer->getAnswer(), ansAddr);
            writeInToMen(buffer->getResult(), resAddr);
          }
          else if (kernel->isThreadExist(receiver)) {
            kernel->currentThread->addBuffer(buffer);

            kernel->currentThread->Sleep();

            writeInToMen(buffer->getAnswer(), ansAddr);
            writeInToMen(buffer->getResult(), resAddr);
          }
          else {
            writeInToMen("message from kerenl, receiver dose not exist!", msgAddr);
          }
          buffer->setStatus(false);
          kernel->currentThread->removeBuffer(bufferName);
          break;
        }

        case SC_Exit:
        {
          //printf("Exit system call made by %s\n", kernel->currentThread->getName());
          kernel->currentThread->Finish();
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
