/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:22:48 by ktoivola          #+#    #+#             */
/*   Updated: 2024/02/22 13:53:55 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"

# define EXIT_CMD_NOT_FOUND 127

typedef struct s_pipex
{
	int		pipe[2];
	char	**env_paths;
	char	**cmd_args;
	int		cmd_count;
	int		c[3];
}	t_pipex;

int		main(int argc, char **argv, char **envp);
void	init_pipex(t_pipex *pipex_args, int argc, char **argv, char **envp);
char	*get_env_paths(t_pipex *pipex_args, char **cmds);
void	close_all_pipes(t_pipex *pipex_args);
void	free_strs(char **ptrs_to_free);
char	**parse_commands(char *cmds, t_pipex *pipex_args);

#endif
