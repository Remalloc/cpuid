#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static inline void LM(int var, uint32_t *vx)
{
  for (int i = 0; i < 3; i++)
  {
    vx[i] = var >> i;
  }
}

void _GetCPUID(char *cpuid, size_t size)
{
#define _CPUID(in, a, b, c, d) __asm__("cpuid"                              \
                                       : "=a"(a), "=b"(b), "=c"(c), "=d"(d) \
                                       : "a"(in));
  unsigned int veax;
  unsigned int vebx;
  unsigned int vecx;
  unsigned int vedx;

  uint32_t ax[3], cx[3], dx[3];
  _CPUID(1, veax, vebx, vecx, vedx);
  LM(veax, ax);
  _CPUID(3, veax, vebx, vecx, vedx);
  LM(vecx, cx);
  LM(vedx, dx);
  snprintf(cpuid, size, "%u%u%u%u%u%u%u%u%u", ax[0], ax[1], ax[2], cx[0], cx[1], cx[2], dx[0], dx[1], dx[2]);
}

char *GetCPUID()
{
  size_t size = 128;
  char *cpuid = (char *)malloc(size * sizeof(char));
  _GetCPUID(cpuid, size);
  return cpuid;
}

int main()
{
  printf("%s\n", GetCPUID());
  return 0;
}
