# Christopher Earl
# Makefile for graphGroup

# Rewritten by Zeal Jagannatha May2011 #

include Makefile.inc

.PHONY: clean realclean git

EXE =	graph

graph: Makefile.dep
	make --no-print-directory -f Makefile.real graph

clean:
	rm -f $(OBJS)

realclean: clean
	rm -f $(EXE)
	rm -f `find . | grep "\.*~"`

Makefile.dep: $(SRCS)
	if [ ! -e Makefile.dep ] ; then touch Makefile.dep ; fi
	$(DEP) $(DEPFLAGS) -fMakefile.dep -- $(CXXFLAGS) -- $(SRCS) 2> /dev/null
	rm -f Makefile.dep.bak