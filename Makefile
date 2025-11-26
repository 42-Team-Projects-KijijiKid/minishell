# <==== Meta Data =====>
NAME	:= minishell
CC		:= cc
# CFLAGS	:= -g -fsanitize=address -Wall -Wextra -Iinc/ -Ilib/libft
# CFLAGS	:= -fsanitize=address -g -Iinc/ -Ilibft
CFLAGS	:= -g -Iinc/ -Ilibft

#Includes
vpath %.h inc/

# <==== Files & Folders =====>
CORE_FILES	:= main.c minishell.c

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
DEBUG_DIR		:= debug/

#SUB Dirs execute
BUILTIN_DIR		:= builtins/
REDIRECTS_DIR	:= redirects/

#SUB Dirs utils
INTEGRATIONS_DIR	:= integrations/
SIGNALS_DIR	:= signals/

#.c files in src/parsing with subfolders
EXPAND_FILES			:= $(addprefix $(EXPAND_DIR), $(addsuffix .c, expand expand_2 expand_helpers expand_helpers_2 get_environment_value expand_total_len)) 
TOKENIZE_FILES			:= $(addprefix $(TOKENIZE_DIR), $(addsuffix .c, tokenize tokenize_helpers $(addprefix tokens_, find_root split_args split_utils validate))) 
TREE_FILES				:= $(addprefix $(TREE_DIR), $(addsuffix .c, tree_build tree_redirects tree_utils tree_subshells tree_subshells_2))
DEBUG_FILES				:= $(addprefix $(DEBUG_DIR), $(addsuffix .c, print_tree debug_ast print_token_list))

#.c files in src/execute with subfolders
BUILTIN_FILES			:= $(addprefix $(BUILTIN_DIR), $(addprefix builtin_, $(addsuffix .c, cd cd_helpers echo env exit export pwd unset export_helpers export_helpers_2 export_print)))
REDIRECTS_FILES			:= $(addprefix $(REDIRECTS_DIR), $(addprefix redirect_, $(addsuffix .c, append heredoc in out)))

#.c files in src/utils with subfolders
INTEGRATIONS_FILES		:= $(addprefix $(INTEGRATIONS_DIR), $(addsuffix .c, fti_malloc fti_readline fti_strdup fti_strjoin fti_fork fti_itoa fti_substr fti_split))
SIGNALS_FILES			:= $(addprefix $(SIGNALS_DIR), $(addsuffix .c, signals))

# This is the total path to the .c files in the prefixed directory
PARSING					:= $(addprefix $(PARSING_DIR), parse.c parsing_validate.c  $(EXPAND_FILES) $(TOKENIZE_FILES) $(TREE_FILES) $(DEBUG_FILES))
EXECUTE					:= $(addprefix $(EXECUTION_DIR), execute.c filedescriptor_helpers.c $(addprefix execute_, $(addsuffix .c, command operator pipe subshell helpers)) $(BUILTIN_FILES) $(REDIRECTS_FILES))
ENVIRONMENT				:= $(addprefix $(ENVIRONMENT_DIR), env_initialize.c environment_utils.c environment_utils_2.c)
UTILS					:= $(addprefix $(UTILS_DIR), garbage.c error.c read_next_line.c $(INTEGRATIONS_FILES) $(SIGNALS_FILES))

# Every folder path including the .c files inside the src/ folder 
MELTING_POT	:= $(PARSING) $(ENVIRONMENT) $(UTILS) $(EXECUTE)

# Every Folder path prefixed with src/ and the main (top level)
SRCS		:= $(addprefix $(SRC_DIR), $(CORE_FILES) $(MELTING_POT))

# All .c to .o -> See compilation Rule $< $@
OBJS		:= $(addprefix $(OBJS_DIR), $(SRCS:%.c=%.o))

LIBFT_A		:= libft/libft.a
LIBFT_DIR	:= libft/

# <===== Rules =====>

all: $(LIBFT_A) $(NAME)

#Compile executable including every .o file
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline libft/libft.a -o $(NAME)

$(LIBFT_A):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR)

#Rule to compile all .o files
$(OBJS_DIR)%.o: %.c | $(OBJS_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@rm -rf $(OBJS_DIR)
	@rm -rf $(LIBFT_DIR)/build

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT_A)

re: fclean
	@make

.PHONY: all clean fclean re
