<?php

function main(): int
{
	$sock = socket_create(AF_INET, SOCK_STREAM, 0);
	$conn = socket_connect($sock, "127.0.0.1", 4242);
	if (!$conn)
		return 1;
	socket_write($sock, "AAAAAAAA", 8);
	sleep(1);
	socket_write($sock, "BBBBBBBB", 8);
	sleep(1);
	socket_write($sock, "CCCCCCCC", 8);
	sleep(1);
	socket_close($sock);
	return 0;
}

exit(main());
