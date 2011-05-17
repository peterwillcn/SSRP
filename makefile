# Christopher Earl
# Makefile for graphGroup

# Rewritten by Zeal Jagannatha May2011 #

.PHONY: clean realclean

CXX		= g++
CXXFLAGS	= -g

OBJS =	basicEdgeGroup.o \
	edge.o \
	journeyGroup.o \
	match.o \
	test.o \
	basicStructures.o \
	FWGroup.o \
	journeyInfo.o \
	path.o \
	vertex.o \
	edgeGroup.o \
	graphGroup.o \
	journey.o \
	sHeuristics.o

EXES =	graph.exe

graph.exe: $(OBJS)
	g++ -o graph.exe $(OBJS)

sHeuristics.o: sHeuristics.cpp sHeuristics.h graphGroup.h journeyInfo.h 

sHeuristics.h:

sHeuristics.cpp:

FWGroup.o: FWGroup.cpp FWGroup.h basicStructures.h vertex.h path.h journeyInfo.h graphGroup.h

FWGroup.cpp:

FWGroup.h:

graphGroup.o: graphGroup.cpp graphGroup.h basicStructures.h path.h basicEdgeGroup.h journeyInfo.h journeyGroup.h edgeGroup.h match.h

graphGroup.cpp:

graphGroup.h:

edgeGroup.o: edgeGroup.cpp edgeGroup.h basicStructures.h vertex.h path.h edge.h basicEdgeGroup.h journeyInfo.h

edgeGroup.h:

edgeGroup.cpp:

journeyGroup.o: journeyGroup.cpp journeyGroup.h basicStructures.h path.h journey.h journeyInfo.h

journeyGroup.cpp:

journeyGroup.h:path.h

journey.o: journey.cpp journey.h basicStructures.h path.h

journey.cpp:

journey.h:

journeyInfo.o: journeyInfo.cpp journeyInfo.h

journeyInfo.cpp:

journeyInfo.h:

basicEdgeGroup.o: basicEdgeGroup.cpp basicEdgeGroup.h basicStructures.h

basicEdgeGroup.h:

basicEdgeGroup.cpp:

edge.o: edge.cpp edge.h basicStructures.h

edge.cpp:

edge.h:

path.o: path.cpp path.h basicStructures.h

path.cpp:

path.h:

vertex.o: vertex.cpp vertex.h basicStructures.h

vertex.cpp:

vertex.h:

basicStructures.o: basicStructures.cpp basicStructures.h

basicStructures.h:

basicStructures.cpp:

match.o: path.h match.cpp match.h

match.cpp:

match.h:

clean:
	rm -f $(OBJS)

realclean: clean
	rm -f $(EXES)