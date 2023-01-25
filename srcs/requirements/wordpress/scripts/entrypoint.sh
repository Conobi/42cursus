#!/bin/sh

if ! wp core is-installed --allow-root
then
	wp core install --allow-root \
		--url="$WP_DOMAIN" \
		--title="$WP_TITLE" \
		--admin_name="$WP_ADMIN" \
		--admin_email="$WP_ADMIN_EMAIL" \
		--admin_password="$WP_ADMIN_PASSWORD"
fi

php-fpm7.3 --nodaemonize
