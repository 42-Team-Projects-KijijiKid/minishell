/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:19:44 by mandre            #+#    #+#             */
/*   Updated: 2025/03/31 14:47:54 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = new;
}

// #include <stdio.h>
// void print_list(t_list *head)
// {
// 	t_list *current = head;
// 	printf("List contents: ");
// 	while (current)
// 	{
// 		printf("%d -> ", *(int *)current->content);
// 		current = current->next;
// 	}
// 	printf("NULL\n");
// }

// int main(void)
// {
// 	t_list	*head = NULL;
// 	t_list	*tmp;

// 	int *value1 = (int *)malloc(sizeof(int));
// 	int *value2 = (int *)malloc(sizeof(int));
// 	int *value3 = (int *)malloc(sizeof(int));
// 	if (!value1 || !value2 || !value3) return (1);

// 	*value1 = 2;
// 	*value2 = 6;
// 	*value3 = 60;

// 	tmp = ft_lstnew(value1);
// 	tmp->next = head;
// 	head = tmp;
// 	tmp = ft_lstnew(value2);
// 	tmp->next = head;
// 	head = tmp;
// 	tmp = ft_lstnew(value3);
// 	ft_lstadd_back(&head, tmp);

// 	print_list(head);
// 	while (head)
// 	{
// 		tmp = head->next;
// 		free(head->content);
// 		free(head);
// 		head = tmp;
// 	}
// 	return (0);
// }