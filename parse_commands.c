/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:55:35 by ktoivola          #+#    #+#             */
/*   Updated: 2024/01/14 15:53:48 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* awk '{count++} END {print count}' */

char	**ft_parse_commands(char *cmds)
{
	char **parsed_cmds;
	int	arg_count;
	int	i;
	int j;
	int k;

	i = 0;
	arg_count = 0;
	char c;
	while (cmds[i])
	{
		if (cmds[i] == ' ')
			arg_count++;
		else if (cmds[i] == '\"' || cmds[i] == '\'')
		{
			arg_count++;
			i++;
			while (cmds[i] && (cmds[i] != '\"' && cmds[i] != '\''))
			{
				c = cmds[i];
				i++;
			}
		}
		printf("\n");
		i++;
	}
	if (cmds[i - 1] != '\"' && cmds[i -1] != '\'')
		arg_count++;
	parsed_cmds = malloc(sizeof(char *) * (arg_count + 1)); //protect
	k = ft_strlen(cmds);
	i = 0;
	j = 0;
	k = 0;
	while (cmds[i] && k < arg_count)
	{
		if (cmds[i] == ' ')
		{
			parsed_cmds[k] = ft_substr(cmds, j, i);
			printf("parsed cmds[%d] is %s\n", k, parsed_cmds[k]);
			k++;
			j = ++i;
			i = 0;
		}
		if (cmds[j + i] == '\"' || cmds[j + i] == '\'')
		{
			i++;
			while (cmds[j + i] != '\"' && cmds[j + i] != '\'')
			{
				c = cmds[j + i];
				i++;
			}
			parsed_cmds[k] = ft_substr(cmds, ++j, i - 1);
			printf("parsed cmds[%d] is %s\n", k, parsed_cmds[k]);
			k++;
			j = i;
		}
		i++;
	}
	return (parsed_cmds);
}
