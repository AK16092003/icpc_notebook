/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Persistent SegmentTree with point updates and range queries, [L,R) 
 * Time: O(\log N).
 * Usage: node *head = build(arr , 0 , N);
 */
 
 // pass by ref in build function
ll f(ll x , ll y) {
	return (x + y);
}
struct node {
    node *l, *r;
    ll val;
    node(ll val) : l(nullptr), r(nullptr), val(val) {}
    node(node *l, node *r) : l(l), r(r), val(1ll) {
        if (l) val = f(val , l->val);
        if (r) val = f(val , r->val);
    }
};

// always considered in [lx, rx)
node* build(ll a[], ll lx, ll rx) {
    if (rx - lx == 1)
        return new node(a[lx]);
    ll m = (lx + rx) / 2;
    return new node(build(a, lx, m), build(a, m, rx));
}

ll range_calc(node* v, ll lx, ll rx, ll l, ll r) {
    if (r <= lx || rx <= l)
        return 1ll;
    if (l <= lx && rx <= r)
        return v->val;
    ll m = (lx + rx) / 2;
    return f(range_calc(v->l, lx, m, l, r) , range_calc(v->r, m, rx, l, r));
}

node* update(node* v, ll lx, ll rx, ll pos, ll new_val) {
    if (rx - lx == 1)
        return new node(new_val);
    ll m = (lx + rx) / 2;
    if (pos < m)
        return new node(update(v->l, lx, m, pos, new_val), v->r);
    else
        return new node(v->l, update(v->r, m, rx, pos, new_val));
}