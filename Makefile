NAME				=	lem-in

# Dir Variables

SRCSDIR   			=	src

OBJSDIR   			=	obj

TESTDIR				=	unit-test

LIBSPATH			=	.

LIBDIRS				:=	$(LIBSPATH)/libft

INCDIR				:=	$(LIBDIRS:%=%/inc) 	\
						inc

# File Variables

SRCS_RAW			:=	main.c						\
						list.c						\
						collector.c					\
						flow_create_all.c			\
						flow_find_new.c				\
						flow_update_nodes.c			\
						flow_update_gates.c			\
						flow_simulate.c				\
						flow_helpers.c				\
						viz_tofile.c				\
						viz_tofile_helpers.c		\
						ft_read_map.c       		\
						ft_make_graph.c     		\
						ft_basic_read.c     		\
						ft_get_edges.c				\
						output.c

SRCS				:=	$(SRCS_RAW:%.c=$(SRCSDIR)/%.c)

OBJS  				:=	$(SRCS:$(SRCSDIR)/%.c=$(OBJSDIR)/%.o)

DEPENDENCIES		:=	$(OBJS:%.o=%.d)

LIBFILES			:=	$(foreach LIB, $(LIBDIRS), $(LIB)/$(notdir $(LIB)).a)

# Compiler Config

CC					=	gcc

CFLAGS				+=	-Wall -Werror -Wextra

INCLUDES			:=	$(addprefix -I ,$(INCDIR))

INCLIBS				:=	$(foreach LIB,$(LIBDIRS),-L $(LIB) $(subst lib,-l,$(notdir $(LIB))))

# Main Target

all					:	libs $(NAME)

$(NAME)				: 	$(OBJS) $(LIBFILES)
						$(CC) -o $@ $(CFLAGS) $(INCLIBS) $(OBJS)
						ar rc $(TESTDIR)/libtest.a $(filter-out $(OBJSDIR)/main.o,$(OBJS))

# Make Libs

.PHONY				:	libs
libs				:
						git submodule init
						git submodule update
						git submodule foreach git fetch origin 
						git submodule foreach git checkout lem_in 
						git submodule foreach git pull origin lem_in
						@$(foreach LIB, $(LIBDIRS), make -C $(LIB);)

# Objs Target

-include $(DEPENDENCIES)

$(OBJS)				: 	$(OBJSDIR)/%.o : $(SRCSDIR)/%.c
						@mkdir -p $(OBJSDIR)
						$(CC) -o $@ $(CFLAGS) $(INCLUDES) -MMD -c $<

# Cleanup

.PHONY				:	clean
clean				:
						@$(foreach LIB, $(LIBDIRS), $(MAKE) -C $(LIB) clean ;)
						rm -f $(OBJS) $(DEPENDENCIES)
						rm -rf $(OBJSDIR)

.PHONY				:	fclean
fclean				:	clean
						@$(foreach LIB, $(LIBDIRS), $(MAKE) -C $(LIB) fclean ;)
						rm -f $(NAME)

.PHONY				:	re
re					:	fclean all
