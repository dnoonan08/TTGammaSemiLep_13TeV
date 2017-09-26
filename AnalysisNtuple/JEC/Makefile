all: FactorizedJetCorrector.o JetCorrectorParameters.o SimpleJetCorrector.o JetCorrectionUncertainty.o JECvariation.o

clean:
	rm FactorizedJetCorrector.o JetCorrectorParameters.o SimpleJetCorrector.o JetCorrectionUncertainty.o SimpleJetCorrectionUncertainty.o JECvariation.o

JECvariation.o: FactorizedJetCorrector.o JetCorrectorParameters.o SimpleJetCorrector.o JetCorrectionUncertainty.o JECvariation.cpp
	g++ -c `root-config --libs` -I`root-config --incdir` -std=c++11 JECvariation.cpp

FactorizedJetCorrector.o: FactorizedJetCorrector.cpp FactorizedJetCorrector.h JetCorrectorParameters.h SimpleJetCorrector.h Utilities.cc
	g++ -c `root-config --libs` -I`root-config --incdir` -std=c++11 FactorizedJetCorrector.cpp

JetCorrectorParameters.o: JetCorrectorParameters.cpp JetCorrectorParameters.h 
	g++ -c `root-config --libs` -I`root-config --incdir` -std=c++11 JetCorrectorParameters.cpp

SimpleJetCorrector.o: JetCorrectorParameters.cpp JetCorrectorParameters.h SimpleJetCorrector.h
	g++ -c `root-config --libs` -I`root-config --incdir` -std=c++11 SimpleJetCorrector.cpp 

JetCorrectionUncertainty.o: JetCorrectionUncertainty.cpp JetCorrectionUncertainty.h SimpleJetCorrectionUncertainty.cpp SimpleJetCorrectionUncertainty.h
	g++ -c `root-config --libs` -I`root-config --incdir` -std=c++11 JetCorrectionUncertainty.cpp SimpleJetCorrectionUncertainty.cpp 
 
