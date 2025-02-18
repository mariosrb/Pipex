/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:28:20 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/02/18 10:45:54 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	setup_pipex(t_pipex *pipex, int ac, char **av, char **env)
{
	if (!env || !*env)
		return (1);
	if (check_args(ac))
		return (1);
	if (check_files(av[1], av[4], pipex))
		return (1);
	pipex->env = env;
	if (init_cmd(pipex, av[2], av[3]))
	{
		free_pipex(pipex);
		return (1);
	}
	if (pipe(pipex->pipe_fd) == -1)
	{
		perror("Pipe creation failed");
		free_pipex(pipex);
		return (1);
	}
	return (0);
}

int	first_child(t_pipex *pipex)
{
	close(pipex->pipe_fd[0]);
	if (dup2(pipex->infile, STDIN_FILENO) == -1)
	{
		close(pipex->pipe_fd[1]);
		perror("Error redirection");
		free_pipex(pipex);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
	{
		close(pipex->pipe_fd[1]);
		perror("Error redirection");
		free_pipex(pipex);
		exit(EXIT_FAILURE);
	}
	close(pipex->pipe_fd[1]);
	if (execve(pipex->cmd1_path, pipex->cmd1_args, pipex->env) == -1)
	{
		perror("Error while execut in first command");
		free_pipex(pipex);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	second_child(t_pipex *pipex)
{
	close(pipex->pipe_fd[1]);
	if (dup2(pipex->pipe_fd[0], STDIN_FILENO) == -1)
	{
		close(pipex->pipe_fd[0]);
		perror("Error redirection");
		free_pipex(pipex);
		exit(EXIT_FAILURE);
	}
	if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
	{
		close(pipex->pipe_fd[0]);
		perror("Error redirection");
		free_pipex(pipex);
		exit(EXIT_FAILURE);
	}
	close(pipex->pipe_fd[0]);
	if (execve(pipex->cmd2_path, pipex->cmd2_args, pipex->env) == -1)
	{
		perror("Error while executing second command");
		free_pipex(pipex);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;
	int		id1;
	int		id2;

	if (setup_pipex(&pipex, ac, av, env))
		return (1);
	id1 = fork();
	if (id1 < 0)
		return (free_pipex(&pipex), perror("Fork failed"), 1);
	if (id1 == 0)
		first_child(&pipex);
	id2 = fork();
	if (id2 < 0)
		return (free_pipex(&pipex), perror("Fork failed"), 1);
	if (id2 == 0)
		second_child(&pipex);
	parent_cleanup(&pipex, id1, id2);
	return (0);
}
