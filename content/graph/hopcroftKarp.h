/**
 * Author: Chen Xing
 * Date: 2009-10-13
 * License: CC0
 * Source: N/A
 * Description: Fast bipartite matching algorithm. Graph $g$ should be a list
 * of neighbors of the left partition, and $btoa$ should be a vector full of
 * -1's of the same size as the right partition. Returns the size of
 * the matching. $btoa[i]$ will be the match for vertex $i$ on the right side,
 * or $-1$ if it's not matched.
 * Time: O(\sqrt{V}E)
 * Status: stress-tested by MinimumVertexCover, and tested on oldkattis.adkbipmatch and SPOJ:MATCHING
 */
#pragma once

// matching : vector<pair<int,int>> 
// edg : vector<pair<int,int>> 
// l - left partition
// r - right partition
// m - edges 
// graph 0-based indexing


vector<pair<int,int>> matching;
vector<pair<int,int>> edg;


auto hopcroft_karp = [&]() -> void {
    vector<int> deg(l+1);
    for (auto &[u, v] : edg) deg[u]++;
    partial_sum(begin(deg), end(deg), begin(deg));
    vector<int> g(m), lmc(l, -1), rmc(r, -1), a, p, q(l);
    for (auto &[u, v] : edg) g[--deg[u]] = v;
    while (true) {
      a.assign(l, -1), p.assign(l, -1);
      int t = 0, match = false;
      for (int i = 0; i < l; i++) {
        if (lmc[i] == -1) q[t++] = a[i] = p[i] = i;
      }
      for (int i = 0; i < t; i++) {
        int x = q[i];
        if (~lmc[a[x]]) continue;
        for (int j = deg[x]; j < deg[x+1]; j++) {
          int y = g[j];
          if (rmc[y] == -1) {
            while (~y) {
              rmc[y] = x, swap(lmc[x], y), x = p[x];
            }
            match = true;
            break;
          }
          if (p[rmc[y]] == -1) q[t++] = y = rmc[y], p[y] = x, a[y] = a[x];
        }
      }
      if (!match) break;
    }
    for (int i = 0; i < l; i++) {
      if (~lmc[i]) matching.push_back({ i, lmc[i] });
    }
  };


  hopcroft_karp();
