#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>


#include "./libft/libft.h"

 /*
 Objectif :

Rediriger la sortie standard (stdout) pour écrire dans un fichier.
Consigne :

    Crée un programme qui :
        Ouvre un fichier en écriture (par exemple, "output.txt").
        Redirige la sortie standard (stdout) vers ce fichier.
        Écrit une phrase avec printf() qui ira dans le fichier.
    Ferme correctement tous les descripteurs.

Indice :

    Utilise dup2(fd, STDOUT_FILENO) pour rediriger stdout vers le fichier ouvert.
    N'oublie pas de vérifier si open() ou dup2() retourne une erreur.*/


int main (int ac, char **av)
{
	// int execve(const char *pathname, char *const argv[], char *const envp[]);
	if (ac == 2)
	{
		perror("Nombres darguments invalide !");
		return 0;
	}

	char	*path = "/bin/ls";
	char	**args = malloc(sizeof(char *) * ac);
	if (!args)
		return (1);
	int		i = 1;

	while (av[i])
	{
		args[i - 1] = av[i];
		i++;
	}
	args[i - 1] = NULL;
	char	*env[] = {NULL};
	i = 0;
	
	if (execve(path, args, env) == -1)
	{
		perror("execve failed");
		return 1;
	}
	printf("si execve reussi pas print ici \n");
	return (0);
}

// int main (int ac, char **av)
// {
// 	int fd = open("Resultats.txt", O_WRONLY | O_CREAT, 0777);
// 	if (fd == -1)
// 		return (1);
// 	dup2(fd, 1);
// 	printf("test pour voir si jai reusi\n");
// 	close(fd);
// 	return (0);
// }

// int	main(int argc, char **argv)
// {
// 	int	pid = fork();
// 	if (pid == -1)
// 		return 1;
	
// 	if (pid == 0)
// 	{
// 		// child process
// 		int err = execlp("ping", "ping", "-c", "1", "google.com", NULL);
// 		if (err == -1)
// 		{
// 			printf("could not find prog to execute\n");
// 			return (0);
// 		}
// 	}
// 	else
// 	{
// 		// process parent
// 		int wstatus;
// 		wait(&wstatus);
// 		if (WIFEXITED(wstatus))
// 		{
// 			int statusCode = WEXITSTATUS(wstatus);
// 			if (statusCode == 0)
// 				printf("Succes\n");
// 			else
// 				printf("Failure\n");
// 		}

// 		printf("Post processing\n");
// 	}

// 	return (0);
// }
