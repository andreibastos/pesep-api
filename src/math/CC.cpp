#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

float determinant(float [][25], float);
void cofactor(float [][25], float);
void transpose(float [][25], float [][25], float);
void fault (float [25][25], int);

int main()
{
  // Ler a matriz
  FILE *file1 = fopen("sus.txt", "r");
  FILE *file2 = fopen("coluna.txt", "r");
  FILE *file3 = fopen("linha.txt", "r");
 
  float matriz_sus[25];
  float a[25][25] = {{0}} ;
  int vetor_coluna[25], vetor_linha[25];
  int  i, j, k, w, c, d;

  //Encontra o numero de elementos do vetor
  ifstream in("linha.txt");
  string t;
  while (in) {
    t.push_back(in.get());
  }
  in.close();
  int ta = (t.size()/2);
  //printf("Quantidade de elementos no vetor:%i\n", ta);
  for(w = 0; w < ta; w++)
  {
    if (!fscanf(file1, "%f", &matriz_sus[w]))
    break;
    if (!fscanf(file2, "%i", &vetor_coluna[w]))
    break;
    if (!fscanf(file3, "%i", &vetor_linha[w]))
    break;  
  }
  
  fclose(file1);
  fclose(file2);
  fclose(file3);
  
  //Encontra o tamanho da matriz
  for(w = 0; w < ta; w++)
  {
	 if ( vetor_linha[w] > k )
	 	k = vetor_linha[w];   	
  }
  
  //printf("Matriz de ordem:%i\n", k);
  //Monta a matriz de admitancia

// int count_linha = 0;
  for (w=0; w < ta; w++){

    int linha = vetor_linha[w];
    int coluna = vetor_coluna[w];
    float sus = matriz_sus[w];

//    printf("%d ", w);
//    printf("%d ", coluna);
//    printf("%d ", linha);
//    printf("%f ", sus);
//    printf("\n");

    a[linha-1][coluna-1] = sus;
  }


//  for(i = 0; i<k;i++){
//      for(j = 0; j<k;j++){
//        printf("%f\t", a[i][j]);
//      }
//    printf("\n");
//  }


  d = determinant(a, k);
  if (d == 0)
  printf("\nSem matriz inversa\n");
  else
  cofactor(a, k);
}



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
    
   printf("\n\n\nMatriz de impedancia: \n");
   for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
         printf("\t%f", inverse[i][j]);
        }
    printf("\n");
     }
     
    fault(inverse, r);
}

/*Finding the fault current and voltage*/
void fault(float imp[25][25], int q)
{
	FILE *file4 = fopen("entrada_falta.txt", "r");
	FILE *file5 = fopen("tensao.txt", "r");
	FILE *file6 = fopen("angulo.txt", "r");
	int v, p, dados_falta[7], local, barra, linha1, linha2, porc_linha, tipo, res_ate;
	float tensao[5], angulo[5], i_f, v_n[5];
	for(v = 0; v < 7; v++)
  	{
    if (!fscanf(file4, "%d", &dados_falta[v]))
    break; 
    	//printf("%d ", dados_falta[v]);
  	}
  	local = dados_falta[0];
  	barra = dados_falta[1];
  	linha1 = dados_falta[2];
  	linha2 = dados_falta[3];
  	porc_linha = dados_falta[4];
  	tipo = dados_falta[5];
  	res_ate = dados_falta[6];
  	
  	printf("\n");
  	printf("Tensao de cada barra:\n");
  	for(p = 0; p < q; p++)
  	{
    	if (!fscanf(file5, "%f", &tensao[p]))
    	break; 
    	if (!fscanf(file6, "%f", &angulo[p]))
    	break; 
    	printf("\t%fL%f\n", tensao[p], angulo[p]);
  	}
  	printf("\nDados da falta:");
	if (local == 1) 									//Falta na barra
    {	
    	printf("\n\tFalta na barra %d", dados_falta[1]);
	}
	if (tipo == 1)							//Falta trifásica
    {	
    	printf("\n\tTrifasica\n");
    	i_f = tensao[dados_falta[1]-1]/((imp[barra-1][barra-1])+res_ate);
    	printf("\nDados de saida:");
		printf("\n\tCorrente de falta: %f A", i_f);
		printf("\n\tTensoes pos-falta:");
		for(p = 0; p < q; p++)
  		{
			v_n[p] = tensao[barra-1-1]*(1-imp[p][barra-1-1]/((imp[barra-1-1][barra-1-1])+res_ate));
			printf("\n\t\tBarra %d\n\t\t\tVa:%fL%f V\n \t\t\tVb:%fL%f V\n \t\t\tVc:%fL%f V\n", p+1, v_n[p], angulo[p],v_n[p], angulo[p]-120,v_n[p], angulo[p]+120);	
  		} 
	}
}



