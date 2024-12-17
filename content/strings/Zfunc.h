/**
 * Author: chilli
 * License: CC0
 * Description: z[i] computes the length of the longest common prefix of s[i:] and s,
 * except z[0] = 0. (abacaba -> 0010301)
 * Time: O(n)
 * Status: stress-tested
 */
#pragma once

template <typename T>
vector<int> z(const T &s, int n = 1){
  n = (int)s.size();
  vector<int> z(n);
  int L = 0, R = 0;
  for(int i = 1;i < n;i++){
    if(i < R) z[i] = min(R-i,z[i-L]);
    while(i + z[i] < n && s[z[i]] == s[i+z[i]]) z[i]++;
    if(i + z[i] > R){
      L = i;
      R = i+z[i];
    }
  }
  return z;
}
