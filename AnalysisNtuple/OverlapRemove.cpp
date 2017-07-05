#include"EventTree.h"
#include<iostream>
#include<cstdlib>
#include <math.h>

double dR(double eta1, double phi1, double eta2, double phi2);

//double secondMinDr(int myInd, const EventTree* tree)
double minDr(int myInd, const EventTree* tree){
	double myEta = tree->mcEta->at(myInd); 
	double myPhi = tree->mcPhi->at(myInd);
	int myPID = tree->mcPID->at(myInd);

	double mindr = 999.0;
	double dr;
	int bestInd = -1;
	for( int oind = 0; oind < tree->nMC_; oind++){
		if(oind == myInd) continue;
		if(tree->mcMass->at(oind) > 10) continue; // this is top or W, not final state particle
		int opid = abs(tree->mcPID->at(oind));
		if(opid == 12 || opid == 14 || opid == 16) continue; // skip neutrinos
		dr = dR(myEta, myPhi, tree->mcEta->at(oind), tree->mcPhi->at(oind));
		if( mindr > dr ) {
			mindr = dr;
			bestInd = oind;
		}
	}
	return dr;
}

bool overlapRemovalTT(EventTree* tree){
	const double Et_cut = 13;
	const double Eta_cut = 3.0;
	bool haveOverlap = false;
	for(int mcInd=0; mcInd<tree->nMC_; ++mcInd){
		//if(tree->mcIndex->at(mcInd) > 100) break;
		if(tree->mcPID->at(mcInd)==22 &&
		tree->mcPt->at(mcInd) > Et_cut &&
		fabs(tree->mcEta->at(mcInd)) < Eta_cut &&
		(tree->mcParentage->at(mcInd)==2 || tree->mcParentage->at(mcInd)==10 || tree->mcParentage->at(mcInd)==26) ) {
			// candidate for signal photon. check dR to other gen particles to confirm
			if(minDr(mcInd, tree) > 0.2) {
				haveOverlap = true;
			}
		}
	}
	return haveOverlap;
}
