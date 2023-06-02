COMPOSE_CMD := docker-compose

COMPOSE_FILE := srcs/docker-compose.yml

.PHONY: start build daemon stop


start: create-volume-dir
	$(COMPOSE_CMD) -f $(COMPOSE_FILE) up --no-deps --build

create-volume-dir:
	@mkdir -p ~/data ~/data/wordpress ~/data/database

build:
	$(COMPOSE_CMD) -f $(COMPOSE_FILE) build

daemon: create-volume-dir
	$(COMPOSE_CMD) -f $(COMPOSE_FILE) up -d --no-deps --build

stop:
	$(COMPOSE_CMD) -f $(COMPOSE_FILE) down

clean:
	$(COMPOSE_CMD) -f $(COMPOSE_FILE) down --rmi all

fclean:
	$(COMPOSE_CMD) -f $(COMPOSE_FILE) down --rmi all -v
	sudo rm -rf ~/data
