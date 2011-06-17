#include "spanningTree.h"

#include <vector>

using namespace std;

#include "graphGroup.h"
#include "journeyInfo.h"
#include "STGroup.hpp"

/*
 * Spanning Tree Algorithm
 *
 * This is the vanilla version of the spanning tree algorithm. It finds the
 * spanning tree for a graph, then routes journeys on the spanning tree.
 */
graphGroup runSpanningTreeHeuristic(graphGroup g, const vector<journeyInfo>& journeyInfos) {

    STGroup st;
    st.findMinSpanningTree(g.returnGraph(), 0);

    graphGroup spanningTree(st.returnMinSpanningTree(), journeyInfos);

    for(int i = 0; i < journeyInfos.size(); i++) {
        spanningTree.addJourneySP(i);
        spanningTree.refindSharedCosts();
    }

    return spanningTree;
}