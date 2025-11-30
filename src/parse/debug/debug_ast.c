/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:16:20 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:16:23 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_operator(t_tree_node_type type)
{
	if (type == AND_IF)
		printf("&&");
	else if (type == OR_IF)
		printf("||");
	else if (type == PIPE)
		printf("|");
}

void	debug_ast(char *prefix, char *file, int line, t_tree_node *node)
{
	char	**tmp;

	tmp = node->args;
	printf("\033[31;3m%s: ", prefix);
	if (node->type != TEXT)
		print_operator(node->type);
	else
	{
		printf("[");
		while (*tmp)
		{
			printf("%s, ", *tmp);
			tmp++;
		}
		printf("] ");
	}
	printf("%s, %d\033[0m\n", file, line);
}
