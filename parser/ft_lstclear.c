/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 00:00:46 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/12 14:34:01 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*to_del;

	if (!lst || !del || !(*lst))
		return ;
	while (*lst)
	{
		to_del = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(to_del, del);
	}
}
