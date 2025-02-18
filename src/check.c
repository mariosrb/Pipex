/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 11:59:50 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/02/18 10:46:02 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	check_args(int ac)
{
	if (ac != 5)
	{
		perror("Nombre d'arguments invalide");
		return (1);
	}
	return (0);
}

int	check_files(char *infile, char *outfile, t_pipex *pipex)
{
	pipex->infile = open(infile, O_RDONLY);
	if (pipex->infile == -1)
		perror("Error opening infile");
	pipex->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		perror("Error opening outfile");
	if (pipex->infile == -1 || pipex->outfile == -1)
		return (1);
	return (0);
}

char	*check_direct_path(char *cmd)
{
	char	*new_cmd;
	char	*path;

	new_cmd = cmd;
	while (*new_cmd)
	{
		if (*new_cmd == '/')
		{
			if (access(cmd, F_OK | X_OK) == 0)
			{
				path = ft_strdup(cmd);
				if (!path)
					return (NULL);
				return (path);
			}
			return (NULL);
		}
		new_cmd++;
	}
	return (NULL);
}
