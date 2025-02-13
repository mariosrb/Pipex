/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:09:38 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/02/13 17:37:38 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

// "Créez un programme qui :

/*Prend deux arguments : 
1 -- > une commande (comme 'ls -l') 
2 -- > un fichier de sortie
Trouve le path complet de la commande avec votre nouvelle fonction
Exécute la commande avec execve et redirige la sortie vers le fichier"*/

#include "include/pipex.h"

int main (int ac, char **av, char** env)
{
	char	**cmd;
	char	*cmd_path;
	//int 	pipefd[2];
	int		id1;
	int		file;
	
	///////////////////ON CHERCHER LE PATH///////////////////////////
	cmd = ft_split(av[1], ' ');
	if (!cmd)
		return (1);
	cmd_path = find_path(cmd[0], env);
	if (!cmd_path)
	{
		free_matrice(cmd);
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
		file = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (file == -1)
		{
			perror("Erreur lors de l'ouverture du ficher");
			exit(EXIT_FAILURE);
		}
		if (dup2(file, STDOUT_FILENO) == -1)
		{
			perror("Erreur lors de la redirection");
			close(file);
			exit(EXIT_FAILURE);
		}
		close(file);
		if (execve(cmd_path, cmd, env) == -1)
		{
			perror("Erreur dans l'execution de la commande");
			free(cmd_path);
			free_matrice(cmd);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int	status;
		waitpid(id1, &status, 0);
	}
	free_matrice(cmd);
	free(cmd_path);
	return (0);
}
