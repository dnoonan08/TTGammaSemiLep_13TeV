all: EventTree_Skim.o EventPick_Skim.o makeSkim 

makeSkim:  EventPick_Skim.o EventTree_Skim.o  makeSkim.cpp 
	g++ -o makeSkim `root-config --libs` -I`root-config --incdir` -std=c++17 EventTree_Skim.o EventPick_Skim.o makeSkim.cpp 

EventTree_Skim.o: EventTree_Skim.cpp EventTree_Skim.h
	g++ -c -I`root-config --incdir` -std=c++17 EventTree_Skim.cpp

EventPick_Skim.o: EventPick_Skim.cpp EventPick_Skim.h
	g++ -c -I `root-config --incdir` -std=c++17 EventPick_Skim.cpp 


clean:
	rm EventTree_Skim.o makeSkim EventPick_Skim.o
