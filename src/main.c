/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:28:20 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/02/14 15:50:28 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	init_cmd(t_pipex *pipex, char *cmd1, char *cmd2)
{
	pipex->cmd1_args = ft_split(cmd1, ' ');
	pipex->cmd2_args = ft_split(cmd2, ' ');
	if (!pipex->cmd1_args || !pipex->cmd2_path)
	{
		if (!pipex->cmd1_args)
			free_matrice(pipex->cmd1_args);
		if (!pipex->cmd2_args)
			free_matrice(pipex->cmd2_args);
		return (1);
	}
	pipex->cmd1_path = find_path(pipex->)
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;
	
	if (check_args(ac)) //verfication 
		return (1);
	if (check_files(av[1], av[4], &pipex))
		return (1);
	pipex.env = env;
	init_cmd(&pipex, av[2], av[3]);

	ft_print(pipex.cmd1_args);

	if (pipe(pipex.pipe_fd) == -1)
	{
		perror("Pipe creation failed");
		return (1);
	}
	close(pipex.infile);
	close(pipex.outfile);
	return (0);
}

