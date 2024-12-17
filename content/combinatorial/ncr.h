/**
 * Author: Simon Lindholm
 * Date: 2018-07-06
 * License: CC0
 * Description: ncr, precomputation of factorials
 * Time: O(n)
 */
#pragma once

void factorial() {
	fact[0] = fact[1] = 1;
	ifact[0] = ifact[1] = 1;
	for(int i = 2 ; i < sz ; i ++)
		fact[i] = (fact[i-1]*i)%mod;	
	ifact[sz-1] = inv_mod(fact[sz-1]);
	for(int i = sz-2 ; i > 0 ; i --)
		ifact[i] = (ifact[i+1]*(i+1))%mod;
}
 
ll ncr(ll n , ll r) {
	if(n<r || r<0) return 0;
	if(r == 0) return 1;
	return (((fact[n]*ifact[n-r])%mod)*ifact[r])%mod;
}

