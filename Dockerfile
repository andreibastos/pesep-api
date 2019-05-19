FROM ubuntu

# define a pasta de trabalho
WORKDIR /root/app

# copia as coisa para a pasta de trabalho
COPY . /root/app

# Instala as dependencias
RUN apt-get update && apt-get install -y python-pip g++
RUN pip install -r requirements.txt --no-cache-dir

# # inicializa o repositóro (baixa ampl, compila o cc) 
# RUN sh src/init.sh
RUN sh src/compile_cc.sh

# variáveis de ambiente
ENV SECRET_KEY=super-secret
ENV ROOT_DIR=/root/app/
ENV SRC_DIR=src/ 
ENV HEADER_FILES=config/headers_files.json
ENV FLASK_RUN_PORT=5000
ENV FLASK_ENV=development
ENV FLASK_DEBUG=1
ENV FLASK_APP=src/app
ENV FLASK_RUN_HOST=0.0.0.0

# expõe a porta da api
EXPOSE 5000

#inicia o container
CMD flask run
