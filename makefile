HEADERS = main.h menubar.h read_mnist.h otmath.h command.h program_info.h som.h utilities.h chart_plot_lib.h vlist.h

main: menubar.o main.o read_mnist.o otmath.o command.o som.o utilities.o chart_plot_lib.o vlist.o
	gcc `pkg-config --cflags gtk+-3.0` -g -ggdb -o main menubar.o main.o read_mnist.o otmath.o command.o som.o utilities.o chart_plot_lib.o vlist.o `pkg-config --libs gtk+-3.0` -lm

main.o: main.c $(HEADERS)
	gcc `pkg-config --cflags gtk+-3.0` -c main.c

som.o: som.c $(HEADERS)
	gcc `pkg-config --cflags gtk+-3.0` -c som.c

menubar.o: menubar.c $(HEADERS) 
	gcc `pkg-config --cflags gtk+-3.0` -c menubar.c

read_mnist.o: read_mnist.c $(HEADERS)
	gcc -c read_mnist.c

otmath.o: otmath.c $(HEADERS)
	gcc -c otmath.c

command.o: command.c $(HEADERS)
	gcc `pkg-config --cflags gtk+-3.0` -c command.c

utilities.o: utilities.c $(HEADERS)
	gcc `pkg-config --cflags gtk+-3.0` -c utilities.c

chart_plot_lib.o: chart_plot_lib.c $(HEADERS)
	gcc `pkg-config --cflags gtk+-3.0` -c chart_plot_lib.c

vlist.o: vlist.c $(HEADERS)
	gcc -c vlist.c

clean:
	rm main main.o menubar.o otmath.o command.o utilities.o chart_plot_lib.o vlist.o som.o
