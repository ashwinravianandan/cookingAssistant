
CookingPlanner.out : main.o
	g++ -std=c++11 -o CookingPlanner.out -L/usr/local/lib main.o -ljsoncpp

main.o: main.cpp
	g++ -std=c++11 -c main.cpp -o main.o
