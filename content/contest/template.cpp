// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
 
#include <bits/stdc++.h>
using namespace std ;
 
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
 
template <class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
#define ll long long 
#define ull unsigned long long
#define lld long double
#define pii pair<int,int>
#define pll pair<ll,ll>
 
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);
#define rep(i,a,n) for (int i = a; i < n; i++)
#define vi vector<int>
#define nline "\n"
#define inf (ll)1e18
#define iinf (int)2e9
#define eb emplace_back
#define vb vector<bool>
#define vll vector<ll> 
#define vvll vector<vll>
#define vpll vector<pll>
#define vvi vector<vector<int>>
#define vvb vector<vector<bool>>
#define vc vector<char>
#define vvc vector<vector<char>>
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define mp make_pair
#define fs first
#define sc second
#define PI 3.141592653589793238462
#define set_bits __builtin_popcountll
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
 

#define fi first
#define se second
#define pb push_back
#define mp make_pair

int rand(int l, int r){
 	static mt19937 
 	rng(chrono::steady_clock::now().time_since_epoch().count());
 	uniform_int_distribution<int> ludo(l, r); 
 	return ludo(rng);
}

void solve()
{

}
signed main(){
	
	fastio();
	int t=1;
	cin >> t;
	for(int i = 1 ; i <= t ; i ++) {
    		solve();
	}	
	return 0;
}
