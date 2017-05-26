TOOLPATH  = ./tools/
CODESPATH = ./codes/
LIBSPATH  = ./libs/
MAKE      = $(TOOLPATH)make.exe -r
DEL       = del
COPY      = copy

default :
	$(MAKE) lib
	$(MAKE) pve
	$(MAKE) zipai
	$(MAKE) clean

BasicClasses.o : $(CODESPATH)BasicClasses.cpp Makefile
	g++ -c $(CODESPATH)BasicClasses.cpp

Node.o : $(CODESPATH)Node.cpp Makefile
	g++ -c $(CODESPATH)Node.cpp

weight.o : $(CODESPATH)weight.cpp Makefile
	g++ -c $(CODESPATH)weight.cpp

GetWeightAll.o : $(CODESPATH)GetWeightAll.cpp Makefile
	g++ -c $(CODESPATH)GetWeightAll.cpp

GameTree.o : $(CODESPATH)GameTree.cpp Makefile
	g++ -c $(CODESPATH)GameTree.cpp

Board.o : $(CODESPATH)Board.cpp Makefile
	g++ -c $(CODESPATH)Board.cpp

libAI.o : BasicClasses.o Node.o weight.o GetWeightAll.o GameTree.o Board.o $(CODESPATH)libAI.cpp Makefile
	g++ -c $(CODESPATH)libAI.cpp

libAI.dll : libAI.o Makefile
	ar -rc $(LIBSPATH)libAI.dll *.o

Board2.o : $(CODESPATH)pve/Board2.cpp Makefile
	g++ -c $(CODESPATH)pve/Board2.cpp

GetWeightAll2.o : $(CODESPATH)pve/GetWeightAll2.cpp Makefile
	g++ -c $(CODESPATH)pve/GetWeightAll2.cpp

pve.exe : libAI.o BasicClasses.o weight.o Node.o GameTree.o Board2.o GetWeightAll2.o $(CODESPATH)pve.cpp Makefile
	g++ -c $(CODESPATH)pve.cpp
	g++ -o pve libAI.o BasicClasses.o weight.o Node.o GameTree.o GetWeightAll2.o Board2.o pve.o

zipAI.exe : $(LIBSPATH)libAI.dll Makefile
	g++ -c $(CODESPATH)zipAI.cpp
	g++ -o zipAI zipAI.o $(LIBSPATH)libAI.dll

lib :
	$(MAKE) libAI.dll

zipai :
	$(MAKE) zipAI.exe

pve :
	$(MAKE) pve.exe

clean :
	$(DEL) /Q *.o
	
move :
	$(COPY) /Y zipAI.exe D:\WandS\wuziqiAI\WindowsFormsApplication1\WindowsFormsApplication1\bin\Debug\
	$(COPY) /Y zipAI.exe D:\WandS\wuziqiAI\WindowsFormsApplication1\WindowsFormsApplication1\bin\Release\