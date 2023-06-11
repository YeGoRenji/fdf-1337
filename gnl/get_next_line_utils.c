/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:09:12 by ylyoussf          #+#    #+#             */
/*   Updated: 2022/11/16 18:44:34 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_noseg(const char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (*s++)
		len++;
	return (len);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (n--)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*target;

	if (!s1)
		return (NULL);
	len = ft_strlen_noseg(s1);
	target = malloc(len + 1);
	if (!target)
		return (NULL);
	ft_memcpy(target, s1, len);
	target[len] = '\0';
	return (target);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen_noseg(s);
	i = 0;
	if (start >= s_len || (len == 0 && start == 0) || len == 0)
		return (ft_strdup(""));
	if (s_len == 0)
		return (NULL);
	if (s_len - start <= len)
		substr = malloc(s_len - start + 1);
	else
		substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	while (s[start] && i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
