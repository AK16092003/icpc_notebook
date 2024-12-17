/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: Basic math
 * Description:\\
\begin{minipage}{75mm}
Line Algorithms
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineDistance}
\end{minipage}
 * Status: tested
 */
#pragma once

#include "Point.h"

struct line {
   point v; lld c;
   // From direction vector v and offset cons
   line(point dir, lld cons) { v = (dir), c = (cons); } 
   // From equation ax+by=cons (prefer not to use this due to bidirectional problems)
   // we don't know if direction is (-b, a) or (b, -a) so avoid using this if possible
   line(lld a, lld b, lld cons) { v = point({-b, a}), c= (cons) ;}
   // From points P and Q  -> line PQ
   line(point p, point q) { v = (q-p), c = (cross(v,p)) ;}
   
   lld side(point p){ // accurate
      return cross(v, p) - c ;
   }

   lld distLinePoint(point p) { // precision
      return abs(side(p)) / abs(v);
   }

   void LineSort(vector<point> &a){ // sort points along the line
      sort(a.begin(), a.end(), [&](point x, point y){
         return dot(v, x) < dot(v, y);
      }); // accurate
   }
}; 

