/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 01:13:21 by vnazioze          #+#    #+#             */
/*   Updated: 2022/02/19 01:13:23 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	*ft_memset(void *s, int c, size_t lenght)
{
	size_t	i;
	char	*buff;

	i = 0;
	buff = s;
	while (i < lenght)
		*(buff + i++) = c;
	return (s);
}

static void	ft_bzero(void *s, size_t n)
{
	ft_memset (s, 0, n);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
