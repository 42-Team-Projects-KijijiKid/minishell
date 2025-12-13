/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:18:06 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:18:07 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "../structs.h"

// tree_build.c
void		tree_build(t_build_manager *manager);

// tree_utils.c
t_tree_node	*token_to_tree_node(t_token *head_token);

// tree_redirects.c
bool		is_redirect(t_tree_node_type type);
void		tree_redirects(t_build_manager *manager);

// tree_subshell.c
void		tree_build(t_build_manager *manager);
void		build_right_subtree(t_build_manager *manager);
void		build_left_subtree(t_build_manager *manager);
t_token		*get_final_before_parenthesis(t_token *token, bool reverse);
t_token		*get_last_token(t_token *node);
int			count_parenthesis_at_start(t_token *token);
int			count_parenthesis_at_end(t_token *token);

// tree_subshell_2.c
int			count_outer_subshells_reverse(t_token *token);
int			count_outer_subshells(t_token *token);
int			count_subshell_cutoffs(t_token *token);
void		tree_subshells(t_build_manager *manager);

#endif