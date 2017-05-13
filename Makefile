trading_system : trading_system.cc file_description.cc main.cc
	g++ -std=c++11 -g -o trading_system trading_system.cc file_description.cc main.cc

clean:
	rm -f trading_system
