#include"EventTree.h"
#include<iostream>
#include<cstdlib>
#include <math.h>

double dR(double eta1, double phi1, double eta2, double phi2);

bool overlapWHIZARD(EventTree* tree){
	const double Et_cut = 20;
	const double dR_cut = 0.1;
	// consider only mcParticles here
	bool haveOverlap = false;
	for(int phoInd=0; phoInd<tree->nMC_; ++phoInd){
		// find photons with Et above cut and that came from ISR or top
		if(tree->mcPID->at(phoInd)==22 && tree->mcPt->at(phoInd) > Et_cut && (tree->mcParentage->at(phoInd)==2 || (tree->mcParentage->at(phoInd)==10 && abs(tree->mcMomPID->at(phoInd))==24))){
			bool closeToLeg = false;
			bool haveLeg = false;
			// find "legs" (b-qark coming from top)
			for(int legInd=0; legInd<tree->nMC_; ++legInd){
				if(abs(tree->mcPID->at(legInd))==5 && abs(tree->mcMomPID->at(legInd))==6){
					haveLeg=true;
					if(dR(tree->mcEta->at(phoInd),tree->mcPhi->at(phoInd),tree->mcEta->at(legInd),tree->mcPhi->at(legInd)) < dR_cut) closeToLeg=true;
				}
			}
			if(haveLeg && !closeToLeg) haveOverlap = true;
		}
	}
	if (0 && !haveOverlap){
		std::cout << "no overlap" << std::endl;
		for(int legInd=0; legInd<tree->nMC_; ++legInd)
			std::cout << "PID " << tree->mcPID->at(legInd) 
			<< "  Pt " << tree->mcPt->at(legInd) 
			<< "  Eta " << tree->mcEta->at(legInd) 
			<< "  Phi " << tree->mcPhi->at(legInd) << std::endl;
	}
	return haveOverlap;
}


double secondMinDr(int myInd, const EventTree* tree){
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

bool overlapISRFSR(EventTree* tree){
	const double Et_cut = 13;
	const double Eta_cut = 3.0;
	bool haveOverlap = false;
	for(int mcInd=0; mcInd<tree->nMC_; ++mcInd){
		if(tree->mcPID->at(mcInd)==22 &&
		tree->mcPt->at(mcInd) > Et_cut &&
		fabs(tree->mcEta->at(mcInd)) < Eta_cut){
			if(abs(tree->mcMomPID->at(mcInd)) == 24 || tree->mcParentage->at(mcInd)==26 || (tree->mcParentage->at(mcInd)==2)){
				if(secondMinDr(mcInd, tree) > 0.2)
					haveOverlap = true;
			}
		}
	}
	return haveOverlap;
}

bool overlapMadGraph(EventTree* tree){
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
			if(secondMinDr(mcInd, tree) > 0.2) 
				haveOverlap = true;
		}
	}
	return haveOverlap;
}


bool isSignalPhoton(EventTree* tree, int mcInd, int recoPhoInd){
	bool parentagePass = tree->mcParentage->at(mcInd)==2 || tree->mcParentage->at(mcInd)==10 || tree->mcParentage->at(mcInd)==26;
	double dptpt = (tree->phoEt_->at(recoPhoInd) - tree->mcPt->at(mcInd)) / tree->mcPt->at(mcInd);
	bool dptptPass = dptpt < 0.1;
	bool drotherPass = secondMinDr(mcInd, tree) > 0.2;
	bool detarecogenPass = fabs(tree->phoEta_->at(recoPhoInd) - tree->mcEta->at(mcInd)) < 0.005;
	bool drrecogenPass = dR(tree->mcEta->at(mcInd),tree->mcPhi->at(mcInd),tree->phoEta_->at(recoPhoInd),tree->phoPhi_->at(recoPhoInd)) < 0.01;
	if(parentagePass && dptptPass && drotherPass && detarecogenPass && drrecogenPass) return true;
	else return false;
}

bool isGoodElectron(EventTree* tree, int mcInd, int recoPhoInd){
	bool parentagePass = tree->mcParentage->at(mcInd)==10;
	double dptpt = (tree->phoEt_->at(recoPhoInd) - tree->mcPt->at(mcInd)) / tree->mcPt->at(mcInd);
	bool dptptPass = dptpt < 0.1;
	bool drotherPass = secondMinDr(mcInd, tree) > 0.2;
	bool detarecogenPass = fabs(tree->phoEta_->at(recoPhoInd) - tree->mcEta->at(mcInd)) < 0.005;
	bool drrecogenPass = dR(tree->mcEta->at(mcInd),tree->mcPhi->at(mcInd),tree->phoEta_->at(recoPhoInd),tree->phoPhi_->at(recoPhoInd)) < 0.04;
	if(parentagePass && dptptPass && drotherPass && detarecogenPass && drrecogenPass) return true;
	else return false;
}

