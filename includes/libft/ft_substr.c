/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:13:07 by oufisaou          #+#    #+#             */
/*   Updated: 2023/04/14 07:03:08 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ret_right_size(char const *s, unsigned int start, size_t len)
{
	size_t	size;

	if (start + len < ft_strlen(s))
		size = len + 1;
	else
		size = ft_strlen(s) - start + 1;
	return (size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*a;
	size_t	i;
	size_t	j;
	size_t	size;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		a = malloc(sizeof(char) * 1);
		a[0] = 0;
		return (a);
	}
	size = ret_right_size(s, start, len);
	a = (char *)malloc(sizeof(char) * (size));
	if (!a)
		return (NULL);
	i = 0;
	j = start;
	while (i < size - 1 && s[j])
		a[i++] = s[j++];
	a[i] = '\0';
	return (a);
}
