int rfib(int n);
// {
//   if (n < 2) {
//     return 1;
//   }
//
//   return rfib(n - 1) + rfib(n - 2);
// }

int mfib(int n);
// {
//   if (n < 2) {
//     return 1;
//   }
//
//   int* fib = malloc((n + 1) * sizeof(int));
//   fib[0] = 1;
//   fib[1] = 1;
//   for (int i = 2; i <= n; ++i) {
//     fib[i] = fib[i - 1] + fib[i - 2];
//   }
//
//   int result = fib[n];
//   free(fib);
//   return result;
// }
