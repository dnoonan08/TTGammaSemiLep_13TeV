//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon May  8 04:09:17 2017 by ROOT version 6.06/01
// from TTree EventTree/Event data (tag V08_00_24_00)
// found on file: skim_TTbar_100k.root
//////////////////////////////////////////////////////////

#ifndef makeAnalysisNtuple_h
#define makeAnalysisNtuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "EventTree.h"
#include "EventPick.h"
#include "Selector.h"

// Standalone Btag scale factor tool from 
// https://twiki.cern.ch/twiki/bin/view/CMS/BTagCalibration
#include "BTagCalibrationStandalone.h"

// Header file for the classes stored in the TTree if any.
#include "vector"

// Header file that includes all of the event luminosity scaling
#include "ScaleFactors.h"

class makeAnalysisNtuple {
public :

   /* TTree          *fChain;   //!pointer to the analyzed TTree or TChain */
   /* Int_t           fCurrent; //!current Tree number in a TChain */
	makeAnalysisNtuple(char* outputFileName,char** inputFileName);
	makeAnalysisNtuple(int ac, char** av);

private :

	EventTree* tree;   
	EventPick* evtPick;   
	Selector* selector;   

	TTree* outputTree;

	string sampleType;
	string systematicType;

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
	Int_t           _run;
	Long64_t        _event;
	Int_t           _lumis;
	Bool_t          _isData;

	Float_t         _PUweight;
	Float_t         _PUweight_Up;
	Float_t         _PUweight_Do;

	std::vector<float> _btagWeight;
	std::vector<float> _btagWeight_Up;
	std::vector<float> _btagWeight_Do;

	std::vector<float> _btagSF;
	std::vector<float> _btagSF_Up;
	std::vector<float> _btagSF_Do;

	Float_t         _muEffWeight;
	Float_t         _muEffWeight_Up;
	Float_t         _muEffWeight_Do;

	Float_t         _eleEffWeight;
	Float_t         _eleEffWeight_Up;
	Float_t         _eleEffWeight_Do;

	Float_t         _evtWeight;
	Float_t         _lumiWeight;

	Int_t           _nVtx;
	Int_t           _nGoodVtx;
	Bool_t          _isPVGood;
	Float_t         _rho;
	Float_t         _genMET;
	Float_t         _pfMET;
	Float_t         _pfMETPhi;
	Float_t         _WtransMass;
	Float_t         _Mt_blgammaMET;
	Float_t         _Mt_lgammaMET;
	Float_t         _Mt_bjj;
	Float_t         _Mt_jj;

//	Float_t         _HT;
	Float_t 	_DilepMass;
	Float_t 	_DiphoMass;
	Float_t         _DilepDelR;
	Int_t           _nPho;
	std::vector<float>   _phoEt;
	std::vector<float>   _phoEta;
	std::vector<float>   _phoSCEta;
	std::vector<float>   _phoPhi;
	std::vector<bool>    _phoIsBarrel;
	std::vector<float>   _phoHoverE;
	std::vector<float>   _phoSIEIE;
	std::vector<float>   _phoPFChIso;
	std::vector<float>   _phoPFPhoIso;
	std::vector<float>   _phoPFNeuIso;
	std::vector<float>   _phoPFRandConeChIso;
	std::vector<float>   _phoPFChIsoUnCorr;
	std::vector<float>   _phoPFPhoIsoUnCorr;
	std::vector<float>   _phoPFNeuIsoUnCorr;
	std::vector<float>   _phoPFRandConeChIsoUnCorr;
	std::vector<bool>    _phoTightID;
	std::vector<bool>    _phoMediumID;


	std::vector<bool>  _photonIsGenuine;
	std::vector<bool>  _photonIsMisIDEle;
	std::vector<bool>  _photonIsHadronicPhoton;
	std::vector<bool>  _photonIsHadronicFake;

	std::vector<int>   _photonParentage;
	std::vector<int>   _photonParentPID;

	std::vector<float>   _dRPhotonJet;
	std::vector<float>   _dRPhotonLepton;
	std::vector<float>   _MPhotonLepton;
	std::vector<float>   _AnglePhotonLepton;


	Int_t           _nLoosePho;
	std::vector<float>   _loosePhoEt;
	std::vector<float>   _loosePhoEta;
	std::vector<float>   _loosePhoSCEta;
	std::vector<float>   _loosePhoPhi;
	std::vector<bool>    _loosePhoIsBarrel;
	std::vector<float>   _loosePhoHoverE;
	std::vector<float>   _loosePhoSIEIE;
	std::vector<float>   _loosePhoPFChIso;
	std::vector<float>   _loosePhoPFPhoIso;
	std::vector<float>   _loosePhoPFNeuIso;
	std::vector<float>   _loosePhoPFRandConeChIso;
	std::vector<float>   _loosePhoPFChIsoUnCorr;
	std::vector<float>   _loosePhoPFPhoIsoUnCorr;
	std::vector<float>   _loosePhoPFNeuIsoUnCorr;
	std::vector<float>   _loosePhoPFRandConeChIsoUnCorr;
	std::vector<bool>    _loosePhoTightID;
	std::vector<bool>    _loosePhoMediumID;
	std::vector<bool>    _loosePhoLooseID;
	std::vector<bool>    _loosePhoMediumIDFunction; 
	std::vector<bool>    _loosePhoMediumIDPassHoverE; 
	std::vector<bool>    _loosePhoMediumIDPassSIEIE; 
	std::vector<bool>    _loosePhoMediumIDPassChIso; 
	std::vector<bool>    _loosePhoMediumIDPassNeuIso; 
	std::vector<bool>    _loosePhoMediumIDPassPhoIso; 
	std::vector<bool>    _loosePhoTightIDFunction; 
	std::vector<bool>    _loosePhoTightIDPassHoverE; 
	std::vector<bool>    _loosePhoTightIDPassSIEIE; 
	std::vector<bool>    _loosePhoTightIDPassChIso; 
	std::vector<bool>    _loosePhoTightIDPassNeuIso; 
	std::vector<bool>    _loosePhoTightIDPassPhoIso; 

	std::vector<bool>    _loosePhotonIsGenuine;
	std::vector<bool>    _loosePhotonIsMisIDEle;
	std::vector<bool>    _loosePhotonIsHadronicPhoton;
	std::vector<bool>    _loosePhotonIsHadronicFake;



	int  _eventCategoryMediumID;
	int  _eventCategoryTightID;



	/* std::vector<bool>    _phoMediumIDNoHoverECut;  */
	/* std::vector<bool>    _phoMediumIDNoSIEIECut;  */
	/* std::vector<bool>    _phoMediumIDNoIsoCut;  */
   
	Int_t           _nEle;
	Int_t           _nEleLoose;

	std::vector<float>   _elePt;
	std::vector<float>   _elePhi;
	std::vector<float>   _eleSCEta;
	std::vector<float>   _elePFRelIso;
	
	Int_t           _nMu;
	Int_t           _nMuLoose;
	std::vector<float>   _muPt;
	std::vector<float>   _muEta;
	std::vector<float>   _muPhi;
	std::vector<float>   _muPFRelIso;
	
	Int_t                _nJet;
	Int_t                _nBJet;
	std::vector<float>   _jetPt;
	std::vector<float>   _jetEn;
	std::vector<float>   _jetEta;
	std::vector<float>   _jetPhi;
	std::vector<float>   _jetRawPt;
	std::vector<float>   _jetArea;
	std::vector<float>   _jetpfCombinedMVAV2BJetTags;
	std::vector<float>   _jetCSV2BJetTags;
	std::vector<float>   _jetDeepCSVTags_b;
	std::vector<float>   _jetDeepCSVTags_bb;
	std::vector<int>     _jetPartonID;
	std::vector<float>   _jetGenJetPt;
	std::vector<int>     _jetGenPartonID;
	std::vector<float>   _jetGenPt;
	std::vector<float>   _jetGenEta;
	std::vector<float>   _jetGenPhi;


	Int_t                _nMC;
	std::vector<float>   _mcPt;
	std::vector<float>   _mcEta;
	std::vector<float>   _mcPhi;
	std::vector<float>   _mcMass;
	std::vector<int>     _mcStatus;
	std::vector<int>     _mcPID;
	std::vector<int>     _mcMomPID;
	std::vector<int>     _mcGMomPID;
	std::vector<int>     _mcParentage;

	double               _M3;
	double               _HT;
	
	bool  _passPresel_Ele;
	bool  _passPresel_Mu;
	bool  _passAll_Ele;
	bool  _passAll_Mu;
	bool  dileptonsample;

	TLorentzVector jetVector;
	TLorentzVector lepVector;
	TLorentzVector lepVector2;
	TLorentzVector phoVector;
	TLorentzVector METVector;
	TLorentzVector phoVector1;
	TLorentzVector phoVector2;


	void InitVariables();
	void FillEvent();
	void InitBranches();

	double SFtop(double pt);
	double topPtWeight();
	vector<float> getBtagSF(string sysType, BTagCalibrationReader reader, vector<float> &btagSF);
	double WjetsBRreweight();
	/* double getMuSF(int muInd, int systLevel); */
	/* double getEleSF(int eleInd, int systLevel); */

	void findPhotonCategory(int phoInd, EventTree* tree, bool* genuine, bool *misIDele, bool *hadronicphoton, bool* hadronicfake);
	int findPhotonParentage(int phoInd, EventTree* tree);

	vector<bool> passPhoMediumID(int phoInd);
	vector<bool> passPhoTightID(int phoInd);
	/* bool passPhoMediumID(int phoInd, bool cutHoverE, bool cutSIEIE, bool cutIso); */

	int minDrIndex(double myEta, double myPhi, std::vector<int> Inds, std::vector<float> *etas, std::vector<float> *phis);
	double minDr(double myEta, double myPhi, std::vector<int> Inds, std::vector<float> *etas, std::vector<float> *phis);

	bool isSignalPhoton(EventTree* tree, int mcInd, int recoPhoInd);
	bool isGoodElectron(EventTree* tree, int mcInd, int recoPhoInd);

};


void makeAnalysisNtuple::InitBranches(){

	outputTree->Branch("run"                        , &_run                         );
	outputTree->Branch("event"                      , &_event                       );
	outputTree->Branch("lumis"                      , &_lumis                       );
	outputTree->Branch("isData"                     , &_isData                      ); 
	outputTree->Branch("PUweight"                   , &_PUweight                    );
	outputTree->Branch("PUweight_Up"                , &_PUweight_Up                 );
	outputTree->Branch("PUweight_Do"                , &_PUweight_Do                 );
	outputTree->Branch("btagWeight"                 , &_btagWeight                  );
	outputTree->Branch("btagWeight_Up"              , &_btagWeight_Up               );
	outputTree->Branch("btagWeight_Do"              , &_btagWeight_Do               );
	outputTree->Branch("btagSF"                     , &_btagSF                      );
	outputTree->Branch("muEffWeight"                , &_muEffWeight                 );
	outputTree->Branch("muEffWeight_Up"             , &_muEffWeight_Up              );
	outputTree->Branch("muEffWeight_Do"             , &_muEffWeight_Do              );
	outputTree->Branch("eleEffWeight"               , &_eleEffWeight                );
	outputTree->Branch("eleEffWeight_Up"            , &_eleEffWeight_Up             );
	outputTree->Branch("eleEffWeight_Do"            , &_eleEffWeight_Do             );
	outputTree->Branch("evtWeight"                  , &_evtWeight                   );      
	outputTree->Branch("nVtx"                       , &_nVtx                        ); 
	outputTree->Branch("nGoodVtx"                   , &_nGoodVtx                    ); 
	outputTree->Branch("isPVGood"                   , &_isPVGood                    ); 
	outputTree->Branch("rho"                        , &_rho                         ); 
	outputTree->Branch("genMET"                     , &_genMET                      ); 
	outputTree->Branch("pfMET"                      , &_pfMET                       );
	outputTree->Branch("pfMETPhi"                   , &_pfMETPhi                    ); 
	outputTree->Branch("WtransMass"                 , &_WtransMass                  );

	outputTree->Branch("Mt_blgammaMET"              , &_Mt_blgammaMET               );
	outputTree->Branch("Mt_lgammaMET"               , &_Mt_lgammaMET                );
	outputTree->Branch("Mt_bjj"                     , &_Mt_bjj                      );
	outputTree->Branch("Mt_jj"                      , &_Mt_jj                       );

	outputTree->Branch("DiphoMass"                  , &_DiphoMass                   ); 
   	outputTree->Branch("DilepMass"                  , &_DilepMass 			);
	outputTree->Branch("DilepDelR"                  , &_DilepDelR                   );
	outputTree->Branch("nPho"                       , &_nPho                        ); 
	outputTree->Branch("phoEt"                      , &_phoEt                       );
	outputTree->Branch("phoEta"                     , &_phoEta                      ); 
	outputTree->Branch("phoSCEta"                   , &_phoSCEta                    ); 
	outputTree->Branch("phoPhi"                     , &_phoPhi                      ); 
	outputTree->Branch("phoIsBarrel"                , &_phoIsBarrel                 ); 
	outputTree->Branch("phoHoverE"                  , &_phoHoverE                   ); 
	outputTree->Branch("phoSIEIE"                   , &_phoSIEIE                    ); 
	outputTree->Branch("phoPFChIso"                 , &_phoPFChIso                  ); 
	outputTree->Branch("phoPFPhoIso"                , &_phoPFPhoIso                 ); 
	outputTree->Branch("phoPFNeuIso"                , &_phoPFNeuIso                 ); 
	outputTree->Branch("phoPFRandConeChIso"         , &_phoPFRandConeChIso          ); 
	outputTree->Branch("phoPFChIsoUnCorr"                 , &_phoPFChIsoUnCorr                  ); 
	outputTree->Branch("phoPFPhoIsoUnCorr"                , &_phoPFPhoIsoUnCorr                 ); 
	outputTree->Branch("phoPFNeuIsoUnCorr"                , &_phoPFNeuIsoUnCorr                 ); 
	outputTree->Branch("phoPFRandConeChIsoUnCorr"         , &_phoPFRandConeChIsoUnCorr          ); 
	outputTree->Branch("phoTightID"                 , &_phoTightID                  ); 
	outputTree->Branch("phoMediumID"                , &_phoMediumID                 ); 

	outputTree->Branch("nLoosePho"                       , &_nLoosePho                        ); 
	outputTree->Branch("loosePhoEt"                      , &_loosePhoEt                       );
	outputTree->Branch("loosePhoEta"                     , &_loosePhoEta                      ); 
	outputTree->Branch("loosePhoSCEta"                   , &_loosePhoSCEta                    ); 
	outputTree->Branch("loosePhoPhi"                     , &_loosePhoPhi                      ); 
	outputTree->Branch("loosePhoIsBarrel"                , &_loosePhoIsBarrel                 ); 
	outputTree->Branch("loosePhoHoverE"                  , &_loosePhoHoverE                   ); 
	outputTree->Branch("loosePhoSIEIE"                   , &_loosePhoSIEIE                    ); 
	outputTree->Branch("loosePhoPFChIso"                 , &_loosePhoPFChIso                  ); 
	outputTree->Branch("loosePhoPFLoosePhoIso"                , &_loosePhoPFPhoIso                 ); 
	outputTree->Branch("loosePhoPFNeuIso"                , &_loosePhoPFNeuIso                 ); 
	outputTree->Branch("loosePhoPFRandConeChIso"         , &_loosePhoPFRandConeChIso          ); 
	outputTree->Branch("loosePhoPFChIsoUnCorr"                 , &_loosePhoPFChIsoUnCorr                  ); 
	outputTree->Branch("loosePhoPFPhoIsoUnCorr"                , &_loosePhoPFPhoIsoUnCorr                 ); 
	outputTree->Branch("loosePhoPFNeuIsoUnCorr"                , &_loosePhoPFNeuIsoUnCorr                 ); 
	outputTree->Branch("loosePhoPFRandConeChIsoUnCorr"         , &_loosePhoPFRandConeChIsoUnCorr          ); 
	outputTree->Branch("loosePhoTightID"                 , &_loosePhoTightID                  ); 
	outputTree->Branch("loosePhoMediumID"                , &_loosePhoMediumID                 ); 
	outputTree->Branch("loosePhoLooseID"                 , &_loosePhoLooseID                  ); 
	outputTree->Branch("loosePhoMediumIDFunction"        , &_loosePhoMediumIDFunction         ); 
	outputTree->Branch("loosePhoMediumIDPassHoverE"      , &_loosePhoMediumIDPassHoverE       ); 
	outputTree->Branch("loosePhoMediumIDPassSIEIE"       , &_loosePhoMediumIDPassSIEIE        ); 
	outputTree->Branch("loosePhoMediumIDPassChIso"       , &_loosePhoMediumIDPassChIso        ); 
	outputTree->Branch("loosePhoMediumIDPassNeuIso"      , &_loosePhoMediumIDPassNeuIso       ); 
	outputTree->Branch("loosePhoMediumIDPassPhoIso"      , &_loosePhoMediumIDPassPhoIso       ); 
	outputTree->Branch("loosePhoTightIDFunction"        , &_loosePhoTightIDFunction         ); 
	outputTree->Branch("loosePhoTightIDPassHoverE"      , &_loosePhoTightIDPassHoverE       ); 
	outputTree->Branch("loosePhoTightIDPassSIEIE"       , &_loosePhoTightIDPassSIEIE        ); 
	outputTree->Branch("loosePhoTightIDPassChIso"       , &_loosePhoTightIDPassChIso        ); 
	outputTree->Branch("loosePhoTightIDPassNeuIso"      , &_loosePhoTightIDPassNeuIso       ); 
	outputTree->Branch("loosePhoTightIDPassPhoIso"      , &_loosePhoTightIDPassPhoIso       ); 

	
	outputTree->Branch("nEle"                        , &_nEle                       ); 
	outputTree->Branch("elePt"                       , &_elePt                      );
	outputTree->Branch("elePhi"                      , &_elePhi                     ); 
	outputTree->Branch("eleSCEta"                    , &_eleSCEta                   ); 
	outputTree->Branch("elePFRelIso"                 , &_elePFRelIso                ); 
	
	outputTree->Branch("nMu"                         , &_nMu                        ); 
	outputTree->Branch("muPt"                        , &_muPt                       ); 
	outputTree->Branch("muEta"                       , &_muEta                      );
	outputTree->Branch("muPhi"                       , &_muPhi                      );
	outputTree->Branch("muPFRelIso"                  , &_muPFRelIso                 );
    
	outputTree->Branch("nJet"                        , &_nJet                       ); 
	outputTree->Branch("nBJet"                       , &_nBJet                      ); 
	outputTree->Branch("jetPt"                       , &_jetPt                      );
	outputTree->Branch("jetEn"                       , &_jetEn                      );
	outputTree->Branch("jetEta"                      , &_jetEta                     ); 
	outputTree->Branch("jetPhi"                      , &_jetPhi                     ); 
	outputTree->Branch("jetRawPt"                    , &_jetRawPt                   ); 
	outputTree->Branch("jetArea"                     , &_jetArea                    ); 
	outputTree->Branch("jetpfCombinedMVAV2BJetTags"  , &_jetpfCombinedMVAV2BJetTags );
	outputTree->Branch("jetCSV2BJetTags"             , &_jetCSV2BJetTags            );
	outputTree->Branch("jetDeepCSVTags_b"            , &_jetDeepCSVTags_b           );
	outputTree->Branch("jetDeepCSVTags_bb"           , &_jetDeepCSVTags_bb          );
	
	if (!tree->isData_){
		outputTree->Branch("jetPartonID"                 , &_jetPartonID                ); 
		outputTree->Branch("jetGenJetPt"                 , &_jetGenJetPt                ); 
		outputTree->Branch("jetGenPartonID"              , &_jetGenPartonID             ); 
		outputTree->Branch("jetGenPt"                    , &_jetGenPt                   ); 
		outputTree->Branch("jetGenEta"                   , &_jetGenEta                  );
		outputTree->Branch("jetGenPhi"                   , &_jetGenPhi                  );
	}		

	outputTree->Branch("dRPhotonJet"                 , &_dRPhotonJet                );
	outputTree->Branch("dRPhotonLepton"              , &_dRPhotonLepton             );
	outputTree->Branch("MPhotonLepton"               , &_MPhotonLepton             );
	outputTree->Branch("AnglePhotonLepton"           , &_AnglePhotonLepton         );

	if (!tree->isData_){
		outputTree->Branch("nMC"   	                     , &_nMC		                ); 
		outputTree->Branch("mcPt"	                     , &_mcPt	   	                );
		outputTree->Branch("mcEta"	                     , &_mcEta	                    ); 
		outputTree->Branch("mcPhi"	                     , &_mcPhi	                    ); 
		outputTree->Branch("mcMass"	                     , &_mcMass	                    ); 
		outputTree->Branch("mcStatus"                    , &_mcStatus                   );
		outputTree->Branch("mcPID"	                     , &_mcPID	                    ); 
		outputTree->Branch("mcMomPID"                    , &_mcMomPID                   );
		outputTree->Branch("mcGMomPID"                   , &_mcGMomPID                  );
		outputTree->Branch("mcParentage"                 , &_mcParentage                );
	}

    outputTree->Branch("M3"                          , &_M3                         ); 
    outputTree->Branch("HT"                          , &_HT                         ); 

	outputTree->Branch("passPresel_Ele"              , &_passPresel_Ele             ); 
	outputTree->Branch("passPresel_Mu"               , &_passPresel_Mu              );
	outputTree->Branch("passAll_Ele"                 , &_passAll_Ele                ); 
	outputTree->Branch("passAll_Mu"                  , &_passAll_Mu                 );

	outputTree->Branch("photonIsGenuine"             , &_photonIsGenuine            );
	outputTree->Branch("photonIsMisIDEle"            , &_photonIsMisIDEle           );
	outputTree->Branch("photonIsHadronicPhoton"      , &_photonIsHadronicPhoton     );
	outputTree->Branch("photonIsHadronicFake"        , &_photonIsHadronicFake       );

	outputTree->Branch("photonParentage"        , &_photonParentage       );
	outputTree->Branch("photonParentPID"        , &_photonParentPID       );
	
	outputTree->Branch("_eventCategoryMediumID"      , &_eventCategoryMediumID      );
	outputTree->Branch("_eventCategoryTightID"       , &_eventCategoryTightID       );
}

void makeAnalysisNtuple::InitVariables()
{

	_run             = -9999;
	_event           = -9999;
	_lumis		     = -9999;
	_isData		     = false;
	_nVtx		     = -9999;
	_nGoodVtx	     = -9999;
	_isPVGood	     = false;
	_rho		     = -9999;
	_genMET		     = -9999;
	_pfMET		     = -9999;
	_pfMETPhi	     = -9999;
	_WtransMass      = -9999;

	_Mt_blgammaMET   = -9999;
	_Mt_lgammaMET    = -9999;
	_Mt_bjj          = -9999;
	_Mt_jj           = -9999;

	_HT		 = -9999;
	_DilepMass	 = -9999;
	_DilepDelR	 = -9999;
	_DiphoMass       = -9999;
	_nPho		     = -9999;
	_nEle		     = -9999;
	_nMu		     = -9999;
	_nMuLoose 	     = -9999;
	_nEleLoose           = -9999;
	_nJet            = -9999;    
	_nBJet           = -9999;    

	_passPresel_Ele  = false;
	_passPresel_Mu   = false;
	_passAll_Ele     = false;
	_passAll_Mu      = false;


	_btagWeight.clear();
	_btagWeight_Up.clear();
	_btagWeight_Do.clear();

	_btagSF.clear();
	_btagSF_Up.clear();
	_btagSF_Do.clear();

	_eventCategoryMediumID = -1;
	_eventCategoryTightID = -1;

	_elePt.clear();
	_elePhi.clear();
	_eleSCEta.clear();
	_elePFRelIso.clear();

	_muPt.clear();
	_muEta.clear();
	_muPhi.clear();
	_muPFRelIso.clear();

	_phoEt.clear();
	_phoEta.clear();
	_phoSCEta.clear();
	_phoPhi.clear();
	_phoIsBarrel.clear();
	_phoHoverE.clear();
	_phoSIEIE.clear();
	_phoPFChIso.clear();
	_phoPFPhoIso.clear();
	_phoPFNeuIso.clear();
	_phoPFRandConeChIso.clear();
	_phoPFChIsoUnCorr.clear();
	_phoPFPhoIsoUnCorr.clear();
	_phoPFNeuIsoUnCorr.clear();
	_phoPFRandConeChIsoUnCorr.clear();
	_phoTightID.clear();
	_phoMediumID.clear();
	_photonIsGenuine.clear();
	_photonIsMisIDEle.clear();
	_photonIsHadronicPhoton.clear();
	_photonIsHadronicFake.clear();
	_photonParentage.clear();
	_photonParentPID.clear();

	_loosePhoEt.clear();
	_loosePhoEta.clear();
	_loosePhoSCEta.clear();
	_loosePhoPhi.clear();
	_loosePhoIsBarrel.clear();
	_loosePhoHoverE.clear();
	_loosePhoSIEIE.clear();
	_loosePhoPFChIso.clear();
	_loosePhoPFPhoIso.clear();
	_loosePhoPFNeuIso.clear();
	_loosePhoPFRandConeChIso.clear();
	_loosePhoPFChIsoUnCorr.clear();
	_loosePhoPFPhoIsoUnCorr.clear();
	_loosePhoPFNeuIsoUnCorr.clear();
	_loosePhoPFRandConeChIsoUnCorr.clear();
	_loosePhoTightID.clear();
	_loosePhoMediumID.clear();
	_loosePhoLooseID.clear();
	_loosePhoMediumIDFunction.clear(); 
	_loosePhoMediumIDPassHoverE.clear(); 
	_loosePhoMediumIDPassSIEIE.clear(); 
	_loosePhoMediumIDPassChIso.clear(); 
	_loosePhoMediumIDPassNeuIso.clear(); 
	_loosePhoMediumIDPassPhoIso.clear(); 
	_loosePhoTightIDFunction.clear(); 
	_loosePhoTightIDPassHoverE.clear(); 
	_loosePhoTightIDPassSIEIE.clear(); 
	_loosePhoTightIDPassChIso.clear(); 
	_loosePhoTightIDPassNeuIso.clear(); 
	_loosePhoTightIDPassPhoIso.clear(); 
	_loosePhotonIsGenuine.clear();
	_loosePhotonIsMisIDEle.clear();
	_loosePhotonIsHadronicPhoton.clear();
	_loosePhotonIsHadronicFake.clear();

	_jetPt.clear();
	_jetEn.clear();
	_jetEta.clear();
	_jetPhi.clear();
	_jetRawPt.clear();
	_jetArea.clear();
	_jetpfCombinedMVAV2BJetTags.clear();
	_jetCSV2BJetTags.clear();
	_jetDeepCSVTags_b.clear();
	_jetDeepCSVTags_bb.clear();
	_jetPartonID.clear();
	_jetGenJetPt.clear();
	_jetGenPartonID.clear();
	_jetGenPt.clear();
	_jetGenEta.clear();
	_jetGenPhi.clear();

	_dRPhotonJet.clear();
	_dRPhotonLepton.clear();
	_MPhotonLepton.clear();
	_AnglePhotonLepton.clear();

	_mcPt.clear();
	_mcPhi.clear();
	_mcEta.clear();
	_mcMass.clear();
	_mcStatus.clear();
	_mcPID.clear();
	_mcMomPID.clear();
	_mcGMomPID.clear();
	_mcParentage.clear();


}



#endif

