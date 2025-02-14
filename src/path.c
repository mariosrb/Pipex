/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:28:22 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/02/14 14:30:05 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// void	init_cmd(char *cmd_str)

void	ft_print(char **strs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (strs[i] != NULL)
	{
		while (strs[i][j])
		{
			write (1, &strs[i][j], 1);
			j++;
		}
		write (1, "\n", 1);
		i++;
		j = 0;
	}
	if (strs[i] == NULL)
		write (1, "null", 4);
}

static char	*create_cmd_path(char *path, char *cmd)
{
	char	*final;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	final = ft_strjoin(tmp, cmd);
	free(tmp);
	return (final);
}

char	*find_path(char *cmd, char **env)
{
	char	**paths;
	char	*final_path;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		final_path = create_cmd_path(paths[i], cmd);
		if (access(final_path, F_OK) == 0)
		{
			free_matrice(paths);
			return (final_path);
		}
		free(final_path);
		i++;
	}
	free_matrice(paths);
	return (NULL);
}
