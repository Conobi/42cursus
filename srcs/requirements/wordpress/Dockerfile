# syntax=docker/dockerfile:1
FROM debian:buster

ARG DB_HOST
ARG DB_NAME
ARG DB_USER
ARG DB_PASSWORD
ARG WP_DOMAIN
ARG WP_ADMIN
ARG WP_ADMIN_EMAIL
ARG WP_ADMIN_PASSWORD
ARG WP_TITLE

# Installs php and all the needed php modules
RUN apt-get update && apt-get upgrade -y && apt-get install \
	php-cgi php-common php-fpm php-pear php-mbstring php-zip php-net-socket \
	php-gd php-xml-util php-gettext php-mysql php-bcmath unzip wget git -y
RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
	chmod +x wp-cli.phar && \
	mv wp-cli.phar /usr/local/bin/wp

WORKDIR /var/www
RUN chmod u=rwX,g=srX,o=rX -R . && \
	chown www-data:www-data -R .
COPY ./scripts/entrypoint.sh /entrypoint.sh
USER www-data
RUN wp --info && \
	mkdir wordpress && \
	cd wordpress && \
	wp core download --locale=fr_FR && \
	wp config create --skip-check \
		--dbhost=$DB_HOST \
		--dbname=$DB_NAME \
		--dbuser=$DB_USER \
		--dbpass=$DB_PASSWORD

WORKDIR /var/www/wordpress
ENTRYPOINT [ "sh", "/entrypoint.sh" ]
