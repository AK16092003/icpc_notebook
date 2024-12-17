/**
 * Author: Johan Sannemo
 * Date: 2016-12-15
 * License: CC0
 * Description: pi[x] computes the length of the longest prefix of s that ends at x,
 * other than s[0...x] itself (abacaba -> 0010123).
 * Can be used to find all occurrences of a string.
 * Time: O(n)
 * Status: Tested on kattis:stringmatching
 */
#pragma once


template <typename T>
vector<int> lps(const T &s, int n = 1){
  n = (int)s.size();
  vector<int> lps(n);
  int j = 0;
  for(int i = 1;i < n;i++){
    while(j > 0 && s[i] != s[j]) j = lps[j-1];
    if(s[i] == s[j]) j++;
    lps[i] = j;
  }
  return lps;
}

template <typename T>
vector<int> kmp(const T &s, const T &p){
  int n = (int)s.size(), m = (int)p.size();
  vector<int> lps = lps(p);
  vector<int> ans;
  int j = 0;
  for(int i = 0;i < n;i++){
    while(j > 0 && s[i] != p[j]) j = lps[j-1];
    if(s[i] == p[j]) j++;
    if(j == m){
      ans.push_back(i-j+1);
      j = lps[j-1];
    }
  }
  return ans;
}


// Prefix Automation

vector<int> prefix_function(string s) {
 int n = (int)s.length();
 vector<int> pi(n);
 for (int i = 1; i < n; i++) {
  int j = pi[i-1];
  while (j > 0 && s[i] != s[j])
   j = pi[j-1];
  if (s[i] == s[j])
   j++;
  pi[i] = j;
 }
 return pi;
}


void compute_automaton(string s, vector<vector<int>>& aut) {
 s += '#';
 int n = s.size();
 vector<int> pi = prefix_function(s);
 aut.assign(n, vector<int>(26));
 for (int i = 0; i < n; i++) {
  for (int c = 0; c < 26; c++) {
   if (i > 0 && 'a' + c != s[i])
    aut[i][c] = aut[pi[i-1]][c];
   else
    aut[i][c] = i + ('a' + c == s[i]);
  }
 }
}

// search fn for automaton
int search(string& arr,string& pattern) {
    
    vector<vector<int>> aut;
    compute_automaton(pattern,aut);
    int cnt = 0;
    int m = (int)pattern.size();
    int n = (int)arr.size();
    pattern += "#";
  
    int j = 0,i = 0;
    for(int i = 0 ; i < n ; i ++) {
        j = aut[j][arr[i] - 'a'];
        if(j == m) cnt++;
    }    
    return cnt;    
}
