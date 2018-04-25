# Conjuntos
set BUS;    							# Barras
set BRANCH; 							# Linhas 
set FAULT;								# Falta

# Dados das barras
param bus_type       {BUS};				# Tipo (3-Slack, 2-PV, 0-PQ)
param bus_name       {BUS} symbolic;	# Nome 
param bus_voltage    {BUS};				# Tensão inicial
param bus_angle	     {BUS};				# Ângulo inicial
param bus_p_gen	     {BUS};			    # Potência ativa do gerador
param bus_q_gen      {BUS};				# Potência reativa do gerador
param bus_p_load     {BUS};				# Potência ativa da carga
param bus_q_load     {BUS};				# Potência reativa da carga

# Dados da falta

param fault_type    {FAULT};			# Tipo de falta (1-Mono, 2-Bi, 3-Bi com terra, 4-Trifásica)
param fault_place   {FAULT};			# Localização da falta (1-Barra, 2-Linha)
param fault_branch  {FAULT};			# Localização da falta na linha
param fault_r       {FAULT};			# Resistência da falta 

# Dados das linhas

param branch_k    	 {BRANCH};			# Origem
param branch_m       {BRANCH};			# Destino 
param MYBUS          {BRANCH};			# Módulo da impedância
param AYBUS          {BRANCH};			# Ângulo da impedância

# Dados nominais

param Sbase;							#Potência nominal

# Carregamento dos dados
data dados_falta.dat;

