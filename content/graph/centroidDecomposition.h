/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Centroid Decomposition. 
 * Perform O(N) algorithms like DFS only on $is_removed = False$ 
 * Time: O(VlogV)
 * Status: Bruteforce-tested for N <= 5
 */
#pragma once

vector<int> adjlst[100005];
bool is_removed[100005];
int subtree_size[100005];

int get_subtree_size(int node, int parent = -1) {
	subtree_size[node] = 1;
	for (int child : adjlst[node]) {
		if (child == parent || is_removed[child]) { continue; }
		subtree_size[node] += get_subtree_size(child, node);
	}
	return subtree_size[node];
}

int get_centroid(int node, int tree_size, int parent = -1) {
	for (int child : adjlst[node]) {
		if (child == parent || is_removed[child]) { continue; }
		if (subtree_size[child] * 2 > tree_size) {
			return get_centroid(child, tree_size, node);
		}
	}
	return node;
}

void build_centroid_decomp(int node = 0) {
	int centroid = get_centroid(node, get_subtree_size(node));

	// calculate

	is_removed[centroid] = true;

	for (int child : adjlst[centroid]) {
		if (is_removed[child]) { continue; }
		build_centroid_decomp(child);
	}
}

