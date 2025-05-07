test: $(TESTS)
	g++ -std=c++17 -Wall -Wextra -o test_battleship cppBattleship/test_battleship.cpp cppBattleship/battleship.cpp -lcppunit

	./test_battleship 

build:
	g++ cppBattleship/battleship.cpp cppBattleship/main.cpp -o cppBattleship/battleship
lint:
	cppcheck cppBattleship/*.cpp
package:
	./package_and_install.sh