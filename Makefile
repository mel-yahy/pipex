.PHONY: all bonus clean fclean re

CC := cc
CFLAGS := -Wall -Wextra -Werror -g
RM := rm -rf

SRC_DIR := src
IDIR := include
BUILD_DIR := build

SRCS := $(shell find $(SRC_DIR)/mandatory -name "*.c")
ifeq ($(MAKECMDGOALS), bonus)
	SRCS := $(shell find $(SRC_DIR)/bonus -name "*.c")
endif
COMMON_SRCS := $(shell find $(SRC_DIR)/common -name "*.c")

OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
COMMON_OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(COMMON_SRCS))

NAME := pipex

all: $(NAME)

$(NAME): $(OBJS) $(COMMON_OBJS)
	$(CC) $(CFLAGS) -I$(IDIR) $^ -o $@

bonus: all

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(IDIR) -c $< -o $@

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
