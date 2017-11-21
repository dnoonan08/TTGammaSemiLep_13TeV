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
		METerror = 0.2;
		Leperror = 0.05;
		useResolutions = true;
		ignoreBtagInfo = false;

	}
	
	void SetMtop(double mTop_){ mTop = mTop_;}
	void SetMW(double mW_){ mW = mW_;}

	void SetLJetVector(std::vector<TLorentzVector> jets_){ ljets = jets_;}
	void SetBJetVector(std::vector<TLorentzVector> jets_){ bjets = jets_;}
	void SetLJetResVector(std::vector<double> jetres_){ ljetsRes = jetres_;}
	void SetBJetResVector(std::vector<double> jetres_){ bjetsRes = jetres_;}
	void SetLepton(TLorentzVector lepton_){ lepton = lepton_;}
	void SetMET(TLorentzVector met_){ met = met_;}

	void SetMETerror(double err){ METerror = err;}
	void SetLeperror(double err){ Leperror = err;}

	void SetUseResolutions(bool useRes_){ useResolutions = useRes_;}
	void SetIgnoreBtag(bool ignoreBtag_){ ignoreBtagInfo = ignoreBtag_;}
		
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

	double topChiSq(TLorentzVector j1, TLorentzVector j2, TLorentzVector bh, TLorentzVector bl, double sigma_j1, double sigma_j2, double sigma_bh, double sigma_bl);

	int run4j2b();
	int run4j1b();
	int run4j0b();
	int runWithoutBInfo();

	bool ignoreBtagInfo;

	std::vector<TLorentzVector> bjets;
	std::vector<TLorentzVector> ljets;
	TLorentzVector lepton;
	TLorentzVector met;

	std::vector<TLorentzVector> tempJetVector;
	std::vector<double> tempJetResVector;


	TLorentzVector bhad;
	TLorentzVector blep;
	TLorentzVector j1;
	TLorentzVector j2;
	

	bool goodCombo;

	bool useResolutions;

	std::vector<double> bjetsRes;
	std::vector<double> ljetsRes;
	double METerror;
	double Leperror;

};

#endif
