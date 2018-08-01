#include <stdio.h> //Biblioteca para usar recursos de entrada e sa�da de dados
#include <math.h>  //Biblioteca para usar opera��es trigonom�tricas e exponenciais
//#include <stdlib.h> //Biblioteca para usar ferramenta de aloca��o de mem�ria (malloc, free)
#include <iostream> //Biblioteca para usar recursos de escrita e leitura de dados
#include <fstream> //Biblioteca para usar recursos de escrita e leitura de dados
#include <string> //Biblioteca para operar vetores


using namespace std; //Delara��o da estrutura para diferenciar quando usa uma "string" ou uma "estrutura de string"
int flag = 1; //Bandeira para identificar se a matriz de imped�ncia positiva/negativa j� foi calculada
float inverse_p[100][100]; //Declara o tamanho m�ximo da matriz inversa positiva/negativa
float inverse_zero[100][100]; //Declara o tamanho m�ximo da matriz inversa zero
float determinant(float [][100], float); //Declara a fun��o que ir� calcular o determinante, suas entradas e retorno
void cofactor(float [][100], float, int[], int[], int); //Declara a fun��o que ir� calcular o cofator, suas entradas e retorno
void transpose(float [][100], float [][100], float, int[], int[], int); //Declara a fun��o que ir� calcular a matriz transposta, suas entradas e retorno
void fault (float [100][100], float [100][100], int, int[], int[], int); //Declara a fun��o que ir� calcular os dados de falta, suas entradas e retorno
FILE *fp4; //Declara o ponteiro para o arquivo que guarda os elementos das matrizes de segu�ncia

int main() //
{
  // Ler a matriz
  FILE *file1 = fopen("sus.txt", "r"); //Abre o arquivo com os elementos da matriz de suscept�ncia diferentes de zero, vindo do FP
  FILE *file1_zero = fopen("sus_zero.txt", "r"); //Abre o arquivo com os elementos da matriz de suscept�ncia de segu�ncia zero, diferentes de zero, vindo do FP
  FILE *file2 = fopen("coluna.txt", "r"); //Abre o arquivo com o �ndice das colunas que cujos par�metros s�o diferentes de zero, vindo do FP
  FILE *file3 = fopen("linha.txt", "r"); //Abre o arquivo com o �ndice das linhas que cujos par�metros s�o diferentes de zero, vindo do FP
  fp4 = fopen("matriz_imp.txt","w"); //Abre o arquivo da matriz de imped�ncia para preenchimento

  float inverse[100][100]; //Declara o tamanho m�ximo da matriz inversa 
 
  float matriz_sus[100]; //Declara o tamanho m�ximo do vetor de elementos da matriz inversa positiva/negativa
  float matriz_sus_zero[100]; //Declara o tamanho m�ximo do vetor de elementos da matriz inversa zero

  float a_zero[100][100] = {{0}}; //Declara a vari�vel que ir� receber os dados da matriz de suscept�ncia zero que ir� para a fun��o Determinante
  float a[100][100] = {{0}}; //Declara a vari�vel que ir� receber os dados da matriz de suscept�ncia que ir� para a fun��o Determinante
  int vetor_coluna[100], vetor_linha[100]; //Declara a vari�vel que ir� receber os dados da posi��o, coluna e linha, dos elementos das matriz que s�o diferentes de zero
  int  i, j, k, w, c, d, wi; //Vari�veis contadoras e tamanho da matriz (k)

  //Encontra o numero de elementos do vetor
  ifstream in("linha.txt"); //Confere se o arquivo linha.txt possui elementos
  string t; //Declara a var�avel que guardar� os elementos de linha.txt
  while (in) { //La�o que ir� varrer o arquivo linha.txt
    t.push_back(in.get()); //Guarda os elementos de linha.txt em t
  }
  in.close(); 
  int ta = (t.size()/2); //Guarda em ta a quantidade de elementos de t
  //printf("Quantidade de elementos no vetor:%i\n", ta);
  for(w = 0; w < ta; w++) //La�o que varre os arquivos de posi��o e elementos das matrizes de suscept�ncia
  {
    if (!fscanf(file1, "%f", &matriz_sus[w])) //Guarda em matriz_sus os elementos do file 1
    break;
    if (!fscanf(file1_zero, "%f", &matriz_sus_zero[w])) //Guarda em matriz_sus_zero os elementos do file 1_zero
    break;
    if (!fscanf(file2, "%i", &vetor_coluna[w])) //Guarda em vetor_coluna os elementos do file 2
    break;
    if (!fscanf(file3, "%i", &vetor_linha[w])) //Guarda em vetor_linha os elementos do file 3
    break;  
  }
  //Fecha os arquivos lidos
  fclose(file1); 
  fclose(file1_zero); 
  fclose(file2); 
  fclose(file3);
  
  //Encontra o tamanho da matriz
  for(w = 0; w < ta; w++) 
  {
	 if ( vetor_linha[w] > k ) 
	 	k = vetor_linha[w];    //Guarda o tamanho da matriz em k	
  }
  
  //printf("Matriz de ordem:%i\n", k);
  //Monta a matriz de admitancia

// int count_linha = 0;
  for (w=0; w < ta; w++) //
  {

    int linha = vetor_linha[w]; //Guarda o posi��o da linha do elemento n�o zero em uma vari�vel auxiliar
    int coluna = vetor_coluna[w]; //Guarda o posi��o da coluna do elemento n�o zero em uma vari�vel auxiliar
    float sus = matriz_sus[w]; //Guarda o elemento n�o zero em uma vari�vel auxiliar
    float sus_zero = matriz_sus_zero[w]; //Guarda o elemento n�o zero, da matriz zero, em uma vari�vel auxiliar
    a[linha-1][coluna-1] = sus; //Preenche o elemento da matriz de suscept�ncia positivo/negativa
    a_zero[linha-1][coluna-1] = sus_zero; //Preenche o elemento da matriz de suscept�ncia zero
  }
  
//    for (w=0; w < k; w++)
//  {
//    for (c=0; c < k; c++)
//  	{
//		printf("\t%f", a[w][c]);
//  	}
//  	printf("\n");
//  }

  d = determinant(a, k); //Chama a fun��o Determinante, com o tamanho da matriz e amtriz de suscept�ncia
  if (d == 0) //Condi��o onde o determinante � zero e em consegu�ncia n�o h� matriz inversa
  printf("\nSem matriz inversa\n");
  else ////Condi��o onde o determinante n�o � zero, h� matriz inversa
  {
  	if (flag == 1) { //Condi��o onde a matriz de admit�ncia positiva/negativa ainda n�o foi calculada
	  	cofactor(a, k, vetor_linha, vetor_coluna, ta); //Chama a fun��o que calcula o cofator da matriz de suscept�ncia  
  	}
  	if (flag == 0) { //Condi��o onde a matriz de admit�ncia zero ainda n�o foi calculada
	  	cofactor(a_zero, k, vetor_linha, vetor_coluna, ta); //Chama a fun��o que calcula o cofator da matriz de suscept�ncia zero
  	}
  }
  

  fault(inverse_p, inverse_zero, k, vetor_linha, vetor_coluna, ta); //Chama a fun��o que calcula as vari�veis de falta
}



//Fun��o que calcula o determinante da matriz de suscept�ncia
float determinant(float a[100][100], float k) 
{
  float s = 1, det = 0, b[100][100]; //vari�veis auxiliares de matriz
  int i, j, m, n, c; //vari�veis auxiliares de contagem
  if (k == 1) //Condi��o de matriz de um elemento
    {
     return (a[0][0]); //Neste caso o �nico elemento � o pr�prio elemento
    }
  else //condi��o com mais de um elemento
    {
     det = 0; //Declara que o valor inicial do determinante � zero
     for (c = 0; c < k; c++) //La�o que varre a matriz de suscept�ncia 
       {
        m = 0; //Zera as vari�veis auxiliares
        n = 0; 
        for (i = 0;i < k; i++) //Varre as linhas da matriz
          {
            for (j = 0 ;j < k; j++) //Varre as colunas da matriz
              {
                b[i][j] = 0; //Zera o elemento da matriz na respectiva posi��o
                if (i != 0 && j != c) //Intera��o onde se obtem a matriz menor complementar
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
          det = det + s * (a[0][c] * determinant(b, k - 1)); //Atualiza na vari�vel o resultado do cofator com a do determinate da matriz menor complementar
          
          s = -1 * s; //Para o pr�ximo cofator a contribui��o � negativa
          }
    }

    return (det); //Retorna o valor calculado do determinante
}

//Fun��o que calcula o cofator da matriz de imped�ncia
void cofactor(float num[100][100], float f, int lin[], int col[], int ta) 
{
 float b[100][100], fac[100][100]; //vari�veis auxiliares de matriz
 int p, q, m, n, i, j; //vari�veis auxiliares de contagem
 for (q = 0;q < f; q++) ///La�o que varre as linhas matriz de suscept�ncia
 {
   for (p = 0;p < f; p++) ///La�o que varre as colunas matriz de suscept�ncia
    {
     m = 0; 
     n = 0; 
     for (i = 0;i < f; i++) 
     {
       for (j = 0;j < f; j++) 
        {
          if (i != q && j != p) //Condi��o das vari�veis fora da diagonal principal
          {
            b[m][n] = num[i][j]; //Faz a transposi��o da matriz
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
      fac[q][p] = pow(-1, q + p) * determinant(b, f - 1); //Monta a matriz de cofatores 
    }
  }
  transpose(num, fac, f, lin, col, ta); //Chama a fun��o que transpo�m a matriz
}

//Fun��o que calcula a matriz de imped�ncia
void transpose(float num[100][100], float fac[100][100], float r, int lin[], int col[], int ta) //
{
  int i, j; ////vari�veis auxiliares de contagem
  float b[100][100], inverse[100][100], d; ////vari�veis auxiliares de matriz

  for (i = 0;i < r; i++) //Varre os elementos pelas linhas da matriz
    {
     for (j = 0;j < r; j++) //Varre os elementos pelas colunas da matriz
       {
         b[i][j] = fac[j][i]; //Faz a transposi��o da matriz
        }
    }
  d = determinant(num, r); //Chama a fun��o do determinante
  for (i = 0;i < r; i++) //Varre a matriz pelas linhas
    {
     for (j = 0;j < r; j++) //Varre a matriz pelas colunas
       {
        inverse[i][j] = b[i][j] / d; //Obtem os elementos da inversa dividindo o elemento do cofator transposto pelo determinante
        }
    }
    if (flag == 1){ //Condi��o da matriz ser de segu�ncia positiva/negativa
    printf("Matriz de impedancia de seguencia positiva/negativa:\n"); //
    for (i = 0;i < r; i++) //Varre as linhas da matriz
    {
     for (j = 0;j < r; j++) //Varre as colunas da matriz
       {
        inverse_p[i][j] = inverse[i][j]; //Guarda na matriz de segu�ncia a inversa
                printf("\t%f", inverse_p[i][j]); 
                fprintf(fp4, "\t%f", inverse_p[i][j]); 
        }
                printf("\n");
                fprintf(fp4, "\n");
    }
	fprintf(fp4, "\n\n");	 
	}
	
	    if (flag == 0){ //Condi��o da matriz ser de segu�ncia positiva/negativa
    for (i = 0;i < r; i++) //Varre as linhas da matriz
    {
     for (j = 0;j < r; j++) //Varre as colunas da matriz
       {
        inverse_zero[i][j] = inverse[i][j]; ////Guarda na matriz de segu�ncia a inversa
        }
    }	
	}
	
    flag = 0; //Se o c�lculo da matriz inversa de segu�ncia positiva/negativa j� estiver sido feito, faz-se o zero 
   
}

//Fun��o que encontra as vari�veis do curto circuito (Corrente de curto, tens�o p�s falta nas barra e corrente p�s falta nas linhas)
void fault(float imp[100][100], float imp_zero[100][100], int q, int lin[], int col[], int ta) 
{
	//Declara o ponteiro para o arquivo que guarda a carrente de falta, tens�o p�s falta das barras e a corrente p�s falta das linhas
	FILE *fp1; 
	FILE *fp2;  
	FILE *fp3; 
	//Abre os arquivos de dados da falta, componentes da linha e sa�da do FP
	FILE *file4 = fopen("entrada_falta.txt", "r"); 
	FILE *file5 = fopen("tensao.txt", "r"); 
	FILE *file6 = fopen("angulo.txt", "r"); 
	FILE *file7 = fopen("x_linha.txt", "r"); 
	FILE *file8 = fopen("x_linha_traf.txt", "r"); 
	FILE *file9 = fopen("sus_zero.txt", "r"); 
	FILE *file10 = fopen("tipo_traf.txt", "r"); 
	FILE *file11 = fopen("local_tipo_traf.txt", "r"); 
	//Vari�veis auxiliares
	int v, p, local, barra, linha1, linha2, tipo, porc_linha, tipo_trafo[10], local_tipo_trafo[10]; 
	float tensao[10], angulo[10], i_f, v_n[10], v_n_zero[10], v_n_n[10], v_n_g[10], v_n_zero_g[10],  i_l_n[10], i_l_zero[10];  
	float i_l_zero_g[10], i_l_g[10], i_l[10], a_n_g[10], a_n_zero[10], xlinha[100], xlinhatraf[100], res_ate, res_zero, dados_falta[7];  
	float sus_zero[100], i_f_n[10], i_f_zero[10], i_f_n2, i_f_zero2, i_f_g, i_f_g_zero, a_f_g; 
	//Leitura da entrada de falta
	for(v = 0; v <= 8; v++) 
  	{
    if (!fscanf(file4, "%f", &dados_falta[v])) 
    break; 
	//printf("%f ", dados_falta[v]);
  	}
	//Aloca��o dos dados da falta lidos em var�aveis
  	local = dados_falta[0]; 
  	barra = dados_falta[1]; 
  	linha1 = dados_falta[2]; 
  	linha2 = dados_falta[3]; 
  	porc_linha = dados_falta[4]; 
  	tipo = dados_falta[5]; 
  	res_ate = dados_falta[6]; 
  	res_zero = dados_falta[7]; 
  	//Abre os arquivos de sa�da para preenchimento
  	fp1 = fopen("corrente_falta.txt","w"); 
  	fp2 = fopen("tensao_pos_falta.txt","w"); 
  	fp3 = fopen("corrente_linha_falta.txt","w"); 
    //fprintf(fp, "%s %d", "Tim", 31);
    //fclose(fp);
  	
  	printf("\n"); 
  	printf("Tensao pre falta das barras:\n"); 
  	//Aloca��o dos dados de sa�da do FP e das linhas lidos em var�aveis 
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
	if (local == 1) 							//Condi��o de falta na barra
    {	
    	printf("\n\tFalta na barra %d\n", barra);
    	if (tipo == 3)							//Condi��o de falta trif�sica
    	{	
    		printf("\n\tTrifasica\n");
    		i_f = tensao[barra-1]/((imp[barra-1][barra-1])+res_ate); //Obten��o da corrente de falta trif�sica
    		fprintf(fp1, "%f,90,%f,90,%f,90", i_f,i_f,i_f);
    		printf("\nDados de saida:");
			printf("\n\tCorrente de falta: %f", i_f);
			printf("\n\tTensoes pos-falta:");
			for(p = 0; p < q; p++) //
  			{
				v_n[p] = tensao[barra-1]*(1-imp[p][barra-1]/((imp[barra-1][barra-1])+res_ate)); //Obten��o da tens�o p�s falta trif�sica das barras
				fprintf(fp2, "%d,%f,%f, %f,%f, %f,%f\n", p+1, v_n[p], angulo[p],v_n[p], angulo[p]-120,v_n[p], angulo[p]+120); //
				printf("\n\t\tBarra %d\n\t\t\tVa:%fL%f\n \t\t\tVb:%fL%f\n \t\t\tVc:%fL%f\n", p+1, v_n[p], angulo[p],v_n[p], angulo[p]-120,v_n[p], angulo[p]+120);	
  			} 	
		}
		
		else //Condi��o de faltas assim�tricas
    	{	
    		for (v = 0; v < q; v++) //Varre o arquivo para obter o tipo de transformadores nas linhas
  			{
  				if (barra == local_tipo_trafo[v]) 
  				tipo_trafo[barra] = tipo_trafo[v]; 
				if (!fscanf(file7, "%f", &xlinha[v])) 
    			break;
			 	if (!fscanf(file8, "%f", &xlinhatraf[v])) 
    			break;	  
			}
			if (tipo_trafo[0] == 1 && tipo_trafo[barra] == 1)		//Transformadores D-Y
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
    			for(p = 0; p < q; p++)  //Obtem a matriz de segu�ncia zero para um sistema formado por transformadores D-Y
    			{
    		    	for(v = 0; v < q; v++) 
    				{
    					if (p == 0 && v == 0 || p == barra-1 && v == barra-1)
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
    			printf("\tTransformadores Y-Y\n");
    			printf("\nMatriz de impedancia de seguencia zero:\n");
				for(p = 0; p < q; p++) //Obtem a matriz de segu�ncia zero para um sistema formado por transformadores Y-Y
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
			if (tipo == 1)							//Condi��o de falta monof�sica
			{
				printf("\n\t Falta monofasica\n");
				i_f = 3*(tensao[barra-1]/(2*(imp[barra-1][barra-1])+imp_zero[barra-1][barra-1])); //Obten��o da corrente de falta monof�sica
    			fprintf(fp1, "%f", i_f,90, i_f,90, i_f,90);
				printf("\nDados de saida:");
				printf("\n\tCorrente de falta: %f (para as 3 fases)", i_f);
				printf("\n\tTensoes pos-falta:");
				for(p = 0; p < q; p++) //
  				{
					v_n_zero[p] = -imp_zero[p][barra-1]*i_f/3; 
					v_n[p] = tensao[barra-1]-imp[p][barra-1]*i_f/3; 
					v_n_n[p] = -imp[p][barra-1]*i_f/3; 
					//printf("\n\t\t%f  %f  %f", v_n_zero[p], v_n[p], v_n_n[p]);
					v_n_zero_g[p] = v_n_zero[p] + v_n[p] + v_n_n[p]; //Obten��o da tens�o p�s falta monof�sica de segu�ncia zero
					//printf("\n\t\t%f", v_n_zero_g[p]);
					a_n_zero[p] = 0; //Obten��o do �ngulo da tens�o p�s falta monof�sica de segu�ncia zero
					a_n_g[p] = (180/3.14)*atan((-v_n_zero[p]+v_n[p]+v_n_n[p])/-(v_n_zero[p]+v_n[p]))+180; //Obten��o do �ngulo da tens�o p�s falta monof�sica de segu�ncia positivo
					v_n_g[p] = sqrt ((v_n_zero[p]-(v_n[p]+v_n_n[p])/2)*(v_n_zero[p]-(v_n[p]+v_n_n[p])/2)+((-sqrt(3)/2)*(v_n[p]-v_n_n[p]))*((-sqrt(3)/2)*(v_n[p]-v_n_n[p]))); //Obten��o da tens�o p�s falta monof�sica de segu�ncia positivo
					printf("\n\t\tBarra %d\n\t\t\tVa:%fL%f\n \t\t\tVb:%fL%f\n \t\t\tVc:%fL%f\n", p+1, v_n_zero_g[p], a_n_zero[p], v_n_g[p], a_n_g[p], v_n_g[p], -a_n_g[p]); 
					fprintf(fp2, "%d,%f,%f, %f,%f, %f,%f\n", p+1, v_n_zero_g[p], a_n_zero[p], v_n_g[p], a_n_g[p], v_n_g[p], -a_n_g[p]); //
  				} 
			}
			
			if (tipo == 2)							//Falta bif�sica sem terra
			{
				printf("\n\tFalta bifasica sem terra\n");
				i_f = tensao[barra-1]/(2*imp[barra-1][barra-1]); //Obten��o da corrente de falta
    			fprintf(fp1, "%f,%f,180,%f,0", 0, i_f*sqrt(3), -i_f*sqrt(3));
				printf("\nDados de saida:");
				printf("\n\tCorrente de falta: \n\t\tIfa %fL0\n\t\tIfb %fL180\n\t\tIfc %fL0", 0, i_f*sqrt(3), -i_f*sqrt(3));
				printf("\n\tTensoes pos-falta:");
				for(p = 0; p < q; p++) //
  				{
					v_n_zero[p] = 0; 
					v_n[p] = tensao[barra-1]-imp[barra-1][p]*i_f; 
					v_n_n[p] = v_n[p]; //
					//printf("\n\t\t%f  %f  %f", v_n_zero[p], v_n[p], v_n_n[p]);
					v_n_zero_g[p] = v_n_zero[p] + v_n[p] + v_n_n[p]; //Obten��o da tens�o p�s falta bif�sica sem terra de segu�ncia zero
					//printf("\n\t\t%f", v_n_zero_g[p]);
					a_n_zero[p] = 0; 
					a_n_g[p] = 180; 
					v_n_g[p] = sqrt ((v_n_zero[p]-(v_n[p]+v_n_n[p])/2)*(v_n_zero[p]-(v_n[p]+v_n_n[p])/2)+((-sqrt(3)/2)*(v_n[p]-v_n_n[p]))*((-sqrt(3)/2)*(v_n[p]-v_n_n[p]))); //Obten��o da tens�o p�s falta bif�sica sem terra de segu�ncia positivo
					printf("\n\t\tBarra %d\n\t\t\tVa:%fL%f\n \t\t\tVb:%fL%f\n \t\t\tVc:%fL%f\n", p+1, v_n_zero_g[p], a_n_zero[p], v_n_g[p], a_n_g[p], v_n_g[p], a_n_g[p]);
					fprintf(fp2, "%d,%f,%f, %f,%f, %f,%f\n", p+1, v_n_zero_g[p], a_n_zero[p], v_n_g[p], a_n_g[p], v_n_g[p], a_n_g[p]);
  				}
			}
				if (tipo == 4)					 //Falta bif�sica com terra
				{
					printf("\n\tFalta bifasica com terra");	
					i_f = tensao[barra-1]/(-imp[barra-1][barra-1]+(-imp[barra-1][barra-1]*imp_zero[barra-1][barra-1])/(-imp[barra-1][barra-1]+imp_zero[barra-1][barra-1])); //Obten��o da corrente de falta bif�sica com terra
					//printf("\n%f/(%f + (%f*%f/%f+%f))", tensao[barra-1], -imp[barra-1][barra-1], -imp[barra-1][barra-1], imp_zero[barra-1][barra-1], -imp[barra-1][barra-1], imp_zero[barra-1][barra-1]);
					i_f_n2 = -i_f*imp_zero[barra-1][barra-1]/(imp[barra-1][barra-1]-imp_zero[barra-1][barra-1]); 
					i_f_zero2 = i_f*imp[barra-1][barra-1]/(imp[barra-1][barra-1]-imp_zero[barra-1][barra-1]); 
					//printf("\n1-%f		2-%f		0-%f\n", i_f, i_f_n2, i_f_zero2);
					i_f_g_zero = i_f+i_f_n2+i_f_zero2; //Obten��o da corrente de falta de segu�ncia zero
					i_f_g = sqrt ((i_f_zero2-(i_f-i_f_n2)/2)*(i_f_zero2-(i_f-i_f_n2)/2)+((-sqrt(3)/2)*(i_f+i_f_n2))*((-sqrt(3)/2)*(i_f+i_f_n2))); //Obten��o da corrente de falta de segu�ncia positiva
					//a_f_g = (180/3.14)*atan((-sqrt(3)/2)*(i_f-i_f_n2)/(i_f_zero2-(i_f+i_f_n2)/2))+90;
					a_f_g = 90+(180/3.14)*atan((((i_f+i_f_n2)/2)/sqrt(3)/2)*(i_f-i_f_n2)); //Obten��o do �ngulo da corrente de falta de segu�ncia positiva
					fprintf(fp1, "0,0,%f,%f,%f,%f", i_f_g,a_f_g,i_f_g,180-a_f_g); 
					printf("\n\tCorrente de falta: \n\t\tIfa 0L0\n\t\tIfb %fL%f\n\t\tIfc %fL%f", i_f_g,a_f_g,i_f_g,180-a_f_g);
					printf("\n\tTensoes pos-falta:");
					for(p = 0; p < q; p++) //
  					{
						v_n_zero[p] = -i_f_zero2*imp_zero[p][barra-1]; 
						v_n[p] = tensao[barra-1]+imp[p][barra-1]*i_f; 
						//printf("\n\t\t%f = %f - %f*%f", v_n[p], tensao[barra-1], imp[p][barra-1], i_f);
						v_n_n[p] = -imp[p][barra-1]*i_f_n2 ; 
						//printf("\n\t\t%f  %f  %f", v_n_zero[p], v_n[p], v_n_n[p]);						
						v_n_zero_g[p] = v_n_zero[p]+sqrt(((v_n[p]+v_n_n[p])*sqrt(3)/2)*((v_n[p]+v_n_n[p])*sqrt(3)/2)+(0.5*(v_n[p]-v_n_n[p]))*(0.5*(v_n[p]-v_n_n[p]))); //Obten��o da tens�o p�s falta bif�sica com terra de segu�ncia zero
						a_n_zero[p] = 90-(180/3.14)*atan(sqrt(3)*(v_n[p]+v_n_n[p])/(v_n[p]-v_n_n[p])); //Obten��o do �ngulo da tens�o p�s falta bif�sica com terra de segu�ncia zero
						//printf("\n\t\t%f", a_n_zero[p]);
						v_n_g[p] = sqrt ((v_n_zero[p]-(v_n[p]+v_n_n[p])/2)*(v_n_zero[p]-(v_n[p]+v_n_n[p])/2)+((-sqrt(3)/2)*(v_n[p]-v_n_n[p]))*((-sqrt(3)/2)*(v_n[p]-v_n_n[p]))); //Obten��o da tens�o p�s falta bif�sica com terra de segu�ncia positivo
						//printf("\n\t\t%f", v_n_g[p]);
						a_n_g[p] = 60+(180/3.14)*atan((v_n_zero[p]-(v_n[p]+v_n_n[p])/2)/((-sqrt(3)/2)*(v_n[p]-v_n_n[p]))); //Obten��o do �ngulo da tens�o p�s falta bif�sica com terra de segu�ncia positiva
						//printf("\n\t\t%f", a_n_g[p]);
						printf("\n\t\tBarra %d\n\t\t\tVa:%fL%f\n \t\t\tVb:%fL%f\n \t\t\tVc:%fL%f\n", p+1, v_n_zero_g[p], a_n_zero[p], v_n_g[p], a_n_g[p], v_n_g[p], a_n_g[p]+60);
						fprintf(fp2, "%d,%f,%f, %f,%f, %f,%f\n", p+1, v_n_zero_g[p], a_n_zero[p], v_n_g[p], a_n_g[p], v_n_g[p], a_n_g[p]+60);
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
		if (tipo == 3)							//Falta trif�sica
    	{	
    		printf("\n\tTrifasica\n");
    		i_f = (tensao[linha2])/((imp[linha1][linha2])+res_ate); //Obten��o da corrente de falta trif�sica na linha
    		fprintf(fp1, "%f,90,%f,90,%f,90", i_f,i_f,i_f);
    		printf("\nDados de saida:");
			printf("\n\tCorrente de falta: %f A", i_f);
			printf("\n\tTensoes pos-falta:");
			for(p = 0; p < q; p++) //
  			{
				v_n[p] = (tensao[linha2-1])*(1-imp[p][linha1-1]/((imp[linha1-1][linha2-1])+res_ate)); //Obten��o da tens�o p�s falta nas barras por falta trif�sica na linha
				fprintf(fp2, "%d,%f,%f, %f,%f, %f,%f\n", p+1, v_n[p], angulo[p],v_n[p], angulo[p]-120,v_n[p], angulo[p]+120); 
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
  	
	if (tipo != 3) //Condi��o para faltas assim�tricas
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
		i_l_zero_g[p] = i_l_zero[p] + i_l[p] + i_l_n[p]; //Obten��o da corrente p�s falta nas linhas de segu�ncia zero
		a_n_zero[p] = 0; 
		a_n_g[p] = (180/3.14)*atan((-i_l_zero[p]+i_l[p]+i_l_n[p])/-(i_l_zero[p]+i_l[p]))+180; 	
		i_l_g[p] = sqrt((i_l_zero[p]-(i_l[p]+i_l_n[p])/2)*(i_l_zero[p]-(i_l[p]+i_l_n[p])/2)+((-sqrt(3)/2)*(i_l[p]-i_l_n[p]))*((-sqrt(3)/2)*(i_l[p]-i_l_n[p]))); //Obten��o da corrente p�s falta nas linhas de segu�ncia postiva
		if (p != 0){ 
		printf("\n\t\tLinhas %d-%d\n\t\t\tIa:%f\n \t\t\tIb:%f\n \t\t\tIc:%f\n", p, p+1, i_l_zero_g[p], i_l_g[p], i_l_g[p]);
		fprintf(fp3, "%d-%d,%f,%f, %f,%f, %f,%f\n", p, p+1, i_l_zero_g[p], i_l_g[p], i_l_g[p]);
	}
  	}
  	}
  	
  	if (tipo == 3) //Condi��o para faltas sim�tricas
	{
	int i = 0;
	for(p = 0; p < ta; p++)
  	{
  		if (lin[p] != col[p])
		{
			if (xlinha[i] > 0.0001 && xlinha[i] < 100) 
			{
				i_l[p] = (v_n[lin[p]-1]-v_n[col[p]-1])/xlinha[i]; //Obten��o da corrente p�s falta nas linhas
				fprintf(fp3,"%d,%d,%f\n",lin[p], col[p], i_l[p]); 
				printf("\n\t\t%d-%d: %f",lin[p], col[p], i_l[p]);  
			}
			i++;
		}	
  	}
  	}

	//Fecha os arquivos de sa[ida de dados do curto circuito   
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
}



