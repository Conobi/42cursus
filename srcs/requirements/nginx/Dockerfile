# syntax=docker/dockerfile:1
FROM debian:buster

ARG WP_HOST

RUN apt-get update && apt-get install nginx openssl curl -y

COPY config/nginx_server.conf /etc/nginx/sites-enabled/default

RUN openssl req -x509 -nodes -days 365 -subj "/C=CA/ST=QC/O=42 School/CN=tjolivet.42.fr" \
		-addext "subjectAltName=DNS:tjolivet.42.fr" \
		-newkey rsa:2048 -keyout /etc/ssl/private/nginx-selfsigned.key \
		-out /etc/ssl/certs/nginx-selfsigned.crt;
RUN sed -i "s/HOSTNAME_PLACEHOLDER/${WP_HOST}/g" /etc/nginx/sites-enabled/default
COPY config/ssl_dhparam /etc/nginx/dhparam

EXPOSE 443

ENTRYPOINT [ "nginx", "-g", "daemon off;"]
