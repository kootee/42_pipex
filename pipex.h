/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:22:48 by ktoivola          #+#    #+#             */
/*   Updated: 2024/02/19 16:47:00 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ./pipex f_in.txt "cat" "wc" f_out.txt */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h> //remove
# include "libft/libft.h"

/* Error message constants */
# define EXIT_FILE_OPEN_ERROR 3
# define EXIT_FILE_READ_ERROR 4
# define EXIT_PIPE_ERROR 5
# define EXIT_EXEC_ERROR 6
# define EXIT_MALLOC_FAIL 7
# define EXIT_FORK_ERROR 8

typedef struct s_pipex
{
	int	pipe[2]; //add second array for bonus part [i][2]
	int here_doc;
	int is_invalid_infile;
	char **env_paths;
	char **cmd_args;
	int	cmd_count;
} t_pipex;

int		main(int argc, char **argv, char **envp);
void	ft_init_pipex(t_pipex *pipex_args, int argc);
void	ft_check_args(t_pipex *pipex_args, char **args);
char	*ft_get_env_paths(t_pipex *pipex_args, char **cmds);
void	close_all_pipes(t_pipex *pipex_args);
void	ft_free_strs(char **ptrs_to_free);
char	**ft_parse_commands(char *cmds);

#endif
