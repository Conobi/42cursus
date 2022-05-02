# Minishell
## To-do list globale
- [ ] Faire un garbage collector
- [ ] Réorganiser la structure du projet
- [ ] Faire un concaténeur
- [ ] Faire un Makefile cool comme Lucas
- [ ] Trouver un moyen de gérer/afficher les erreurs
## To-do list Théo
- [ ] Capter tous les types de bidules existants (heredocs, redirections, pipe)
- [ ] Trouver un moyen de les séparer
- [ ] Créer un header avec des tags stylés
- [ ] Créer un afficheur de découpage de commande
- [ ] Lire des ressources sur les signaux
- [ ] Tracker les `$truc` et leur merdier associé

## Glossaire des fonctions
En vrac:
```
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs
```
- `readline (const char *prompt)`: Readline lit une ligne du terminal et la retournem en utilisant prompt comme un prompt. La ligne retournée est malloc. Il y a plein de features sur les raccourcis etc, faudra bien en profiter et les gérer.
À voir comment aussi comment intégrer la bonne librairie.
- `rl_clear_history`:
- `rl_on_new_line`:
- `rl_replace_line`:
- `rl_redisplay`:
- `add_history`:
- `printf`, `malloc`, `free`, `write`: On les connait bien, osef.
- `access`:
- `read`:
- `close`:
- `fork`:
- `wait`:
- `waitpid`:
- `wait3`:
- `wait4`:
- `signal`:
- `sigaction`:
- `sigemptyset`:
- `sigaddset`:
- `kill`:
- `exit`:
- `getcwd`:
- `chdir`:
- `stat`:
- `lstat`:
- `fstat`:
- `unlink`:
- `execve`:
- `dup`:
- `dup2`:
- `pipe`:
- `opendir`:
- `readdir`:
- `closedir`:
- `strerror`:
- `perror`:
- `perror`:
- `isatty`:
- `ttyname`:
- `ttyslot`:
- `ioctl`:
- `getenv`:
- `tcsetattr`:
- `tcgetattr`:
- `tgetent`:
- `tgetflag`:
- `tgetnum`:
- `tgetstr`:
- `tgoto`:
- `tputs`:
