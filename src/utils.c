/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:28:24 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/02/26 12:59:24 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	init_cmd(t_pipex *pipex, char *cmd1, char *cmd2)
{
	init_all(pipex);
	pipex->cmd1_args = ft_split(cmd1, ' ');
	pipex->cmd2_args = ft_split(cmd2, ' ');
	if (!pipex->cmd1_args || !pipex->cmd2_args)
		return (handle_split_error(pipex));
	if (is_empty_cmd(pipex->cmd1_args[0]) || is_empty_cmd(pipex->cmd2_args[0]))
		return (handle_empty_cmd(pipex));
	pipex->cmd1_path = get_cmd_path(pipex->cmd1_args[0], pipex->env);
	pipex->cmd2_path = get_cmd_path(pipex->cmd2_args[0], pipex->env);
	if (!pipex->cmd1_path || !pipex->cmd2_path)
		return (handle_path_error(pipex));
	return (0);
}

int	parent_cleanup(t_pipex *pipex, int id1, int id2)
{
	int	status1;
	int	status2;

	close(pipex->pipe_fd[0]);
	close(pipex->pipe_fd[1]);
	waitpid(id1, &status1, 0);
	waitpid(id2, &status2, 0);
	free_pipex(pipex);
	if (WIFEXITED(status1))
		return (WEXITSTATUS(status1));
	return (ERR_GENERAL);
}

void	free_cleanup(t_pipex *pipex)
{
	free_matrice(pipex->cmd1_args);
	free_matrice(pipex->cmd2_args);
	if (pipex->cmd1_path)
		free(pipex->cmd1_path);
	if (pipex->cmd2_path)
		free(pipex->cmd2_path);
}

void	free_matrice(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	free_pipex(t_pipex *pipex)
{
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
	if (pipex->pipe_fd[0] >= 0)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] >= 0)
		close(pipex->pipe_fd[1]);
	if (pipex->cmd1_args)
		free_matrice(pipex->cmd1_args);
	if (pipex->cmd2_args)
		free_matrice(pipex->cmd2_args);
	if (pipex->cmd1_path)
		free(pipex->cmd1_path);
	if (pipex->cmd2_path)
		free(pipex->cmd2_path);
}
