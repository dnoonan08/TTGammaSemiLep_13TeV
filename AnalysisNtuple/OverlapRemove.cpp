#include"EventTree.h"
#include<iostream>
#include<cstdlib>
#include <math.h>

double dR(double eta1, double phi1, double eta2, double phi2);

//double secondMinDr(int myInd, const EventTree* tree)
double minGenDr(int myInd, const EventTree* tree){
    double myEta = tree->GenPart_eta_[myInd]; 
    double myPhi = tree->GenPart_phi_[myInd];
    int myPID = tree->GenPart_pdgId_[myInd];
    
    double mindr = 999.0;
    double dr;
    int bestInd = -1;
    for( int oind = 0; oind < tree->nGenPart_; oind++){
        if(oind == myInd) continue;
        if(tree->GenPart_status_[oind] != 1) continue; // check if it's final state
        if(tree->GenPart_pt_[oind] < 5)  continue;
        int opid = abs(tree->GenPart_pdgId_[oind]);
        if(opid == 12 || opid == 14 || opid == 16) continue; // skip neutrinos
        dr = dR(myEta, myPhi, tree->GenPart_eta_[oind], tree->GenPart_phi_[oind]);
        if( mindr > dr ) {
            mindr = dr;
            bestInd = oind;
        }
    }
    return mindr;
}

bool overlapRemovalTT(EventTree* tree){
    const double Et_cut = 10;
    const double Eta_cut = 5.0;
    bool haveOverlap = false;
    for(int mcInd=0; mcInd<tree->nGenPart_; ++mcInd){
        if(tree->GenPart_pdgId_[mcInd]==22 &&
           tree->GenPart_pt_[mcInd] > Et_cut &&
           fabs(tree->GenPart_eta_[mcInd]) < Eta_cut){
	    
	    Int_t parentIdx = mcInd;
	    int maxPDGID = 0;
	    int motherPDGID = 0;
	    while (parentIdx != -1){
		motherPDGID = std::abs(tree->GenPart_pdgId_[parentIdx]);
		maxPDGID = std::max(maxPDGID,motherPDGID);
		parentIdx = tree->GenPart_genPartIdxMother_[parentIdx];
	    }

	    bool parentagePass = maxPDGID < 37;
	    if (parentagePass) {
		double minDR = minGenDr(mcInd, tree);
			
		if(minDR > 0.1) {
		    haveOverlap = true;
		}
	    }
	}
    }
    return haveOverlap;
}

bool overlapRemovalWJets(EventTree* tree){
    const double Et_cut = 10;
    const double Eta_cut = 2.5;
    bool haveOverlap = false;
    for(int mcInd=0; mcInd<tree->nGenPart_; ++mcInd){
        if(tree->GenPart_pdgId_[mcInd]==22 &&
           tree->GenPart_pt_[mcInd] > Et_cut &&
           fabs(tree->GenPart_eta_[mcInd]) < Eta_cut) {

	    Int_t parentIdx = mcInd;
	    int maxPDGID = 0;
	    int motherPDGID = 0;
	    while (parentIdx != -1){
		motherPDGID = std::abs(tree->GenPart_pdgId_[parentIdx]);
		maxPDGID = std::max(maxPDGID,motherPDGID);
		parentIdx = tree->GenPart_genPartIdxMother_[parentIdx];
	    }

	    bool parentagePass = maxPDGID < 37;
	    
	    if (parentagePass) {
		if(minGenDr(mcInd, tree) > 0.05) {
		    haveOverlap = true;
		}
	    }
        }
    }
    return haveOverlap;
}

bool overlapRemovalZJets(EventTree* tree){
    const double Et_cut = 15;
    const double Eta_cut = 2.6;
    bool haveOverlap = false;
    for(int mcInd=0; mcInd<tree->nGenPart_; ++mcInd){
        if(tree->GenPart_pdgId_[mcInd]==22 &&
           tree->GenPart_pt_[mcInd] > Et_cut &&
           fabs(tree->GenPart_eta_[mcInd]) < Eta_cut) {

	    Int_t parentIdx = mcInd;
	    int maxPDGID = 0;
	    int motherPDGID = 0;
	    while (parentIdx != -1){
		motherPDGID = std::abs(tree->GenPart_pdgId_[parentIdx]);
		maxPDGID = std::max(maxPDGID,motherPDGID);
		parentIdx = tree->GenPart_genPartIdxMother_[parentIdx];
	    }

	    bool parentagePass = maxPDGID < 37;
	    
	    if (parentagePass) {
		if(minGenDr(mcInd, tree) > 0.05) {
		    haveOverlap = true;
		}
	    }
        }
    }
    return haveOverlap;
}


bool overlapRemoval_Tchannel(EventTree* tree){
    const double Et_cut = 10;
    const double Eta_cut = 2.6;
    bool haveOverlap = false;
    for(int mcInd=0; mcInd<tree->nGenPart_; ++mcInd){
	if(tree->GenPart_pdgId_[mcInd]==22 &&
	   tree->GenPart_pt_[mcInd] > Et_cut &&
	   fabs(tree->GenPart_eta_[mcInd]) < Eta_cut) {
	    
	    // TGJets doesn't include photons from top decay, so if gmom is top continue (don't remove)
	    
	    Int_t parentIdx = tree->GenPart_genPartIdxMother_[mcInd];
	    bool fromTopDecay = false;
	    int maxPDGID = 0;

	    if (parentIdx>-1) {	    
		int motherPDGID = tree->GenPart_pdgId_[parentIdx];
		maxPDGID = abs(motherPDGID);
		while (parentIdx != -1){
		    motherPDGID = std::abs(tree->GenPart_pdgId_[parentIdx]);
		    maxPDGID = std::max(maxPDGID,motherPDGID);
		    parentIdx = tree->GenPart_genPartIdxMother_[parentIdx];
		    //if photon is coming from a 
		    if ( abs(motherPDGID)==6 ){
			fromTopDecay = true;
		    }
		}
	    }
	    bool parentagePass = maxPDGID < 37;
	    if(parentagePass && !fromTopDecay && minGenDr(mcInd, tree) > 0.05) {
		haveOverlap = true;
	    }
	}
    }
    return haveOverlap;
}
