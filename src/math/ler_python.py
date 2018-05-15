a = "matriz.txt"

f = open(a,'r')

linhas = f.readlines()
matrix = []

for linha in linhas:
	adm = linha.split(" ")
	adm_linha =[]
	for x in adm:
		adm_linha.append(float(x))

	matrix.append(adm_linha)

print(matrix)
