# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-madi <ael-madi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/24 17:53:37 by ael-madi          #+#    #+#              #
#    Updated: 2021/07/24 17:57:29 by ael-madi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC = fractol.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		#linux
		gcc -g -Wall -Wextra -Werror fractol.c  ./mlx.h -D NUM_THREADS=4 -D LINUX -L ./minilibx-linux -lmlx -lm -lX11 -lXext -lpthread
		#MACOS
		#gcc -Wall -g -Werror -Wextra -c $(SRC)
		#gcc -Wall -g -Werror -Wextra -L. -lmlx -framework OpenGL -framework Appkit $(OBJ) -o $(NAME)
clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re : fclean all
