# syntax=docker/dockerfile:1
FROM debian:buster

ARG DB_NAME
ARG DB_USER
ARG DB_PASSWORD

RUN apt-get update && apt-get install -y mariadb-server mariadb-client
# RUN service mysql start

# if [ -z "$DB_NAME" || -z "$DB_USER" || -z "$DB_PASSWORD" ];  \
# 	then echo 'Some environment variables must be specified. Exiting.'; exit 1; fi \

RUN mysql_install_db && \
	/usr/bin/mysqld_safe --datadir='/var/lib/mysql' & \
	sleep 5s && \
	mysql -u root -e "CREATE DATABASE $DB_NAME DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci; \
					  GRANT ALL ON $DB_NAME.* TO '$DB_USER'@'%' IDENTIFIED BY '$DB_PASSWORD'; \
					  FLUSH PRIVILEGES;"

RUN sed -i -e"s/^bind-address\s*=\s*127.0.0.1/bind-address = 0.0.0.0/" /etc/mysql/mariadb.conf.d/50-server.cnf
EXPOSE 3306
CMD /usr/bin/mysqld_safe --datadir='/var/lib/mysql'
