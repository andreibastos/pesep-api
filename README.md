# Programa Educacional para Sistemas Elétricos de Potência
API para calcular fluxo de potência e Curto-Circuito.
## Como Usar
### Virtualenv
instale virtuallenv em sua máquina. [Mais informações](https://virtualenv.pypa.io/en/latest/installation/) 
```sh
pip install virtualenv
```
 clone o repositório
```sh
git clone git@github.com:andreibastos/pesep-api.git
```
navege até a pasta
```sh
cd pesep-api
```

crie o ambiente virtual na pasta do repositorio
```sh
virtualenv .
```

ative o ambiente virtual criado
```sh
source bin/activate
```

instale as dependências
```sh
pip install -r requirements.txt
```

baixe o AMPL
```sh
sh get_ampl.sh
```

execute o servidor
```sh
python src/app.py
```