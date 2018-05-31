# Conjuntos
set BUS;    										# Barras
set BRANCH within {1..4000} cross BUS cross BUS; 	# Linhas (Guarda os índices e barra de partida e chegada)

# Arquivo de solução
option solver './MINOS';				#Escolhe o MINOS como solver

# Dados das barras
param bus_type       {BUS};				# Tipo (3-Slack 2-PV 0-PQ)
param bus_name       {BUS} symbolic;	# Nome 
param bus_voltage0   {BUS};				# Tensão inicial: As PQs serão 1
param bus_angle0     {BUS};				# Ângulo inicial: As PQs e PVs serão 0
param bus_p_gen0     {BUS};			    # Potência ativa do gerador
param bus_q_gen      {BUS};				# Potência reativa do gerador
param bus_q_min      {BUS};				# Potência reativa mínima
param bus_q_max      {BUS};				# Potência reativa máxima
param bus_p_load     {BUS};				# Potência ativa da carga
param bus_q_load     {BUS};				# Potência reativa da carga
param bus_p_gen_min  {BUS};				# Potência ativa mínima no gerador
param bus_p_gen_max  {BUS};				# Potência ativa máxima no gerador
param bus_q_shunt    {BUS};				# Potência reativa do shunt em cada barra

# Dados das linhas

param branch_type    {BRANCH};			# Índice
param branch_r       {BRANCH};			# Resistência 
param branch_x       {BRANCH};			# Indutância
param branch_tap     {BRANCH};			# Razão de transformação
param branch_def     {BRANCH};			# Angulo de defasamento
param branch_g       {(l,k,m) in BRANCH} := branch_r[l,k,m]/(branch_r[l,k,m]^2+branch_x[l,k,m]^2); # Condutância
param branch_b       {(l,k,m) in BRANCH} :=-branch_x[l,k,m]/(branch_r[l,k,m]^2+branch_x[l,k,m]^2); # Susceptância

# Dados nominais

param Sbase;		#Potência nominal

# Variáveis

var bus_voltage {i in BUS};		# Tensão nas barras
var bus_angle   {i in BUS};		# Ângulo nas barras
var bus_p_gen   {i in BUS};		# Potência ativa das barras de geração nas barras

# Variáveis auxiliares

var p_g {BUS};    # Potência ativa transmitida nas linhas
var q_g {BUS};    # Potência reativa transmitida nas linhas

var p_d {BRANCH}; # Fluxo direto ativo
var q_d {BRANCH}; # fluxo direto reativo
var p_r {BRANCH}; # fluxo inverso ativo
var q_r {BRANCH}; # fluxo inverso reativo

# Matriz YBUS

set YBUS := setof{i in BUS} (i,i) union 
setof {(l,k,m) in BRANCH} (k,m) union
setof {(l,k,m) in BRANCH} (m,k);

param G{(k,m) in YBUS} =		# Monta o vetor de condutância para o fluxo de potência
if(k == m) then (sum{(l,k,i) in BRANCH} branch_g[l,k,i]*branch_tap[l,k,i]^2
                                + sum{(l,i,k) in BRANCH} branch_g[l,i,k])
else if(k != m) then (sum{(l,k,m) in BRANCH} (-branch_g[l,k,m]*cos(branch_def[l,k,m])-branch_b[l,k,m]*sin(branch_def[l,k,m]))*branch_tap[l,k,m]
                     +sum{(l,m,k) in BRANCH} (-branch_g[l,m,k]*cos(branch_def[l,m,k])+branch_b[l,m,k]*sin(branch_def[l,m,k]))*branch_tap[l,m,k]);

param B{(k,m) in YBUS} =		# Monta o vetor de susceptância para o fluxo de potência
if(k == m) then (sum{(l,k,i) in BRANCH} (branch_b[l,k,i]*branch_tap[l,k,i]^2)
                                + sum{(l,i,k) in BRANCH} (branch_b[l,i,k]))
else if(k != m) then (sum{(l,k,m) in BRANCH} (branch_g[l,k,m]*sin(branch_def[l,k,m])-branch_b[l,k,m]*cos(branch_def[l,k,m]))*branch_tap[l,k,m]
                     +sum{(l,m,k) in BRANCH} (-branch_g[l,m,k]*sin(branch_def[l,m,k])-branch_b[l,m,k]*cos(branch_def[l,m,k]))*branch_tap[l,m,k]);

#Montagem da matriz de impedâncias
#param MYBUS{(k,m) in YBUS} = sqrt((G[k,m]^2)+(B[k,m]^2)); 	#Módulo 
#param AYBUS{(k,m) in YBUS} = tan(B[k,m]/G[k,m]); 		 	#Ângulo 

# Função objetivo

minimize pot_ativa :	# Fluxo de potência ativa
sum {k in BUS : bus_type[k] == 0}
(bus_p_gen[k] - bus_p_load[k] - sum{(k,m) in YBUS} (bus_voltage[k]*bus_voltage[m]*
(G[k,m]*cos(bus_angle[k]-bus_angle[m])+B[k,m]*sin(bus_angle[k]-bus_angle[m]))));

# Restrições
				# Fluxo de potência reativa
subject to q_load {k in BUS : bus_type[k] == 0}:	
   bus_q_gen[k] + bus_q_shunt[k] - bus_q_load[k] - sum{(k,m) in YBUS} (bus_voltage[k]*bus_voltage[m]*
                          (G[k,m]*sin(bus_angle[k]-bus_angle[m])-B[k,m]*cos(bus_angle[k]-bus_angle[m]))) = 0;
   				# Fluxo de potência reativa injetada
subject to q_inj {k in BUS : bus_type[k] == 2 || bus_type[k] == 3}:
   bus_q_min[k] <= - bus_q_shunt[k] + bus_q_load[k] + sum{(k,m) in YBUS} (bus_voltage[k]*bus_voltage[m]*
                (G[k,m]*sin(bus_angle[k]-bus_angle[m])-B[k,m]*cos(bus_angle[k]-bus_angle[m]))) <= bus_q_max[k];
   				# Fluxo de potência ativa injetada
subject to p_inj {k in BUS : bus_type[k] == 2 || bus_type[k] == 3}:
   bus_p_gen_min[k] <= bus_p_load[k] - bus_p_gen[k] + sum{(k,m) in YBUS} (bus_voltage[k]*bus_voltage[m]*
               (G[k,m]*cos(bus_angle[k]-bus_angle[m])+B[k,m]*sin(bus_angle[k]-bus_angle[m]))) <= bus_p_gen_max[k];
				# Precisão
subject to p_inj_pos {k in BUS : bus_type[k] == 2 || bus_type[k] == 3}:
   bus_p_load[k] + sum{(k,m) in YBUS} (bus_voltage[k]*bus_voltage[m]*
               (G[k,m]*cos(bus_angle[k]-bus_angle[m])+B[k,m]*sin(bus_angle[ k]-bus_angle[m]))) >= 1e-15;
   				#Limite de tensão transmitida
subject to bus_voltate_limits {k in BUS : bus_type[k] == 0}:
   0.90 <= bus_voltage[k] <= 1.1;

#subject to bus_angle_limits {k in BUS : bus_type[k] == 0 || bus_type[k] == 2}:
#   -2*3.14159 <= bus_angle[k] <= 2*3.14159;

# Carregamento dos dados
data dados.dat;

# Escalamento e inicialização de dados

for{i in BUS : bus_type[i] == 0} {	# Torna as tensões e ângulos da barra PQ em 1 e 0
	let bus_voltage[i] := 1;
   let bus_angle[i] := 0;
  };

for{i in BUS : bus_type[i] == 2} {  # Torna o ângulo da barra PV em 0
   let bus_angle[i] := 0;
  };

for{i in BUS} {	
   let bus_q_shunt[i] := bus_q_shunt[i]/Sbase;			# Coloca as potências em pu
   let bus_p_gen[i] := bus_p_gen[i]/Sbase;
   let bus_q_gen[i] := bus_q_gen[i]/Sbase;
   let bus_q_min[i] := bus_q_min[i]/Sbase;
   let bus_q_max[i] := bus_q_max[i]/Sbase;
   let bus_p_load[i] := bus_p_load[i]/Sbase;
   let bus_q_load[i] := bus_q_load[i]/Sbase;
   let bus_p_gen_min[i] := bus_p_gen_min[i]/Sbase;
   let bus_p_gen_max[i] := bus_p_gen_max[i]/Sbase;
  };

for{(l,k,m) in BRANCH} {								# Coloca os ângulos de defasamento em radianos
   let branch_def[l,k,m] := -branch_def[l,k,m]*3.14159/180; 
  };

# Fixação das variáveis

fix {i in BUS : bus_type[i] == 3} bus_angle[i] := bus_angle0[i]; 		# Fixa o angulo da barra Slack
fix {i in BUS : bus_type[i] == 3 || bus_type[i] == 2} bus_voltage[i] := bus_voltage0[i]; 	# Fixa a tensão da barra Slack e PV
fix {i in BUS : bus_type[i] == 2}  bus_p_gen[i] := 	bus_p_gen0[i]; 		# Fixa a potência ativa da barra PV

solve pot_ativa; # Resolve a função objetiva com o solucionador selecionado

	#Exemplo 05
#let bus_angle[1] := -0.0388;
#let bus_voltage[2] := 0.9929;
#let bus_angle[2] := -0.1244;
#let bus_voltage[3] := 0.9898;
#let bus_angle[3] := -0.1138;

	#Exemplo 06
#let bus_angle[1] := -0.053;
#let bus_voltage[1] := 0.9842;
#let bus_angle[2] := -0.0899;
#let bus_voltage[2] := 0.9567;

	#Exemplo 08
#let bus_voltage[2] := 0.961;
#let bus_voltage[4] := 0.92;
#let bus_voltage[5] := 0.964;
#let bus_angle[2] := -6.3;
#let bus_angle[3] := -3.7;
#let bus_angle[4] := -10.9;
#let bus_angle[5] := -6.2;

	#Exemplo 09
#let bus_voltage[2] := 0.982;
#let bus_angle[2] := -0.976;
#let bus_voltage[3] := 0.969;
#let bus_angle[3] := -1.872;
#let bus_angle[4] := 1.523;

#for {i in BUS }{
#	printf "%f\n", bus_voltage[i];
#	printf "%f\n", bus_angle[i];
#}

for {i in BUS }{
  	let bus_angle[i] := bus_angle[i]*3.14/180;
}

# Calcula geração de potência ativa e reativa

for{k in BUS : bus_type[k] == 2} { 
   let p_g[k] := bus_p_gen0[k]/Sbase;
}

 for{k in BUS : bus_type[k] == 3} { 
   let p_g[k]  := bus_p_load[k] + sum{(k,m) in YBUS} (bus_voltage[k]*bus_voltage[m]*
                   (G[k,m]*cos(bus_angle[k]-bus_angle[m])+B[k,m]*sin(bus_angle[k]-bus_angle[m])));
}

 for{k in BUS : bus_type[k] == 3 || bus_type[k] == 2} { 
   let q_g[k]  := bus_q_load[k] + sum{(k,m) in YBUS} (bus_voltage[k]*bus_voltage[m]*
                   (G[k,m]*sin(bus_angle[k]-bus_angle[m])-B[k,m]*cos(bus_angle[k]-bus_angle[m])));
}

# Calcula os fluxos diretos e inversos de potência ativa e reativa

for{(l,k,m) in BRANCH} {

  let p_d[l,k,m] := branch_g[l,k,m]*bus_voltage[k]^2*branch_tap[l,k,m]^2 
  -branch_g[l,k,m]*bus_voltage[k]*bus_voltage[m]*branch_tap[l,k,m]*cos(bus_angle[k]-bus_angle[m]+branch_def[l,k,m])
  -branch_b[l,k,m]*bus_voltage[k]*bus_voltage[m]*branch_tap[l,k,m]*sin(bus_angle[k]-bus_angle[m]+branch_def[l,k,m]);

  let q_d[l,k,m] :=-(branch_b[l,k,m])*bus_voltage[ k]^2*branch_tap[l,k,m]^2 
  -branch_g[l,k,m]*bus_voltage[k]*bus_voltage[m]*branch_tap[l,k,m]*sin(bus_angle[k]-bus_angle[m]+branch_def[l,k,m])
  +branch_b[l,k,m]*bus_voltage[k]*bus_voltage[m]*branch_tap[l,k,m]*cos(bus_angle[k]-bus_angle[m]+branch_def[l,k,m]);

  let p_r[l,k,m] := branch_g[l,k,m]*bus_voltage[m]^2 
  -branch_g[l,k,m]*bus_voltage[k]*bus_voltage[m]*branch_tap[l,k,m]*cos(bus_angle[k]-bus_angle[m]+branch_def[l,k,m])
  +branch_b[l,k,m]*bus_voltage[k]*bus_voltage[m]*branch_tap[l,k,m]*sin(bus_angle[k]-bus_angle[m]+branch_def[l,k,m]);

  let q_r[l,k,m] :=-(branch_b[l,k,m])*bus_voltage[m]^2 
  +branch_g[l,k,m]*bus_voltage[k]*bus_voltage[m]*branch_tap[l,k,m]*sin(bus_angle[k]-bus_angle[m]+branch_def[l,k,m])
  +branch_b[l,k,m]*bus_voltage[k]*bus_voltage[m]*branch_tap[l,k,m]*cos(bus_angle[k]-bus_angle[m]+branch_def[l,k,m]);
}

# Gera o arquivo de saída

  printf "Barra,Nome,Tensão,Angulo,Pgerada,Qgerada,Pcarga,Qcarga,Para,P_fluxo,Q_fluxo\n" > fluxo.csv;
  for{i in BUS} {
  printf "%d,%s,%f,%f,%f,%f,%f,%f,,,,\n", i, bus_name[i], bus_voltage[ i], bus_angle[i]*180/3.14159,
    p_g[i]*Sbase, q_g[i]*Sbase, bus_p_load[i]*Sbase, bus_q_load[i]*Sbase > fluxo.csv;
    
    	for{(l,i,m) in BRANCH} {
      printf ",,,,,,,%s,%d,%f,%f\n","", m , p_d[l,i,m]*Sbase, q_d[l,i,m]*Sbase > fluxo.csv;
    }

    for{(l,k,i) in BRANCH} {
      printf ",,,,,,,%s,%d,%f,%f\n","", k, p_r[l,k,i]*Sbase, q_r[l,k,i]*Sbase > fluxo.csv;
    }
  }

# Gera o arquivo de barra para o Curto Circuito

  for{i in BUS} {
  printf "%f ", bus_voltage[i], bus_angle[i]*180/3.14159 > tensao.txt;
  }

  for{i in BUS} {
  printf "%f ", bus_angle[i]*180/3.14159 > angulo.txt;
  }

# Gera o arquivo da matriz de susceptâncias para o Curto Circuito
  for {(k,m) in YBUS }{
		printf "%f ", B[k,m] > sus.txt;
	}

# Gera o arquivo da coluna para o Curto Circuito
  for {(k,m) in YBUS }{
    printf "%d ", k > coluna.txt;
  }

  # Gera o arquivo da linha para o Curto Circuito
  for {(k,m) in YBUS }{
    printf "%d ", m > linha.txt;
  }

# Gera o arquivo da matriz de susceptâncias para o Curto Circuito
  for {(k,m) in YBUS }{
		printf "%d,%d,%f\n", k, m, B[k,m] > suscep.txt;
	}

