/**
 * @mainpage
 *
 * @authors Ronald Fenelus, Zeal Jagannatha
 *
 * @section intro Introduction
 *
 * The Shared Shortest Path Project (SSPP) attempts to find the shared shortest
 * path of a graph and journeys using a variety of heuristics. It is designed in
 * such a way as to be extendable, and allow easy addition of heuristics.
 *
 * @section todo To Do:
 *
 * Create documentation for remaining parts of project:
 *    - src/commandParser/*
 *    - src/debug/*
 *    - src/edge/*
 *    - src/edgeGroup/*
 *    - src/equilib/*
 *    - src/FWGroup/*
 *    - src/graphGroup/*
 *    - src/heuristics/*
 *    - src/ioFunctions/*
 *    - src/journey/*
 *    - src/journeyGroup/*
 *    - src/journeyInfo/*
 *    - src/match/*
 *    - src/options/*
 *    - src/path/*
 *    - src/rand/*
 *    - src/treeSearch/*
 *    - src/main.cpp
 *    - src/messages.h
 *
 * @section parser About the Command Line Parser
 *
 * This program uses flex and bison to parse command-line arguments. For information on these tools, visit:
 *
 * <a href="http://www.gnu.org/software/flex/">Flex</a>
 *
 * <a href="http://www.gnu.org/software/bison/">Bison</a>
 *
 * @section heuristics Heuristics Information
 *
 * For information on the currently used heuristics, see 'src/messages.h'
 *
 * For information on how to add heuristics see 'src/heuristics/heuristics.h'.
 *
 * @section compiling Compiling
 *
 * To compile, ensure that you have installed the following tools:
 *      bison, flex, make, makedepend
 * Then run `make` in the project directory.
 *
 * If you would like to change compilation options, change them in 'Makefile.inc'.
 */
