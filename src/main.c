/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:28:20 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/02/17 12:09:46 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	init_cmd(t_pipex *pipex, char *cmd1, char *cmd2)
{
	pipex->cmd1_args = ft_split(cmd1, ' ');
	pipex->cmd2_args = ft_split(cmd2, ' ');
	if (!pipex->cmd1_args || !pipex->cmd2_args)
	{
		if (pipex->cmd1_args)
			free_matrice(pipex->cmd1_args);
		if (pipex->cmd2_args)
			free_matrice(pipex->cmd2_args);
		return (1);
	}
	pipex->cmd1_path = find_path(pipex->cmd1_args[0], pipex->env);
	pipex->cmd2_path = find_path(pipex->cmd2_args[0], pipex->env);
	if (!pipex->cmd1_path || !pipex->cmd2_path)
	{
		free_matrice(pipex->cmd1_args);
		free_matrice(pipex->cmd2_args);
		if (pipex->cmd1_path)
			free(pipex->cmd1_path);
		if(pipex->cmd2_path)
			free(pipex->cmd2_path);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;
	int		id1;
	int		id2;
	
	if (!env || !*env)
		return (1);
	if (check_args(ac)) //verfication 
		return (1);
	if (check_files(av[1], av[4], &pipex))
		return (1);
	pipex.env = env;
	if (init_cmd(&pipex, av[2], av[3]))
		return (1);
	if (pipe(pipex.pipe_fd) == -1)
	{
		perror("Pipe creation failed");
		return (1);
	}
	
	id1 = fork();
	if (id1 < 0)
	{
		// voir sil faut fermer les pipefd[1, 0];
		free_pipex(&pipex);
		return (1);
	}
	if (id1 == 0)
	{
		close(pipex.pipe_fd[0]);
		if (dup2(pipex.infile, STDIN_FILENO) == -1)
		{
			perror("Erreur lors de la redirection");
			close(pipex.pipe_fd[1]);
			exit(EXIT_FAILURE);
		}
		if (dup2(pipex.pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("Erreur lors de la redirection");
			close(pipex.pipe_fd[1]);
			exit(EXIT_FAILURE);
		}
		close(pipex.pipe_fd[1]);
		if (execve(pipex.cmd1_path, pipex.cmd1_args, env) == -1)
		{
			perror("Erreur lors de l'execution de la commande");
			exit(EXIT_FAILURE);
		}
	}
	id2 = fork();
	if (id2 < 0)
	{
		// voir sil faut fermer les pipefd[1, 0];
		free_pipex(&pipex);
		return (1);
	}	
	if (id2 == 0)
	{
		close(pipex.pipe_fd[1]);
		if (dup2(pipex.pipe_fd[0], STDIN_FILENO) == -1)
		{
			//vori sil faut fermer les piefd
			perror("Erreur lors de la rediretion");
			free_pipex(&pipex);
		}
		if (dup2(pipex.outfile, STDOUT_FILENO) == -1)
		{
			//voir fermer pipefd
			perror("Erreur lors de la redirection");
			exit(EXIT_FAILURE);
		}
		if (execve(pipex.cmd2_path, pipex.cmd2_args, env) == -1)
		{
			perror("Erreur lors de l'execution de la 2eme commande");
			exit(EXIT_FAILURE);
		}
	}
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	waitpid(id1, NULL, 0);
	waitpid(id2, NULL, 0);
	free_pipex(&pipex);
	return (0);
}

