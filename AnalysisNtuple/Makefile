all: Selector.o EventTree.o EventPick.o makeSkim makeAnalysisNtuple

makeSkim: Selector.o EventPick.o EventTree.o  makeSkim.cpp OverlapRemove.cpp
	g++ -o makeSkim `root-config --libs` -I`root-config --incdir` -std=c++11 EventTree.o EventPick.o Selector.o  OverlapRemove.cpp makeSkim.cpp 

EventTree.o: EventTree.cpp EventTree.h
	g++ -c -I`root-config --incdir` -std=c++11 EventTree.cpp

BTagCalibrationStandalone.o: BTagCalibrationStandalone.cpp BTagCalibrationStandalone.h
	g++ -c -I`root-config --incdir` -std=c++11 BTagCalibrationStandalone.cpp

JECUncertainty.o: JECUncertainty.cpp JetDefs.hpp ErrorTypes.cpp ErrorTypes.hpp
	g++ -c -I`root-config --incdir` -std=c++11 JECUncertainty.cpp

makeAnalysisNtuple: Selector.o EventPick.o EventTree.o makeAnalysisNtuple.C OverlapRemove.cpp PUReweight.cpp PUReweight.h BTagCalibrationStandalone.o
	g++ -o makeAnalysisNtuple `root-config --libs` -I`root-config --incdir` -std=c++11 EventTree.o EventPick.o Selector.o  OverlapRemove.cpp makeAnalysisNtuple.C PUReweight.cpp BTagCalibrationStandalone.o

Selector.o: EventTree.o Selector.cpp Selector.h
	g++ -c -I`root-config --incdir` -std=c++11 Selector.cpp

EventPick.o: EventPick.cpp EventPick.h
	g++ -c -I `root-config --incdir` -std=c++11 EventPick.cpp 

clean:
	rm EventTree.o Selector.o EventPick.o BTagCalibrationStandalone.o
