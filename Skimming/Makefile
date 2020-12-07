GIT_COMMIT_FULL := "$(shell git log -1 --oneline)"
GIT_COMMIT := "$(shell git rev-parse HEAD)"
GIT_COMMIT_TIME := "$(shell git show -s --format=%ci $(GIT_COMMIT))"
GIT_BRANCH := "$(shell git rev-parse --abbrev-ref HEAD)"
GIT_STATUS := "$(shell git status -uno -s)"

all: EventTree_Skim.o EventPick_Skim.o makeSkim 

makeSkim:  EventPick_Skim.o EventTree_Skim.o  makeSkim.cpp 
	g++ -o makeSkim `root-config --libs` -I`root-config --incdir` -std=c++17 EventTree_Skim.o EventPick_Skim.o makeSkim.cpp -DVERSION=\"$(GIT_COMMIT_FULL)\" -DBRANCH=\"$(GIT_BRANCH)\" -DSTATUS=\"$(GIT_STATUS)\" -DCOMMITTIME=\"$(GIT_COMMIT_TIME)\"

EventTree_Skim.o: EventTree_Skim.cpp EventTree_Skim.h
	g++ -c -I`root-config --incdir` -std=c++17 EventTree_Skim.cpp

EventPick_Skim.o: EventPick_Skim.cpp EventPick_Skim.h
	g++ -c -I `root-config --incdir` -std=c++17 EventPick_Skim.cpp 


clean:
	rm EventTree_Skim.o makeSkim EventPick_Skim.o
