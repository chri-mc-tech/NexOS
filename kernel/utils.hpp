inline const char* int_to_string(int n) {
  static char buf[12];
  char* p = buf + 11;
  bool neg = n < 0;

  *p = '\0';

  do {
    *--p = '0' + (neg ? -(n % 10) : n % 10);
    n /= 10;
  } while (n);

  if (neg)
    *--p = '-';

  return p;
}