# Philosophers

- [x] 1. On fait le `Makefile` + git
- [x] 2. On include les structures avec fork = `mutex`, id
- [ ] 3. On prégénere les philosophes, avec des id et des mutex unlock, temps de miam la dernière fois
- [ ] 4. On créée les threads (avec pair/impaire pour éviter qu'ils crèvent ces chiens)
- [ ] 5. On gère la morning routine de chaque thread/philosopher
- [ ] 6. Gérer la mort, unlock tous les `mutex` et arrêter les threads.

Créer un usleep check death, qui fait `x` `usleep` et checke si le temps qu'il a fini de mager pour la dernière fois est > `time_to_die`.
