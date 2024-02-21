game.x: main.o getInput.o Screen.o Worm.o circleQ.o
	g++ -ggdb -o game.x main.o getInput.o Screen.o Worm.o circleQ.o -lcurses -ltermcap

main.o: main.cpp getInput.hpp Screen.hpp Worm.hpp circleQ.hpp queue.hpp Cell.hpp
	g++ -c -ggdb main.cpp -o main.o

getInput.o: getInput.cpp
	gcc -c -ggdb getInput.cpp -o getInput.o

circleQ.o: circleQ.cpp queue.hpp Cell.hpp
	gcc -c -ggdb circleQ.cpp -o circleQ.o

Worm.o: Worm.cpp circleQ.hpp queue.hpp
	gcc -c -ggdb Worm.cpp -o Worm.o

Screen.o: Screen.cpp Cell.hpp
	gcc -c -ggdb Screen.cpp -o Screen.o

clean:
	/bin/rm -f game.x *.o *~
