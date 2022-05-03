# Minishell
## To-do list globale
- [x] Faire un garbage collector
- [ ] Réorganiser la structure du projet
- [x] Faire un concaténeur
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
- `readline (const char *prompt)`: Readline lit une ligne du terminal et la retourne en utilisant prompt comme un prompt. La ligne retournée est malloc. Il y a plein de features sur les raccourcis etc, faudra bien en profiter et les gérer.
À voir comment aussi comment intégrer la bonne librairie.
- `rl_clear_history(void)`: rl_clear_history supprime toutes les entrées de l'historique
- `rl_on_new_line(void)`: rl_on_new_line indique aux autre fonctions que l'on est passé sur une autre ligne vide
- `rl_replace_line(const char *text, int clear_undo)`:
- `rl_redisplay`:
- `add_history(const char *string)`: add_history ajoute une entrée a la fin de l'historique. Si const char *string n'est pas set, lentrée sera null
- `printf`, `malloc`, `free`, `write`: On les connait bien, osef.
- `access(const char *pathname, int mode)`: access permet de verifier si le path d'entrée est accessible. Renvoit 0 si le path est accessible et -1 en cas d'erreur (l'erreur est stockée dans errno)
- `read(int fd, void *buf, size_t count)`: read lit size_t count octets stockés dans buf du fd spécifié. La fonction renvoit -1 si elle echoue (errno contient le code d'erreur), elle renvoit le nombre d'octets lus (0 si elle est arrivée a la fin du fichier). La fonctione renvoit un nombre < 0 dans certains cas si elle est arrivée a la fin du ficher, si la lecture se fait depuis un pipe ou le terminal ou alors si read() est interompue par un signal
- `close(int fd)`: close ferme le fd spécifié (la référence au fichier ne sera plus accessible). La fonctione renvoit 0 si aucunes erreurs, au quel cas elle renvera -1 (errno stockera l'erreur)
- `fork(void)`: fork créer un nouveau processus en clonant le processus actuel. Le processus céer est referencé comme le processus fils, le processus cloné comme le parent. En cas de reussite la fonction renvoit le PID du processus fils. Sinon elle renvoit -1, errno stockera l'erreur et le processus fils ne sera pas créer
- `wait(int *status)`: wait suspend l'execution du precessus appelant jusqu'a ce qu'un de ses processus fils se termine (equivaut a  waitpid(-1, &status, 0))
- `waitpid(pid_t pid, int *status, int options)`: waitpid suspend l'execution du precessus appelant jusqu'a ce aue le processus fils correspondant au pid se termine
pid_t pid peut prendre:

  - < -1 attendre la fin de n'importe lequel des processus fils dont le GID du processus est égal à la valeur absolue de pid

  - -1 attendre n'importe lequel des processus fils

  - 0 attendre n'importe lequel des processus fils dont le GID du processus est égal à celui du processus appelant

  - \> 0 attendre n'importe lequel des processus fils dont le PID est égal à pid
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
