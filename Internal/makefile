ROOTDIR = $(shell pwd)/..
DEPDIR = $(ROOTDIR)/.d
OBJDIR = $(ROOTDIR)/.obj
INCLUDEDIR = -iquote $(ROOTDIR)/Include/
DEBUGFLAG = -g
OBJFLAGS = -Werror -ansi -O -g -c -std=c++11 -MMD -MF $(DEPDIR)/$(addsuffix .d,$(basename $(@:$(OBJDIR)/%=%) )) -MP $(INCLUDEDIR)
SOURCE = $(wildcard *.cpp)
TARGET = $(SOURCE:%.cpp=$(OBJDIR)/%.o)

all: 
	make $(TARGET) 

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(DEBUGFLAG) $(OBJFLAGS) $< -o $@

debug: DEBUGFLAG += -g
debug: all

remake: clean all && make alls

-include $(DEPDIR)/$(SOURCE:.cpp=.d)