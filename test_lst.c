/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 13:12:04 by conobi            #+#    #+#             */
/*   Updated: 2021/11/11 16:02:47 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
#include <stdio.h>

static void	*f_toupper_map(void *content)
{
	char	*ret;
	int		i;

	ret = ft_strdup((char *)content);
	i = -1;
	while (ret[++i])
		if (ret[i] >= 'a' && ret[i] <= 'z')
			ret[i] -= 32;
	return (ret);
}

static void	del(void *content)
{
	printf("On supprime %s\n", (char *)content);
}

int	main(void)
{
	t_list	*lst;
	t_list	*nlst;
	t_list	*last;
	char ghi[] = "ghi";
	char def[] = "deF";
	char abc[] = "Abc";
	char jkl[] = "jkl";

	lst = ft_lstnew(ghi);
	ft_lstadd_front(&lst, ft_lstnew(def));
	ft_lstadd_front(&lst, ft_lstnew(abc));
	ft_lstadd_back(&lst, ft_lstnew(jkl));
	printf("Taille de la liste : %d\n", ft_lstsize(lst));
	printf("Dernier élément :\n");
	last = ft_lstlast(lst);
	printf("(%p) %s -> %p\n", last, (char *)last->content, last->next);
	printf("Test f_toupper_map : %s -> ", (char *)lst->content);
	printf("%s\n", f_toupper_map(lst->content));
	printf("????? %s\n", lst->content);
	nlst = ft_lstmap(lst, f_toupper_map, del);
	printf("------------------------------------\n");
	printf("Liste complète :\n");
	while (lst)
	{
		printf("(%p) %s -> %p\n", lst, (char *)lst->content, lst->next);
		lst = lst->next;
	}
	printf("Liste avec lstmap + toupper :\n");
	while (nlst)
	{
		printf("(%p) %s -> %p\n", nlst, (char *)nlst->content, nlst->next);
		nlst = nlst->next;
	}
	return (0);
}

/* 	Pour tester :
 *	gcc -Werror -Wall -Wextra -L . -lft main.c -o exec && ./exec
 */
