/**
 * Author: Simon Lindholm
 * License: CC0
 * Source: http://codeforces.com/blog/entry/8219
 * Description: character trie
 * Time: O(|S|)
 */

#pragma once

struct Trie {
  static const int ALPHA = 26;    // Number of alphabets
  static const char c = 'a';      // Starting alphabet
  struct node {
    node* child[ALPHA];
    int start, stop;
    node() {
      for (int i = 0; i < ALPHA; i++) child[i] = NULL;
      start = stop = 0;
    }
  } *root;

  Trie() {
    root = new node();
  }
  void insert(string s) {          // Insert string into trie
    node* cur = root;
    for (int i = 0; i < sz(s); i++) {
      if (!cur->child[s[i] - c]) cur->child[s[i] - c] = new node();
      cur->start++;
      cur = cur->child[s[i] - c];
    }
    cur->start++;
    cur->stop++;
  }
  bool search(string s) {          // Search if a string is present or not
    node* cur = root;
    for (int i = 0; i < sz(s); i++) {
      if (!cur->child[s[i] - c]) return false;
      cur = cur->child[s[i] - c];
    }
    return cur->stop;
  }
  int count(string s) {            // Count how many words have prefix=s
    node* cur = root;
    for (int i = 0; i < sz(s); i++) {
      if (!cur->child[s[i] - c]) return 0;
      cur = cur->child[s[i] - c];
    }
    return cur->start;
  }
  void del(string s) {             // Delete a word from trie
    if (!search(s)) return;
    node* cur = root;
    for (int i = 0; i < sz(s); i++) {
      cur->start--;
      cur = cur->child[s[i] - c];
    }
    cur->start--;
    cur->stop--;
  }
};
