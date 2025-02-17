/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:28:24 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/02/17 13:16:11 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_matrice(char **strs)
{
	int	i = 0;
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