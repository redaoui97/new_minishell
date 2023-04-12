/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnabil <rnabil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 02:05:01 by rnabil            #+#    #+#             */
/*   Updated: 2023/04/12 21:51:24 by rnabil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*allocates and copies the 2 strings given in param into the allocated space*/
char	*ft_strjoin_adjusted(char *s1, char *s2)
{
	char	*str;
	int		s1_len;
	int		s2_len;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
		str[s1_len++] = s2[i++];
	str[s1_len] = '\0';
	free(s1);
	s1 = NULL;
	return (str);
}

/*allocates and returns pointer to a substring starting from a specific pos*/
char	*ft_substr_adjusted(char const *s, unsigned int start, size_t len)
{
	char *substr;
	size_t i;

	i = 0;
	if (!s)
		return (NULL);
	if ((int)start >= (int)ft_strlen((char *)s))
		return ((char *)ft_calloc(1, sizeof(char)));
	if ((int)ft_strlen((char *)s) <= (int)(start + len))
		substr = malloc(sizeof(char) * (ft_strlen((char *)s) - start + 1));
	else
		substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (s[start] && i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}