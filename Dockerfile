FROM alpine:3.9

# define a pasta de trabalho
WORKDIR /root/app

# copia as coisa para a pasta de trabalho
COPY . /root/app

# Instala as dependencias
RUN apk add --update gcc
RUN apk add --update g++
RUN apk add --update python2-dev
RUN apk add --update py2-pip
RUN apk add --update libffi-dev
RUN apk add --update openssl-dev
RUN pip install -r requirements.txt --no-cache-dir

# # inicializa o repositóro (baixa ampl, compila o cc) 
# RUN sh src/init.sh
RUN sh src/compile_cc.sh

# variáveis de ambiente
ENV SECRET_KEY=super-secret
ENV ROOT_DIR=/root/app/
ENV SRC_DIR=src/ 
ENV HEADER_FILES=config/headers_files.json
ENV PORT=5000
ENV DEBUG=False
ENV FLASK_ENV=development

# expõe a porta da api
EXPOSE 5000

#inicia o container
CMD python src/app.py
