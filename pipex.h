/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:22:48 by ktoivola          #+#    #+#             */
/*   Updated: 2024/01/06 15:16:19 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"

//void	pipex(int argc, char **argv, char **env);
typedef struct s_pipex
{
	int	pipe[2]; //add second array for bonus part [i][2]
	int here_doc;
	int is_invalid_infile;
	char **env_path; //?
	char **cmd_args; //?
	int	cmd_count; // for bonus
} t_pipex;

int		main(int argc, char **argv, char **envp);
void	ft_init_pipex(t_pipex *pipex_args, int argc);
void	ft_check_args(t_pipex *pipex_args, char **args, char **envp);
void	ft_clear_all(t_pipex *pipex_args);

#endif
