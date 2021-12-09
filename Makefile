CC			= g++
STANDARD	= -std=c++20
ERROPTS		= -Wall -Wextra -Werror
ADDOPTS		= -fstack-protector-strong -O2
OPTS		= $(STANDARD) $(ERROPTS) $(ADDOPTS)
CALL		= $(CC) $(OPTS)
BINARY		= clikv

all: main.cpp
	$(CALL) main.cpp -o $(BINARY)

install: all
	cp $(BINARY) /usr/local/bin 
