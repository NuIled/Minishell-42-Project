NAME = minishell

OBJ_DIR := obj

SRCS := $(wildcard *.c)
SRCS_SUBDIR := $(wildcard builtins/*.c)
SRCS_SUBDIR2 := $(wildcard check/*.c)

OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

OBJS_SUBDIR := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS_SUBDIR))

OBJS_SUBDIR2 := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS_SUBDIR2))

CC := cc
CFLAGS := -Wall -g -fsanitize=address
LIBFT = libft/

all: libft $(NAME)

libft :
	make all -sC $(LIBFT)

$(NAME): $(OBJS) $(OBJS_SUBDIR) $(OBJS_SUBDIR2)
	$(CC) $(CFLAGS) -lreadline $(LIBFT)libft.a $^ -o $@

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/builtins/%.o: builtins/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/check/%.o: check/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(OBJ_DIR)/builtins)
$(shell mkdir -p $(OBJ_DIR)/check)

re : clean all

clean:
	rm -rf $(OBJ_DIR) $(NAME)