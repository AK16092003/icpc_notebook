/**
 * Author: chilli, pajenegod
 * Date: 2020-02-20
 * License: CC0
 * Source: Folklore
 * Description: Data structure for computing lowest common ancestors in a tree
 * (with 0 as root). C should be an adjacency list of the tree, either directed
 * or undirected.
 * Time: $O(N \log N + Q)$
 * Status: stress-tested
 */
#pragma once

//nodes are 1-based indexing
//initialize all parents to 0.

#define maxsz 200005
#define logmax 18

ll parent[maxsz];
ll level[maxsz];
ll memo[maxsz][logmax];

void preprocess(ll n)
{
	for(ll i = 0 ; i < logmax ; i ++)
	{
		for(ll j = 0 ; j <= n ; j ++)
		{
			if(i == 0) 
			{
				memo[j][i] = parent[j];
			}
			else{
				memo[j][i] = memo[memo[j][i-1]][i-1];
			}
		}
	}
}

int lca(ll  u , ll v)
{
	if(level[u] > level[v]) {
		swap(u , v);
	}		

	for(int i = logmax-1 ; i>=0 ; i--) {
		if(level[v] - (1ll << i) >= level[u])
		{
			v = memo[v][i];
		}
	}

	for(int i = logmax-1 ; i >= 0 ; i --)
	{
		if(memo[u][i] != memo[v][i])
		{
			u = memo[u][i];
			v = memo[v][i];
		}
	}
	
	if(u != v)
	{
		u = memo[u][0];
		v = memo[v][0];
	}
	return u;
}
