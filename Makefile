
runon:=g
check:=g

ifeq ($(runon),$(check))
ICC=g++
IFLAGS=-c -lm -O3	
else
ICC=icpc
IFLAGS=-c -O3 -fp-model precise -no-multibyte-chars
endif

##VPATH = ../Source
objects = constants.o init.o main.o variables.o
exec : $(objects)
	$(ICC) -o exec $(objects)

main.o : main.cpp main.h 
	$(ICC) $(IFLAGS) main.cpp

constants.o : constants.cpp main.h
	$(ICC) $(IFLAGS) constants.cpp 

init.o : init.cpp main.h
	$(ICC) $(IFLAGS) init.cpp

variables.o : variables.cpp main.h
	$(ICC) $(IFLAGS) variables.cpp

.PHONY: cleanall cleanobj cleanprogram

cleanall :
	rm exec $(objects)

cleanobj : 
	rm $(objects)

cleanprogram : 
	rm exec
