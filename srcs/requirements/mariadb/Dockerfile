# syntax=docker/dockerfile:1
FROM debian:buster
# VOLUME [ "/var/lib/mysql" ]
RUN apt-get update && apt-get install -y mariadb-server mariadb-client
# RUN service mysql start
RUN mysql_install_db && \
	/usr/bin/mysqld_safe --datadir='/var/lib/mysql' & \
	sleep 5s && \
	mysql -u root -e "CREATE DATABASE wordpress DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;" && \
	mysql -u root -e "GRANT ALL ON wordpress.* TO 'wordpress_user'@'%' IDENTIFIED BY 'passwordABCD';" && \
	mysql -u root -e "FLUSH PRIVILEGES;" && \
	killall mysqld && \
	sleep 5s
RUN sed -i -e"s/^bind-address\s*=\s*127.0.0.1/bind-address = 0.0.0.0/" /etc/mysql/mariadb.conf.d/50-server.cnf
EXPOSE 3306
CMD /usr/bin/mysqld_safe --datadir='/var/lib/mysql'
