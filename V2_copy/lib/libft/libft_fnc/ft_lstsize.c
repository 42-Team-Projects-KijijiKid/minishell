/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandre <mandre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 13:25:31 by mandre            #+#    #+#             */
/*   Updated: 2025/03/30 14:18:43 by mandre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

// void printlist(t_list *head)
// {
//     t_list *temporary = head;

//     printf("\n----------\n");
//     while (temporary != NULL)
//     {
//         printf("%d - ", *(int *)temporary->content);
//         temporary = temporary->next;
//     }
//     printf("\n----------\n");
// }

// int	main(void)
// {
// 	int i;
// 	t_list *tmp;
// 	t_list *head = NULL;

// 	i = 0;
// 	while (i < 10)
// 	{
// 		int *value = malloc(sizeof(int)); 
// 		*value = i;
// 		tmp = ft_lstnew(value);
// 		tmp->next = head;
// 		head = tmp;
// 		i++;
// 	}
// 	printlist(head);
// 	printf("%i", ft_lstsize(head));
// 	t_list *current = head;
//     t_list *next_node;
//     while (current != NULL)
//     {
//         next_node = current->next;
// 		free(current->content);
//         free(current);  // Free the current node
//         current = next_node;  // Move to the next node
//     }
// }