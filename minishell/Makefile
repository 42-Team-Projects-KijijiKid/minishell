# <==== Meta Data =====>
NAME	:= minishell
CC		:= cc
CFLAGS	:= -g -Wall -Werror -Wextra -Iinc/ -Ilib/libft
 
# Flag to gernerate dependencies (output to a.d file)
# INC_INS	:= -MMD -MP -MF $(@:.o=.d)
# Not working at moment

#Includes
vpath %.h inc/

# <==== Files & Folders =====>
MAIN_FILE	:= main.c

SRC_DIR		:= src/
OBJS_DIR	:= objs/

PARSING_DIR	:= parsing/
GC_DIR		:= garbage_col/
UTILS_DIR	:= utils/

#Folders inside src/parsing
CORE_DIR		:= core/
TMP_TOKEN_DIR	:= tmp_token/
DEBUG_DIR		:= debug/

#.c files in src/parsing with subfolders
CORE_FILES_PARSING		:= $(addprefix $(CORE_DIR), $(addsuffix .c, ast_creation parsing_helpers parsing_process token_gen syntax_errors expand)) 
TMP_TOKEN_FILES_PARSING	:= $(addprefix $(TMP_TOKEN_DIR), $(addsuffix .c, 2d_arr tmp_token string)) 
DEBUG_FILES_PARSING		:= $(addprefix $(DEBUG_DIR), $(addsuffix .c, debug print_ast)) 

#.c files in src/garbage_col with subfolders
CORE_FILES_GC	:= garbage_col.cs

#.c files in src/utils with subfolders
CORE_FILES_UTILS		:= $(addsuffix .c, utils)


# This is the total path to the .c files
PARSING_MAIN_PATH	:= $(addprefix $(PARSING_DIR), $(CORE_FILES_PARSING) $(TMP_TOKEN_FILES_PARSING) $(DEBUG_FILES_PARSING))
GC_MAIN_PATH		:= $(addprefix $(GC_DIR), $(CORE_FILES_GC))
UTILS_MAIN_PATH		:= $(addprefix $(UTILS_DIR), $(CORE_FILES_UTILS))

# Every folder path including the .c files inside the src/ folder 
MELTING_POT	:= $(PARSING_MAIN_PATH) $(GC_MAIN_PATH) $(UTILS_MAIN_PATH)


# Every Folder path prefixed with src/ and the main (top level)
SRCS		:= $(MAIN_FILE) $(addprefix $(SRC_DIR), $(MELTING_POT))

# All .c to .o -> See compilation Rule $< $@
OBJS		:= $(addprefix $(OBJS_DIR), $(SRCS:%.c=%.o))



# <===== Rules =====>

all: $(NAME)

#Compile executable including every .o file
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) libft.a -o $(NAME)

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