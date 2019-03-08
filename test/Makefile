# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbally <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/15 17:12:52 by hbally            #+#    #+#              #
#    Updated: 2019/03/08 16:50:59 by hbally           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	lem_in_test

# Dir Variables

SRCSDIR   			=	src

OBJSDIR   			=	obj

LIBSPATH			=	..

LIBDIRS				:=	$(LIBSPATH)/libft

INCDIR				:=	$(LIBDIRS:%=%/inc) 					\
						../inc						\
						./inc

# File Variables

SRCS_RAW			:=	main.c			\
						flow.c

SRCS				:=	$(SRCS_RAW:%.c=$(SRCSDIR)/%.c)

OBJS  				:=	$(SRCS:$(SRCSDIR)/%.c=$(OBJSDIR)/%.o)

DEPENDENCIES			:=	$(OBJS:%.o=%.d)

LIBFILES			:=	$(foreach LIB, $(LIBDIRS), $(LIB)/$(notdir $(LIB)).a)

# Compiler Config

CC					=	gcc

CFLAGS				+=	-Wall -Werror -Wextra

INCLUDES			:=	$(addprefix -I ,$(INCDIR))

INCLIBS				:=	$(foreach LIB,$(LIBDIRS),-L $(LIB) $(subst lib,-l,$(notdir $(LIB))))	\
					-L ./ -ltest

# Main Target

all					:	libs $(NAME)

$(NAME)				: 	$(OBJS) $(LIBFILES)
						
						$(CC) -o $@ $(CFLAGS) $(INCLIBS) $(OBJS)

.PHONY				:	libs
libs				:
					make -C ..

# Objs Target

-include $(DEPENDENCIES)

$(OBJS)				: 	$(OBJSDIR)/%.o : $(SRCSDIR)/%.c
						@mkdir -p $(OBJSDIR)
						$(CC) -o $@ $(CFLAGS) $(INCLUDES) -MMD -c $<

# Cleanup

.PHONY				:	clean
clean				:
						rm -f $(OBJS) $(DEPENDENCIES)
						rm -rf $(OBJSDIR)

.PHONY				:	fclean
fclean				:	clean
						rm -f $(NAME)

.PHONY				:	re
re					:	fclean all
