INCLUDES_CPP = /home/mingjian/pro2/cplus/includes

pro2.exe:
	g++ -c *.cpp -D_GLIBCXX_DEBUG -I$(INCLUDES_CPP)
	g++ -o pro2.exe *.o

clean:
	rm -f *.o
	rm -f *.exe
