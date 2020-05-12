.PHONY: JEC

GIT_COMMIT_FULL := "$(shell git log -1 --oneline)"
GIT_COMMIT := "$(shell git rev-parse HEAD)"
GIT_COMMIT_TIME := "$(shell git show -s --format=%ci $(GIT_COMMIT))"
GIT_BRANCH := "$(shell git rev-parse --abbrev-ref HEAD)"
GIT_STATUS := "$(shell git status -uno -s)"

all: JEC Selector.o EventTree.o EventPick.o makeAnalysisNtuple #makeCutflows testLepSF

testLepSF: testLepSF.cpp muSF_reader.h eleSF_reader.h phoSF_reader.h
	g++ -o testLepSF `root-config --libs` -I`root-config --incdir` -std=c++17 testLepSF.cpp 

# makeSkim: Selector.o EventPick.o EventTree.o  makeSkim.cpp OverlapRemove.cpp
# 	g++ -o makeSkim `root-config --libs` -I`root-config --incdir` -std=c++17 EventTree.o EventPick.o Selector.o ParsePhotonID.cpp OverlapRemove.cpp makeSkim.cpp -DVERSION=\"$(GIT_VERSION)\" -DBRANCH=\"$(GIT_BRANCH)\" -DSTATUS=\"$(GIT_STATUS)\"

# makeCutflows: Selector.o EventPick.o EventTree.o  makeCutflows.cpp OverlapRemove.cpp BTagCalibrationStandalone.o PUReweight.cpp PUReweight.h ScaleFactors.h
# 	g++ -o makeCutflows `root-config --libs` -I`root-config --incdir` -std=c++17 EventTree.o EventPick.o Selector.o  OverlapRemove.cpp makeCutflows.cpp BTagCalibrationStandalone.o PUReweight.cpp


# makeCutflows_gen2: Selector_gen.o EventPick_gen.o EventTree.o  makeCutflows_gen2.cpp OverlapRemove.cpp BTagCalibrationStandalone.o PUReweight.cpp PUReweight.h ScaleFactors.h
# 	g++ -o makeCutflows_gen2 `root-config --libs` -I`root-config --incdir` -std=c++17 EventTree.o EventPick_gen.o Selector_gen.o  OverlapRemove.cpp makeCutflows_gen2.cpp BTagCalibrationStandalone.o PUReweight.cpp


# checkOverlap: EventTree.o  checkOverlap.cpp OverlapRemove.cpp Selector.o
# 	g++ -o checkOverlap `root-config --libs` -I`root-config --incdir` -std=c++17 EventTree.o Selector.o OverlapRemove.cpp checkOverlap.cpp 

EventTree.o: EventTree.cpp EventTree.h
	g++ -c -I`root-config --incdir` -std=c++17 -D STANDALONE EventTree.cpp

BTagCalibrationStandalone.o: BTagCalibrationStandalone.cpp BTagCalibrationStandalone.h
	g++ -c -I`root-config --incdir` -std=c++17 -D STANDALONE BTagCalibrationStandalone.cpp

JEC: JEC/FactorizedJetCorrector.cpp JEC/JetCorrectorParameters.cpp JEC/SimpleJetCorrector.cpp JEC/JetCorrectionUncertainty.cpp JEC/SimpleJetCorrectionUncertainty.cpp
	$(MAKE) -C JEC

makeAnalysisNtuple: Selector.o EventPick.o EventTree.o makeAnalysisNtuple.C makeAnalysisNtuple.h OverlapRemove.cpp PUReweight.cpp PUReweight.h BTagCalibrationStandalone.o ScaleFactorFunction.h JEC/JECvariation.o TopEventCombinatorics.cpp muSF_reader.h eleSF_reader.h phoSF_reader.h
	g++ -o makeAnalysisNtuple `root-config --libs` -I`root-config --incdir` -std=c++17 -D STANDALONE makeAnalysisNtuple.C EventTree.o EventPick.o ParsePhotonID.cpp Selector.o  OverlapRemove.cpp  PUReweight.cpp BTagCalibrationStandalone.o JEC/FactorizedJetCorrector.o JEC/JetCorrectorParameters.o JEC/SimpleJetCorrector.o JEC/JetCorrectionUncertainty.o JEC/SimpleJetCorrectionUncertainty.o JEC/JECvariation.o JEC/JetResolution.cc JEC/JetResolutionObject.cc METzCalculator.cpp TopEventCombinatorics.cpp -DVERSION=\"$(GIT_COMMIT_FULL)\" -DBRANCH=\"$(GIT_BRANCH)\" -DSTATUS=\"$(GIT_STATUS)\" -DCOMMITTIME=\"$(GIT_COMMIT_TIME)\"


Selector.o: EventTree.o Selector.cpp Selector.h
	g++ -c -I `root-config --incdir` -std=c++17 -D STANDALONE ParsePhotonID.cpp JEC/JetResolution.cc JEC/JetResolutionObject.cc  Selector.cpp

EventPick.o: Selector.o EventPick.cpp EventPick.h
	g++ -c -I `root-config --incdir` -std=c++17 -D STANDALONE EventPick.cpp 

Selector_gen.o: EventTree.o Selector_gen.cpp Selector.h
	g++ -c -I`root-config --incdir` -std=c++17 -D STANDALONE Selector_gen.cpp

EventPick_gen.o: Selector_gen.o EventPick_gen.cpp EventPick.h
	g++ -c -I `root-config --incdir` -std=c++17 -D STANDALONE EventPick_gen.cpp 

clean:
	rm EventTree.o Selector.o EventPick.o BTagCalibrationStandalone.o makeAnalysisNtuple
	$(MAKE) -C JEC clean
