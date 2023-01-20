# syntax=docker/dockerfile:1
FROM debian:buster
RUN apt-get update && apt-get install -y mariadb-server mariadb-client
# RUN service mysql start
RUN mysql_install_db && \
	/usr/bin/mysqld_safe --datadir='/var/lib/mysql' & \
	sleep 5s && \
	mysql -u root -e "CREATE DATABASE wordpress DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci;" && \
	mysql -u root -e "GRANT ALL ON wordpress.* TO 'wordpress_user'@'localhost' IDENTIFIED BY 'password';" && \
	mysql -u root -e "FLUSH PRIVILEGES;" && \
	killall mysqld && \
	sleep 5s
CMD /usr/bin/mysqld_safe --datadir='/var/lib/mysql'
