NAME = webserv

SRCS = $(wildcard ./*/*.cpp)

HEADERS	= $(wildcard ./*/*.hpp)

OBJS = $(SRCS:.cpp=.o)

CPP = g++

NAME = webserv

CPPFLAGS = # -Wall -Wextra -Werror -std=c++98

RM = rm -f

RESET = "\033[0m"
GREEN = "\033[32m"
RED = "\033[31m"

all : $(NAME)

%.o : %.cpp $(HEADERS)
	@$(CPP) -c $(CPPFLAGS) $< -o $@

$(NAME) : $(OBJS) $(HEADERS)
	@$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)
	@echo $(GREEN) 🌐 webserv compiled 🌐 $(RESET)

run : $(NAME)
	@./$(NAME)

clean :
	@$(RM) $(OBJS)
	@echo $(RED) 🌐 Objects file deleted 🌐 $(RESET)

fclean : clean
	@$(RM) $(NAME)
	@echo $(RED) 🌐 executable file deleted 🌐 $(RESET)

re : fclean all

.PHONY : clean