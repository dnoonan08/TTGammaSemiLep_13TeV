.PHONY: JEC

all: JEC Selector.o EventTree.o EventPick.o makeSkim makeAnalysisNtuple makeCutflows checkOverlap

makeSkim: Selector.o EventPick.o EventTree.o  makeSkim.cpp OverlapRemove.cpp
	g++ -o makeSkim `root-config --libs` -I`root-config --incdir` -std=c++11 EventTree.o EventPick.o Selector.o  OverlapRemove.cpp makeSkim.cpp 

makeCutflows: Selector.o EventPick.o EventTree.o  makeCutflows.cpp OverlapRemove.cpp BTagCalibrationStandalone.o PUReweight.cpp PUReweight.h ScaleFactors.h
	g++ -o makeCutflows `root-config --libs` -I`root-config --incdir` -std=c++11 EventTree.o EventPick.o Selector.o  OverlapRemove.cpp makeCutflows.cpp BTagCalibrationStandalone.o PUReweight.cpp

checkOverlap: EventTree.o  checkOverlap.cpp OverlapRemove.cpp Selector.o
	g++ -o checkOverlap `root-config --libs` -I`root-config --incdir` -std=c++11 EventTree.o Selector.o OverlapRemove.cpp checkOverlap.cpp 

EventTree.o: EventTree.cpp EventTree.h
	g++ -c -I`root-config --incdir` -std=c++11 EventTree.cpp

BTagCalibrationStandalone.o: BTagCalibrationStandalone.cpp BTagCalibrationStandalone.h
	g++ -c -I`root-config --incdir` -std=c++11 BTagCalibrationStandalone.cpp

JEC: JEC/FactorizedJetCorrector.cpp JEC/JetCorrectorParameters.cpp JEC/SimpleJetCorrector.cpp JEC/JetCorrectionUncertainty.cpp JEC/SimpleJetCorrectionUncertainty.cpp
	$(MAKE) -C JEC

makeAnalysisNtuple: Selector.o EventPick.o EventTree.o makeAnalysisNtuple.C makeAnalysisNtuple.h OverlapRemove.cpp JetResolutions.h PUReweight.cpp PUReweight.h BTagCalibrationStandalone.o ScaleFactors.h JEC/JECvariation.o TopEventCombinatorics.cpp
	g++ -o makeAnalysisNtuple `root-config --libs` -I`root-config --incdir` -std=c++11 makeAnalysisNtuple.C EventTree.o EventPick.o Selector.o  OverlapRemove.cpp  PUReweight.cpp BTagCalibrationStandalone.o JEC/FactorizedJetCorrector.o JEC/JetCorrectorParameters.o JEC/SimpleJetCorrector.o JEC/JetCorrectionUncertainty.o JEC/SimpleJetCorrectionUncertainty.o JEC/JECvariation.o METzCalculator.cpp TopEventCombinatorics.cpp 

Selector.o: EventTree.o Selector.cpp Selector.h
	g++ -c -I`root-config --incdir` -std=c++11 Selector.cpp

EventPick.o: Selector.o EventPick.cpp EventPick.h
	g++ -c -I `root-config --incdir` -std=c++11 EventPick.cpp 

clean:
	rm EventTree.o Selector.o EventPick.o BTagCalibrationStandalone.o
	$(MAKE) -C JEC clean