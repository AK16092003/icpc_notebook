/**
 * Author: Benjamin Qi, Oleksandr Kulkov, chilli
 * Date: 2020-01-12
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most log(n)
 * light edges. Code does additive modifications and max queries, but can
 * support commutative segtree modifications/queries on paths and subtrees.
 * Takes as input the full adjacency list. VALS\_EDGES being true means that
 * values are stored in the edges, as opposed to the nodes. All values
 * initialized to the segtree default. Root must be 0.
 * Time: O((\log N)^2)
 * Status: stress-tested against old HLD
 */
#pragma once

struct HLD {
  int n;
  vector<int> siz, top, dep, par, in, out, seq;
  vector<vector<int>> adj;
  int timer;
  
  HLD() {}
  HLD(int n) {
    init(n);
  }
  void init(int n) {
    this->n = n;
    siz.resize(n);
    top.resize(n);
    dep.resize(n);
    par.resize(n);
    in.resize(n);
    out.resize(n);
    seq.resize(n);
    timer = -1;
    adj.assign(n, {});
  }
  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void work(int root = 0) {
    top[root] = root;
    dep[root] = 0;
    par[root] = -1;
    dfs1(root);
    dfs2(root);
  }
  void dfs1(int u) {
    if (par[u] != -1) {
      adj[u].erase(find(adj[u].begin(), adj[u].end(), par[u]));
    }
    
    siz[u] = 1;
    for (auto &v : adj[u]) {
      par[v] = u;
      dep[v] = dep[u] + 1;
      dfs1(v);
      siz[u] += siz[v];
      if (siz[v] > siz[adj[u][0]]) {
        swap(v, adj[u][0]);
      }
    }
  }
  void dfs2(int u) {
    in[u] = ++timer;
    seq[in[u]] = u;
    for (auto v : adj[u]) {
      top[v] = v == adj[u][0] ? top[u] : v;
      dfs2(v);
    }
    out[u] = timer;
  }
  int lca(int u, int v) {
    while (top[u] != top[v]) {
      if (dep[top[u]] > dep[top[v]]) {
        u = par[top[u]];
      } else {
        v = par[top[v]];
      }
    }
    return dep[u] < dep[v] ? u : v;
  }
  
  int dist(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[lca(u, v)];
  }
  
  int jump(int u, int k) {
    if (dep[u] < k) {
      return -1;
    }
    
    int d = dep[u] - k;
    
    while (dep[top[u]] > d) {
      u = par[top[u]];
    }
    
    return seq[in[u] - dep[u] + d];
  }
  
  bool isAncester(int u, int v) {
    return in[u] <= in[v] && in[v] <= out[u];
  }
  
  int rootedParent(int u, int v) {
    swap(u, v);
    if (u == v) {
      return u;
    }
    if (!isAncester(u, v)) {
      return par[u];
    }
    auto it = upper_bound(adj[u].begin(), adj[u].end(), v, [&](int x, int y) {
      return in[x] < in[y];
    }) - 1;
    return *it;
  }
  
  int rootedSize(int u, int v) {
    if (u == v) {
      return n;
    }
    if (!isAncester(v, u)) {
      return siz[v];
    }
    return n - siz[rootedParent(u, v)];
  }
  
  int rootedLca(int a, int b, int c) {
    return lca(a, b) ^ lca(b, c) ^ lca(c, a);
  }
};
