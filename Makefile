##
## EPITECH PROJECT, 2023
## RayTracer
## File description:
## Makefile
##

SRC_DIRS = ./src

BIN = raytracer

DEBUG = no

ifeq ($(DEBUG),yes)
	CFLAGS += -g3
endif

SRCS := $(shell find $(SRC_DIRS) -name "*.cpp")
SRC_TESTS = src/Maths/Vector3.cpp \
			src/Maths/Matrix4.cpp \
			src/Primitives/Sphere.cpp \
			src/Textures/ChessTexture.cpp \
			src/core/Engine/Camera.cpp \
			src/core/Engine/BoundingBoxes.cpp \
			src/core/Engine/Ray.cpp \
			src/Textures/BaseTexture.cpp

OBJS = $(SRCS:.cpp=.o)

CPPFLAGS = $(shell find ./include -type d | awk '{printf "-I%s ", $$0}')
CPPFLAGS += -g3

CRITERION = --coverage -lcriterion

LDLIBS = -lconfig++

CC = g++

all : $(BIN)

$(BIN) : $(OBJS)
	@$(CC) $(OBJS) -o $(BIN) $(LDFLAGS) $(LDLIBS) $(CRITERION)

%.o :	%.cpp
	@echo "\e[92;1m[\e[36;1m⏳ \e[92;1m] \
\e[1;32mCompiling\e[1;35m $< \e[1;32m...\e[1;0m"
	@$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
	@echo "    \e[32;1m✔ \e[34m\"\e[1;35m$(@)\e[34m\" \
\e[1;32mSuccessfully compiled !"

tests_run:
	@$(CC) -o unit_tests $(SRC_TESTS) $(shell find ./tests -name "*.cpp") $(CFLAGS) $(CPPFLAGS) $(LDLIBS) $(CRITERION)
	@./unit_tests

re : fclean all

fclean : clean
	@ $(RM) -rf $(BIN)
	@ $(RM) -rf unit_tests

clean :
	@ $(RM) -rf $(OBJS)
	@ $(RM) -rf *.gcda
	@ $(RM) -rf *.gcno
