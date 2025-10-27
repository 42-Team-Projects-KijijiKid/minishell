#include "parsing.h"



/// @brief Opens or creates the outfile
/// and adds the matching redir token
/// @param token 
static void	handle_out_redir(t_token *token)
{
	int	fd;

	printf("IM here!!");
	fd = open(*token->left->args_2d, O_CREAT | O_WRONLY, 0644);
	if(fd == -1)
		ft_error("Open error:", __FILE__, __LINE__, 38);
	assign_redir_node_values(token->back, OUT_FD, fd);
}

static void	handle_in_redir(t_token *token)
{
	int	fd;

	fd = open(*token->left->args_2d, O_WRONLY);
	if(fd == -1)
		ft_error("No such file or directory:", __FILE__, __LINE__, 39);
	assign_redir_node_values(token->back, IN_FD, fd);
}

void	handle_io_redir(t_token *token)
{
	printf("HEre??");
	if (!token->back || !token->left)
		ft_error("I/O redirection error:", __FILE__, __LINE__, 82);
	if (token->type == T_IN_RDR)
		handle_in_redir(token);
	if (token->type == T_OUT_RDR)
		handle_out_redir(token);
}
