OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Cluster.o Area_espera.o Prioridad.o Proceso.o Procesador.o
	g++ -o program.exe program.o Cluster.o Area_espera.o Prioridad.o Proceso.o Procesador.o $(OPCIONS)

Cluster.o: Cluster.cc Cluster.hh
	g++ -c Cluster.cc $(OPCIONS)

Area_espera.o: Area_espera.cc Area_espera.hh
	g++ -c Area_espera.cc $(OPCIONS)

Prioridad.o: Prioridad.cc Prioridad.hh
	g++ -c Prioridad.cc $(OPCIONS)

Proceso.o: Proceso.cc Proceso.hh
	g++ -c Proceso.cc $(OPCIONS)

Procesador.o: Procesador.cc Procesador.hh
	g++ -c Procesador.cc $(OPCIONS)

program.o: program.cc Area_espera.hh Procesador.hh Prioridad.hh Proceso.hh Cluster.hh
	g++ -c program.cc $(OPCIONS)

practica.tar:
	tar -cvf practica.tar Area_espera.hh Procesador.hh Prioridad.hh Proceso.hh Cluster.hh Area_espera.cc Procesador.cc Prioridad.cc Proceso.cc Cluster.cc program.cc Makefile
