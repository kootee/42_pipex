/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:22:48 by ktoivola          #+#    #+#             */
/*   Updated: 2024/02/20 10:11:23 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"

# define EXIT_FILE_OPEN_ERROR 3
# define EXIT_FILE_READ_ERROR 4
# define EXIT_PIPE_ERROR 5
# define EXIT_EXEC_ERROR 6
# define EXIT_MALLOC_FAIL 6
# define EXIT_FORK_ERROR 7
# define EXIT_CMD_NOT_FOUND 8
# define EXIT_ARG_COUNT 22

typedef struct s_pipex
{
	int		pipe[2];
	char	**env_paths;
	char	**cmd_args;
	int		cmd_count;
}	t_pipex;

int		main(int argc, char **argv, char **envp);
void	ft_init_pipex(t_pipex *pipex_args, int argc);
char	*ft_get_env_paths(t_pipex *pipex_args, char **cmds);
void	close_all_pipes(t_pipex *pipex_args);
void	ft_free_strs(char **ptrs_to_free);
char	**ft_parse_commands(char *cmds);

#endif
