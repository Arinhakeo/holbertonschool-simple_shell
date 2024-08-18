# Simple Shell

Ce projet est une implémentation simple d'un interpréteur de commandes UNIX. Le shell permet de :

- Afficher une invite (`#cisfun$`) et attendre une commande de l'utilisateur.
- Exécuter des commandes simples sans arguments.
- Afficher un message d'erreur si la commande n'est pas trouvée.
- Gérer la sortie avec `Ctrl+D` ou la commande `exit`.

## Compilation

Pour compiler le projet, utilisez la commande suivante :

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
