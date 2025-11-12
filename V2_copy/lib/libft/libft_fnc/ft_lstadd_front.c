/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 12:24:13 by mandre            #+#    #+#             */
/*   Updated: 2025/03/30 13:21:08 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

// int main(void)
// {
// 	t_list *list = NULL;
// 	int *num1 = malloc(sizeof(int));
// 	*num1 = 42;
// 	list = ft_lstnew(num1);
// 	int *num2 = malloc(sizeof(int));
// 	*num2 = 21;
// 	t_list *new_node = ft_lstnew(num2);
// 	printf("Before adding to front:\n");
// 	printf("First node content: %d\n", *(int*)list->content);
// 	ft_lstadd_front(&list, new_node);
// 	printf("\nAfter adding to front:\n");
// 	printf("First node content: %d\n", *(int*)list->content);
// 	printf("Second node content: %d\n", *(int*)list->next->content);
// 	free(num1);
// 	free(num2);
// 	free(list->next);
// 	free(list);
// 	return (0);
// }