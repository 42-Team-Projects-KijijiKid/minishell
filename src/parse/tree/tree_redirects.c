#include "../../../inc/minishell.h"

bool	is_redirect(t_tree_node_type type)
{
	if (type == DGREAT)
		return (true);
	else if (type == DLESS)
		return (true);
	else if (type == GREAT)
		return (true);
	else if (type == LESS)
		return (true);
	return (false);
}

static t_token	*init_redirect_traversal(t_build_manager *m)
{
	t_token	*tok;

	if (!m->head_token->next)
		return (NULL);
	if (m->head_token->type == TEXT && m->head_token == m->root_token)
		return (m->head_token->next);
	if (is_redirect(m->head_token->type))
	{
		tok = m->head_token;
		m->root_node->args = (char **)fti_malloc(
				sizeof(char *), TEMPORARY);
		m->root_node->args[0] = NULL;
		return (tok);
	}
	return (NULL);
}

static t_redirect_node	*append_redirect_node(t_build_manager *m,
	t_token *tok, t_redirect_node *redir)
{
	if (!redir)
		redir = (t_redirect_node *)fti_malloc(
				sizeof(t_redirect_node), TEMPORARY);
	if (m->root_node->redirect.head == NULL)
		m->root_node->redirect.head = redir;
	redir->type = tok->type;
	redir->file = tok->next->args[0];
	redir->next = NULL;
	return (redir);
}

void	tree_redirects(t_build_manager *m)
{
	t_token			*tok;
	t_redirect_node	*redir;

	tok = init_redirect_traversal(m);
	if (!tok || !is_redirect(tok->type))
		return ;
	redir = (t_redirect_node *)fti_malloc(
			sizeof(t_redirect_node), TEMPORARY);
	while (tok && is_redirect(tok->type))
	{
		redir = append_redirect_node(m, tok, redir);
		tok = tok->next->next;
		if (tok && is_redirect(tok->type))
			redir->next = (t_redirect_node *)fti_malloc(
					sizeof(t_redirect_node), TEMPORARY);
		redir = redir->next;
	}
}
