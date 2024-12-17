/**
 * Author: Simon Lindholm
 * Date: 2018-07-06
 * License: CC0
 * Description: A Power B 
 * Time: O(log(n))
 */
#pragma once

ll mod = 1e9 + 7;
int sz = 1000005;
ll fact[1000005];
ll ifact[1000005];
 
ll power(ll x, ll n) {
    if(n==0) return 1;
    x = x%mod;
    if(x==0) return 0; 
    ll pow = 1;
    while (n) {
        if (n & 1) pow = (pow*x)%mod;
        n = n >> 1;
        x = (x*x)%mod;
    }
    return pow;
}
 
ll inv_mod(ll x) { return power(x , mod - 2)%mod; }

