/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:17:34 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:17:36 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_env_var(char *key, char *value)
{
	t_minishell	*shell;
	t_env_node	*new_node;

	shell = minishell_get();
	new_node = fti_malloc(sizeof(t_env_node), PERSISTENT);
	shell->env.tail->next = new_node;
	new_node->prev = shell->env.tail;
	shell->env.size++;
	shell->env.tail = new_node;
	new_node->next = NULL;
	new_node->key_len = ft_strlen(key);
	new_node->key = fti_malloc(new_node->key_len + 1, PERSISTENT);
	ft_strlcpy(new_node->key, key, new_node->key_len + 1);
	if (value)
	{
		new_node->value = fti_strdup(value, PERSISTENT);
		new_node->value_len = ft_strlen(new_node->value);
	}
	else
	{
		new_node->value_len = 0;
		new_node->value = NULL;
	}
}
