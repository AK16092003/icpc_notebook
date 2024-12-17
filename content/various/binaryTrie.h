/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: http://codeforces.com/blog/entry/8219
 * Description: binary trie
 * Time: O(|S|)
 */

#pragma once

struct BinTrie {
  static const int B = 31; // change if LL
  struct node {
    node *nxt[2];
    int sz;
    node() {
      nxt[0] = nxt[1] = NULL;
      sz = 0;
    }
  } *root;
  BinTrie() {
    root = new node();
  }
  void insert(int val) {
    node *cur = root;
    cur->sz++;
    for (int i = B - 1; i >= 0; i--) {
      int b = val >> i & 1;
      if (cur->nxt[b] == NULL)
        cur->nxt[b] = new node();
      cur = cur->nxt[b];
      cur->sz++;
    }
  }
  bool search(int val) {
    node *cur = root;
    for (int i = B - 1; i >= 0; i--) {
      int b = val >> i & 1;
      if (cur->nxt[b] == NULL) return false;
      cur = cur->nxt[b];
    }
    return true;
  }
  int query(int x, int k) { // number of values s.t. val ^ x < k
    node *cur = root;
    int ans = 0;
    for (int i = B - 1; i >= 0; i--) {
      if (cur == NULL) break;
      int b1 = x >> i & 1, b2 = k >> i & 1;
      if (b2 == 1) {
        if (cur->nxt[b1])
          ans += cur->nxt[b1]->sz;
        cur = cur->nxt[!b1];
      } else cur = cur->nxt[b1];
    }
    return ans;
  }
  int get_max(int x) { // returns maximum of val ^ x
    node *cur = root;
    int ans = 0;
    for (int i = B - 1; i >= 0; i--) {
      int k = x >> i & 1;
      if (cur->nxt[!k]) cur = cur->nxt[!k], ans <<= 1, ans++;
      else cur = cur->nxt[k], ans <<= 1;
    }
    return ans;
  }
  int get_min(int x) { // returns minimum of val ^ x
    node *cur = root;
    int ans = 0;
    for (int i = B - 1; i >= 0; i--) {
      int k = x >> i & 1;
      if (cur->nxt[k]) cur = cur->nxt[k], ans <<= 1;
      else cur = cur->nxt[!k], ans <<= 1, ans++;
    }
    return ans;
  }
  void del(int val) {
    if (!search(val)) return;
    node *cur = root;
    cur->sz--;
    for (int i = B - 1; i >= 0; i--) {
      int b = val >> i & 1;
      if (cur->nxt[b] == NULL) return;
      else if (cur->nxt[b]->sz == 1) {
        cur->nxt[b] = NULL;
        return;
      }
      cur = cur->nxt[b];
      cur->sz--;
    }
  }
};
