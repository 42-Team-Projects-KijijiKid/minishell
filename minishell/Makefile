# <==== Meta Data =====>
NAME	:= minishell
CC		:= cc
# CFLAGS	:= -g -Wall -Werror -Wextra -Iinc/ -Ilib/libft
CFLAGS	:= -g -Iinc/ -Ilib/libft

#Includes
vpath %.h inc/

# <==== Files & Folders =====>
MAIN_FILE	:= main.c

SRC_DIR		:= src/
OBJS_DIR	:= objs/

PARSING_DIR		:= parse/
EXECUTION_DIR	:= execute/
ENVIRONMENT_DIR	:= environment/
UTILS_DIR		:= utils/

#SUB Dir parsing
EXPAND_DIR 		:= expand/
TOKENIZE_DIR	:= tokenize/
TREE_DIR		:= tree/

#SUB Dirs execute
BUILTIN_DIR		:= builtins/
REDIRECTS_DIR	:= redirects/

#SUB Dirs utils
INTEGRATIONS_DIR	:= integrations/

#.c files in src/parsing with subfolders
EXPAND_FILES			:= $(addprefix $(EXPAND_DIR), $(addsuffix .c, expand_quotes expand_variables expand)) 
TOKENIZE_FILES			:= $(addprefix $(TOKENIZE_DIR), $(addsuffix .c, token_list_utils tokenization_utils tokenize_command tokenize_operator tokens_process tokens_seperate)) 
TREE_FILES				:= $(addprefix $(TREE_DIR), $(addsuffix .c, tree_build_utils tree_build tree_find_root tree_redirect))

#.c files in src/execute with subfolders
BUILTIN_FILES			:= $(addprefix $(BUILTIN_DIR), $(addprefix builtin_, $(addsuffix .c, cd echo env exit export pwd unset)))
REDIRECTS_FILES			:= $(addprefix $(REDIRECTS_DIR), redirection_utils.c $(addprefix redirect_, $(addsuffix .c, append heredoc in out)))

#.c files in src/utils with subfolders
INTEGRATIONS_FILES		:= $(addprefix $(INTEGRATIONS_DIR), $(addsuffix .c, fti_malloc fti_readline))

# This is the total path to the .c files in the prefixed directory
PARSING			:= $(addprefix $(PARSING_DIR), parse.c parsing_validate.c $(EXPAND_FILES) $(TOKENIZE_FILES) $(TREE_FILES))
EXECUTE			:= $(addprefix $(EXECUTION_DIR), execute.c $(addprefix execute_, $(addsuffix .c, command operator pipe subshell)) $(BUILTIN_FILES) $(REDIRECTS_FILES))
ENVIRONMENT		:= $(addprefix $(ENVIRONMENT_DIR), env_initialize.c environment_utils.c)
UTILS			:= $(addprefix $(UTILS_DIR), garbage.c error.c $(INTEGRATIONS_FILES))

# Every folder path including the .c files inside the src/ folder 
MELTING_POT	:= $(PARSING) $(EXECUTE) $(ENVIRONMENT) $(UTILS)


# Every Folder path prefixed with src/ and the main (top level)
SRCS		:= $(addprefix $(SRC_DIR), $(MAIN_FILE) $(MELTING_POT))

# All .c to .o -> See compilation Rule $< $@
OBJS		:= $(addprefix $(OBJS_DIR), $(SRCS:%.c=%.o))


# <===== Rules =====>

all: $(NAME)

#Compile executable including every .o file
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline lib/libft/libft.a -o $(NAME)

#Rule to compile all .o files
$(OBJS_DIR)%.o: %.c | $(OBJS_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	@make

.PHONY: all clean fclean re