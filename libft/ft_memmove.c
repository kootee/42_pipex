/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:54:20 by ktoivola          #+#    #+#             */
/*   Updated: 2023/11/15 09:58:18 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dest_ptr;
	unsigned char		*tmp_src;

	if (dst == src || len == 0)
		return (dst);
	if (dst < src)
	{
		dest_ptr = (unsigned char *)dst;
		tmp_src = (unsigned char *)src;
		while (len--)
			*dest_ptr++ = *tmp_src++;
	}
	else
	{
		dest_ptr = (unsigned char *)dst + (len - 1);
		tmp_src = (unsigned char *)src + (len - 1);
		while (len--)
			*dest_ptr-- = *tmp_src--;
	}
	return (dst);
}
