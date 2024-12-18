/**
 * Author: Johan Sannemo
 * Date: 2016-12-15
 * License: CC0
 * Description: 
 * calcpow() preprocessing powers
 * calchash() preprocess hash for a string
 * hashval(l,r) compute hash for a substring
 * Time: O(n)
 * Status: Tested on kattis:stringmatching
 */
#pragma once

pll p = {31,53};
ll mod = 1e9+7;
pll powerval[SZ];

void calcpow()
{
	powerval[0] = {1,1};
	for(int i = 1 ; i < SZ ; i ++)
	{
		powerval[i].first = (p.first*powerval[i-1].first)%mod;
		powerval[i].second = (p.second*powerval[i-1].second)%mod;
	}
}

vpll calchash(string &s)
{
	int n = s.length();
	vpll hash_array(n);
	for(int i = 0 ; i < n ; i ++) hash_array[i] = {0,0};
	hash_array[0] = {(s[0] - 'a' + 1) , (s[0] - 'a' + 1)};
	for(int i = 1 ; i < n ; i ++)
	{
		hash_array[i].first = ((p.first*hash_array[i-1].first) + (s[i] - 'a' + 1))%mod;
		hash_array[i].second = ((p.second*hash_array[i-1].second) + (s[i] - 'a' + 1))%mod;
	}
	return hash_array;
}

pll hashval(ll l , ll r , vpll &hash_array)
{
	ll len = r - l + 1;
	int n = hash_array.size();
	if(len <= 0 || l < 0 || r >= n || r<l) return {0,0};
	pll ans = hash_array[r];
	if(l >= 1)
	{
		ans.first -= (hash_array[l-1].first*powerval[len].first)%mod;
		ans.second -= (hash_array[l-1].second*powerval[len].second)%mod;
	}
	if(ans.first<0) ans.first += mod;
	if(ans.second<0) ans.second += mod;
	return ans;
}

