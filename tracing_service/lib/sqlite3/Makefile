create_archive: sqlite3.o
	ar -cvq ../libsqlite3.a *.o

%.o : %.c
	gcc -c $< -o $@