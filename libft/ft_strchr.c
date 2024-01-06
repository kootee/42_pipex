/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:33:23 by ktoivola          #+#    #+#             */
/*   Updated: 2023/11/18 15:39:55 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	src_chr;

	src_chr = c;
	if (src_chr == 0)
		return ((char *)(s + ft_strlen(s)));
	while (*s || src_chr == 0)
	{
		if (*s == src_chr)
			return ((char *)s);
		s++;
	}
	return (0);
}
