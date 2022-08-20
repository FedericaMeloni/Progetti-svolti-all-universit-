
OUTPUT = SpaceDefender
SORGENTI = main.o controlli.o navicelle.o grafica.o 
LIBRERIE = -lncurses 

SpaceDefender: $(SORGENTI)
	cc -o $(OUTPUT) $(SORGENTI) $(LIBRERIE)
	
main.o: main.c macro.h 
	cc -c -o main.o main.c

controlli.o: controlli.c macro.h
	cc -c -o controlli.o controlli.c

navicelle.o: navicelle.c  macro.h
	cc -c -o navicelle.o navicelle.c

grafica.o: grafica.c macro.h
	cc -c -o grafica.o grafica.c
	

clean:
	rm *.o $(OUTPUT)


