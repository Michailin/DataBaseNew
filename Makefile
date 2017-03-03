main.o : main.cpp
	g++ -c main.cpp -g -o main.o
database.o : DataBase.cpp 
	g++ -c DataBase.cpp -g -o database.o
compare.o : compare.cpp
	g++ -c compare.cpp -g -o compare.o
main : main.o database.o compare.o
	g++ main.o database.o compare.o -g -o main
remove : 
	rm -f main main.o database.o compare.o