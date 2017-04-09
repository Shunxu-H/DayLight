ROOTDIR = $(shell pwd)
OBJDIR = $(ROOTDIR)/.obj
DEPDIR = $(ROOTDIR)/.d
INCLUDEDIR = -iquote $(ROOTDIR)/Include/

DEBUGFLAG = 
DEBUG = all
OBJFLAGS = -Werror -ansi -O -c -std=c++11 -MMD -MF $(DEPDIR)/$(addsuffix .d,$(basename $@)) -MP $(INCLUDEDIR)
EXCFLAGS = -Werror -ansi -O -std=c++11
TARGET = RayTracer
SOURCE = $(wildcard *.cpp)
OBJECTS = $(wildcard $(OBJDIR)/*.o)



all: 
	if [ ! -e $(OBJDIR) ]; then mkdir $(OBJDIR); fi;
	if [ ! -e $(DEPDIR) ]; then mkdir $(DEPDIR); fi;
	+$(MAKE) $(DEDBUG) -C Internal/
	+$(MAKE) $(DEDBUG) -C Utility/
	+$(MAKE) $(DEDBUG) -C Input/
	+$(MAKE) $(DEDBUG) -C Output/
	make $(TARGET) 


$(TARGET): $(OBJECTS)
	$(CXX) $(DEBUGFLAG) $(EXCFLAGS) $(OBJECTS) -o $(TARGET) -lglut -lGL


debug: DEBUGFLAG = -g 
debug: DEBUG = debug 
debug: all

clean:
	rm -rf $(TARGET) $(OBJECTS) *.d
remake: clean
	make all
r: 
	make all && ./p2.out

-include $(DEPDIR)/$(SOURCE:.cpp=.d)
