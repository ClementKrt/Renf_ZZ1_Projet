CC= gcc        # compilateur
CFLAGS= -Wall -Wextra -g  # options de compilation pour les sources C

sources= draw.c MatriceQ.c main.c
objets= $(sources:.c=.o)
DEPS := $(objets:.o=.d)


copain: $(objets) #créer l'éxecutable à partir de tout les fichier .o
	$(CC) $(CFLAGS) -o $@ $^ -lSDL2 -lSDL2_image -lSDL2_ttf

%.o: %.c #créer les fichiers objets des fichiers .c
	$(CC) $(CFLAGS) -o $@ -c $< -MMD -MP

-include $(DEPS)

clean:
	rm -rf *.o
	rm -rf *.d