#
# Makefile for building user programs to run on top of Nachos
#
#  Use "make" to build the test executable(s)
#  Use "make clean" to remove .o files and .coff files
#  Use "make distclean" to remove all files produced by make, including
#     the test executables
#
# This is a GNU Makefile.  It must be used with the GNU make program.
# At UW, the GNU make program is /software/gnu/bin/make.
# In many other places it is known as "gmake".
# You may wish to include /software/gnu/bin/ early in your command
# search path, so that you will be using GNU make when you type "make".
#
# Several things to be aware of:
#
#    It should not be necessary to build the test executables for
#     every type of host machine on which Nachos runs.  You should
#     be able to build them once, and then use them regardless of
#     the host machine type.  That is because the test executables
#     run on the simulated MIPS machine, and not on the host.
#
#    However:
#	(1) if you are experiencing problems with the test executables,
#	    it would be prudent to rebuild them on the host machine
#	    on which you are currently running Nachos.  To do this,
#    	    just type "make distclean", and then "make"
#
#	(2) the procedure used to build the test executables does
#	    depend on the host machine you are on.  All of the machine
#	    dependencies are isolated in the Makefile.dep file.
#	    It should be possible to build the test executables on
#	    any MFCF machine.   In the MFCF environment, this makefile
#           should automatically figure out what type of host you are
#	    on, and should use the appropriate procedure.
#           However, if you are working outside the MFCF environment,
#           you will need to build a cross-compiler, build coff2noff,
#           and edit Makefile.dep in this directory before you
#           can build the test programs.
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed 
# 	to ld, in order for the routine "Start" to be loaded at location 0
#
#    When you make the test programs, you will see messages like these:
#		numsections 3 
#		Loading 3 sections:
#		        ".text", filepos 0xd0, mempos 0x0, size 0x440
#		        ".data", filepos 0x510, mempos 0x440, size 0x0
#		        ".bss", filepos 0x0, mempos 0x440, size 0x12c0
#    These messages are normal.  They come from the coff2noff program.
#    They are useful in that they tell you how big the various parts of your
#     compiled user program are, and where in the address space
#     coff2noff is going to place them.   This information is also
#     recorded in the header of the executable file that coff2noff
#     creates.  See the method AddrSpace::Load (in userprog/addrspace.cc)
#     for an example of how this header is used by the Nachos OS to set up the
#     address space for a new process that will run the executable.
#
#
# Adding New Test Programs:
#
#     You are free to write new test programs, and to modify the
#	existing programs.   If you write a new program, you will
# 	need to modify this makefile so that the new program will
#       get built.
#     You will need to make the following changes for each program
#       you add:
#		(1) add the program's name to PROGRAMS variable definition
#	 	(2) add dependencies and build commands for the new
#			program.  The easiest way to do this is to
#			copy the dependencies and commands for an
#			existing program, and then change the names.
#
#	For example, if you write a test program in foo.c, for which
#	the executable is to be called foo, you should do the following:
#
#	change the PROGRAMS definition to look like this:
#
#		PROGRAMS = halt shell matmult sort foo
#
#	add these dependencies/commands:
#
#		foo.o: foo.c
#			$(CC) $(CFLAGS) -c foo.c
#		foo: foo.o start.o
#			$(LD) $(LDFLAGS) start.o foo.o -o foo.coff
#			$(COFF2NOFF) foo.coff foo
#
#       Be careful when you copy the commands!  The commands
# 	must be indented with a *TAB*, not a bunch of spaces.
#
#
#############################################################################
# Makefile.dep contains all machine-dependent definitions
# If you are trying to build coff2noff somewhere outside
# of the MFCF environment, you will almost certainly want
# to visit and edit Makefile.dep before doing so
#############################################################################

include Makefile.dep

CC = $(GCCDIR)gcc
AS = $(GCCDIR)as
LD = $(GCCDIR)ld

INCDIR =-I../userprog -I../lib
CFLAGS = -G 0 -c $(INCDIR) -B/usr/local/nachos/lib/gcc-lib/decstation-ultrix/2.95.2/ -B/usr/local/nachos/decstation-ultrix/bin/

ifeq ($(hosttype),unknown)
PROGRAMS = unknownhost
else
# change this if you create a new test program!
<<<<<<< Updated upstream
PROGRAMS = add halt shell matmult sort segments client server uprog1 uprog2_client uprog2_server uprog3_client uprog3_server uprog4
=======
PROGRAMS = add halt shell matmult sort segments client server uprog1 uprog2_client uprog2_server uprog3_A  uprog3_B uprog3_C uprog4 uprog5_client uprog5_server1 uprog5_server2 uprog5_server3 
>>>>>>> Stashed changes
endif

all: $(PROGRAMS)

start.o: start.S ../userprog/syscall.h
	$(CC) $(CFLAGS) $(ASFLAGS) -c start.S

halt.o: halt.c
	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	$(COFF2NOFF) halt.coff halt

add.o: add.c
	$(CC) $(CFLAGS) -c add.c

add: add.o start.o
	$(LD) $(LDFLAGS) start.o add.o -o add.coff
	$(COFF2NOFF) add.coff add

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c
shell: shell.o start.o
	$(LD) $(LDFLAGS) start.o shell.o -o shell.coff
	$(COFF2NOFF) shell.coff shell

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c
sort: sort.o start.o
	$(LD) $(LDFLAGS) start.o sort.o -o sort.coff
	$(COFF2NOFF) sort.coff sort

segments.o: segments.c
	$(CC) $(CFLAGS) -c segments.c
segments: segments.o start.o
	$(LD) $(LDFLAGS) start.o segments.o -o segments.coff
	$(COFF2NOFF) segments.coff segments

matmult.o: matmult.c
	$(CC) $(CFLAGS) -c matmult.c
matmult: matmult.o start.o
	$(LD) $(LDFLAGS) start.o matmult.o -o matmult.coff
	$(COFF2NOFF) matmult.coff matmult

client.o: client.c
	$(CC) $(CFLAGS) -c client.c
client: client.o start.o
	$(LD) $(LDFLAGS) start.o client.o -o client.coff
	$(COFF2NOFF) client.coff client

server.o: server.c
	$(CC) $(CFLAGS) -c server.c
server: server.o start.o
	$(LD) $(LDFLAGS) start.o server.o -o server.coff
	$(COFF2NOFF) server.coff server

uprog1.o: uprog1.c
	$(CC) $(CFLAGS) -c uprog1.c
uprog1: uprog1.o start.o
	$(LD) $(LDFLAGS) start.o uprog1.o -o uprog1.coff
	$(COFF2NOFF) uprog1.coff uprog1

uprog2_client.o: uprog2_client.c
	$(CC) $(CFLAGS) -c uprog2_client.c
uprog2_client: uprog2_client.o start.o
	$(LD) $(LDFLAGS) start.o uprog2_client.o -o uprog2_client.coff
	$(COFF2NOFF) uprog2_client.coff uprog2_client

uprog2_server.o: uprog2_server.c
	$(CC) $(CFLAGS) -c uprog2_server.c
uprog2_server: uprog2_server.o start.o
	$(LD) $(LDFLAGS) start.o uprog2_server.o -o uprog2_server.coff
	$(COFF2NOFF) uprog2_server.coff uprog2_server

uprog3_A.o: uprog3_A.c
	$(CC) $(CFLAGS) -c uprog3_A.c
uprog3_A: uprog3_A.o start.o
	$(LD) $(LDFLAGS) start.o uprog3_A.o -o uprog3_A.coff
	$(COFF2NOFF) uprog3_A.coff uprog3_A

uprog3_B.o: uprog3_B.c
	$(CC) $(CFLAGS) -c uprog3_B.c
uprog3_B: uprog3_B.o start.o
	$(LD) $(LDFLAGS) start.o uprog3_B.o -o uprog3_B.coff
	$(COFF2NOFF) uprog3_B.coff uprog3_B

uprog3_C.o: uprog3_C.c
	$(CC) $(CFLAGS) -c uprog3_C.c
uprog3_C: uprog3_C.o start.o
	$(LD) $(LDFLAGS) start.o uprog3_C.o -o uprog3_C.coff
	$(COFF2NOFF) uprog3_C.coff uprog3_C

uprog4.o: uprog4.c
	$(CC) $(CFLAGS) -c uprog4.c
uprog4: uprog4.o start.o
	$(LD) $(LDFLAGS) start.o uprog4.o -o uprog4.coff
	$(COFF2NOFF) uprog4.coff uprog4

uprog5_client.o: uprog5_client.c
	$(CC) $(CFLAGS) -c uprog5_client.c
uprog5_client: uprog5_client.o start.o
	$(LD) $(LDFLAGS) start.o uprog5_client.o -o uprog5_client.coff
	$(COFF2NOFF) uprog5_client.coff uprog5_client

uprog5_server1.o: uprog5_server1.c
	$(CC) $(CFLAGS) -c uprog5_server1.c
uprog5_server1: uprog5_server1.o start.o
	$(LD) $(LDFLAGS) start.o uprog5_server1.o -o uprog5_server1.coff
	$(COFF2NOFF) uprog5_server1.coff uprog5_server1

uprog5_server2.o: uprog5_server2.c
	$(CC) $(CFLAGS) -c uprog5_server2.c
uprog5_server2: uprog5_server2.o start.o
	$(LD) $(LDFLAGS) start.o uprog5_server2.o -o uprog5_server2.coff
	$(COFF2NOFF) uprog5_server2.coff uprog5_server2

uprog5_server3.o: uprog5_server3.c
	$(CC) $(CFLAGS) -c uprog5_server3.c
uprog5_server3: uprog5_server3.o start.o
	$(LD) $(LDFLAGS) start.o uprog5_server3.o -o uprog5_server3.coff
	$(COFF2NOFF) uprog5_server3.coff uprog5_server3

clean:
	$(RM) -f *.o *.ii
	$(RM) -f *.coff

distclean: clean
	$(RM) -f $(PROGRAMS)

unknownhost:
	@echo Host type could not be determined.
	@echo make is terminating.
	@echo If you are on an MFCF machine, contact the instructor to report this problem
	@echo Otherwise, edit Makefile.dep and try again.
