/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:46:10 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/02/18 10:47:29 by mdodevsk         ###   ########.fr       */
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

// check
int		check_args(int ac);
int		check_files(char *infile, char *outfile, t_pipex *pipex);
char	*check_direct_path(char *cmd);

// utils
int		init_cmd(t_pipex *pipex, char *cmd1, char *cmd2);
void	parent_cleanup(t_pipex *pipex, int id1, int id2);
void	free_matrice(char **strs);
void	free_pipex(t_pipex *pipex);
void	ft_print(char **strs);
void	free_cleanup(t_pipex *pipex);

#endif