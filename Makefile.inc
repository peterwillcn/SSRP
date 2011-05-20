
EXE	= graph
SrcDir	= src

CXX	= g++
CXXFLAGS = -g $(Includes)
#CXXFLAGS = -g -DDEBUG $(Includes)

# Makedepend
DEP = makedepend
DEPFLAGS = -m -Y

Includes = \
	-I$(SrcDir)/FWGroup \
	-I$(SrcDir)/basicEdgeGroup \
	-I$(SrcDir)/edge \
	-I$(SrcDir)/journeyGroup \
	-I$(SrcDir)/match \
	-I$(SrcDir)/basicStructures \
	-I$(SrcDir)/journeyInfo \
	-I$(SrcDir)/path \
	-I$(SrcDir)/vertex \
	-I$(SrcDir)/edgeGroup \
	-I$(SrcDir)/graphGroup \
	-I$(SrcDir)/journey \
	-I$(SrcDir)/sHeuristics \
	-I$(SrcDir)/rand \
	-I$(SrcDir)/ioFunctions \
        -I$(SrcDir)/debug

OBJS =  $(SrcDir)/basicEdgeGroup/basicEdgeGroup.o \
	$(SrcDir)/edge/edge.o \
	$(SrcDir)/journeyGroup/journeyGroup.o \
	$(SrcDir)/match/match.o \
	$(SrcDir)/test.o \
	$(SrcDir)/basicStructures/basicStructures.o \
	$(SrcDir)/FWGroup/FWGroup.o \
	$(SrcDir)/journeyInfo/journeyInfo.o \
	$(SrcDir)/path/path.o \
	$(SrcDir)/vertex/vertex.o \
	$(SrcDir)/edgeGroup/edgeGroup.o \
	$(SrcDir)/graphGroup/graphGroup.o \
	$(SrcDir)/journey/journey.o \
	$(SrcDir)/sHeuristics/sHeuristics.o \
	$(SrcDir)/rand/rand.o \
	$(SrcDir)/ioFunctions/ioFunctions.o

SRCS =	$(SrcDir)/test.cpp \
	$(SrcDir)/sHeuristics/sHeuristics.h \
	$(SrcDir)/sHeuristics/sHeuristics.cpp \
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
	$(SrcDir)/match/match.cpp \
	$(SrcDir)/match/match.h \
	$(SrcDir)/ioFunctions/ioFunctions.h \
	$(SrcDir)/ioFunctions/ioFunctions.cpp \
	$(SrcDir)/rand/rand.h \
	$(SrcDir)/rand/rand.cpp \
        $(SrcDir)/debug/debug.h