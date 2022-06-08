# Les arguments et redirections
Toutes les redirections prennent qu'un argument.
Les redirections peuvent être partout. Dans n'importe quel sens.
`>` : Redirection de sortie. Prend en argument un file.
`<` : Redirection d'entrée. Prend en argument un file. Toute entrée sera écrasée par la suivante. On est obligés de toutes les parser pour gérer correctement les erreurs.
`>>` : Redirection append. Comme celle d'entrée mais on ajoute à la fin du fichier
`<<` : Heredoc classique, son argument est le `delimiter`


## Globalement
- 1. On split-quote en dry
- 2. On split-quote avec les bonnes allocs

- 3. On compte le nombre de redirections de chaque type, on alloc le tableau
- 4. On remplit chaque tableau de redirections. Si le prochain token est '\0' ou une redirection, on remplit avec un '\0'
- 5. Pour chaque entrée avec pas de redirection avant, on le compte
- 6. Pour chaque entrée avec pas de redirection avant, on l'ajoute et on enlève les split.

`int count_redirect(char **tab, char *delimiter)`
count_redirect(split_quoted, ">>");

## token_count:
1. On trim
2. On compte, et on passe les non space tant que != \0
3. On passe les espaces tant que != \0
4. Si cur est une quote et qu'avant ct un espace, on compte +1
5. Si cur est une quote, on switch `set_quote_bool`
6. On passe tout en faisant un `set_quote_bool` tant que les bool sont pas à -1


