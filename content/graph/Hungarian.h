/**
 * Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: $O(N^3)$ Task assignment minimum cost
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */
#pragma once

vector<ll> u (n+1), v (m+1), p (m+1), way (m+1);
for (ll i=1; i<=n; ++i) {
    p[0] = i;
    ll j0 = 0;
    vector<ll> minv (m+1, inf);
    vector<bool> used (m+1, false);
    do {
        used[j0] = true;
        ll i0 = p[j0],  delta = inf,  j1;
        for (ll j=1; j<=m; ++j)
            if (!used[j]) {
                ll cur = A[i0][j]-u[i0]-v[j];
                if (cur < minv[j])
                    minv[j] = cur,  way[j] = j0;
                if (minv[j] < delta)
                    delta = minv[j],  j1 = j;
            }
        for (ll j=0; j<=m; ++j)
            if (used[j])
                u[p[j]] += delta,  v[j] -= delta;
            else
                minv[j] -= delta;
        j0 = j1;
    } while (p[j0] != 0);
    do {
        ll j1 = way[j0];
        p[j0] = p[j1];
        j0 = j1;
    } while (j0);
}

ll cost = -v[0];
vector<ll> ans (n+1);
for (ll j=1; j<=m; ++j)
    ans[p[j]] = j;
