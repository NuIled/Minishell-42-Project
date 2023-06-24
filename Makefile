NAME = minishell

OBJ_DIR := obj

SRCS := $(wildcard *.c)
SRCS_SUBDIR := $(wildcard builtins/*.c)

OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))
OBJS_SUBDIR := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS_SUBDIR))

CC := cc
CFLAGS := -Wall -g -fsanitize=address
LIBFT = libft/

all: libft $(NAME)

libft :
	make all -sC $(LIBFT)

$(NAME): $(OBJS) $(OBJS_SUBDIR)
	$(CC) $(CFLAGS) -lreadline $(LIBFT)libft.a $^ -o $@

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/builtins/%.o: builtins/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(OBJ_DIR)/builtins)

re : clean all

clean:
	rm -rf $(OBJ_DIR) $(NAME)