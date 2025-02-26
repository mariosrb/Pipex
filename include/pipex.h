/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:46:10 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/02/26 11:55:05 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <time.h>

# define ERR_CMD_NOT_FOUND 127
# define ERR_CMD_NOT_EXECUTABLE 126
# define ERR_GENERAL 1

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd1_args;
	char	**cmd2_args;
	char	**env;
	int		pipe_fd[2];
}	t_pipex;

// parsing
char	*find_path(char *cmd, char **env);

// error
int		handle_split_error(t_pipex *pipex);
int		handle_empty_cmd(t_pipex *pipex);
int		handle_path_error(t_pipex *pipex);

// check
int		check_args(int ac);
int		check_cmd_errors(char *cmd_path, char *cmd_name);
int		check_files(char *infile, char *outfile, t_pipex *pipex);
char	*get_cmd_path(char *cmd, char **env);
char	*check_direct_path(char *cmd);
int		is_empty_cmd(char *cmd);

// utils
int		init_cmd(t_pipex *pipex, char *cmd1, char *cmd2);
int		parent_cleanup(t_pipex *pipex, int id1, int id2);
void	free_matrice(char **strs);
void	free_pipex(t_pipex *pipex);
void	free_cleanup(t_pipex *pipex);
void	init_all(t_pipex *pipex);

#endif