SRCDIR := srcs
INCDIR := incs
OBJDIR := objs
DEPDIR := $(OBJDIR)/.deps

SRCS := $(wildcard $(SRCDIR)/*.c)
OBJS := $(addprefix $(OBJDIR)/,$(notdir $(SRCS:%.c=%.o)))

NAME := fractol

CC := gcc
CFLAGS := -Wall -Wextra -Werror -O3 -I $(INCDIR)/
MLXFLAGS := -lmlx -framework OpenGL -framework AppKit
DEPFLAGS = -MT $@ -MMD -MF $(DEPDIR)/$*.tmpd

COMPILE.c = $(CC) $(CFLAGS) $(DEPFLAGS) -c -o
LINK.c = $(CC) $(CFLAGS) $(MLXFLAGS) -o
POSTCOMPILE = mv -f $(DEPDIR)/$*.tmpd $(DEPDIR)/$*.d && touch $@

MKDIR = mkdir -p $@
RM := rm -rf

$(NAME): $(OBJS)
	$(LINK.c) $@ $^

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPDIR)/%.d | $(OBJDIR) $(DEPDIR)
	$(COMPILE.c) $@ $<
	@$(POSTCOMPILE)

$(OBJDIR):
	@$(MKDIR)

$(DEPDIR):
	@$(MKDIR)

DEPS := $(addprefix $(DEPDIR)/,$(notdir $(SRCS:%.c=%.d)))
$(DEPS):
include $(wildcard $(DEPS))

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
