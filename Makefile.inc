
EXE	= sspp
SrcDir	= src

Includes = \
	-I$(SrcDir)/FWGroup \
	-I$(SrcDir)/basicEdgeGroup \
	-I$(SrcDir)/edge \
	-I$(SrcDir)/journeyGroup \
	-I$(SrcDir)/basicStructures \
	-I$(SrcDir)/journeyInfo \
	-I$(SrcDir)/path \
	-I$(SrcDir)/vertex \
	-I$(SrcDir)/edgeGroup \
	-I$(SrcDir)/graphGroup \
	-I$(SrcDir)/journey \
	-I$(SrcDir)/rand \
	-I$(SrcDir)/ioFunctions \
	-I$(SrcDir)/STGroup \
	-I$(SrcDir)/equilib \
	-I$(SrcDir)/debug \
	-I$(SrcDir)/options \
	-I$(SrcDir)/heuristics \
	-I$(SrcDir)/commandParser \
	-I$(SrcDir)/treeSearch

CXX	= g++
LD	= g++

# Bison
YACC = bison
YFLAGS = -d

# Bisonfix
BISONFIX = ./bisonfix

# Flex
LEX = flex
LFLAGS = -+

COMMONCXXFLAGS = -g -Wno-write-strings
COMMONLDFLAGS = -g

#COMMONCXXFLAGS = -O3 -Wno-write-strings
#COMMONLDFLAGS = -O3

#COMMONCXXFLAGS = -g -DDEBUG

CXXFLAGS = $(COMMONCXXFLAGS) $(Includes)
LDFLAGS = $(COMMONLDFLAGS) -lrt

# Makedepend
DEP = makedepend
DEPFLAGS = -m -Y

OBJS =  $(SrcDir)/basicEdgeGroup/basicEdgeGroup.o \
	$(SrcDir)/edge/edge.o \
	$(SrcDir)/journeyGroup/journeyGroup.o \
	$(SrcDir)/main.o \
	$(SrcDir)/basicStructures/basicStructures.o \
	$(SrcDir)/FWGroup/FWGroup.o \
	$(SrcDir)/journeyInfo/journeyInfo.o \
	$(SrcDir)/path/path.o \
	$(SrcDir)/vertex/vertex.o \
	$(SrcDir)/edgeGroup/edgeGroup.o \
	$(SrcDir)/graphGroup/graphGroup.o \
	$(SrcDir)/journey/journey.o \
	$(SrcDir)/rand/rand.o \
	$(SrcDir)/ioFunctions/ioFunctions.o \
	$(SrcDir)/equilib/nashTest.o \
	$(SrcDir)/STGroup/STGroup.o \
	$(SrcDir)/options/options.o \
	$(SrcDir)/heuristics/heuristics.o \
	$(SrcDir)/ioFunctions/color.o \
	$(SrcDir)/ioFunctions/colorString.o \
	$(SrcDir)/commandParser/parser.o \
	$(SrcDir)/commandParser/scanner.o \
	$(SrcDir)/treeSearch/treeSearch.o

SRCS =	$(SrcDir)/main.cpp \
	$(SrcDir)/FWGroup/FWGroup.cpp \
	$(SrcDir)/FWGroup/FWGroup.h \
	$(SrcDir)/graphGroup/graphGroup.cpp \
	$(SrcDir)/graphGroup/graphGroup.h \
	$(SrcDir)/edgeGroup/edgeGroup.h \
	$(SrcDir)/edgeGroup/edgeGroup.cpp \
	$(SrcDir)/journeyGroup/journeyGroup.cpp \
	$(SrcDir)/journeyGroup/journeyGroup.h \
	$(SrcDir)/journey/journey.cpp \
	$(SrcDir)/journey/journey.h \
	$(SrcDir)/journeyInfo/journeyInfo.h \
	$(SrcDir)/journeyInfo/journeyInfo.cpp \
	$(SrcDir)/basicEdgeGroup/basicEdgeGroup.h \
	$(SrcDir)/basicEdgeGroup/basicEdgeGroup.cpp \
	$(SrcDir)/edge/edge.cpp \
	$(SrcDir)/edge/edge.h \
	$(SrcDir)/path/path.cpp \
	$(SrcDir)/path/path.h \
	$(SrcDir)/vertex/vertex.cpp \
	$(SrcDir)/vertex/vertex.h \
	$(SrcDir)/basicStructures/basicStructures.h \
	$(SrcDir)/basicStructures/basicStructures.cpp \
	$(SrcDir)/ioFunctions/ioFunctions.h \
	$(SrcDir)/ioFunctions/ioFunctions.cpp \
	$(SrcDir)/rand/rand.h \
	$(SrcDir)/rand/rand.cpp \
	$(SrcDir)/STGroup/STGroup.hpp \
	$(SrcDir)/STGroup/STGroup.cpp \
	$(SrcDir)/equilib/nashTest.hpp \
	$(SrcDir)/equilib/nashTest.cpp \
	$(SrcDir)/debug/debug.h \
	$(SrcDir)/options/options.h \
	$(SrcDir)/options/options.cpp \
	$(SrcDir)/heuristics/heuristics.h \
	$(SrcDir)/heuristics/heuristics.cpp \
	$(SrcDir)/ioFunctions/color.h \
	$(SrcDir)/ioFunctions/color.cpp \
	$(SrcDir)/commandParser/parser.cpp \
	$(SrcDir)/commandParser/parser.hpp \
	$(SrcDir)/commandParser/scanner.cpp \
	$(SrcDir)/ioFunctions/colorString.h \
	$(SrcDir)/ioFunctions/colorString.cpp \
	$(SrcDir)/heuristics/dease.h \
	$(SrcDir)/heuristics/heuristics.h \
	$(SrcDir)/heuristics/nashEquilib.h \
	$(SrcDir)/heuristics/spanNash.h \
	$(SrcDir)/heuristics/subGraph.h \
	$(SrcDir)/heuristics/heuristics.cpp \
	$(SrcDir)/heuristics/heuristics.o \
	$(SrcDir)/heuristics/shortestPath.h \
	$(SrcDir)/heuristics/spanningTree.h \
	$(SrcDir)/heuristics/traversal.h \
	$(SrcDir)/treeSearch/treeSearch.h \
	$(SrcDir)/treeSearch/treeSearch.cpp \
	$(SrcDir)/messages.h

# makedepend can't handle flex or bison files,
# so we need to explictly say how to build these

# bison the parser file
$(SrcDir)/commandParser/parser.hpp $(SrcDir)/commandParser/parser.cpp: $(SrcDir)/commandParser/parser.yy
	$(YACC) $(YFLAGS) -o $(SrcDir)/commandParser/parser.cpp $(SrcDir)/commandParser/parser.yy
	$(BISONFIX) $(SrcDir)/commandParser/parser.cpp $(SrcDir)/commandParser/parser.hpp

# Empty rule for the actual parser source file
$(SrcDir)/commandParser/parser.yy:

# compile the parser object file
$(SrcDir)/commandParser/parser.o: $(SrcDir)/commandParser/parser.hpp $(SrcDir)/commandParser/parser.cpp

# flex the scanner file
$(SrcDir)/commandParser/scanner.cpp: $(SrcDir)/commandParser/scanner.ll
	$(LEX) $(LFLAGS) -o $(SrcDir)/commandParser/scanner.cpp $(SrcDir)/commandParser/scanner.ll

# empty rule for the actual scanner source file
$(SrcDir)/commandParser/scanner.ll:

# compile the scanner object file
$(SrcDir)/commandParser/scanner.o: $(SrcDir)/commandParser/scanner.cpp
