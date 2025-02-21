/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:15:33 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/02/21 11:34:21 by mdodevsk         ###   ########.fr       */
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
