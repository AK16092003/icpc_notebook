/**
 * Author: User adamant on CodeForces
 * Source: http://codeforces.com/blog/entry/12143
 * Description: For each position in a string, computes p[0][i] = half length of
 *  longest even palindrome around pos i, p[1][i] = longest odd (half rounded down).
 * Time: O(N)
 * Status: Stress-tested
 */
#pragma once

// Returns {even, odd} each value denotes how much left/right u can go from this point

array<vi, 2> manacher(const string& s) {
	int n = sz(s);
	array<vi,2> p = {vi(n+1), vi(n)};
	rep(z,0,2) for (int i=0,l=0,r=0; i < n; i++) {
		int t = r-i+!z;
		if (i<r) p[z][i] = min(t, p[z][l+t]);
		int L = i-p[z][i], R = i+p[z][i]-!z;
		while (L>=1 && R+1<n && s[L-1] == s[R+1])
			p[z][i]++, L--, R++;
		if (R>r) l=L, r=R;
	}
	return p;
}

pii getLongestPal(const array<vi, 2> &p){
  int idx = 0, len = 1;
  for(int i = 0;i<sz(p[1]);i++){
    if(2*p[0][i] > len) len = 2*p[0][i], idx = i - p[0][i];
    if(2*p[1][i] + 1 > len) len = 2*p[1][i] + 1, idx = i - p[1][i];
  }
  return {idx, len};
}
bool isPal(int l, int r,const array<vi, 2> &p){
  int len = r-l+1;
  return p[len%2][l+len/2] >= len/2;
}
