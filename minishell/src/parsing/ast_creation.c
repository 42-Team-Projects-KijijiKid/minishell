#include "parsing.h"

/// @brief Builds the ast asigning
/// left right of each node
void	build_ast(t_token *root)
{
	t_token	*pre_pipe;
	t_token	*post_pipe;

	// here we first have to split left from operator and right from operator
	// Trying to figure out a recursive way. 
	// We again have to also detect precedence
	pre_pipe = root;
	root->back->left = NULL;
	while (pre_pipe->back)
		pre_pipe = pre_pipe->back;
	post_pipe = root->left;
	post_pipe->back = NULL;
	root->left = NULL;
	root->left = pre_pipe;
	root->right = post_pipe;
}
