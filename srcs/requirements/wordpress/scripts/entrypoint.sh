#!/bin/sh

if ! wp core is-installed
then
	wp core install \
		--url="$WP_DOMAIN" \
		--title="$WP_TITLE" \
		--admin_name="$WP_ADMIN" \
		--admin_email="$WP_ADMIN_EMAIL" \
		--admin_password="$WP_ADMIN_PASSWORD"
fi

echo $DB_HOST
echo $DB_NAME
echo $DB_USER
echo $DB_PASSWORD
echo $WP_DOMAIN
echo $WP_ADMIN
echo $WP_ADMIN_EMAIL
echo $WP_ADMIN_PASSWORD
echo $WP_TITLE

php-fpm7.3 --nodaemonize
