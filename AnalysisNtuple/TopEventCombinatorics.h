#ifndef TopEventCombinatorics_h
#define TopEventCombinatorics_h


#include "TLorentzVector.h"
#include "TMath.h"
#include <vector>

class TopEventCombinatorics{

 public:

	TopEventCombinatorics(){
		ClearVectors();
		mTop = 172.5;
		mW = 80.4;
		chi2 = 9999.;
		goodCombo = false;
	}
	
	void SetMtop(double mTop_){ mTop = mTop_;}
	void SetMW(double mW_){ mW = mW_;}

	void SetLJetVector(std::vector<TLorentzVector> jets_){ ljets = jets_;}
	void SetBJetVector(std::vector<TLorentzVector> jets_){ bjets = jets_;}
	void SetLepton(TLorentzVector lepton_){ lepton = lepton_;}
	void SetMET(TLorentzVector met_){ met = met_;}
		
	TLorentzVector getBHad(){ return bhad; }
	TLorentzVector getBLep(){ return blep; }
	TLorentzVector getJ1(){ return j1; }
	TLorentzVector getJ2(){ return j2; }
	
	bool GoodCombination(){ return goodCombo; }

	void ClearVectors(){
		bjets.clear();
		ljets.clear();
	}
	int Calculate();



 private:
	double mTop;
	double mW;
	double chi2;

	double topChiSq(TLorentzVector j1, TLorentzVector j2, TLorentzVector bh, TLorentzVector bl);

	std::vector<TLorentzVector> bjets;
	std::vector<TLorentzVector> ljets;
	TLorentzVector lepton;
	TLorentzVector met;

	TLorentzVector bhad;
	TLorentzVector blep;
	TLorentzVector j1;
	TLorentzVector j2;
	

	bool goodCombo;

};

#endif
