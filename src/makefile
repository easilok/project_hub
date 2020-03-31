APPNAME=projectHub
APPFOLDER=../build
IDIR = ../inc
CCPP=g++
CPPFLAGS=-g -pthread -I$(IDIR) -Wall

ODIR=../obj
_LDIR=../lib
LDIR=$(patsubst %, -L%, $(_LDIR))

LIBS=-lm -lcurlpp -lcurl -lncurses

_DEPS = connection.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

SOURCES = $(shell find . -name "*.cpp" | sed 's/.\///')
# SOURCES = connection.cpp projectHub.cpp

_OBJ = $(patsubst %.cpp,%.o,$(SOURCES))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(APPFOLDER)/$(APPNAME): $(OBJ)
	$(CCPP) -g -o $@ $^ $(LDIR) $(LIBS) $(EXTFLAGS)

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CCPP) $(CPPFLAGS) -c $< -o $@ $(EXTFLAGS)

# ===== SINGLE FILE =====
# $(ODIR)/connection.o: connection.cpp $(DEPS)
# 	$(CCPP) $(CPPFLAGS) -c -o $@ $<

# $(ODIR)/projectHub.o: projectHub.cpp $(DEPS)
# 	$(CCPP) $(CPPFLAGS) -c -o $@ $< 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ *.o $(APPNAME) $(APPFOLDER)/$(APPNAME)
