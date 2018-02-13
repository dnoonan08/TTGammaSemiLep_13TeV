#include"EventTree.h"
#include<iostream>
#include<cstdlib>
#include <math.h>

double dR(double eta1, double phi1, double eta2, double phi2);

//double secondMinDr(int myInd, const EventTree* tree)
double minGenDr(int myInd, const EventTree* tree){
	double myEta = tree->mcEta->at(myInd); 
	double myPhi = tree->mcPhi->at(myInd);
	int myPID = tree->mcPID->at(myInd);

	double mindr = 999.0;
	double dr;
	int bestInd = -1;
	for( int oind = 0; oind < tree->nMC_; oind++){
		if(oind == myInd) continue;
		//		if(tree->mcMass->at(oind) > 10) continue; // this is top or W, not final state particle
		if(tree->mcStatus->at(oind) != 1) continue; // check if it's final state
		if(tree->mcPt->at(oind) < 5)  continue;
		int opid = abs(tree->mcPID->at(oind));
		if(opid == 12 || opid == 14 || opid == 16) continue; // skip neutrinos
		dr = dR(myEta, myPhi, tree->mcEta->at(oind), tree->mcPhi->at(oind));
		if( mindr > dr ) {
			mindr = dr;
			bestInd = oind;
		}
	}
	//	cout << tree->event_ << "  " << mindr << "  " << bestInd << "  " << tree->mcPID->at(bestInd) << "  " << tree->mcPt->at(bestInd) << endl;
	return mindr;
}

bool overlapRemovalTT(EventTree* tree){
	const double Et_cut = 13;
	const double Eta_cut = 3.0;
	bool haveOverlap = false;
	for(int mcInd=0; mcInd<tree->nMC_; ++mcInd){
		if(tree->mcPID->at(mcInd)==22 &&
		   tree->mcPt->at(mcInd) > Et_cut &&
		   fabs(tree->mcEta->at(mcInd)) < Eta_cut &&
		   (fabs(tree->mcMomPID->at(mcInd))<37 || tree->mcMomPID->at(mcInd) == -999)  && (fabs(tree->mcGMomPID->at(mcInd))<37 || tree->mcGMomPID->at(mcInd) -999)  ) {
			//			(tree->mcParentage->at(mcInd)==2 || tree->mcParentage->at(mcInd)==10 || tree->mcParentage->at(mcInd)==26) ) {
			// candidate for signal photon. check dR to other gen particles to confirm
			double minDR = minGenDr(mcInd, tree);
			
			if(minDR > 0.2) {
				haveOverlap = true;
			}
		}
	}
	return haveOverlap;
}

bool overlapRemovalWZ(EventTree* tree){
	const double Et_cut = 10;
	const double Eta_cut = 2.6;
	bool haveOverlap = false;
	for(int mcInd=0; mcInd<tree->nMC_; ++mcInd){
		if(tree->mcPID->at(mcInd)==22 &&
		   tree->mcPt->at(mcInd) > Et_cut &&
		   fabs(tree->mcEta->at(mcInd)) < Eta_cut &&
		   (fabs(tree->mcMomPID->at(mcInd))<37 || tree->mcMomPID->at(mcInd) == -999)  && (fabs(tree->mcGMomPID->at(mcInd))<37 || tree->mcGMomPID->at(mcInd) -999)  ) {
			//		   (tree->mcParentage->at(mcInd)==2 || tree->mcParentage->at(mcInd)==10 || tree->mcParentage->at(mcInd)==26) ) {
			if(minGenDr(mcInd, tree) > 0.2) {
				haveOverlap = true;
			}
		}
	}
	return haveOverlap;
}


bool overlapRemoval_Tchannel(EventTree* tree){
	const double Et_cut = 10;
	const double Eta_cut = 2.6;
	bool haveOverlap = false;
	for(int mcInd=0; mcInd<tree->nMC_; ++mcInd){
		if(tree->mcPID->at(mcInd)==22 &&
		   tree->mcPt->at(mcInd) > Et_cut &&
		   fabs(tree->mcEta->at(mcInd)) < Eta_cut &&
		   (tree->mcParentage->at(mcInd)==2 || tree->mcParentage->at(mcInd)==10) ) {
			// TGJets doesn't include photons from top decay, so if gmom is top continue (don't remove)
			if (abs(tree->mcGMomPID->at(mcInd))==6){ 
				continue;
			}
			else if(minGenDr(mcInd, tree) > 0.05) {
				haveOverlap = true;
			}
		}
	}
	return haveOverlap;
}
