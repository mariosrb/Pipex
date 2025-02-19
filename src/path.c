/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:28:22 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/02/19 13:01:11 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		final_path = create_cmd_path(paths[i], cmd);
		if (access(final_path, F_OK | X_OK) == 0)
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
