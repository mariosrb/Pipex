/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:59:50 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/02/26 10:52:53 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	check_args(int ac)
{
	if (ac != 5)
	{
		ft_putstr_fd("Invalid number of arguments", 2);
		return (1);
	}
	return (0);
}

int	check_files(char *infile, char *outfile, t_pipex *pipex)
{
	pipex->infile = open(infile, O_RDONLY);
	if (pipex->infile == -1)
	{
		perror(infile);
		return (1);
	}
	pipex->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
	{
		perror(outfile);
		return (1);
	}
	return (0);
}

void	init_all(t_pipex *pipex)
{
	pipex->pipe_fd[0] = -1;
	pipex->pipe_fd[1] = -1;
	pipex->cmd1_args = NULL;
	pipex->cmd2_args = NULL;
	pipex->cmd1_path = NULL;
	pipex->cmd2_args = NULL;
}
