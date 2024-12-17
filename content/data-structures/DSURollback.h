/**
 * Author: Lukas Polacek, Simon Lindholm
 * Date: 2019-12-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure with undo.
 * Time: $O(\log(N))$
 */
struct DSUwithRollback {
  vector<int> par, size;
  int c;
  stack<array<int,4>> st;
  void init(int n){
    c = n;
    par.resize(n + 1);
    size.assign(n + 1, 1);
    iota(par.begin(), par.end(), 0);
  }
  int leader(int u){
    return u == par[u] ? u : leader(par[u]);
  }
  bool same(int u,int v){
    return leader(u) == leader(v);
  }
  int get_size(int u){
    return size[leader(u)];
  }
  int count(){
    return c;
  }
  bool merge(int u,int v){
    u = leader(u);
    v = leader(v);
    if(u == v) return false;
    if(size[u] < size[v]) swap(u,v);
    st.push({u, v, size[u], size[v]});
    c--;
    par[v] = u;
    size[u] += size[v];
    return true;
  }
  void rollback(){
    if(st.empty()) return;
    auto [u, v, su, sv] = st.top();
    st.pop();
    c++;
    par[v] = v;
    size[u] = su;
    size[v] = sv;
  }
};
