NAME        := libft.a

# <=== Tools & Flags ===>
CC          := cc
AR          := ar rcs
RANLIB      := ranlib
CFLAGS      := -Wall -Wextra -Werror -g -MMD -MP

# <=== Dirs ===>
BUILD_DIR   := build
LIBFT_DIR   := libft_fnc
PRINTF_DIR  := printf
GNL_DIR     := get_next_line

INCDIRS     := -I. -I$(LIBFT_DIR) -I$(PRINTF_DIR) -I$(GNL_DIR)

# <=== Colors ===>
GREEN       := \033[0;32m
YELLOW      := \033[0;33m
RED         := \033[0;31m
BLUE        := \033[0;34m
RESET       := \033[0m

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

SRCS := ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
        ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
        ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
        ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_split.c ft_itoa.c \
        ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
        ft_atol.c free2d.c atodl.c

BONUS_SRCS := ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
              ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstclear.c

GNL_SRCS := get_next_line.c get_next_line_utils.c

PRINTF_SRCS := ft_error.c ft_printf.c ft_putchar.c helper_utils.c hexa_lowercase.c hexa_uppercase.c \
               print_int.c print_ptr.c print_str.c print_unsignednbr.c

LIBFT_CS     := $(addprefix $(LIBFT_DIR)/,$(SRCS))
BONUS_CS     := $(addprefix $(LIBFT_DIR)/,$(BONUS_SRCS))
GNL_CS       := $(addprefix $(GNL_DIR)/,$(GNL_SRCS))
PRINTF_CS    := $(addprefix $(PRINTF_DIR)/,$(PRINTF_SRCS))

LIBFT_OBJS   := $(LIBFT_CS:%.c=$(BUILD_DIR)/%.o)
BONUS_OBJS   := $(BONUS_CS:%.c=$(BUILD_DIR)/%.o)
GNL_OBJS     := $(GNL_CS:%.c=$(BUILD_DIR)/%.o)
PRINTF_OBJS  := $(PRINTF_CS:%.c=$(BUILD_DIR)/%.o)

OBJS         := $(LIBFT_OBJS) $(GNL_OBJS) $(PRINTF_OBJS)
DEPS         := $(OBJS:.o=.d)
BONUS_DEPS   := $(BONUS_OBJS:.o=.d)

ALL_OBJS     := $(OBJS) $(if $(BONUS),$(BONUS_OBJS))

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

all: msg_start $(NAME)

$(NAME): $(ALL_OBJS)
	@echo "$(YELLOW)[AR] Creating $(NAME)$(RESET)"
	@$(AR) $@ $^
	@$(RANLIB) $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)[CC] $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCDIRS) -c $< -o $@

bonus:
	@$(MAKE) BONUS=1 --no-print-directory

clean:
	@echo "$(RED)🧹 Cleaning object & dep files...$(RESET)"
	@rm -rf $(BUILD_DIR)

fclean: clean
	@echo "$(RED)🧨 Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)

re:
	@$(MAKE) fclean --no-print-directory
	@$(MAKE) all --no-print-directory

msg_start:
	@echo "$(GREEN)🛠️  Building Libft (+ printf & GNL)$(RESET)"

-include $(DEPS) $(BONUS_DEPS)

.PHONY: all clean fclean re bonus msg_start
