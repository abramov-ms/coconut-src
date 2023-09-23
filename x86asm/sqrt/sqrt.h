double sse_sqrt(double x, double eps);
// {
//   double hi = x;
//   double lo = 0;
//   while (hi != lo) {
//      double mid = (hi + lo) / 2;
//      if (x < mid * mid) {
//         lo = mid;
//      } else {
//         hi = mid;
//      }
//   }
//
//    return hi;
// }
