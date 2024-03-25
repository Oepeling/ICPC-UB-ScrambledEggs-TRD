
/**
 * Author: Simon Lindholm
 * Description: Computes $a \times b$ modulo $mod$ when $a$ and $b$ are large.
 * Time: O(1)
 */
typedef long double ld;

long long mulsmart(long long a, long long b, long long mod) {
  ld guy = (ld)1 / (ld)mod * (ld)a * (ld)b;
  long long dif = (long long)a * (long long)b - (long long)guy * (long long)mod;
  if (dif >= mod) {
    dif -= mod;
  }
  if (dif < 0) {
    dif += mod;
  }
  return dif;
 
}