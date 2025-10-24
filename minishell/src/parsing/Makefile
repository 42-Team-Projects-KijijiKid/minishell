# <==== Meta Data =====>
NAME	:= parsing
CC		:= cc
CFLAGS	:= -Wall -Werror -Wextra -Iparsing_inc/ -Igarbage_col/inc/ -I../../inc -I../../lib/libft/
 
# Flag to gernerate dependencies (outpu to a.d file)
# INC_INS	:= -MMD -MP -MF $(@:.o=.d)
# Not working at moment

#Includes
vpath %.h inc parsing_inc

# <==== Files & Folders =====>
MAIN_FILE	:= main.c

SRC_DIR		:= src/
OBJS_DIR	:= objs/

#TEMPORARY
GARBAGE_COL_FILES	:= garbage_col/garbage_col.c

#Folders inside src/
CORE_DIR		:= core/
TMP_TOKEN_DIR	:= tmp_token/
DEBUG_DIR		:= debug/

CORE_FILES	:= $(addprefix $(CORE_DIR), $(addsuffix .c, ast_creation parsing_helpers parsing_process token_gen)) 
TMP_TOKEN_FILES	:= $(addprefix $(TMP_TOKEN_DIR), $(addsuffix .c, 2d_arr tmp_token)) 
DEBUG_FILES	:= $(addprefix $(DEBUG_DIR), $(addsuffix .c, debug print_ast)) 


# Every folder path including the .c files inside the src/ folder 
MELTING_POT	:= $(CORE_FILES) $(TMP_TOKEN_FILES) $(DEBUG_FILES)


# Every Folder path prefixed with src/ and the main (top level)
SRCS		:= $(MAIN_FILE) $(GARBAGE_COL_FILES) $(addprefix $(SRC_DIR), $(MELTING_POT))

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