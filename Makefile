##
## EPITECH PROJECT, 2021
## B-CCP-400-LYN-4-1-theplazza-lucas.guichard
## File description:
## Makefile
##

NAME		=   plazza

SRCS        =   $(wildcard sources/*.cpp) \
				$(wildcard sources/Ingredients/*.cpp) \
				$(wildcard sources/Pizzas/*.cpp)

OBJS        =   $(SRCS:.cpp=.o)

CXX			=	g++

CXXFLAGS    =   -Wall -Wextra -Iincludes

LDFLAGS		=	-lrt -lpthread

DEBUG       =   -ggdb3

RM          =   rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CXX) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
			$(RM) $(OBJS)
			$(RM) vgcore*
			$(RM) record.txt

fclean: 	clean
			$(RM) $(NAME)

re:     	fclean all

.PHONY: 	all clean fclean re