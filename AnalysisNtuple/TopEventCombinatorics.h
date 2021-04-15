#ifndef TopEventCombinatorics_h
#define TopEventCombinatorics_h


#include "TLorentzVector.h"
#include "METzCalculator.h"
#include "TMath.h"
#include <vector>

class TopEventCombinatorics{

 public:

    TopEventCombinatorics(){
	ClearVectors();
	mTop = 172.5;
	mW = 80.4;
	chi2_TT = 9999.;
	chi2_TstarGluGlu = 9999.;
	chi2_TstarGluGamma = 9999.;
	goodCombo = false;
	goodCombo_TstarGluGlu = false;
	goodCombo_TstarGluGamma = false;
	METRes = 0.2;
	leptonRes = 0.05;
	useResolutions = true;
	nBjetSize = 2;
	btagThresh = 0.;
	bhad_idx = 0;
	blep_idx = 0;
	j1_idx = 0;
	j2_idx = 0;
	g_idx = 0;
	pho_idx = 0;
	ghad_idx = 0;
	glep_idx = 0;
	tHad_idx = 0;
    }
	
    void SetMtop(double mTop_){ mTop = mTop_;}
    void SetMW(double mW_){ mW = mW_;}

    void SetFatJetVector(std::vector<TLorentzVector> jets_){ ak8jets = jets_;}
    void SetJetVector(std::vector<TLorentzVector> jets_){ jets = jets_;}
    void SetJetResVector(std::vector<double> jetres_){ jetsRes = jetres_;}
    void SetBtagVector(std::vector<double> jetsTag_){ btag = jetsTag_;}

    void SetPhotonVector(std::vector<TLorentzVector> photons_){ photons = photons_;}

    void SetLepton(TLorentzVector lepton_){ lepton = lepton_; metZ.SetLepton(lepton_);}
    void SetMET(TLorentzVector met_){ met = met_; metZ.SetMET(met_);}

    void SetMETerror(double err){ METRes = err;}
    void SetLeperror(double err){ leptonRes = err;}

    void SetBJetsSize(int _nB){ nBjetSize = _nB;}
    void SetBtagThresh(double thresh){ btagThresh = thresh;}

    void SetUseResolutions(bool useRes_){ useResolutions = useRes_;}
		
    unsigned int getBHad(){ return bhad_idx; }
    unsigned int getBLep(){ return blep_idx; }
    unsigned int getJ1(){ return j1_idx; }
    unsigned int getJ2(){ return j2_idx; }
    unsigned int getGHad(){ return ghad_idx; }
    unsigned int getGLep(){ return glep_idx; }
    unsigned int getG(){ return g_idx; }
    unsigned int getPho(){ return pho_idx; }

    unsigned int getTHad(){ return tHad_idx; }

    bool getPhotonSide(){ return photonIsLeptonSide; }

    double getNuPz(){ return nu_pz; }
	
    double getChi2_TT(){ return chi2_TT; }
    double getChi2_TstarGluGlu(){ return chi2_TstarGluGlu; }
    double getChi2_TstarGluGamma(){ return chi2_TstarGluGamma; }

    bool GoodCombination(){ return goodCombo; }
    bool GoodCombinationTstarGluGlu(){ return goodCombo_TstarGluGlu; }
    bool GoodCombinationTstarGluGamma(){ return goodCombo_TstarGluGamma; }

    void ClearVectors(){
	jets.clear();
	ak8jets.clear();
    }

    int Calculate();

    int CalculateTstarGluGlu(int N=-1);
    int CalculateTstarGluGamma(int N=-1);
    int CalculateTstarGluGamma_Boosted(int N=-1);


 private:
    double mTop;
    double mW;
    double chi2_TT;
    double chi2_TstarGluGlu;
    double chi2_TstarGluGamma;

    double topChiSq(TLorentzVector j1, double sigma_j1,
		    TLorentzVector j2, double sigma_j2,
		    TLorentzVector bh, double sigma_bh,
		    TLorentzVector bl, double sigma_bl,
		    double nu_pz_hypo);

    double tstarChiSq(TLorentzVector j1,
                      TLorentzVector j2,
                      TLorentzVector bh,
                      TLorentzVector bl,
                      TLorentzVector hadDecay,
                      TLorentzVector lepDecay,
                      double nu_pz_hypo);

    double tstarChiSq_boosted(TLorentzVector ak8j,
                              TLorentzVector bl,
                              TLorentzVector hadDecay,
                              TLorentzVector lepDecay,
                              double nu_pz_hypo);

    /* double tstarGluGammaChiSq(TLorentzVector j1, double sigma_j1, */
    /*                           TLorentzVector j2, double sigma_j2, */
    /*                           TLorentzVector bh, double sigma_bh, */
    /*                           TLorentzVector bl, double sigma_bl, */
    /*                           TLorentzVector g, double sigma_g, */
    /*                           double nu_pz_hypo); */

    std::vector<TLorentzVector> jets;
    std::vector<TLorentzVector> ak8jets;
    std::vector<double> jetsRes;
    std::vector<double> btag;

    TLorentzVector lepton;
    double leptonRes;

    std::vector<TLorentzVector> photons;


    TLorentzVector met;
    double METRes;
 
    std::vector<int> bJetsList;
    std::vector<double> nu_pz_List;

    int nBjetSize;

    std::vector<TLorentzVector> tempJetVector;
    std::vector<double> tempJetResVector;


    /* TLorentzVector bhad; */
    /* TLorentzVector blep; */
    /* TLorentzVector j1; */
    /* TLorentzVector j2; */

    int tHad_idx;
    int bhad_idx;
    int blep_idx;
    int j1_idx;
    int j2_idx; 
    int g_idx;
    int pho_idx;
    int ghad_idx;
    int glep_idx;
    int nu_pz;
    int photonIsLeptonSide;
	
    bool goodCombo;
    bool goodCombo_TstarGluGlu;
    bool goodCombo_TstarGluGamma;

    bool useResolutions;

    double btagThresh;

    METzCalculator metZ;

};

#endif
