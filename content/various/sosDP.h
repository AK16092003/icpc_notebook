/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: http://codeforces.com/blog/entry/8219
 * Description: SOS DP
 * Time: O(N^2)
 */

#pragma once

const int LOG = 22;
//pull contribution from its subsets
void forward1(vl &dp){      
  for(int bit = 0; bit < LOG; bit++)
    for(int i = 0; i < MAXN; i++)
        if(i&(1<<bit)) dp[i] += dp[i^(1<<bit)];
}
void backward1(vl &dp){
  for(int bit = 0; bit < LOG; bit++)
    for(int i = MAXN-1; i >= 0; i--)
      if(i&(1<<bit)) dp[i] -= dp[i^(1<<bit)];
}
//pull contribution from its supersets
void forward2(vl &dp){      
  for(int bit = 0;bit < LOG;bit++)
    for(int i = MAXN-1; i >= 0; i--)
      if(i&(1<<bit)) dp[i^(1<<bit)] += dp[i];
}
void backward2(vl &dp){
  for(int bit = 0;bit < LOG;bit++)
    for(int i = 0; i < MAXN; i++)
      if(i&(1<<bit)) dp[i^(1<<bit)] -= dp[i];
}

