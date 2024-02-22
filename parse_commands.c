/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:55:35 by ktoivola          #+#    #+#             */
/*   Updated: 2024/02/22 13:52:49 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	reset_counters(t_pipex *pipex_args)
{
	pipex_args->c[0] = 0;
	pipex_args->c[1] = 0;
	pipex_args->c[2] = 0;
}

static void	skip_whitespace(char *cmd, int *arg_count, int *i)
{
	(*arg_count)++;
	while (cmd[*i] && cmd[*i] == ' ')
		(*i)++;
}

static void	iterate_cmds(char *cmd, char **parsed_cmds, t_pipex *p)
{
	if (cmd[p->c[0] + p->c[1]] == ' ')
	{
		parsed_cmds[p->c[2]] = ft_substr(cmd, p->c[1], p->c[0]);
		while (cmd[p->c[0] + p->c[1] + 1] == ' ')
			p->c[0]++;
		p->c[2]++;
		p->c[1] += p->c[0] + 1;
		p->c[0] = 0;
	}
	if (cmd[p->c[0] + p->c[1]] == '\"' || cmd[p->c[0] + p->c[1]] == '\'')
	{
		p->c[0]++;
		while (cmd[p->c[1] + p->c[0]] != '\"' && cmd[p->c[1] + p->c[0]] != '\'')
			p->c[0]++;
		parsed_cmds[p->c[2]] = ft_substr(cmd, ++(p->c[1]), p->c[0] - 1);
		p->c[2]++;
		p->c[1] = p->c[0];
		p->c[0] = 0;
	}
}

static int	count_args(char *cmds)
{
	int	arg_count;
	int	i;

	i = 0;
	arg_count = 0;
	while (cmds[i])
	{
		if (cmds[i] == ' ')
			skip_whitespace(cmds, &arg_count, &i);
		if (cmds[i] == '\"' || cmds[i] == '\'')
		{
			arg_count++;
			i++;
			while (cmds[i] && (cmds[i] == '\"' || cmds[i] == '\''))
				i++;
			while (cmds[i] && (cmds[i] != '\"' && cmds[i] != '\''))
				i++;
		}
		if (cmds[i])
			i++;
	}
	if (cmds[i - 1] != '\"' && cmds[i -1] != '\'')
		arg_count++;
	return (arg_count);
}

char	**parse_commands(char *cmds, t_pipex *p)
{
	char	**parsed_cmds;
	int		arg_count;

	arg_count = count_args(cmds);
	parsed_cmds = malloc(sizeof(char *) * (arg_count + 1));
	reset_counters(p);
	if (parsed_cmds == NULL)
		exit(EXIT_FAILURE);
	while (p->c[2] < arg_count && cmds[p->c[0] + p->c[1]])
	{
		iterate_cmds(cmds, parsed_cmds, p);
		p->c[0]++;
	}
	if (p->c[2] < arg_count)
		parsed_cmds[p->c[2]] = ft_substr(cmds, p->c[1], p->c[0]);
	parsed_cmds[arg_count] = NULL;
	return (parsed_cmds);
}
