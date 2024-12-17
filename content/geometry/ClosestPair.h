/**
 * Author: Simon Lindholm
 * Date: 2019-04-17
 * License: CC0
 * Source: https://codeforces.com/blog/entry/58747
 * Description: Finds the closest pair of points.
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

ll ClosestPairDist(vector<point> &p, ll l, ll r){ // accurate
   // returns the square of the two closest points in range [l, r]
   if(l >= r) return 8e18 ;
   ll mid = (l + r) / 2 ;

   ll DisL = ClosestPairDist(p, l, mid);
   ll DisR = ClosestPairDist(p, mid + 1, r);

   ll allowD = min(DisL, DisR);

   vector<point> candidates ;
   for(auto i = l; i <= r; i ++){
      point v = p[i];
      ll d = v.X - p[mid].X;
      if(d * d <= allowD) candidates.push_back(v);
   }

   sort(all(candidates), [&](point x, point y){
      return x.Y != y.Y ? x.Y < y.Y : x.X < y.X ;
   });


   for(ll i = 0 ; i < sz(candidates); i ++){ // this won'b be n^2
      for(ll j = i + 1; j < sz(candidates) ; j ++){ 
         ll dx = candidates[i].X - candidates[j].X ;
         ll dy = candidates[i].Y - candidates[j].Y ;

         if(dy * dy >= allowD) break; // this limits to maximum 7 iterations
         allowD = min(allowD, dx * dx + dy * dy);
      }
   }

   return allowD;
}
ll ClosestPairDist(vector<point> &a){
   // returns the square of the two closest points
   sort(all(a), [&](point x, point y){
      return x.X == y.X ? x.Y < y.Y : x.X < y.X ;
   });

   return ClosestPairDist(a, 0, a.size() - 1) ;
}
