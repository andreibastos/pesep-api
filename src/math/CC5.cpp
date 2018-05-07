#include<stdio.h>
#include<math.h>


float determinant(float [][25], float);
void cofactor(float [][25], float);
void transpose(float [][25], float [][25], float);
//void printMatrix(float [][25], float);

int main()
{
  // Ler a matriz
  float a[25][25], k, d;
  int i, j;
  k = 4;
  FILE *file = fopen("matriz.txt", "r");
  printf("\nMatriz lida: \n");
  for (i = 0;i < k; i++)
    {
     for (j = 0;j < k; j++)
       {
        if (!fscanf(file, "%f", &a[i][j]))
           break;
           printf("\t%f", a[i][j]);
        }
        printf("\n");
    }
   fclose(file);
//   printMatrix(a,k);

  d = determinant(a, k);
  if (d == 0)
   printf("\nSem matriz inversa\n");
  else
   cofactor(a, k);
}

//void printMatrix(float a, float n){
//    int j, i;
//   for (i=0;i<n;i++) {
//      for (j=0;j<n;j++) {
//        printf("%f ",a[i][j]);
//      }
//      printf("\n");
//   }
//   printf("\n");
//}

/*For calculating Determinant of the Matrix */
float determinant(float a[25][25], float k)
{
  float s = 1, det = 0, b[25][25];
  int i, j, m, n, c;
  if (k == 1)
    {
     return (a[0][0]);
    }
  else
    {
     det = 0;
     for (c = 0; c < k; c++)
       {
        m = 0;
        n = 0;
        for (i = 0;i < k; i++)
          {
            for (j = 0 ;j < k; j++)
              {
                b[i][j] = 0;
                if (i != 0 && j != c)
                 {
                   b[m][n] = a[i][j];
                   if (n < (k - 2))
                    n++;
                   else
                    {
                     n = 0;
                     m++;
                     }
                   }
               }
             }
          det = det + s * (a[0][c] * determinant(b, k - 1));
          s = -1 * s;
          }
    }

    return (det);
}

void cofactor(float num[25][25], float f)
{
 float b[25][25], fac[25][25];
 int p, q, m, n, i, j;
 for (q = 0;q < f; q++)
 {
   for (p = 0;p < f; p++)
    {
     m = 0;
     n = 0;
     for (i = 0;i < f; i++)
     {
       for (j = 0;j < f; j++)
        {
          if (i != q && j != p)
          {
            b[m][n] = num[i][j];
            if (n < (f - 2))
             n++;
            else
             {
               n = 0;
               m++;
               }
            }
        }
      }
      fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
    }
  }
  transpose(num, fac, f);
}
/*Finding transpose of matrix*/
void transpose(float num[25][25], float fac[25][25], float r)
{
  int i, j;
  float b[25][25], inverse[25][25], d;

  for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
         b[i][j] = fac[j][i];
        }
    }
  d = determinant(num, r);
  for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
        inverse[i][j] = b[i][j] / d;
        }
    }
   printf("\n\n\nInverso da matriz: \n");

   for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
         printf("\t%f", inverse[i][j]);
        }
    printf("\n");
     }
}
