#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
      int i, N=10;

      for(i = 0; i<N; i++)
            printf("Random number = %i\n", rand()%100);

      return 0;
}
