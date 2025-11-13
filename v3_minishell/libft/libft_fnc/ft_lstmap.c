/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:25:47 by mandre            #+#    #+#             */
/*   Updated: 2025/04/01 10:12:50 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new_lst;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		content = f(lst->content);
		tmp = ft_lstnew(content);
		if (!tmp)
		{
			if (del)
				del(content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, tmp);
		lst = lst->next;
	}
	return (new_lst);
}

// void *double_value(void *content)
// {
//     int *new_value = malloc(sizeof(int));
//     if (!new_value)
//         return (NULL);
//     *(new_value) = *(int *)content * 2;
//     return new_value;
// }
// void delete_value(void *content)
// {
//     free(content);
// }
// void print_list(t_list *lst)
// {
//     while (lst)
//     {
//         printf("%d -> ", *(int *)lst->content);
//         lst = lst->next;
//     }
//     printf("NULL\n");
// }
// void test_ft_lstmap()
// {
//     t_list *lst = ft_lstnew(malloc(sizeof(int)));
//     *(int *)lst->content = 1;
//     t_list *second = ft_lstnew(malloc(sizeof(int)));
//     *(int *)second->content = 2;
//     t_list *third = ft_lstnew(malloc(sizeof(int)));
//     *(int *)third->content = 3;
//     lst->next = second;
//     second->next = third;
//     third->next = NULL;
//     printf("Original list:\n");
//     print_list(lst);
//     t_list *new_lst = ft_lstmap(lst, double_value, delete_value);
//     printf("\nNew list after mapping (doubled values):\n");
//     print_list(new_lst);
//     ft_lstclear(NULL, delete_value);
//     ft_lstclear(&new_lst, delete_value);
// }
// int main()
// {
//     test_ft_lstmap();
//     return 0;
// }