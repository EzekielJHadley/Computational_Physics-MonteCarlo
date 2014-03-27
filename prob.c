#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
      //number of particles
      int N=1000, time, T=250000;
      int P[N][3];
      int i, j, k, l;
      int ni, pNum, step, nOld;
      double Et, Eold, Enew, dE;
      double KT = 10;
      double B = 1.0/KT;
      double prob;

      FILE *file;
      FILE *fileP;
      file = fopen("energy", "wt");
      fileP = fopen("particle", "wt");
      
      //inicialize the particles to have nx=ny=nz=1
      for(i=0; i<N; i++)
      {
            for(j=0; j<3; j++)
            {
                  P[i][j] = 1;
            }
      }
      
      //start the energy off at the ground state
      Et = pow(3.14159,2)/2.0*3*N;
      Eold = Et;
      Enew = Et;
      
      //seed the random number generator
      srand(999);

      i=0;
      j=0;
      k=0;
      l=0;

      //no begin steping through the particles
      for(time = 0; time < T; time++)
      {
            //chose a random particle
            pNum = rand()%N;
            //choose a random coordinate
            ni = rand()%3;
            //does it increase or decrease
            step = rand()%2;
            if(step == 0)
                  step = -1;

            //set up the change in energy and then step the n value
            dE = pow(3.14159,2)/2.0*(1 + 2*P[pNum][ni]*step);
            nOld = P[pNum][ni];
            P[pNum][ni] += step;
             
            if(P[pNum][ni] < 1)
            {
                  P[pNum][ni] = nOld;
                  dE = 0.0;
            }

            Enew = Eold + dE;
            
            /*if(dE <= 0)
            {
                  l++;
                  Eold = Enew;
            }else if(dE > 0)
            {
                  prob = exp(-B*dE)*100;
                  if(rand()%100 <= prob)
                  {
                        l++;
                        Eold = Enew;
                  }else
                  {     
                        l++;
                        P[pNum][ni] = nOld;
                        dE = 0;
                        Enew = Eold;
                  }
             }*/
             if(dE > 0)
             {
                  prob = exp(-B*dE)*100;
                  if(rand()%100 > prob)
                  {
                        P[pNum][ni] = nOld;
                        dE = 0;
                  }
             }

             Et += dE;

             fprintf(file, "%i       %f\n", time, Et);

      }
      //printf("decrease = %i \nincrease = %i \nexit = %i \ntottal = %i \n T = %i\n", i, j, k, (i+j+k), l);
      //printf("what is the difference? = %i\n", (l - (i+j+k)));
      for(i=0; i<N; i++)
      {
             fprintf(fileP, "%i %i,%i,%i\n", i, P[i][0], P[i][1], P[i][2]);
      }
      return 0;
}
