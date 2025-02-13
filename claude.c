#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#include "include/pipex.h"

int main (int ac, char **av, char **env)
{
	int		pipefd[2];
	char	*cmd_path;
	char	**cmd;
	int		id1;
	int		id2;
	int		file;
	char	*tst[] = {"wc", "-l", NULL};

	cmd = ft_split(av[1], ' ');
	if (!cmd)
		return (1);
	cmd_path = find_path(cmd[0], env);
	if (!cmd_path)
	{
		free_matrice(cmd);
		return (1);
	}

	if (pipe(pipefd) == -1)
	{
		free_matrice(cmd);
		free(cmd_path);
		return (1);
	}

	id1 = fork();
	if (id1 < 0)
	{
		free_matrice(cmd);
		free(cmd_path);
		return (1);
	}
	if (id1 == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("Erreur lors de la redirection");
			close(pipefd[1]);
			exit(EXIT_FAILURE);			
		}
		close(pipefd[1]);
		if (execve(cmd_path, cmd, env) == -1)
		{
			perror("Erreur dans l'execution de la commande");
			free(cmd_path);
			free_matrice(cmd);
			exit(EXIT_FAILURE);
		}	
	}

	// free(cmd_path);
	// free_matrice(cmd);
	// cmd = ft_split(av[2], ' ');
	// if (!cmd)
	// 	return (1);
	// cmd_path = find_path(cmd[0], env);
	// if (!cmd_path)
	// {
	// 	free_matrice(cmd);
	// 	return (1);
	// }
	
	id2 = fork();
	if (id2 < 0)
	{
		free_matrice(cmd);
		free(cmd_path);
		return (1);
	}
	if (id2 == 0)
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
		{
			perror("Erreur lors de la redirection");
			close(pipefd[0]);
			exit(EXIT_FAILURE);	
		}
		close(pipefd[0]);
		if (execve(cmd_path, tst, env) == -1)
		{
			perror("Erreur dans l'execution de la commande");
			free(cmd_path);
			free_matrice(cmd);
			exit(EXIT_FAILURE);
		}	
	}
	waitpid(id1, NULL, 0);
	waitpid(id2, NULL, 0);
	close(pipefd[1]);
	close(pipefd[0]);
	free(cmd_path);
	free_matrice(cmd);
	return (0);
}