NAME	:= PmergeMe
LIB		:= ./lib/
OBJDIR	:= ./obj
SRCDIR	:= ./srcs/
SRC		:= main.cpp RPN.cpp
SRC		:= main.cpp  PmergeMe.cpp
ENTRY	:= 

INCS	:= ./include
IFLAGS	:= $(addprefix -I,$(INCS))
SRCS	:= $(addprefix $(SRCDIR), $(SRC))
OBJS	:= $(SRCS:.cpp=.o)
OBJECTS	:= $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
DEPS	:= $(OBJECTS:.o=.d)

CXX			:= c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98

all:
	@make $(NAME)	

$(NAME)	:	$(OBJECTS) | $(OBJDIR)
		$(CXX)  $(OBJECTS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -MMD -MP -MF $(OBJDIR)/$*.d  -o $@

$(OBJDIR) :
	@mkdir $(OBJDIR)

clean	:
			$(RM) -r $(OBJDIR)

fclean	:	clean
			$(RM) $(NAME)

re	:		fclean all

bonus	:	
			@make WITH_BONUS=1

ifeq ($(findstring clean,$(MAKECMDGOALS)),)
-include $(DEPS)
endif

.PHONY: all clean fclean bonus re

