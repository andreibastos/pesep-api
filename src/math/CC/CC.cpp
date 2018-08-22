#include <stdio.h> //Biblioteca para usar recursos de entrada e saï¿½da de dados
#include <math.h>  //Biblioteca para usar operaï¿½ï¿½es trigonomï¿½tricas e exponenciais
//#include <stdlib.h> //Biblioteca para usar ferramenta de alocaï¿½ï¿½o de memï¿½ria (malloc, free)
#include <iostream> //Biblioteca para usar recursos de escrita e leitura de dados
#include <fstream> //Biblioteca para usar recursos de escrita e leitura de dados
#include <string> //Biblioteca para operar vetores


using namespace std; //Delaraï¿½ï¿½o da estrutura para diferenciar quando usa uma "string" ou uma "estrutura de string"
int flag = 1; //Bandeira para identificar se a matriz de impedï¿½ncia positiva/negativa jï¿½ foi calculada
float inverse_p[100][100]; //Declara o tamanho mï¿½ximo da matriz inversa positiva/negativa
float inverse_zero[100][100]; //Declara o tamanho mï¿½ximo da matriz inversa zero
float determinant(float [][100], float); //Declara a funï¿½ï¿½o que irï¿½ calcular o determinante, suas entradas e retorno
void cofactor(float [][100], float, int[], int[], int); //Declara a funï¿½ï¿½o que irï¿½ calcular o cofator, suas entradas e retorno
void transpose(float [][100], float [][100], float, int[], int[], int); //Declara a funï¿½ï¿½o que irï¿½ calcular a matriz transposta, suas entradas e retorno
void fault (float [100][100], float [100][100], int, int[], int[], int); //Declara a funï¿½ï¿½o que irï¿½ calcular os dados de falta, suas entradas e retorno
FILE *fp4; //Declara o ponteiro para o arquivo que guarda os elementos das matrizes de seguï¿½ncia
FILE *fp5; //Declara o ponteiro para o arquivo que guarda os elementos das matriz de susceptância
FILE *fp6; //Declara o ponteiro para o arquivo que guarda os elementos das matriz de susceptância

int main() //
{
  // Ler a matriz
  FILE *file1 = fopen("sus.txt", "r"); //Abre o arquivo com os elementos da matriz de susceptï¿½ncia diferentes de zero, vindo do FP
  FILE *file1_zero = fopen("sus_zero.txt", "r"); //Abre o arquivo com os elementos da matriz de susceptï¿½ncia de seguï¿½ncia zero, diferentes de zero, vindo do FP
  FILE *file2 = fopen("coluna.txt", "r"); //Abre o arquivo com o ï¿½ndice das colunas que cujos parï¿½metros sï¿½o diferentes de zero, vindo do FP
  FILE *file3 = fopen("linha.txt", "r"); //Abre o arquivo com o ï¿½ndice das linhas que cujos parï¿½metros sï¿½o diferentes de zero, vindo do FP
  fp4 = fopen("matriz_imp.txt","w"); //Abre o arquivo da matriz de impedï¿½ncia positiva/negativa para preenchimento
  fp5 = fopen("matriz_sus.txt","w"); //Abre o arquivo da matriz de susceptância para preenchimento
  fp6 = fopen("matriz_imp_zero.txt","w"); //Abre o arquivo da matriz de impedï¿½ncia zero para preenchimento

  float inverse[100][100]; //Declara o tamanho mï¿½ximo da matriz inversa 
 
  float matriz_sus[100]; //Declara o tamanho mï¿½ximo do vetor de elementos da matriz inversa positiva/negativa
  float matriz_sus_zero[100]; //Declara o tamanho mï¿½ximo do vetor de elementos da matriz inversa zero

  float a_zero[100][100] = {{0}}; //Declara a variï¿½vel que irï¿½ receber os dados da matriz de susceptï¿½ncia zero que irï¿½ para a funï¿½ï¿½o Determinante
  float a[100][100] = {{0}}; //Declara a variï¿½vel que irï¿½ receber os dados da matriz de susceptï¿½ncia que irï¿½ para a funï¿½ï¿½o Determinante
  int vetor_coluna[100], vetor_linha[100]; //Declara a variï¿½vel que irï¿½ receber os dados da posiï¿½ï¿½o, coluna e linha, dos elementos das matriz que sï¿½o diferentes de zero
  int  i, j, k, w, c, d, wi; //Variï¿½veis contadoras e tamanho da matriz (k)

  //Encontra o numero de elementos do vetor
  ifstream in("linha.txt"); //Confere se o arquivo linha.txt possui elementos
  string t; //Declara a varï¿½avel que guardarï¿½ os elementos de linha.txt
  while (in) { //Laï¿½o que irï¿½ varrer o arquivo linha.txt
    t.push_back(in.get()); //Guarda os elementos de linha.txt em t
  }
  in.close(); 
  int ta = (t.size()/2); //Guarda em ta a quantidade de elementos de t
  //printf("Quantidade de elementos no vetor:%i\n", ta);
  for(w = 0; w < ta; w++) //Laï¿½o que varre os arquivos de posiï¿½ï¿½o e elementos das matrizes de susceptï¿½ncia
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

    int linha = vetor_linha[w]; //Guarda o posiï¿½ï¿½o da linha do elemento nï¿½o zero em uma variï¿½vel auxiliar
    int coluna = vetor_coluna[w]; //Guarda o posiï¿½ï¿½o da coluna do elemento nï¿½o zero em uma variï¿½vel auxiliar
    float sus = matriz_sus[w]; //Guarda o elemento nï¿½o zero em uma variï¿½vel auxiliar
    float sus_zero = matriz_sus_zero[w]; //Guarda o elemento nï¿½o zero, da matriz zero, em uma variï¿½vel auxiliar
    a[linha-1][coluna-1] = sus; //Preenche o elemento da matriz de susceptï¿½ncia positivo/negativa
    a_zero[linha-1][coluna-1] = sus_zero; //Preenche o elemento da matriz de susceptï¿½ncia zero
  }
  
  //Salva a matriz de susceptância no arquivo matriz_sus.txt
    for (w=0; w < k; w++)
  {
    for (c=0; c < k; c++)
  	{
		//printf("\t%f", a[w][c]);
		fprintf(fp5, "\t%f", a[w][c]); 
  	}
  	//printf("\n");
  	fprintf(fp5, "\n"); 
  }

  d = determinant(a, k); //Chama a funï¿½ï¿½o Determinante, com o tamanho da matriz e amtriz de susceptï¿½ncia
  if (d == 0) //Condiï¿½ï¿½o onde o determinante ï¿½ zero e em conseguï¿½ncia nï¿½o hï¿½ matriz inversa
  printf("\nSem matriz inversa\n");
  else ////Condiï¿½ï¿½o onde o determinante nï¿½o ï¿½ zero, hï¿½ matriz inversa
  {
  	if (flag == 1) { //Condiï¿½ï¿½o onde a matriz de admitï¿½ncia positiva/negativa ainda nï¿½o foi calculada
	  	cofactor(a, k, vetor_linha, vetor_coluna, ta); //Chama a funï¿½ï¿½o que calcula o cofator da matriz de susceptï¿½ncia  
  	}
  	if (flag == 0) { //Condiï¿½ï¿½o onde a matriz de admitï¿½ncia zero ainda nï¿½o foi calculada
	  	cofactor(a_zero, k, vetor_linha, vetor_coluna, ta); //Chama a funï¿½ï¿½o que calcula o cofator da matriz de susceptï¿½ncia zero
  	}
  }
  

  fault(inverse_p, inverse_zero, k, vetor_linha, vetor_coluna, ta); //Chama a funï¿½ï¿½o que calcula as variï¿½veis de falta
}



//Funï¿½ï¿½o que calcula o determinante da matriz de susceptï¿½ncia
float determinant(float a[100][100], float k) 
{
  float s = 1, det = 0, b[100][100]; //variï¿½veis auxiliares de matriz
  int i, j, m, n, c; //variï¿½veis auxiliares de contagem
  if (k == 1) //Condiï¿½ï¿½o de matriz de um elemento
    {
     return (a[0][0]); //Neste caso o ï¿½nico elemento ï¿½ o prï¿½prio elemento
    }
  else //condiï¿½ï¿½o com mais de um elemento
    {
     det = 0; //Declara que o valor inicial do determinante ï¿½ zero
     for (c = 0; c < k; c++) //Laï¿½o que varre a matriz de susceptï¿½ncia 
       {
        m = 0; //Zera as variï¿½veis auxiliares
        n = 0; 
        for (i = 0;i < k; i++) //Varre as linhas da matriz
          {
            for (j = 0 ;j < k; j++) //Varre as colunas da matriz
              {
                b[i][j] = 0; //Zera o elemento da matriz na respectiva posiï¿½ï¿½o
                if (i != 0 && j != c) //Interaï¿½ï¿½o onde se obtem a matriz menor complementar
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
          det = det + s * (a[0][c] * determinant(b, k - 1)); //Atualiza na variï¿½vel o resultado do cofator com a do determinate da matriz menor complementar
          
          s = -1 * s; //Para o prï¿½ximo cofator a contribuiï¿½ï¿½o ï¿½ negativa
          }
    }

    return (det); //Retorna o valor calculado do determinante
}

//Funï¿½ï¿½o que calcula o cofator da matriz de impedï¿½ncia
void cofactor(float num[100][100], float f, int lin[], int col[], int ta) 
{
 float b[100][100], fac[100][100]; //variï¿½veis auxiliares de matriz
 int p, q, m, n, i, j; //variï¿½veis auxiliares de contagem
 for (q = 0;q < f; q++) ///Laï¿½o que varre as linhas matriz de susceptï¿½ncia
 {
   for (p = 0;p < f; p++) ///Laï¿½o que varre as colunas matriz de susceptï¿½ncia
    {
     m = 0; 
     n = 0; 
     for (i = 0;i < f; i++) 
     {
       for (j = 0;j < f; j++) 
        {
          if (i != q && j != p) //Condiï¿½ï¿½o das variï¿½veis fora da diagonal principal
          {
            b[m][n] = num[i][j]; //Faz a transposiï¿½ï¿½o da matriz
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
  transpose(num, fac, f, lin, col, ta); //Chama a funï¿½ï¿½o que transpoï¿½m a matriz
}

//Funï¿½ï¿½o que calcula a matriz de impedï¿½ncia
void transpose(float num[100][100], float fac[100][100], float r, int lin[], int col[], int ta) //
{
  int i, j; ////variï¿½veis auxiliares de contagem
  float b[100][100], inverse[100][100], d; ////variï¿½veis auxiliares de matriz

  for (i = 0;i < r; i++) //Varre os elementos pelas linhas da matriz
    {
     for (j = 0;j < r; j++) //Varre os elementos pelas colunas da matriz
       {
         b[i][j] = fac[j][i]; //Faz a transposiï¿½ï¿½o da matriz
        }
    }
  d = determinant(num, r); //Chama a funï¿½ï¿½o do determinante
  for (i = 0;i < r; i++) //Varre a matriz pelas linhas
    {
     for (j = 0;j < r; j++) //Varre a matriz pelas colunas
       {
        inverse[i][j] = b[i][j] / d; //Obtem os elementos da inversa dividindo o elemento do cofator transposto pelo determinante
        }
    }
    if (flag == 1){ //Condiï¿½ï¿½o da matriz ser de seguï¿½ncia positiva/negativa
    printf("Matriz de impedancia de seguencia positiva/negativa:\n"); //
    for (i = 0;i < r; i++) //Varre as linhas da matriz
    {
     for (j = 0;j < r; j++) //Varre as colunas da matriz
       {
        inverse_p[i][j] = inverse[i][j]; //Guarda na matriz de seguï¿½ncia a inversa
                printf("\t%f", inverse_p[i][j]); 
                fprintf(fp4, "\t%f", inverse_p[i][j]); 
        }
                printf("\n");
                fprintf(fp4, "\n");
    } 
	}
	
	    if (flag == 0){ //Condiï¿½ï¿½o da matriz ser de seguï¿½ncia positiva/negativa
    for (i = 0;i < r; i++) //Varre as linhas da matriz
    {
     for (j = 0;j < r; j++) //Varre as colunas da matriz
       {
        inverse_zero[i][j] = inverse[i][j]; ////Guarda na matriz de seguï¿½ncia a inversa
        }
    }	
	}
	
    flag = 0; //Se o cï¿½lculo da matriz inversa de seguï¿½ncia positiva/negativa jï¿½ estiver sido feito, faz-se o zero 
   
}

//Funï¿½ï¿½o que encontra as variï¿½veis do curto circuito (Corrente de curto, tensï¿½o pï¿½s falta nas barra e corrente pï¿½s falta nas linhas)
void fault(float imp[100][100], float imp_zero[100][100], int q, int lin[], int col[], int ta) 
{
	//Declara o ponteiro para o arquivo que guarda a carrente de falta, tensï¿½o pï¿½s falta das barras e a corrente pï¿½s falta das linhas
	FILE *fp1; 
	FILE *fp2;  
	FILE *fp3; 
	//Abre os arquivos de dados da falta, componentes da linha e saï¿½da do FP
	FILE *file4 = fopen("entrada_falta.txt", "r"); 
	FILE *file5 = fopen("tensao.txt", "r"); 
	FILE *file6 = fopen("angulo.txt", "r"); 
	FILE *file7 = fopen("x_linha.txt", "r"); 
	FILE *file8 = fopen("x_linha_traf.txt", "r"); 
	FILE *file9 = fopen("sus_zero.txt", "r"); 
	FILE *file10 = fopen("tipo_traf.txt", "r"); 
	FILE *file11 = fopen("local_tipo_traf.txt", "r"); 
	//Variï¿½veis auxiliares
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
	//Alocaï¿½ï¿½o dos dados da falta lidos em varï¿½aveis
  	//local = dados_falta[0]; 
  	barra = dados_falta[0]; 
  	//linha1 = dados_falta[2]; 
  	//linha2 = dados_falta[3]; 
  	porc_linha = dados_falta[1]; 
  	tipo = dados_falta[2]; 
  	res_ate = dados_falta[3]; 
  	res_zero = dados_falta[4]; 
  	//printf("\n%d,%d,%d,%f,%f",barra,porc_linha,tipo,res_ate,res_zero);  	
  	//Abre os arquivos de saï¿½da para preenchimento
  	fp1 = fopen("corrente_falta.txt","w"); 
  	fp2 = fopen("tensao_pos_falta.txt","w"); 
  	fp3 = fopen("corrente_linha_falta.txt","w"); 
    //fprintf(fp, "%s %d", "Tim", 31);
    //fclose(fp);
  	
  	printf("\n"); 
  	printf("Tensao pre falta das barras:\n"); 
  	//Alocaï¿½ï¿½o dos dados de saï¿½da do FP e das linhas lidos em varï¿½aveis 
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
    	if (tipo == 3)							//Condiï¿½ï¿½o de falta trifï¿½sica
    	{	
    		printf("\n\tTrifasica\n");
    		i_f = tensao[barra-1]/((imp[barra-1][barra-1])+res_ate); //Obtenï¿½ï¿½o da corrente de falta trifï¿½sica
    		fprintf(fp1, "%f,90,%f,90,%f,90", i_f,i_f,i_f);
    		printf("\nDados de saida:");
			printf("\n\tCorrente de falta: %f", i_f);
			printf("\n\tTensoes pos-falta:");
			for(p = 0; p < q; p++) //
  			{
				v_n[p] = tensao[barra-1]*(1-imp[p][barra-1]/((imp[barra-1][barra-1])+res_ate)); //Obtenï¿½ï¿½o da tensï¿½o pï¿½s falta trifï¿½sica das barras
				fprintf(fp2, "%d,%f,%f, %f,%f, %f,%f\n", p+1, v_n[p], angulo[p],v_n[p], angulo[p]-120,v_n[p], angulo[p]+120); //
				printf("\n\t\tBarra %d\n\t\t\tVa:%fL%f\n \t\t\tVb:%fL%f\n \t\t\tVc:%fL%f\n", p+1, v_n[p], angulo[p],v_n[p], angulo[p]-120,v_n[p], angulo[p]+120);	
  			} 	
		}
		
		else //Condiï¿½ï¿½o de faltas assimï¿½tricas
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
				printf("\n\tTransformadores D-Y\n");
  				printf("\nMatriz de impedancia de seguencia zero:\n");
    			for(p = 0; p < q; p++)  //Obtem a matriz de seguï¿½ncia zero para um sistema formado por transformadores D-Y
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
						fprintf(fp6, "\t%f", imp_zero[p][v]);
					}
					printf("\n");
					fprintf(fp6, "\n");	
				}
			}
			if (tipo_trafo[0] == 2 && tipo_trafo[barra] == 2)							//Transformadores Y-Y
    		{
    			printf("\n\tTransformadores Y-Y\n");
    			printf("\nMatriz de impedancia de seguencia zero:\n");
				for(p = 0; p < q; p++) //Obtem a matriz de seguï¿½ncia zero para um sistema formado por transformadores Y-Y
  				{
    				for (v = 0; v < q; v++) 
  					{
	  					printf("\t%f", imp_zero[p][v]);
	  					fprintf(fp6, "\t%f", imp_zero[p][v]);
					}
					printf("\n");
					fprintf(fp6, "\n");
				}
			}
			if (tipo == 1)							//Condiï¿½ï¿½o de falta monofï¿½sica
			{
				printf("\n\t Falta monofasica\n");
				i_f = 3*(tensao[barra-1]/(2*(imp[barra-1][barra-1])+imp_zero[barra-1][barra-1])); //Obtenï¿½ï¿½o da corrente de falta monofï¿½sica
    			fprintf(fp1, "%f,90,%f,90,%f,90", i_f, i_f, i_f);
				printf("\nDados de saida:");
				printf("\n\tCorrente de falta: %f (para as 3 fases)", i_f);
				printf("\n\tTensoes pos-falta:");
				for(p = 0; p < q; p++) //
  				{
					v_n_zero[p] = -imp_zero[p][barra-1]*i_f/3; 
					v_n[p] = tensao[barra-1]-imp[p][barra-1]*i_f/3; 
					v_n_n[p] = -imp[p][barra-1]*i_f/3; 
					//printf("\n\t\t%f  %f  %f", v_n_zero[p], v_n[p], v_n_n[p]);
					v_n_zero_g[p] = v_n_zero[p] + v_n[p] + v_n_n[p]; //Obtenï¿½ï¿½o da tensï¿½o pï¿½s falta monofï¿½sica de seguï¿½ncia zero
					//printf("\n\t\t%f", v_n_zero_g[p]);
					a_n_zero[p] = 0; //Obtenï¿½ï¿½o do ï¿½ngulo da tensï¿½o pï¿½s falta monofï¿½sica de seguï¿½ncia zero
					a_n_g[p] = (180/3.14)*atan((-v_n_zero[p]+v_n[p]+v_n_n[p])/-(v_n_zero[p]+v_n[p]))+180; //Obtenï¿½ï¿½o do ï¿½ngulo da tensï¿½o pï¿½s falta monofï¿½sica de seguï¿½ncia positivo
					v_n_g[p] = sqrt ((v_n_zero[p]-(v_n[p]+v_n_n[p])/2)*(v_n_zero[p]-(v_n[p]+v_n_n[p])/2)+((-sqrt(3)/2)*(v_n[p]-v_n_n[p]))*((-sqrt(3)/2)*(v_n[p]-v_n_n[p]))); //Obtenï¿½ï¿½o da tensï¿½o pï¿½s falta monofï¿½sica de seguï¿½ncia positivo
					printf("\n\t\tBarra %d\n\t\t\tVa:%fL%f\n \t\t\tVb:%fL%f\n \t\t\tVc:%fL%f\n", p+1, v_n_zero_g[p], a_n_zero[p], v_n_g[p], a_n_g[p], v_n_g[p], -a_n_g[p]); 
					fprintf(fp2, "%d,%f,%f, %f,%f, %f,%f\n", p+1, v_n_zero_g[p], a_n_zero[p], v_n_g[p], a_n_g[p], v_n_g[p], -a_n_g[p]); 
  				} 
			}
			
			if (tipo == 2)							//Falta bifï¿½sica sem terra
			{
				printf("\n\tFalta bifasica sem terra\n");
				i_f = tensao[barra-1]/(2*imp[barra-1][barra-1]); //Obtenï¿½ï¿½o da corrente de falta
    			fprintf(fp1, "0,0,%f,180,%f,0", i_f*sqrt(3), -i_f*sqrt(3));
				printf("\nDados de saida:");
				printf("\n\tCorrente de falta: \n\t\tIfa %fL0\n\t\tIfb %fL180\n\t\tIfc %fL0", 0, i_f*sqrt(3), -i_f*sqrt(3));
				printf("\n\tTensoes pos-falta:");
				for(p = 0; p < q; p++) //
  				{
					v_n_zero[p] = 0; 
					v_n[p] = tensao[barra-1]-imp[barra-1][p]*i_f; 
					v_n_n[p] = v_n[p]; //
					//printf("\n\t\t%f  %f  %f", v_n_zero[p], v_n[p], v_n_n[p]);
					v_n_zero_g[p] = v_n_zero[p] + v_n[p] + v_n_n[p]; //Obtenï¿½ï¿½o da tensï¿½o pï¿½s falta bifï¿½sica sem terra de seguï¿½ncia zero
					//printf("\n\t\t%f", v_n_zero_g[p]);
					a_n_zero[p] = 0; 
					a_n_g[p] = 180; 
					v_n_g[p] = sqrt ((v_n_zero[p]-(v_n[p]+v_n_n[p])/2)*(v_n_zero[p]-(v_n[p]+v_n_n[p])/2)+((-sqrt(3)/2)*(v_n[p]-v_n_n[p]))*((-sqrt(3)/2)*(v_n[p]-v_n_n[p]))); //Obtenï¿½ï¿½o da tensï¿½o pï¿½s falta bifï¿½sica sem terra de seguï¿½ncia positivo
					printf("\n\t\tBarra %d\n\t\t\tVa:%fL%f\n \t\t\tVb:%fL%f\n \t\t\tVc:%fL%f\n", p+1, v_n_zero_g[p], a_n_zero[p], v_n_g[p], a_n_g[p], v_n_g[p], a_n_g[p]);
					fprintf(fp2, "%d,%f,%f, %f,%f, %f,%f\n", p+1, v_n_zero_g[p], a_n_zero[p], v_n_g[p], a_n_g[p], v_n_g[p], a_n_g[p]);
  				}
			}
				if (tipo == 4)					 //Falta bifï¿½sica com terra
				{
					printf("\n\tFalta bifasica com terra");	
					i_f = tensao[barra-1]/(-imp[barra-1][barra-1]+(-imp[barra-1][barra-1]*imp_zero[barra-1][barra-1])/(-imp[barra-1][barra-1]+imp_zero[barra-1][barra-1])); //Obtenï¿½ï¿½o da corrente de falta bifï¿½sica com terra
					//printf("\n%f/(%f + (%f*%f/%f+%f))", tensao[barra-1], -imp[barra-1][barra-1], -imp[barra-1][barra-1], imp_zero[barra-1][barra-1], -imp[barra-1][barra-1], imp_zero[barra-1][barra-1]);
					i_f_n2 = -i_f*imp_zero[barra-1][barra-1]/(imp[barra-1][barra-1]-imp_zero[barra-1][barra-1]); 
					i_f_zero2 = i_f*imp[barra-1][barra-1]/(imp[barra-1][barra-1]-imp_zero[barra-1][barra-1]); 
					//printf("\n1-%f		2-%f		0-%f\n", i_f, i_f_n2, i_f_zero2);
					i_f_g_zero = i_f+i_f_n2+i_f_zero2; //Obtenï¿½ï¿½o da corrente de falta de seguï¿½ncia zero
					i_f_g = sqrt ((i_f_zero2-(i_f-i_f_n2)/2)*(i_f_zero2-(i_f-i_f_n2)/2)+((-sqrt(3)/2)*(i_f+i_f_n2))*((-sqrt(3)/2)*(i_f+i_f_n2))); //Obtenï¿½ï¿½o da corrente de falta de seguï¿½ncia positiva
					//a_f_g = (180/3.14)*atan((-sqrt(3)/2)*(i_f-i_f_n2)/(i_f_zero2-(i_f+i_f_n2)/2))+90;
					a_f_g = 90+(180/3.14)*atan((((i_f+i_f_n2)/2)/sqrt(3)/2)*(i_f-i_f_n2)); //Obtenï¿½ï¿½o do ï¿½ngulo da corrente de falta de seguï¿½ncia positiva
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
						v_n_zero_g[p] = v_n_zero[p]+sqrt(((v_n[p]+v_n_n[p])*sqrt(3)/2)*((v_n[p]+v_n_n[p])*sqrt(3)/2)+(0.5*(v_n[p]-v_n_n[p]))*(0.5*(v_n[p]-v_n_n[p]))); //Obtenï¿½ï¿½o da tensï¿½o pï¿½s falta bifï¿½sica com terra de seguï¿½ncia zero
						a_n_zero[p] = 90-(180/3.14)*atan(sqrt(3)*(v_n[p]+v_n_n[p])/(v_n[p]-v_n_n[p])); //Obtenï¿½ï¿½o do ï¿½ngulo da tensï¿½o pï¿½s falta bifï¿½sica com terra de seguï¿½ncia zero
						//printf("\n\t\t%f", a_n_zero[p]);
						v_n_g[p] = sqrt ((v_n_zero[p]-(v_n[p]+v_n_n[p])/2)*(v_n_zero[p]-(v_n[p]+v_n_n[p])/2)+((-sqrt(3)/2)*(v_n[p]-v_n_n[p]))*((-sqrt(3)/2)*(v_n[p]-v_n_n[p]))); //Obtenï¿½ï¿½o da tensï¿½o pï¿½s falta bifï¿½sica com terra de seguï¿½ncia positivo
						//printf("\n\t\t%f", v_n_g[p]);
						a_n_g[p] = 60+(180/3.14)*atan((v_n_zero[p]-(v_n[p]+v_n_n[p])/2)/((-sqrt(3)/2)*(v_n[p]-v_n_n[p]))); //Obtenï¿½ï¿½o do ï¿½ngulo da tensï¿½o pï¿½s falta bifï¿½sica com terra de seguï¿½ncia positiva
						//printf("\n\t\t%f", a_n_g[p]);
						printf("\n\t\tBarra %d\n\t\t\tVa:%fL%f\n \t\t\tVb:%fL%f\n \t\t\tVc:%fL%f\n", p+1, v_n_zero_g[p], a_n_zero[p], v_n_g[p], a_n_g[p], v_n_g[p], a_n_g[p]+60);
						fprintf(fp2, "%d,%f,%f, %f,%f, %f,%f\n", p+1, v_n_zero_g[p], a_n_zero[p], v_n_g[p], a_n_g[p], v_n_g[p], a_n_g[p]+60);
  					}		
				}					
		}	
	
//	if (local == 0) 									//Falta na linha
//    {	
//    	if (porc_linha == 1)
//		{
//			printf("\n\tFalta na linha %d-%d", linha1, linha2);
//		}
//		else {
//			printf("\n\tFalta a %d por cento da linha %d-%d", porc_linha, linha1, linha2);
//			
//		}
//		if (tipo == 3)							//Falta trifï¿½sica
//    	{	
//    		printf("\n\tTrifasica\n");
//    		i_f = (tensao[linha2])/((imp[linha1][linha2])+res_ate); //Obtenï¿½ï¿½o da corrente de falta trifï¿½sica na linha
//    		fprintf(fp1, "%f,90,%f,90,%f,90", i_f,i_f,i_f);
//    		printf("\nDados de saida:");
//			printf("\n\tCorrente de falta: %f A", i_f);
//			printf("\n\tTensoes pos-falta:");
//			for(p = 0; p < q; p++) //
//  			{
//				v_n[p] = (tensao[linha2-1])*(1-imp[p][linha1-1]/((imp[linha1-1][linha2-1])+res_ate)); //Obtenï¿½ï¿½o da tensï¿½o pï¿½s falta nas barras por falta trifï¿½sica na linha
//				fprintf(fp2, "%d,%f,%f, %f,%f, %f,%f\n", p+1, v_n[p], angulo[p],v_n[p], angulo[p]-120,v_n[p], angulo[p]+120); 
//				printf("\n\t\tBarra %d\n\t\t\tVa:%fL%f\n \t\t\tVb:%fL%f\n \t\t\tVc:%fL%f\n", p+1, v_n[p], angulo[p],v_n[p], angulo[p]-120,v_n[p], angulo[p]+120); 	
//  			} 	
//		}
//	}
		
	for(v = 0; v < (ta-q); v++)
  	{
    	if (!fscanf(file7, "%f", &xlinha[v]))
    	break; 
    	//printf("%f ", xlinha[v]);
  	}
  	
  	printf("\n\tCorrente de falta nas linhas:");
  	
	if (tipo != 3) //Condiï¿½ï¿½o para faltas assimï¿½tricas
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
		i_l_zero_g[p] = i_l_zero[p] + i_l[p] + i_l_n[p]; //Obtenï¿½ï¿½o da corrente pï¿½s falta nas linhas de seguï¿½ncia zero
		a_n_zero[p] = 0; 
		a_n_g[p] = (180/3.14)*atan((-i_l_zero[p]+i_l[p]+i_l_n[p])/-(i_l_zero[p]+i_l[p]))+180; 	
		i_l_g[p] = sqrt((i_l_zero[p]-(i_l[p]+i_l_n[p])/2)*(i_l_zero[p]-(i_l[p]+i_l_n[p])/2)+((-sqrt(3)/2)*(i_l[p]-i_l_n[p]))*((-sqrt(3)/2)*(i_l[p]-i_l_n[p]))); //Obtenï¿½ï¿½o da corrente pï¿½s falta nas linhas de seguï¿½ncia postiva
		if (p != 0){ 
		printf("\n\t\tLinhas %d-%d\n\t\t\tIa:%f\n \t\t\tIb:%f\n \t\t\tIc:%f\n", p, p+1, i_l_zero_g[p], i_l_g[p], i_l_g[p]);
		fprintf(fp3, "%d,%d,%f,%f, %f,%f, %f,%f\n", p, p+1, i_l_zero_g[p], i_l_g[p], i_l_g[p]);
	}
  	}
  	}
  	
  	if (tipo == 3) //Condiï¿½ï¿½o para faltas simï¿½tricas
	{
	int i = 0;
	for(p = 0; p < ta; p++)
  	{
  		if (lin[p] != col[p])
		{
			if (xlinha[i] > 0.0001 && xlinha[i] < 100) 
			{
				i_l[p] = (v_n[lin[p]-1]-v_n[col[p]-1])/xlinha[i]; //Obtenï¿½ï¿½o da corrente pï¿½s falta nas linhas
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
	fclose(fp5);
	fclose(fp6);
}



