# Written by Zeal Jagannatha May 2011

.PHONY: clean realclean linecount deleteGraphs

EXE =	graph

graph: Makefile.dep
	make --no-print-directory -f Makefile.real graph

include Makefile.inc

clean:
	rm -f $(OBJS) $(SrcDir)/commandParser/parser.cpp $(SrcDir)/commandParser/parser.hpp $(SrcDir)/commandParser/scanner.cpp

deleteGraphs:
	rm -f .graphConfig graph*.pdf

realclean: clean deleteGraphs
	rm -f $(EXE) Makefile.dep
	rm -f `find . | grep "\.*~"`

Makefile.dep: $(SRCS)
	if [ ! -e Makefile.dep ] ; then touch Makefile.dep ; fi
	$(DEP) $(DEPFLAGS) -fMakefile.dep -- $(CXXFLAGS) -- $(SRCS) 2> /dev/null
	rm -f Makefile.dep.bak

linecount:
	wc -l $(SRCS) Makefile Makefile.inc Makefile.real
