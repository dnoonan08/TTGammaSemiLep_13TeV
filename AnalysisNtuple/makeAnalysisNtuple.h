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

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
	Int_t           _run;
	Long64_t        _event;
	Int_t           _lumis;
	Bool_t          _isData;

	Float_t         _PUweight;
	Float_t         _PUweight_Up;
	Float_t         _PUweight_Do;

	Float_t         _btagWeight;
	Float_t         _btagWeight_Up;
	Float_t         _btagWeight_Do;

	Float_t         _muEffWeight;
	Float_t         _muEffWeight_Up;
	Float_t         _muEffWeight_Do;

	Float_t         _eleEffWeight;
	Float_t         _eleEffWeight_Up;
	Float_t         _eleEffWeight_Do;

	Float_t         _evtWeight;

	Int_t           _nVtx;
	Int_t           _nGoodVtx;
	Bool_t          _isPVGood;
	Float_t         _rho;
	Float_t         _genMET;
	Float_t         _pfMET;
	Float_t         _pfMETPhi;
	Int_t           _nPho;
	std::vector<float>   _phoEt;
	std::vector<float>   _phoEta;
	std::vector<float>   _phoPhi;
	std::vector<float>   _phoHoverE;
	std::vector<float>   _phoSigmaIEtaIEtaFull5x5;
	std::vector<float>   _phoPFChIso;
	std::vector<float>   _phoPFPhoIso;
	std::vector<float>   _phoPFNeuIso;
	std::vector<bool>    _phoTightID;
	std::vector<bool>    _phoMediumID;
	std::vector<bool>    _phoLooseID;
	std::vector<bool>    _phoMediumIDFunction; 
	std::vector<bool>    _phoMediumIDNoHoverECut; 
	std::vector<bool>    _phoMediumIDNoSIEIECut; 
	std::vector<bool>    _phoMediumIDNoIsoCut; 
   
	Int_t           _nEle;

	std::vector<float>   _elePt;
	std::vector<float>   _elePhi;
	std::vector<float>   _eleSCEta;
	std::vector<float>   _elePFRelIso;
	
	Int_t           _nMu;
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
	std::vector<int>     _jetPartonID;
	std::vector<float>   _jetGenJetPt;
	std::vector<int>     _jetGenPartonID;
	std::vector<float>   _jetGenPt;
	std::vector<float>   _jetGenEta;
	std::vector<float>   _jetGenPhi;

	std::vector<float>   _dRPhotonJet;
	std::vector<float>   _dRPhotonLepton;
	std::vector<float>   _MPhotonLepton;
	std::vector<float>   _AnglePhotonLepton;

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

	bool  _photonIsGenuine;
	bool  _photonIsMisIDEle;
	bool  _photonIsHadronicPhoton;
	bool  _photonIsHadronicFake;

	TLorentzVector jetVector;
	TLorentzVector lepVector;
	TLorentzVector phoVector;


	void InitVariables();
	void FillEvent();
	void InitBranches();

	double SFtop(double pt);
	double topPtWeight();
	double getBtagSF(string sysType, BTagCalibrationReader reader);
	double WjetsBRreweight();
	/* double getMuSF(int muInd, int systLevel); */
	/* double getEleSF(int eleInd, int systLevel); */

	void findPhotonCategory(int phoInd, EventTree* tree, bool* genuine, bool *misIDele, bool *hadronicphoton, bool* hadronicfake);
	bool passPhoMediumID(int phoInd, bool cutHoverE, bool cutSIEIE, bool cutIso);

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
    
	outputTree->Branch("nPho"                       , &_nPho                        ); 
	outputTree->Branch("phoEt"                      , &_phoEt                       );
	outputTree->Branch("phoEta"                     , &_phoEta                      ); 
	outputTree->Branch("phoPhi"                     , &_phoPhi                      ); 
	outputTree->Branch("phoHoverE_"                 , &_phoHoverE                   ); 
	outputTree->Branch("phoSigmaIEtaIEtaFull5x5"    , &_phoSigmaIEtaIEtaFull5x5     ); 
	outputTree->Branch("phoPFChIso"                 , &_phoPFChIso                  ); 
	outputTree->Branch("phoPFPhoIso"                , &_phoPFPhoIso                 ); 
	outputTree->Branch("phoPFNeuIso"                , &_phoPFNeuIso                 ); 
	outputTree->Branch("phoTightID"                 , &_phoTightID                  ); 
	outputTree->Branch("phoMediumID"                , &_phoMediumID                 ); 
	outputTree->Branch("phoLooseID"                 , &_phoLooseID                  ); 
	outputTree->Branch("phoMediumIDFunction"        , &_phoMediumIDFunction         ); 
	outputTree->Branch("phoMediumIDNoHoverECut"     , &_phoMediumIDNoHoverECut      ); 
	outputTree->Branch("phoMediumIDNoSIEIECut"      , &_phoMediumIDNoSIEIECut       ); 
	outputTree->Branch("phoMediumIDNoIsoCut"        , &_phoMediumIDNoIsoCut         ); 
	
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
	_nPho		     = -9999;
	_nEle		     = -9999;
	_nMu		     = -9999;
	_nJet            = -9999;    
	_nBJet           = -9999;    

	_passPresel_Ele  = false;
	_passPresel_Mu   = false;
	_passAll_Ele     = false;
	_passAll_Mu      = false;

	_photonIsGenuine        = false;
	_photonIsMisIDEle       = false;
	_photonIsHadronicPhoton = false;
	_photonIsHadronicFake   = false;

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
	_phoPhi.clear();
	_phoHoverE.clear();
	_phoSigmaIEtaIEtaFull5x5.clear();
	_phoPFChIso.clear();
	_phoPFPhoIso.clear();
	_phoPFNeuIso.clear();
	_phoTightID.clear();
	_phoMediumID.clear();
	_phoLooseID.clear();
	_phoMediumIDFunction.clear(); 
	_phoMediumIDNoHoverECut.clear(); 
	_phoMediumIDNoSIEIECut.clear(); 
	_phoMediumIDNoIsoCut.clear(); 

	_jetPt.clear();
	_jetEn.clear();
	_jetEta.clear();
	_jetPhi.clear();
	_jetRawPt.clear();
	_jetArea.clear();
	_jetpfCombinedMVAV2BJetTags.clear();
	_jetCSV2BJetTags.clear();
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

