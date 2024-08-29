all: clean compile link cleanObjAndRun

link:
	g++ -o bin/'warehouse' bin/main.o bin/Order.o bin/Customer.o bin/Volunteer.o bin/LimitedDriver.o bin/WareHouse.o bin/Driver.o bin/Action.o bin/CivilianCustomer.o bin/SoldierCustomer.o bin/Collector.o bin/LimitedCollector.o

compile:
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/main.o src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Order.o src/Order.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Customer.o src/Customer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Volunteer.o src/Volunteer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Collector.o src/Collector.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/WareHouse.o src/WareHouse.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Driver.o src/Driver.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Action.o src/Action.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/CivilianCustomer.o src/CivilianCustomer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/SoldierCustomer.o src/SoldierCustomer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/LimitedCollector.o src/LimitedCollector.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/LimitedDriver.o src/LimitedDriver.cpp


clean:
	rm -f bin/*


cleanObjAndRun:
	rm -f *.o
	clear
	valgrind --leak-check=full --show-reachable=yes ./bin/'warehouse' ./run/configFileExample.txt
