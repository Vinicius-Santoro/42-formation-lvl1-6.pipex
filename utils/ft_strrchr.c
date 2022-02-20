/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnazioze <vnazioze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 01:13:55 by vnazioze          #+#    #+#             */
/*   Updated: 2022/02/19 01:13:58 by vnazioze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strrchr(const char *string, int c)
{
	size_t	lenght;

	lenght = ft_strlen(string) + 1;
	while (lenght--)
	{
		if (string[lenght] == (unsigned char)c)
			return ((char *) string + lenght);
	}
	return (NULL);
}
