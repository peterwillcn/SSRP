/*
 * Spanning Tree / Nash Equilibrium Heuristic
 *
 * This algorithm finds the spanning tree for a graph and then routes Journeys
 * on this spanning tree. It then transforms these routes back into the original
 * graph, and runs the nash equilibrium heuristic.
 */
graphGroup runSpanningNashHeuristic(graphGroup g, const vector<journeyInfo>& journeyInfos) {

    STGroup st;
    st.findMinSpanningTree(g.returnGraph(), 0);

    graphGroup spanningTree(st.returnMinSpanningTree(), journeyInfos);

    for(int i = 0; i < journeyInfos.size(); i++) {
        spanningTree.addJourneySP(i);
        spanningTree.refindSharedCosts();
    }

    // Route the paths back on the original graph
    for(int i = 0; i < journeyInfos.size(); i++) {
        path p = spanningTree.returnSharedPath(i);
        g.addJourney(i, p);
    }

    //bool nash = nashEquilibrium(g);

    return g;
}