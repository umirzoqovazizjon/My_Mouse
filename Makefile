CC = gcc
CFLAGC = -Wall -Wextra -Werror #-fsanitize=address -g3
SOURCES = src/*.c
TARGET = my_mouse

$(TARGET):$(SOURCES)
	$(CC) $(CFLAGC) -o $@ $^

clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET)

re: fclean all