
#ifndef PUREWEIGHT_H
#define PUREWEIGHT_H

#include<TH1F.h>
#include<TFile.h>
#include<iostream>
#include<vector>
#include<string>

class PUReweight{
public:
	PUReweight(int nFiles, char** fileNames, std::string PUfilename);
	~PUReweight();
	double getWeight(int nPUInfo, std::vector<int> *puBX, std::vector<float> *puTrue);
	double getAvgWeight();
	
private:
	double PUweightSum;
	long int events;
	TH1D* PUweightHist;
};

#endif
