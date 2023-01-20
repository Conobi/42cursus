# syntax=docker/dockerfile:1
FROM debian:buster
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
USER www-data
RUN wp --info && \
	mkdir wordpress && \
	cd wordpress && \
	wp core download --locale=fr_FR && \
	wp config create --skip-check \
		--dbhost=localhost \
		--dbname=wordpress \
		--dbuser=wordpress_user \
		--dbpass=passwordABCD
	# wp core install \
	# 	--url=yourwebsite.com \
	# 	--title="Your Blog Title" \
	# 	--admin_name=wordpress_admin \
	# 	--admin_password="4Long&Strong1" \
	# 	--admin_email=you@example.com

CMD [ "ping", "kiyo.ooo"]
