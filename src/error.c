/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:15:33 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/02/26 12:59:33 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	check_cmd_errors(char *cmd_path, char *cmd_name)
{
	if (!cmd_path)
	{
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (ERR_CMD_NOT_FOUND);
	}
	if (access(cmd_path, X_OK) == -1)
	{
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (ERR_CMD_NOT_EXECUTABLE);
	}
	return (0);
}

int	handle_split_error(t_pipex *pipex)
{
	if (pipex->cmd1_args)
		free_matrice(pipex->cmd1_args);
	if (pipex->cmd2_args)
		free_matrice(pipex->cmd2_args);
	return (1);
}

int	handle_empty_cmd(t_pipex *pipex)
{
	free_matrice(pipex->cmd1_args);
	free_matrice(pipex->cmd2_args);
	ft_putstr_fd("Command not found\n", 2);
	return (127);
}

int	handle_path_error(t_pipex *pipex)
{
	free_cleanup(pipex);
	ft_putstr_fd("Command not found\n", 2);
	return (127);
}
