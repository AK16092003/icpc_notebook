/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Sparse Table finding sum in range. Both L,R inclusive
 * Usage:
 *  st god(N);
 *  god.build();
 *  god.qry(L,R) in $O(\log N)$  god.qry_i(L,R) in $O(1)$
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
const ll N=200000;
const ll M = 21;
ll tab[N+1][M+1],L[N+1],a[N];

struct st{
  ll n;
  st(ll _n){
    n=_n;
    for(ll i=2;i<=n;i++) L[i]=L[i/2]+1;
  }
  ll f(ll x,ll y){
    return (x+y);
  }
  void build(){
    for(ll i=0;i<n;i++) tab[i][0]=a[i];
    for(ll j=1;j<=M;j++){
      for(ll i=0;i<n;i++){
        if(i+(1<<j)-1<n)
          tab[i][j]=f(tab[i][j-1],tab[i+(1<<(j-1))][j-1]);
      }
    }
  }
  ll qry(ll l,ll r){
    ll len=r-l+1;
    ll idx=l;
    ll tot=0; // initialize neutral
    for(ll j=M;j>=0;j--){
      if(len&(1ll<<j)){
        tot=f(tot,tab[idx][j]);
        idx+=(1<<j);
      }
    }
    return tot;
  }
  ll qry_i(ll l,ll r){
    ll lg=L[r-l+1];
    return f(tab[l][lg],tab[r-(1<<lg)+1][lg]);
  }
};
