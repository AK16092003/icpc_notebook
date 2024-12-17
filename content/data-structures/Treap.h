/**
 * Author: someone on Codeforces
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 * Time: $O(\log N)$
 * Status: stress-tested
 */
#pragma once

struct Treap{
  int data, priority, subtreeSize;
  long long sum;
  bool rev;
  Treap *left, *right;
  Treap(int d);
};
int size(Treap *t){
  return t ? t->subtreeSize : 0;
}
long long getSum(Treap *t){
  return t ? t->sum : 0;
}
void pull(Treap *t){
  if(!t) return;
  t->subtreeSize = 1 + size(t->left) + size(t->right);
  t->sum = t->data + getSum(t->left) + getSum(t->right);
}
Treap::Treap(int d){
  this->data = d;
  priority = rand(0, INT_MAX);
  subtreeSize = 1;
  sum = d;
  rev = false;
  left = right = NULL;
  pull(this);
}
void push(Treap *t){
  if(!t) return;
  if(t->rev){
    swap(t->left, t->right);
    if(t->left) t->left->rev ^= 1;
    if(t->right) t->right->rev ^= 1;
    t->rev = 0;
  }
  pull(t);
}
pair<Treap*, Treap*> split(Treap *t, int k){
  if(!t) return {NULL, NULL};
  push(t);
  if(size(t->left) >= k){
    auto [lTreap, rTreap] = split(t->left, k);
    t->left = rTreap;
    pull(t);
    return {lTreap, t};
  } else {
    k = k - size(t->left) - 1;
    auto [lTreap, rTreap] = split(t->right, k);
    t->right = lTreap;
    pull(t);
    return {t, rTreap};
  }
  return {NULL, NULL};
}
Treap* merge(Treap *l, Treap *r){
  if(!l) return r;
  if(!r) return l;
  push(l);push(r);
  if(l->priority < r->priority){
    l->right = merge(l->right, r);
    pull(l);
    return l;
  }
  else{
    r->left = merge(l, r->left);
    pull(r);
    return r;
  }
}

