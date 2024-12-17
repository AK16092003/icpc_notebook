/**
 * Author: Stjepan Glavina, chilli
 * Date: 2019-05-05
 * License: Unlicense
 * Source: https://github.com/stjepang/snippets/blob/master/convex_hull.cpp
 * Description:
\\\begin{minipage}{75mm}
Returns a vector of the points of the convex hull in counter-clockwise order.
Points on the edge of the hull between two other points are not considered part of the hull.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{content/geometry/ConvexHull}
\vspace{-6mm}
\end{minipage}
 * Time: O(n \log n)
 * Status: stress-tested, tested with kattis:convexhull
*/
#pragma once

#include "Point.h"

vector<point> ConvexHull(vector<point> &p){ // accurate
   // returns the convex Hull of some set of points
   ll n = p.size();
   if(n <= 2) return p ;

   vector<point> up, down; // stores ans for top and bottom HULLS
   vector<point> active ; // acts as stack
   map<pll, ll> vis ; // helps avoid taking duplicates

   sort(all(p), [&](point x, point y){
      return x.X != y.X ? x.X < y.X : x.Y < y.Y ;
   });

   active.push_back(p[0]);
   active.push_back(p[1]);

   for(ll i = 2; i < n; i ++){
      while(active.size() > 1 and cross(active[active.size() - 1] - active[active.size() - 2], p[i] - active[active.size() - 2]) > 0){
         active.pop_back();
      }
      active.push_back(p[i]);
   }

   up = active ;
   active.clear();

   for(auto i: up) vis[{i.X, i.Y}] = 1 ;

   active.push_back(up[up.size() - 2]);
   active.push_back(up.back());

   for(ll i = n - 2; i > -1; i --){
      while(active.size() > 1 and cross(active[active.size() - 1] - active[active.size() - 2], p[i] - active[active.size() - 2]) > 0){
         active.pop_back();
      }
      active.push_back(p[i]);
   }

   down = active ;

   for(auto i: down) {
      if(not vis[{i.X, i.Y}]) up.push_back(i);
   }
   return up;
}

