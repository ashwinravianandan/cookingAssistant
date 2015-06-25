
CookingPlanner.out : main.o CFoodMenu.o CFoodDatabase.o
	g++ -std=c++11 -o CookingPlanner.out -L/usr/local/lib main.o CFoodMenu.o CFoodDatabase.o -ljsoncpp

main.o: main.cpp
	g++ -std=c++11 -c main.cpp -o main.o


CFoodMenu.o: CFoodMenu.cpp
	g++ -std=c++11 -c CFoodMenu.cpp -o CFoodMenu.o


CFoodDatabase.o: CFoodDatabase.cpp
	g++ -std=c++11 -c CFoodDatabase.cpp -o CFoodDatabase.o
