/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: Basic math
 * Description:\\
\begin{minipage}{75mm}
Useful functions for geometry
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{content/geometry/lineDistance}
\end{minipage}
 * Status: tested
 */
#pragma once

#include "Point.h"
#include "Line.h"

bool inDisk(point a, point b, point p) {// check if p lies inside circle with Daimeter AB
   return dot(a-p, b-p) <= 0;  // accurate
}
bool onSegment(point a, point b, point p) { // check if P lies on AB
   return orient(a,b,p) == 0 && inDisk(a,b,p); // accurate
}


point properIntersection(point a, point b, point c, point d) { // precision
   // used to return the only single point of intersection btw AB and CD
   lld oa = orient(c,d,a),
   ob = orient(c,d,b),
   oc = orient(a,b,c),
   od = orient(a,b,d);
   // Proper intersection exists iff opposite signs
   if (oa*ob < 0 && oc*od < 0) { // accurate
      point ans = (a*ob - b*oa) / (ob-oa);
      return ans;
   }
   return point(-2e9, -2e9);
}
point intersectionLineSegment(point a, point b, point c, point d) {
   // finds any point of intersection between AB and CD
   // returns {-2e9, -2e9} if no point is found !!
   if (onSegment(c,d,a)) return a;
   if (onSegment(c,d,b)) return b;
   if (onSegment(a,b,c)) return c;
   if (onSegment(a,b,d)) return d;
   return properIntersection(a,b,c,d) ;
}


lld areaTriangle(point a, point b, point c) {
   return abs(cross(b-a, c-a)) / 2.0;
}
lld areaPolygon(vector<point> &p) { // Risky!! careful sums can overflow
   ll area = 0;
   for (int i = 0, n = p.size(); i < n; i++) {
      ll x = cross(p[i], p[(i+1)%n]); 
      area += x;
   }

   return abs((lld)area / 2.0);
}


bool above(point a, point p) { // accurate
   // true if P at least as high as A (blue part)
   return p.Y >= a.Y;
}
bool crossesRay(point a, point p, point q) { // accurate
   // check if [PQ] crosses ray from A
   // casts a ray towards right if points are in counter-clockwise
   // otherwise casts ray towards left
   return (above(a,q) - above(a,p)) * orient(a,p,q) > 0;
}
int inPolygon(vector<point> &p, point a) { // accurate
   // -1 if pt(a) -> inside polygon, 0 if lies on a side, 1 otherwise
   int numCrossings = 0;
   for (int i = 0, n = p.size(); i < n; i++) {
      if (onSegment(p[i], p[(i+1)%n], a))
         return 0;
      numCrossings += crossesRay(a, p[i], p[(i+1)%n]);
   }

   return (numCrossings & 1 ? -1 : 1); // inside if odd number of crossings
}

