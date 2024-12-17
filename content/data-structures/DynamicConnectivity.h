/**
 * Author: Lukas Polacek, Simon Lindholm
 * Date: 2019-12-26
 * License: CC0
 * Source: folklore
 * Description: Dynamic Connectivity (DSU rollback example)
 * Time: $O(N log^2(N))$
 */
template<class Info>
struct DynamicConnectivity{
  int Q;
  vector<vector<Info>> seg;
  void init(int _q){
    Q = _q;
    seg.assign(4 * _q, {});
  }
  void update(int p, int l, int r, int ql, int qr, const Info &v){
    if(ql >= r || qr <= l) return;
    if(ql <= l && r <= qr){
      seg[p].push_back(v);
      return;
    }
    int m = (l + r) >> 1;
    update(p << 1, l, m, ql, qr, v);
    update(p << 1 | 1, m, r, ql, qr, v);
  }
  void dfs(int p, int l, int r, int L, int R){
    for(auto &v : seg[p]) v.add();
    if(l + 1 == r){
      // print answer
      if(l>=L && l<=R){
        cout<<dsu.count()<<" ";
      }
      for(int i = sz(seg[p]) - 1; i >= 0; i--){seg[p][i].remove();}
      return;
    }
    int m = (l + r) >> 1;
    dfs(p << 1, l, m, L, R);
    dfs(p << 1 | 1, m, r, L, R);
    for(int i = sz(seg[p]) - 1; i >= 0; i--){seg[p][i].remove();}
  }
  
  void add(const Info &v, int l, int r){
    update(1, 0, Q, l, r, v);
  }
  void get(int L, int R){
    dfs(1, 0, Q, L, R);
    cout<<nl;
  }
};
struct Info{
  int u, v, added = 0;
  void add(){added = dsu.merge(u, v);}
  void remove(){ if(added) dsu.rollback();}
};
