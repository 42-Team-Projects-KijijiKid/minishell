# <==== Meta Data =====>
NAME	:= parsing_out
CC		:= cc
CFLAGS	:= -Wall -Werror -Wextra -pthread

#Includes
vpath	%.h inc

# <==== Files & Folders =====>
MAIN_FILE	:= main.c

SRC_DIR		:= src/
OBJS_DIR	:= objs/

#Folders inside src/
CORE_DIR	:= core/
TOOL_DIR	:= tools/
ERR_DIR		:= error/


CORE_FILES	:= $(addprefix $(CORE_DIR), $(addsuffix .c, )) 
TOOL_FILES	:= $(addprefix $(TOOL_DIR), $(addsuffix .c, )) #time type_converters parsing init_structs destroy_mutexes output
ERR_FILES	:= $(addprefix $(ERR_DIR), $(addsuffix .c, )) 


# Every folder path including the .c files inside the src/ folder 
MELTING_POT	:= $(CORE_FILES) $(TOOL_FILES) $(ERR_FILES)


# Every Folder path prefixed with src/ and the main (top level)
SRCS		:= $(MAIN_FILE) $(addprefix $(SRC_DIR), $(MELTING_POT))

# All .c to .o -> See compilation Rule $< $@
OBJS		:= $(addprefix $(OBJS_DIR), $(SRCS:%.c=%.o))



# <===== Rules =====>

all: $(NAME)

#Compile executable including every .o file
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -Iinc/ -o $(NAME)

#Rule to compile all .o files
$(OBJS_DIR)%.o: %.c | $(OBJS_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -Iinc/ -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean
	@make

.PHONY: all clean fclean re
