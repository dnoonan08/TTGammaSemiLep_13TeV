.PHONY: JEC

GIT_COMMIT := "$(shell git log -1 --oneline)"
GIT_COMMIT_TIME := "$(shell git show -s --format=%ci $(GIT_COMMIT))"
GIT_BRANCH := "$(shell git rev-parse --abbrev-ref HEAD)"
GIT_STATUS := "$(shell git status -uno -s)"

all: JEC Selector.o EventTree.o EventPick.o makeSkim makeAnalysisNtuple #makeCutflows testLepSF

testLepSF: testLepSF.cpp muSF_reader.h eleSF_reader.h phoSF_reader.h
	g++ -o testLepSF `root-config --libs` -I`root-config --incdir` -std=c++17 testLepSF.cpp 

makeSkim: Selector.o EventPick.o EventTree.o  makeSkim.cpp OverlapRemove.cpp
	g++ -o makeSkim `root-config --libs` -I`root-config --incdir` -std=c++17 EventTree.o EventPick.o Selector.o  OverlapRemove.cpp makeSkim.cpp -DVERSION=\"$(GIT_VERSION)\" -DBRANCH=\"$(GIT_BRANCH)\" -DSTATUS=\"$(GIT_STATUS)\"

makeCutflows: Selector.o EventPick.o EventTree.o  makeCutflows.cpp OverlapRemove.cpp BTagCalibrationStandalone.o PUReweight.cpp PUReweight.h ScaleFactors.h
	g++ -o makeCutflows `root-config --libs` -I`root-config --incdir` -std=c++17 EventTree.o EventPick.o Selector.o  OverlapRemove.cpp makeCutflows.cpp BTagCalibrationStandalone.o PUReweight.cpp


makeCutflows_gen2: Selector_gen.o EventPick_gen.o EventTree.o  makeCutflows_gen2.cpp OverlapRemove.cpp BTagCalibrationStandalone.o PUReweight.cpp PUReweight.h ScaleFactors.h
	g++ -o makeCutflows_gen2 `root-config --libs` -I`root-config --incdir` -std=c++17 EventTree.o EventPick_gen.o Selector_gen.o  OverlapRemove.cpp makeCutflows_gen2.cpp BTagCalibrationStandalone.o PUReweight.cpp


checkOverlap: EventTree.o  checkOverlap.cpp OverlapRemove.cpp Selector.o
	g++ -o checkOverlap `root-config --libs` -I`root-config --incdir` -std=c++17 EventTree.o Selector.o OverlapRemove.cpp checkOverlap.cpp 

EventTree.o: EventTree.cpp EventTree.h
	g++ -c -I`root-config --incdir` -std=c++17 EventTree.cpp

BTagCalibrationStandalone.o: BTagCalibrationStandalone.cpp BTagCalibrationStandalone.h
	g++ -c -I`root-config --incdir` -std=c++17 BTagCalibrationStandalone.cpp

JEC: JEC/FactorizedJetCorrector.cpp JEC/JetCorrectorParameters.cpp JEC/SimpleJetCorrector.cpp JEC/JetCorrectionUncertainty.cpp JEC/SimpleJetCorrectionUncertainty.cpp
	$(MAKE) -C JEC

makeAnalysisNtuple: Selector.o EventPick.o EventTree.o makeAnalysisNtuple.C makeAnalysisNtuple.h OverlapRemove.cpp JetResolutions.h PUReweight.cpp PUReweight.h BTagCalibrationStandalone.o ScaleFactorFunction.h JEC/JECvariation.o TopEventCombinatorics.cpp muSF_reader.h eleSF_reader.h phoSF_reader.h
	g++ -o makeAnalysisNtuple `root-config --libs` -I`root-config --incdir` -std=c++17 makeAnalysisNtuple.C EventTree.o EventPick.o Selector.o  OverlapRemove.cpp  PUReweight.cpp BTagCalibrationStandalone.o JEC/FactorizedJetCorrector.o JEC/JetCorrectorParameters.o JEC/SimpleJetCorrector.o JEC/JetCorrectionUncertainty.o JEC/SimpleJetCorrectionUncertainty.o JEC/JECvariation.o METzCalculator.cpp TopEventCombinatorics.cpp -DVERSION=\"$(GIT_COMMIT)\" -DBRANCH=\"$(GIT_BRANCH)\" -DSTATUS=\"$(GIT_STATUS)\" -DCOMMITTIME=\"$(GIT_COMMIT_TIME)\"


Selector.o: EventTree.o Selector.cpp Selector.h
	g++ -c -I`root-config --incdir` -std=c++17 Selector.cpp

EventPick.o: Selector.o EventPick.cpp EventPick.h
	g++ -c -I `root-config --incdir` -std=c++17 EventPick.cpp 


Selector_gen.o: EventTree.o Selector_gen.cpp Selector.h
	g++ -c -I`root-config --incdir` -std=c++17 Selector_gen.cpp

EventPick_gen.o: Selector_gen.o EventPick_gen.cpp EventPick.h
	g++ -c -I `root-config --incdir` -std=c++17 EventPick_gen.cpp 

clean:
	rm EventTree.o Selector.o EventPick.o BTagCalibrationStandalone.o
	$(MAKE) -C JEC clean
