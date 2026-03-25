server: main.cpp WebServer.cpp HttpSession.cpp HtmlHandler.cpp ApiHandler.cpp
	@g++ -std=c++11 -o $@ $^ -I../include -lboost_system -lpthread

.PHONY: clean
clean:
	@rm -f server
