OPCIONS2 = -std=c++11
OPCIONS1 = -std=c++11 -D_GLIBCXX_DEBUG
OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Proces.o Processador.o Cluster.o Prioritat.o AreaEspera.o
	g++ -o program.exe program.o Proces.o Processador.o Cluster.o Prioritat.o AreaEspera.o

Proces.o:  Proces.cc Proces.hh
	g++ -c Proces.cc $(OPCIONS)

Processador.o:  Processador.cc Processador.hh
	g++ -c Processador.cc $(OPCIONS)

Cluster.o:  Cluster.cc Cluster.hh
	g++ -c Cluster.cc $(OPCIONS)

Prioritat.o:  Prioritat.cc Prioritat.hh
	g++ -c Prioritat.cc $(OPCIONS)

AreaEspera.o: AreaEspera.cc AreaEspera.hh
	g++ -c AreaEspera.cc $(OPCIONS)

program.o: program.cc
	g++ -c program.cc $(OPCIONS)

clean:
	rm *.o
	rm *.exe