# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashih <ashih@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/22 08:52:13 by ashih             #+#    #+#              #
#    Updated: 2018/08/26 22:19:14 by ashih            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc

TARGET := philo

INCLUDES := includes/

LIBFT := libft/
LIBFT_INC := $(LIBFT)includes/
LIBFT_LIB := $(LIBFT)libft.a

SDL2_LOC := $(shell brew --prefix sdl2)
SDL2_INC := $(SDL2_LOC)/include/SDL2/
SDL2_LINK := -L $(SDL2_LOC)/lib/ -lSDL2

SDL2_IMAGE_LOC := $(shell brew --prefix sdl2_image)
SDL2_IMAGE_INC := $(SDL2_IMAGE_LOC)/include/SDL2/
SDL2_IMAGE_LINK := -L $(SDL2_IMAGE_LOC)/lib/ -lSDL2_image

SDL2_TTF_LOC := $(shell brew --prefix sdl2_ttf)
SDL2_TTF_INC := $(SDL2_TTF_LOC)/include/SDL2/
SDL2_TTF_LINK := -L $(SDL2_TTF_LOC)/lib/ -lSDL2_ttf

CFLAGS := -Wall -Werror -Wextra
HEADERS := -I $(INCLUDES) -I $(LIBFT_INC) -I $(SDL2_INC) -I $(SDL2_IMAGE_INC) -I $(SDL2_TTF_INC)

SRCS := main.c \
events.c \
font.c \
freedom.c \
init_actors.c \
init_sdl.c \
philo_util.c \
philosophize.c \
render.c \
render_philo.c \
sound.c \
texture.c

SRCDIR := srcs/
OBJDIR := objs/
OBJS := $(addprefix $(OBJDIR), $(SRCS:.c=.o))

all: sdl2 sdl2_image sdl2_ttf $(LIBFT_LIB) $(TARGET)

sdl2:
	@echo "\x1b[1mInstalling SDL2 library...\x1b[0m"
	@HOMEBREW_NO_AUTO_UPDATE=1 brew install sdl2
	@echo

sdl2_image:
	@echo "\x1b[1mInstalling SDL2 Image library...\x1b[0m"
	@HOMEBREW_NO_AUTO_UPDATE=1 brew install sdl2_image
	@echo

sdl2_ttf:
	@echo "\x1b[1mInstalling SDL2 TTF library...\x1b[0m"
	@HOMEBREW_NO_AUTO_UPDATE=1 brew install sdl2_ttf
	@echo

$(LIBFT_LIB):
	@echo "\x1b[1mBuilding $(LIBFT) library...\x1b[0m"
	@make -C $(LIBFT)
	@echo

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) -c $(CFLAGS) $(HEADERS) $< -o $@

$(TARGET): $(OBJS)
	@echo "\x1b[1mBuilding $(TARGET)...\x1b[0m"
	$(CC) -o $(TARGET) $(OBJS) \
		-L$(LIBFT) -lft \
		-lpthread \
		$(SDL2_LINK) $(SDL2_IMAGE_LINK) $(SDL2_TTF_LINK)
	@echo "\x1b[1mBuild finished!!\x1b[0m"

clean:
	@echo "\x1b[1mCleaning...\x1b[0m"
	make -C $(LIBFT) clean
	/bin/rm -rf $(OBJDIR)
	@echo

fclean: clean
	@echo "\x1b[1mFcleaning...\x1b[0m"
	/bin/rm -f $(LIBFT_LIB)
	/bin/rm -f $(TARGET)
	@echo

re: fclean all

.PHONY: all clean fclean re sdl2 sdl2_image sdl2_ttf
