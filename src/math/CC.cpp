#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>


using namespace std;
int flag = 1;
float inverse_p[100][100];
float inverse_zero[100][100];
float determinant(float [][100], float);
void cofactor(float [][100], float, int[], int[], int);
void transpose(float [][100], float [][100], float, int[], int[], int);
void fault (float [100][100], float [100][100], int, int[], int[], int);
FILE *fp4; 

int main()
{
  // Ler a matriz
  FILE *file1 = fopen("sus.txt", "r");
  FILE *file1_zero = fopen("sus_zero.txt", "r");
  FILE *file2 = fopen("coluna.txt", "r");
  FILE *file3 = fopen("linha.txt", "r");
  fp4 = fopen("matriz_imp.txt","w");
  ;

  float inverse[100][100];
 
  float matriz_sus[100];
  float matriz_sus_zero[100];

  float a_zero[100][100] = {{0}};
  float a[100][100] = {{0}};
  int vetor_coluna[100], vetor_linha[100];
  int  i, j, k, w, c, d, wi;

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
    if (!fscanf(file1_zero, "%f", &matriz_sus_zero[w]))
    break;
    if (!fscanf(file2, "%i", &vetor_coluna[w]))
    break;
    if (!fscanf(file3, "%i", &vetor_linha[w]))
    break;  
  }
  
  fclose(file1);
  fclose(file1_zero);
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
  for (w=0; w < ta; w++)
  {

    int linha = vetor_linha[w];
    int coluna = vetor_coluna[w];
    float sus = matriz_sus[w];
    float sus_zero = matriz_sus_zero[w];
    a[linha-1][coluna-1] = sus;
    a_zero[linha-1][coluna-1] = sus_zero;
  }
  
//    for (w=0; w < k; w++)
//  {
//    for (c=0; c < k; c++)
//  	{
//		printf("\t%f", a[w][c]);
//  	}
//  	printf("\n");
//  }

  d = determinant(a, k);
  if (d == 0)
  printf("\nSem matriz inversa\n");
  else
  {
  	if (flag == 1) {
	  	cofactor(a, k, vetor_linha, vetor_coluna, ta);  
  	}
  	if (flag == 0) {
	  	cofactor(a_zero, k, vetor_linha, vetor_coluna, ta);
  	}
  }
  

  fault(inverse_p, inverse_zero, k, vetor_linha, vetor_coluna, ta); 
}



/*For calculating Determinant of the Matrix */
float determinant(float a[100][100], float k)
{
  float s = 1, det = 0, b[100][100];
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

void cofactor(float num[100][100], float f, int lin[], int col[], int ta)
{
 float b[100][100], fac[100][100];
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
  transpose(num, fac, f, lin, col, ta);
}
/*Finding transpose of matrix*/
void transpose(float num[100][100], float fac[100][100], float r, int lin[], int col[], int ta)
{
  int i, j;
  float b[100][100], inverse[100][100], d;

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
    if (flag == 1){
    printf("Matriz de impedancia de seguencia positiva/negativa:\n");
    for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
        inverse_p[i][j] = inverse[i][j];
                printf("\t%f", inverse_p[i][j]);
                fprintf(fp4, "\t%f", inverse_p[i][j]);
        }
                printf("\n");
                fprintf(fp4, "\n");
    }
	fprintf(fp4, "\n\n");	
	}
	
	    if (flag == 0){
    for (i = 0;i < r; i++)
    {
     for (j = 0;j < r; j++)
       {
        inverse_zero[i][j] = inverse[i][j];
        }
    }	
	}
	
    flag = 0;
   
}

///*Finding the fault current and voltage*/
void fault(float imp[100][100], float imp_zero[100][100], int q, int lin[], int col[], int ta)
{
	FILE *fp1;
	FILE *fp2;
	FILE *fp3;
	FILE *file4 = fopen("entrada_falta.txt", "r");
	FILE *file5 = fopen("tensao.txt", "r");
	FILE *file6 = fopen("angulo.txt", "r");
	FILE *file7 = fopen("x_linha.txt", "r");
	FILE *file8 = fopen("x_linha_traf.txt", "r");
	FILE *file9 = fopen("sus_zero.txt", "r");
	FILE *file10 = fopen("tipo_traf.txt", "r");
	FILE *file11 = fopen("local_tipo_traf.txt", "r");
	int v, p, local, barra, linha1, linha2, tipo, porc_linha, tipo_trafo[10], local_tipo_trafo[10];
	float tensao[10], angulo[10], i_f, v_n[10], v_n_zero[10], v_n_n[10], v_n_g[10], v_n_zero_g[10],  i_l_n[10], i_l_zero[10], i_l_zero_g[10], i_l_g[10], i_l[10], a_n_g[10], a_n_zero[10], xlinha[100], xlinhatraf[100], res_ate, res_zero, dados_falta[7], sus_zero[100], i_f_n[10], i_f_zero[10], i_f_n2, i_f_zero2, i_f_g, i_f_g_zero, a_f_g;
	for(v = 0; v <= 8; v++)
  	{
    if (!fscanf(file4, "%f", &dados_falta[v]))
    break; 
	//printf("%f ", dados_falta[v]);
  	}

  	local = dados_falta[0];
  	barra = dados_falta[1];
  	linha1 = dados_falta[2];
  	linha2 = dados_falta[3];
  	porc_linha = dados_falta[4];
  	tipo = dados_falta[5];
  	res_ate = dados_falta[6];
  	res_zero = dados_falta[7];
  	
  	fp1 = fopen("corrente_falta.txt","w");
  	fp2 = fopen("tensao_pos_falta.txt","w");
  	fp3 = fopen("corrente_linha_falta.txt","w");
    //fprintf(fp, "%s %d", "Tim", 31);
    //fclose(fp);
  	
  	printf("\n");
  	printf("Tensao pre falta das barras:\n");
  	for(p = 0; p < q; p++)
  	{
    	if (!fscanf(file5, "%f", &tensao[p]))
    	break; 
    	if (!fscanf(file6, "%f", &angulo[p]))
    	break; 
    	if (!fscanf(file10, "%d", &tipo_trafo[p]))
    	break; 
    	if (!fscanf(file11, "%d", &local_tipo_trafo[p]))
    	break; 
    	printf("\t%d: %fL%f\n", p+1, tensao[p], angulo[p]);
  	}
  	printf("\nDados da falta:");
	if (local == 1) 									//Falta na barra
    {	
    	printf("\n\tFalta na barra %d", barra);
    	if (tipo == 3)							//Falta trifásica
    	{	
    		printf("\n\tTrifasica\n");
    		i_f = tensao[barra-1]/((imp[barra-1][barra-1])+res_ate);
    		fprintf(fp1, "%f,%f,%f", i_f,i_f,i_f);
    		printf("\nDados de saida:");
			printf("\n\tCorrente de falta: %f", i_f);
			printf("\n\tTensoes pos-falta:");
			for(p = 0; p < q; p++)
  			{
				v_n[p] = tensao[barra-1]*(1-imp[p][barra-1]/((imp[barra-1][barra-1])+res_ate));
				fprintf(fp2, "%d,%f %f, %f %f, %f %f\n", p+1, v_n[p], angulo[p],v_n[p], angulo[p]-120,v_n[p], angulo[p]+120);
				printf("\n\t\tBarra %d\n\t\t\tVa:%fL%f\n \t\t\tVb:%fL%f\n \t\t\tVc:%fL%f\n", p+1, v_n[p], angulo[p],v_n[p], angulo[p]-120,v_n[p], angulo[p]+120);	
  			} 	
		}
		
		else
    	{	
    		for (v = 0; v < q; v++)
  			{
  				if (barra == local_tipo_trafo[v])
  				tipo_trafo[barra] = tipo_trafo[v];
				if (!fscanf(file7, "%f", &xlinha[v]))
    			break;
			 	if (!fscanf(file8, "%f", &xlinhatraf[v]))
    			break;	  
			}
			if (tipo_trafo[0] == 1 && tipo_trafo[barra] == 1)							//Transformadores D-Y
    		{
  					for(p = 0; p < q; p++) 
    			{
    		    	for(v = 0; v < q; v++) 
    				{
    					imp_zero[p][v] = 0;
    				}
    			}
				  printf("\tTransformadores D-Y\n");
  				printf("\nMatriz de impedancia de seguencia zero:\n");
    			for(p = 0; p < q; p++) 
    			{
    		    	for(v = 0; v < q; v++) 
    				{
    					if (p == 0 && v == 0 || p == barra && v == barra)
						{
    						imp_zero[p][v] = 3*res_ate + xlinhatraf[p-v];	
    					}
    					else if (p == v && p < barra-1)
						{
    						imp_zero[p][v] = xlinhatraf[v-1] + xlinha[p-1];	
    					}
    					else if (p == v && p >= barra-1)
						{
    						imp_zero[p][v] = xlinhatraf[p] + xlinha[p] + res_zero;	
    					}
    					else if (p != v && (p != 0 && v != 0) && (p != barra && v != barra) && v > p)
						{
    						imp_zero[p][v] = xlinhatraf[v] + xlinha[v];
    					}
    					else if (p != v && (p != 0 && v != 0) && (p != barra && v != barra) && v < p)
						{
    						imp_zero[p][v] = xlinhatraf[p] + xlinha[p];
    					}
						printf("\t%f ", imp_zero[p][v]);
						fprintf(fp4, "\t%f", imp_zero[p][v]);
					}
					printf("\n");
					fprintf(fp4, "\n");	
				}
			}
			if (tipo_trafo[0] == 2 && tipo_trafo[barra] == 2)							//Transformadores Y-Y
    		{
    			printf("\n\tTrafo do Gerador Y-Y\n\tTrafo da falta Y-Y\n");
    			printf("\nMatriz de impedancia de seguencia zero:\n");
				for(p = 0; p < q; p++)
  				{
    				for (v = 0; v < q; v++)
  					{
	  					printf("\t%f", imp_zero[p][v]);
	  					fprintf(fp4, "\t%f", imp_zero[p][v]);
					}
					printf("\n");
					fprintf(fp4, "\n");
				}
			}
			if (tipo == 1)							//Falta monofásica
			{
				printf("\n\t Falta monofasica\n");
				i_f = 3*(tensao[barra-1]/(2*(imp[barra-1][barra-1])+imp_zero[barra-1][barra-1]));
    			fprintf(fp1, "%f", i_f,0, i_f,0, i_f,0);
				printf("\nDados de saida:");
				printf("\n\tCorrente de falta: %f (para as 3 fases)", i_f);
				printf("\n\tTensoes pos-falta:");
				for(p = 0; p < q; p++)
  				{
					v_n_zero[p] = -imp_zero[p][barra-1]*i_f/3;
					v_n[p] = tensao[barra-1]-imp[p][barra-1]*i_f/3;
					v_n_n[p] = -imp[p][barra-1]*i_f/3;
					//printf("\n\t\t%f  %f  %f", v_n_zero[p], v_n[p], v_n_n[p]);
					v_n_zero_g[p] = v_n_zero[p] + v_n[p] + v_n_n[p];
					//printf("\n\t\t%f", v_n_zero_g[p]);
					a_n_zero[p] = 0;
					a_n_g[p] = (180/3.14)*atan((-v_n_zero[p]+v_n[p]+v_n_n[p])/-(v_n_zero[p]+v_n[p]))+180;
					v_n_g[p] = sqrt ((v_n_zero[p]-(v_n[p]+v_n_n[p])/2)*(v_n_zero[p]-(v_n[p]+v_n_n[p])/2)+((-sqrt(3)/2)*(v_n[p]-v_n_n[p]))*((-sqrt(3)/2)*(v_n[p]-v_n_n[p])));
					printf("\n\t\tBarra %d\n\t\t\tVa:%fL%f\n \t\t\tVb:%fL%f\n \t\t\tVc:%fL%f\n", p+1, v_n_zero_g[p], a_n_zero[p], v_n_g[p], a_n_g[p], v_n_g[p], -a_n_g[p]);
					fprintf(fp2, "%d,%f %f, %f %f, %f %f\n", p+1, v_n_zero_g[p], a_n_zero[p], v_n_g[p], a_n_g[p], v_n_g[p], -a_n_g[p]);
  				} 
			}
			
			if (tipo == 2)							//Falta bifásica
			{
				if (res_ate == 0)					//Falta bifásica sem terra
				{
				printf("\n\t Falta bifasica sem terra\n");
				i_f = tensao[barra-1]/(2*imp[barra-1][barra-1]);
    			fprintf(fp1, "%f,%f,180,%f,0", 0, i_f*sqrt(3), -i_f*sqrt(3));
				printf("\nDados de saida:");
				printf("\n\tCorrente de falta: \n\t\tIfa %fL0\n\t\tIfb %fL180\n\t\tIfc %fL0", 0, i_f*sqrt(3), -i_f*sqrt(3));
				printf("\n\tTensoes pos-falta:");
				for(p = 0; p < q; p++)
  				{
					v_n_zero[p] = 0;
					v_n[p] = tensao[barra-1]-imp[barra-1][p]*i_f;
					v_n_n[p] = v_n[p];
					//printf("\n\t\t%f  %f  %f", v_n_zero[p], v_n[p], v_n_n[p]);
					v_n_zero_g[p] = v_n_zero[p] + v_n[p] + v_n_n[p];
					//printf("\n\t\t%f", v_n_zero_g[p]);
					a_n_zero[p] = 0;
					a_n_g[p] = 180;
					v_n_g[p] = sqrt ((v_n_zero[p]-(v_n[p]+v_n_n[p])/2)*(v_n_zero[p]-(v_n[p]+v_n_n[p])/2)+((-sqrt(3)/2)*(v_n[p]-v_n_n[p]))*((-sqrt(3)/2)*(v_n[p]-v_n_n[p])));
					printf("\n\t\tBarra %d\n\t\t\tVa:%fL%f\n \t\t\tVb:%fL%f\n \t\t\tVc:%fL%f\n", p+1, v_n_zero_g[p], a_n_zero[p], v_n_g[p], a_n_g[p], v_n_g[p], a_n_g[p]);
					fprintf(fp2, "%d,%f %f, %f %f, %f %f\n", p+1, v_n_zero_g[p], a_n_zero[p], v_n_g[p], a_n_g[p], v_n_g[p], a_n_g[p]);
  				}
				} 
				if (res_ate != 0) //Falta bifásica com terra
				{
					printf("\n\t Falta bifasica com terra");	
					i_f = tensao[barra-1]/(imp[barra-1][barra-1]+(imp[barra-1][barra-1]*imp_zero[barra-1][barra-1])/(imp[barra-1][barra-1]+imp_zero[barra-1][barra-1]));
					i_f_n2 = (-i_f*imp_zero[barra-1][barra-1])/(imp[barra-1][barra-1]+imp_zero[barra-1][barra-1]);
					i_f_zero2 = (-i_f*imp[barra-1][barra-1])/(imp[barra-1][barra-1]+imp_zero[barra-1][barra-1]);
					i_f_g_zero = i_f+i_f_n2+i_f_zero2;
					i_f_g = sqrt ((i_f_zero2-(i_f+i_f_n2)/2)*(i_f_zero2-(i_f+i_f_n2)/2)+((-sqrt(3)/2)*(i_f-i_f_n2))*((-sqrt(3)/2)*(i_f-i_f_n2)));
					a_f_g = (180/3.14)*atan((-sqrt(3)/2)*(i_f-i_f_n2)/(i_f_zero2-(i_f+i_f_n2)/2))+90;
					fprintf(fp1, "0,0,%f,%f,%f,%f", i_f_g,a_f_g,i_f_g,180-a_f_g);
					printf("\n\tCorrente de falta: \n\t\tIfa 0L0\n\t\tIfb %fL%f\n\t\tIfc %fL%f", i_f_g,a_f_g,i_f_g,180-a_f_g);
				}					
			}
			

		}	
	}
	
	if (local == 0) 									//Falta na linha
    {	
    	if (porc_linha == 1)
		{
			printf("\n\tFalta na linha %d-%d", linha1, linha2);
		}
		else {
			printf("\n\tFalta a %d por cento da linha %d-%d", porc_linha, linha1, linha2);
			
		}
		if (tipo == 3)							//Falta trifásica
    	{	
    		printf("\n\tTrifasica\n");
    		i_f = (tensao[linha1]-tensao[linha2])/((imp[linha1][linha2])+res_ate);
    		fprintf(fp1, "%f,%f,%f", i_f,i_f,i_f);
    		printf("\nDados de saida:");
			printf("\n\tCorrente de falta: %f A", i_f);
			printf("\n\tTensoes pos-falta:");
			for(p = 0; p < q; p++)
  			{
				v_n[p] = (tensao[linha1-1]-tensao[linha2-1])*(1-imp[p][linha1-1]/((imp[linha1-1][linha2-1])+res_ate));
				fprintf(fp2, "%d,%f %f, %f %f, %f %f\n", p+1, v_n[p], angulo[p],v_n[p], angulo[p]-120,v_n[p], angulo[p]+120);
				printf("\n\t\tBarra %d\n\t\t\tVa:%fL%f\n \t\t\tVb:%fL%f\n \t\t\tVc:%fL%f\n", p+1, v_n[p], angulo[p],v_n[p], angulo[p]-120,v_n[p], angulo[p]+120);	
  			} 	
		}
	}
		
	for(v = 0; v < (ta-q); v++)
  	{
    	if (!fscanf(file7, "%f", &xlinha[v]))
    	break; 
    	//printf("%f ", xlinha[v]);
  	}
  	
  	printf("\n\tCorrente de falta nas linhas:");
  	
	if (tipo == 1 || tipo == 2)
	{
		xlinha[q] = xlinha[q-2];
	for(p = 0; p < q; p++)
  	{
  		if (p == q-1){
		xlinha[p] = xlinha[p-2]+res_ate;
		}
		i_l[p] = (tensao[p]-v_n[p])/xlinha[p];
		//printf("\n\t%f-%f/%f-%f", tensao[p], v_n[p], xlinha[p], i_l[p]);
		i_l_n[p] = -v_n_n[p]/xlinha[p];
		//printf("\n\t%f/%f-%f", v_n_n[p], xlinha[p], i_l_n[p]);
		if (p == q-1){
			xlinha[p] = xlinha[p-1];
		}
		i_l_zero[p] = -v_n_zero[p]/xlinha[p];
		i_l_zero_g[p] = i_l_zero[p] + i_l[p] + i_l_n[p];
		a_n_zero[p] = 0;
		a_n_g[p] = (180/3.14)*atan((-i_l_zero[p]+i_l[p]+i_l_n[p])/-(i_l_zero[p]+i_l[p]))+180;	
		i_l_g[p] = sqrt((i_l_zero[p]-(i_l[p]+i_l_n[p])/2)*(i_l_zero[p]-(i_l[p]+i_l_n[p])/2)+((-sqrt(3)/2)*(i_l[p]-i_l_n[p]))*((-sqrt(3)/2)*(i_l[p]-i_l_n[p])));
		if (p != 0){
		printf("\n\t\tLinhas %d-%d\n\t\t\tIa:%f\n \t\t\tIb:%f\n \t\t\tIc:%f\n", p, p+1, i_l_zero_g[p], i_l_g[p], i_l_g[p]);
		fprintf(fp3, "%d-%d,%f %f, %f %f, %f %f\n", p, p+1, i_l_zero_g[p], i_l_g[p], i_l_g[p]);
	}
  	}
  	}
  	
  	if (tipo == 3)
	{
	int i = 0;
	for(p = 0; p < ta; p++)
  	{
  		if (lin[p] != col[p])
		{
			if (xlinha[i] > 0.0001 && xlinha[i] < 100)
			{
				i_l[p] = (v_n[lin[p]-1]-v_n[col[p]-1])/xlinha[i];
				fprintf(fp3,"%d,%d,%f\n",lin[p], col[p], i_l[p]);
				printf("\n\t\t%d-%d: %f",lin[p], col[p], i_l[p]); 
			}
			i++;
		}	
  	}
  	}

	   
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
}



