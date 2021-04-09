# minishell with flmarsil

First 42's team project.

Shell allow people to communicate with kernel (action with CPU MEMORY and DEVICE) through the terminal. Kernel + Shell + some programs = UNIX OS.

In computing, a shell is a computer program which exposes an operating system's services to a human user or other program. In general, operating system shells use either a command-line interface (CLI) or graphical user interface (GUI), depending on a computer's role and particular operation. It is named a shell because it is the outermost layer around the operating system.

Command-line shells require the user to be familiar with commands and their calling syntax, and to understand concepts about the shell-specific scripting language (for example, bash).

Graphical shells place a low burden on beginning computer users, and are characterized as being easy to use. Since they also come with certain disadvantages, most GUI-enabled operating systems also provide CLI shells.

We code a MINIshell, which is a simplified shell. See the correction below to see which case we handle.

Some ressources
Explication du code source	overall	https://developpaper.com/shellbash-scripting-seven-source-code-analysis/
what is env var 	env	https://www.youtube.com/watch?v=ADh_OFBfdEE
how bash scripting works	bash	https://www.youtube.com/watch?v=4-hw6DPBlsw&ab_channel=tutoriaLinux,https://www.youtube.com/watch?v=MYWvVgIL_Ys&ab_channel=tutoriaLinux
Creating pipes in C	pipes	https://tldp.org/LDP/lpg/node11.html
Pipe tutorial youtube	pipes	https://www.youtube.com/watch?v=uHH7nHkgZ4w&ab_channel=holidaylvr
propagate signals to child	signals	https://linuxconfig.org/how-to-propagate-a-signal-to-child-processes-from-a-bash-script
ctrl D EOF	shortcuts	https://www.howtogeek.com/howto/ubuntu/keyboard-shortcuts-for-bash-command-shell-for-ubuntu-debian-suse-redhat-linux-etc/
check exit code	$?	https://bencane.com/2014/09/02/understanding-exit-codes-and-how-to-use-them-in-bash-scripts/
explication francaise de dup	dup	https://www.cyril-rabat.fr/articles/index.php?article=32

Basic correction
- [ ]  Commande simple
- [ ]  Exécutez une commande simple avec un PATH absolu tel que /bin/ls ou n’importe quelle autre commande sans option
- [ ]  Arguments
- [ ]  Exécutez une commande simple avec un PATH absolu tel que /bin/ls ou n’importe quelle autre commande, avec option mais sans ‘’ ni “”
- [ ]  Répetez plusieurs fois avec différentes commandes & arguments.
- [ ]  echo
- [ ]  Lancez la commande “echo” avec et sans argument ou options
- [ ]  Répetez plusieurs fois avec différents arguments
- [ ]  exit
    - [ ]  Lancez la commande “exit” avec et sans arguments
    - [ ]  Répetez plusieurs fois avec différents arguments
    - [ ]  N’oubliez pas de relancer le minishell
- [ ]  Valeur de retour d’un processus
- [ ]  Exécutez des commandes simple avec un PATH absolu tel que /bin/ls ou n’importe quelle autre commande avec argument mais sans ‘’ ni “”, puis lancez “echo $?”
- [ ]  Vérifiez la valeur affichée. Vous pouvez le refaire dans bash et comparer.
- [ ]  Répetez plusieurs fois avec différentes commandes et arguments, utilisez des commandes qui ne fonctionnent pas telles que ‘/bin/ls fichiernul’
- [ ]  Point virgule
- [ ]  Exécutez plusieurs commandes simple avec un PATH absolu avec argument, mais séparez les par des ‘;’
- [ ]  Répetez plusieurs fois avec des commandes différentes, n’oubliez pas de tester avec et sans espaces autour du ‘;’ colons
- [ ]  Signaux
- [ ]  Essayez ctrl-C dans un prompt vide
- [ ]  Essayez ctrl-\ dans un prompt vide
- [ ]  Essayez ctrl-D dans un prompt vide
- [ ]  Essayez ctrl-C dans un prompt après que vous ayiez écrit des choses
- [ ]  Essayez ctrl-D dans un prompt après que vous ayiez écrit des choses
- [ ]  Essayez ctrl-\ dans un prompt après que vous ayiez écrit des choses
- [ ]  Essayez ctrl-C après avoir lancé une commande bloquante, comme cat ou grep sans argument
- [ ]  Essayez ctrl-\ après avoir lancé une commande bloquante, comme cat ou grep sans argument
- [ ]  Essayez ctrl-D après avoir lancé une commande bloquante, comme cat ou grep sans argument
- [ ]  Répetez plusieurs fois en utilisant des commandes différentes
- [ ]  Guillemets
- [ ]  Exécutez une commande simple avec un PATH absolu avec argument, mais cette fois utilisez des guillemets (Rajoutez des ‘;’ et des espaces dans les guillemets)
- [ ]  Utilisez des arguments vides et des ‘\’
- [ ]  N’essayez pas des lignes multiples
- [ ]  env
- [ ]  Vérifiez qu’env vous affiche les bonnes variables d’environnement
- [ ]  export
- [ ]  Exportez des variables d’environnement, nouvelles et remplacez les anciennes
- [ ]  Vérifiez le résultat avec env
- [ ]  unset
- [ ]  Exportez des variables d’environnement, nouvelles et remplacez les anciennes
- [ ]  Utilisez “unset” pour en retirer
- [ ]  Vérifiez le résultat avec env
- [ ]  Variables d’environnement
- [ ]  Exécutez echo avec des variables “$” en argument
- [ ]  Vérifiez que les guillemets autour des $variable fonctionnent correctement (comme dans bash)
- [ ]  cd
- [ ]  Utiliez la commande cd pour vous déplacer dans l’arborescence et utilisez /bin/ls pour vérifier que vous êtes dans le bon dossier
- [ ]  Répetez plusieurs fois avec des cd qui fonctionnent et qui ne fonctionnent pas
- [ ]  Essayez ‘.’ et ‘..’ en argument
- [ ]  pwd
- [ ]  Utilisez la commande ‘pwd’, avec et sans argument
- [ ]  Répetez plusieurs fois dans divers dossiers
- [ ]  Essayez ‘.’ et ‘..’ en argument
- [ ]  PATH relatif
- [ ]  Exécutez des commandes en utilisant un PATH relatif
- [ ]  Répetez plusieurs fois dans d’autrses dossier avec un PATH relatif complexe (beaucoup de ..)
- [ ]  PATH d’environnement
- [ ]  Exécutez des commandes mais sans PATH (ls, wc, awk, etc...)
- [ ]  Retirez le $PATH et vérifiez si ca fonctionne toujours
- [ ]  Mettez plusieurs dossiers à PATH (directory1:directory2) et vérifiez que les dossiers sont appellés de gauche à droite
- [ ]  Simple Quotes
- [ ]  Exécutez des commandes avec des simple quote en argument
- [ ]  Essayez des arguments vides
- [ ]  Essayez des variables d’environnement, des espaces, des ‘;’ dans les quotes
- [ ]  Redirection
- [ ]  Exécutez des commandes avec les redirections < et/ou >
- [ ]  Répetez plusieurs fois avec différentes commandes et arguments, et remplacez parfois > par >>
- [ ]  Vérifiez si plusieurs instances de la même redirections échouent
- [ ]  Pipes
- [ ]  Exécutez des commandes avec pipes telles que ‘cat file | grep bla | more’
- [ ]  Répetez plusieurs fois avec différentes commandes et arguments
- [ ]  Essayez des commandes qui échouent telles que ‘ls fichiernul | grep bla | more’
- [ ]  Mixez des pipes et des redirections
- [ ]  Soyons fous
- [ ]  Exécutez des commandes qui ne fonctionnent pas telles que ‘dskdskdksd’ et vérifiez que tout fonctionne comme prévu
- [ ]  Essayez des commandes vraiment, vraiment longues avec des tonnes d’arguments
- [ ]  Amusez vous avec ce superbe minishell et profitez-en

- [ ]  Bonus
- [ ]  Les bonus ne seront abordés que si votre partie obligatoire est excellente. Cela signifie que vous devez compléter la partie obligatoire, du début à la fin, que votre gestion d’erreur doit être parfaite, même dans des situations tordues. Si tous les points ne sont pas attribués pendant cette soutenance, aucun point ne sera comptabilisé dans les bonus.
- [ ]  Redirection <<
- [ ]  Vérifiez que << fonctionne correctement
- [ ]  Édition de ligne
- [ ]  Peut-on déplacer le curseur à gauche et à droite et éditer la ligne en ajoutant/supprimant des caractère au curseur
- [ ]  Peut-on naviguer dans l’historique
- [ ]  Peut-on copier/couper et coller tout ou une partie de ligne en utilisant une séquence de touches
- [ ]  Peut-on se déplacer de mot en mot en utilisant ctrl+gauche et ctrl+droite
- [ ]  Peut-on utiliser home et end pour aller au début/à la fin de la ligne
- [ ]  Peut-on écrire et éditer une commande multi-lignes
- [ ]  Rate it from 0 (failed) through 5 (excellent)
- [ ]  Et, Ou
- [ ]  Utilisez &&, || et des parenthèses dans une commande et vérifiez que ca fonctionne
- [ ]  Chaque flag valide rapporte 1
- [ ]  Si tous les flags marchent rajoutez 1
- [ ]  WildCard
- [ ]  Utilisez des wildcards en argument
- [ ]  Essayez par exemple */*
- [ ]  Testez tout types d’interactions
