DIR_CERTS=../certs

# cria a pasta dos certificados 
mkdir -p $DIR_CERTS

# cria os certificados
openssl req -x509 -newkey rsa:4096 -nodes -out $DIR_CERTS/cert.pem -keyout $DIR_CERTS/key.pem -days 365