/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeckert <aeckert@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 12:18:17 by aeckert           #+#    #+#             */
/*   Updated: 2025/11/30 12:18:18 by aeckert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTS_H
# define REDIRECTS_H

# include "../structs.h"

// redirect_append.c
int		execute_rdr_append(t_redirect_node *redirect);

// redirect_heredoc.c
void	execute_rdr_heredoc(t_redirect_node *redirect);

// redirect_in.c
int		execute_rdr_in(t_redirect_node *redirect);

// redirect_out.c
int		execute_rdr_out(t_redirect_node *redirect);

#endif
