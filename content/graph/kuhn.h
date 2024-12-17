/**
 * Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: O(N*M) maximal edge matching 
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */
#pragma once

// maximal matching only bipartite
// first group n, second group k
// graph g[firstGrp].pushback(secondGrp)

int n , k;
vector<int> g[200005];
vector<bool> used;
vector<int> mt;

bool try_kuhn(int v) {
    if (used[v])
        return false;
    used[v] = true;
    for (int to : g[v]) {
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

// inside main function
mt.assign(k, -1);
for (int v = 0; v < n; ++v) {
   used.assign(n, false);
   try_kuhn(v);
}

for (int i = 0; i < k; ++i)
    if (mt[i] != -1)
       printf("%d %d\n", mt[i] + 1, i + 1);
