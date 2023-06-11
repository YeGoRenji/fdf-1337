/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 20:47:08 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/11 20:31:31 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>


int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
#endif
