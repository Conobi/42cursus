# Minishell
## To-do list globale
- [x] Faire un garbage collector
- [ ] Réorganiser la structure du projet
- [x] Faire un concaténeur
- [x] Faire un Makefile cool comme Lucas
- [ ] Trouver un moyen de gérer/afficher les erreurs
## To-do list Théo
- [ ] Capter tous les types de bidules existants (heredocs, redirections, pipe)
- [ ] Trouver un moyen de les séparer
- [ ] Créer un header avec des tags stylés
- [ ] Créer un afficheur de découpage de commande
- [ ] Lire des ressources sur les signaux
- [ ] Tracker les `$truc` et leur merdier associé
- [ ] Rajouter une value builtins pour la commande

## To-do list Arthur
- [ ] cd multi path parsing
- [x] cd Permission denied in /Users/user/Desktop fix
- [ ] check cd perms with symbolic links
- [ ] return codes with wait pid
- [ ] Verif all return error codes in fork

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
- `wait3(int *status, int options, struct rusage *rusage) & wait4(pid_t pid, int *status, int options, struct rusage *rusage)`: retournent également des informations sur l’utilisation des ressources par le processus fils dans la structure pointée par rusage. wait3() attend n’importe quel fils, et wait4() peut être utilisé pour sélectionner un ou des fils spécifique(s) à attendre
- `signal(int signalId, __sighandler_t handler)`: signal permet de définir le gestionnaire de signal à invoquer en cas de réception d'un signal particulier
- `sigaction(int signum, const struct sigaction *act, struct sigaction *oldact)`: sigaction() sert à modifier l'action effectuée par un processus à la réception d'un signal spécifique. signum indique le signal concerné, à l'exception de SIGKILL et SIGSTOP. Si act est non nul, la nouvelle action pour le signal signum est définie par act. Si oldact est non nul, l'ancienne action est sauvegardée dans oldact
- `sigemptyset(sigset_t *set)`: sigemptyset() vide l'ensemble de signaux fourni par set, tous les signaux étant exclus de cet ensemble
- `sigaddset(sigset_t *set, int signum)`: sigaddset() ajoute le signal signum de l'ensemble set.
- `kill(pid_t pid, int sig)`: kill() peut être utilisé pour envoyer n'importe quel signal à n'importe quel processus ou groupe de processus
  - Si pid est positif, le signal sig est envoyé au processus dont l'identifiant est indiqué par pid.

  - Si pid vaut zéro, alors le signal sig est envoyé à tous les processus appartenant au même groupe que le processus appelant

  - Si pid vaut -1, alors le signal sig est envoyé à tous les processus pour lesquels le processus appelant à la permission d'envoyer des signaux, sauf celui de PID 1 (init), mais voir plus bas

  - Si pid est inférieur à -1, alors le signal sig est envoyé à tous les processus du groupe dont l'identifiant est -pid

  - Si sig vaut 0, aucun signal n'est envoyé mais les conditions d'erreur sont vérifiées ; cela peut être utilisé pour vérifier l'existence d'un identifiant de processus ou de groupe de processus
- `exit(int returnCode)`: exit() permet de mettre fin au programme en spécifiant un code de retour.
- `getcwd(char *buf, size_t size)`: getcwd() copie le chemin d'accès absolu du répertoire de travail courant dans la chaîne pointée par buf, qui est de longueur size
- `chdir(const char *path)`: chdir() permet de changer le répertoire de travail courant.
- `stat(const char *path, struct stat *buf)`: stat() récupère l'état du fichier pointé par path et remplit buf
- `lstat(const char *path, struct stat *buf)`: lstat() est identique à stat(), sauf que si path est un lien symbolique, il donne l'état du lien plutôt que celui du fichier visé
- `fstat(int fd, struct stat *buf)`: fstat() est identique à stat(), sauf que le fichier ouvert est pointé par le descripteur fd, obtenu avec open()
- `unlink(const char *pathname)`:
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
