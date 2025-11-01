#include "execution.h"

void	execution_process(t_token *token)
{
	if (T_TEXT == token->type)
		run_cmd(token, STD, 1);
	else if (T_OUT_RDR == token->type)
		out_redir(token);
	else if (T_IN_RDR == token->type)
		in_redir(token);
}
