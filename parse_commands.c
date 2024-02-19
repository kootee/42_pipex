/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:55:35 by ktoivola          #+#    #+#             */
/*   Updated: 2024/02/19 18:12:59 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* awk '{count++} END {print count}' */

static int	ft_count_args(char *cmds)
{
	int	arg_count;
	int	i;

	i = 0;
	arg_count = 0;
	while (cmds[i])
	{
		if (cmds[i] == ' ')
		{
			arg_count++;
			while (cmds[i] && cmds[i] == ' ') // or i + 1
				i++;
		}
		if (cmds[i] == '\"' || cmds[i] == '\'')
		{
			arg_count++;
			i++;
			while (cmds[i] && (cmds[i] == '\"' || cmds[i] == '\''))
				i++;
			while (cmds[i] && (cmds[i] != '\"' && cmds[i] != '\''))
				i++;
			//ft_check_if_end();
		}
		if (cmds[i]) 
			i++;
	}
	if (cmds[i - 1] != '\"' && cmds[i -1] != '\'')
		arg_count++;
	return (arg_count);
}

char	**ft_parse_commands(char *cmds)
{
	char **parsed_cmds;
	int	arg_count;
	int	i;
	int j;
	int k;
	
	arg_count = ft_count_args(cmds);
	parsed_cmds = malloc(sizeof(char *) * (arg_count + 1)); //protect
	i = 0;
	j = 0;
	k = 0;
	while (k < arg_count && cmds[i + j])
	{
		if (cmds[i + j] == ' ')
		{
			parsed_cmds[k] = ft_substr(cmds, j, i);
			while (cmds[i + j + 1] == ' ')
				i++;
			k++;
			j += i + 1; // i + 1
			i = 0;
		}
		if (cmds[j + i] == '\"' || cmds[j + i] == '\'')
		{
			i++;
			while (cmds[j + i] != '\"' && cmds[j + i] != '\'')
				i++;
			parsed_cmds[k] = ft_substr(cmds, ++j, i - 1);
			k++;
			j = i;
			i = 0;
		}
		i++;
	}
	if (k < arg_count)
		parsed_cmds[k] = ft_substr(cmds, j, i);
	parsed_cmds[arg_count] = NULL;
	return (parsed_cmds);
}
