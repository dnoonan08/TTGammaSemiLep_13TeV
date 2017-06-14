#define makeAnalysisNtuple_cxx
#include "makeAnalysisNtuple.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

#include"PUReweight.h"


std::string PUfilename = "MyDataPileupHistogram.root";
int jecvar012_g = 1; // 0:down, 1:norm, 2:up
int jervar012_g = 1; // 0:down, 1:norm, 2:up
int mueff012_g = 1; // 0:down, 1:norm, 2:up
int eleeff012_g = 1;
int btagvar012_g = 1; // 0:down, 1:norm, 2:up
int phosmear012_g = 1; // 0:down, 1:norm, 2:up 
int musmear012_g = 1; // 0:down, 1:norm, 2: up
int elesmear012_g = 1; // 0:down, 1:norm, 2: up
int toppt012_g = 1; // 0:down, 1:norm, 2: up


#include "BTagCalibrationStandalone.h"

BTagCalibration calib("csvv2", "CSVv2_Moriond17_B_H.csv");

BTagCalibrationReader reader(BTagEntry::OP_MEDIUM,  // operating point
							 "central",             // central sys type
							 {"up", "down"});      // other sys types

#ifdef makeAnalysisNtuple_cxx
makeAnalysisNtuple::makeAnalysisNtuple(int ac, char** av)
{

	tree = new EventTree(ac-3, av+3);

	selector = new Selector();
	evtPick = new EventPick("");

	if (tree == 0) {
		std::cout <<"Tree not recognized" << endl;
	}

	reader.load(calib,                // calibration instance
				BTagEntry::FLAV_B,    // btag flavour
				"comb");               // measurement type

	reader.load(calib,                // calibration instance
				BTagEntry::FLAV_C,    // btag flavour
				"comb");               // measurement type

	reader.load(calib,                // calibration instance
				BTagEntry::FLAV_UDSG,    // btag flavour
				"comb");               // measurement type


	//Look into the output file names for indications of whether this is for a systematic
	bool systematics = false;
	std::string outDirName(av[2]);
	if( outDirName.find("JEC_up") != std::string::npos) {systematics=true; jecvar012_g = 2;}
	if( outDirName.find("JEC_down") != std::string::npos) {systematics=true; jecvar012_g = 0;}
	if( outDirName.find("JER_up") != std::string::npos) {systematics=true; jervar012_g = 2;}
	if( outDirName.find("JER_down") != std::string::npos) {systematics=true; jervar012_g = 0;}
	if( outDirName.find("EleEff_up") != std::string::npos) {systematics=true; eleeff012_g = 2;}
	if( outDirName.find("EleEff_down") != std::string::npos) {systematics=true; eleeff012_g = 0;}
	if( outDirName.find("MuEff_up") != std::string::npos) {systematics=true; mueff012_g = 2;}
	if( outDirName.find("MuEff_down") != std::string::npos) {systematics=true; mueff012_g = 0;}
	if( outDirName.find("Btag_up") != std::string::npos) {systematics=true; btagvar012_g = 2;}
	if( outDirName.find("Btag_down") != std::string::npos) {systematics=true; btagvar012_g = 0;}
	if( outDirName.find("pho_up") != std::string::npos) {systematics=true; phosmear012_g = 2;}
	if( outDirName.find("pho_down") != std::string::npos) {systematics=true; phosmear012_g = 0;}
	if( outDirName.find("musmear_up") != std::string::npos) {systematics=true; musmear012_g = 2;}
	if( outDirName.find("musmear_down") != std::string::npos) {systematics=true; musmear012_g = 0;}
	if( outDirName.find("elesmear_up") != std::string::npos) {systematics=true; elesmear012_g = 2;}
	if( outDirName.find("elesmear_down") != std::string::npos) {systematics=true; elesmear012_g = 0;}
	if( outDirName.find("toppt_up") != std::string::npos) {systematics=true; toppt012_g = 2;}
	if( outDirName.find("toppt_down") != std::string::npos) {systematics=true; toppt012_g = 0;}	

	std::cout << "JEC: " << jecvar012_g << "  JER: " << jervar012_g << "  MuEff: " << mueff012_g << "  BtagVar: " << btagvar012_g << "  ";
	std::cout << "  PhoSmear: " << phosmear012_g << "  muSmear: " << musmear012_g << "  eleSmear: " << elesmear012_g << "  ";
	std::cout << "  topPt: " << toppt012_g << std::endl;


	
	outputTree = new TTree("AnalysisTree","AnalysisTree");

	PUReweight* PUweighter = new PUReweight(ac-3, av+3, PUfilename);
	// PUReweight* PUweighterUp = new PUReweight(ac-3, av+3, PUfilename);
	// PUReweight* PUweighterDown = new PUReweight(ac-3, av+3, PUfilename);
	bool isMC;





	Long64_t nEntr = tree->GetEntries();
	//	for(Long64_t entry=0; entry<100; entry++){
	for(Long64_t entry=0; entry<nEntr; entry++){
		if(entry%10000 == 0) std::cout << "processing entry " << entry << " out of " << nEntr << std::endl;

		tree->GetEntry(entry);
		isMC = !(tree->isData_);

		selector->process_objects(tree);

		evtPick->process_event(tree, selector, _PUweight);

		if ( evtPick->passPresel_ele || evtPick->passPresel_mu ) {
			InitVariables();
			FillEvent();

			if(isMC) {
				_PUweight    = PUweighter->getWeight(tree->nPUInfo_, tree->puBX_, tree->puTrue_);
				std::cout << "PUweight " << _PUweight << std::endl;
				// _PUweight_Up = PUweighterUp->getWeight(tree->nPUInfo_, tree->puBX_, tree->puTrue_);
				// _PUweight_Do = PUweighterDown->getWeight(tree->nPUInfo_, tree->puBX_, tree->puTrue_);
				_btagWeight    = getBtagSF("central");
				// _btagWeight_Up = getBtagSF("up");
				// _btagWeight_Do = getBtagSF("down");
				

			}

			outputTree->Fill();
		}
	}


	TFile *outputFile = new TFile(av[2],"recreate");
	outputTree->Write();
	outputFile->Close();

}


void makeAnalysisNtuple::FillEvent()
{

	_run             = tree->run_;
	_event           = tree->event_;
	_lumis		     = tree->lumis_;
	_isData		     = tree->isData_;
	_nVtx		     = tree->nVtx_;
	_nGoodVtx	     = tree->nGoodVtx;
	_isPVGood	     = tree->isPVGood_;
	_rho		     = tree->isPVGood_;

	_genMET		     = tree->genMET_;
	_pfMET		     = tree->pfMET_;
	_pfMETPhi	     = tree->pfMETPhi_;

	_nPho		     = evtPick->Photons.size();
	_nEle		     = evtPick->Electrons.size();
	_nMu		     = evtPick->Muons.size();
	_nJet            = evtPick->Jets.size();
	_nBJet           = evtPick->bJets.size();

	for (int i_ele = 0; i_ele <_nEle; i_ele++){
		int eleInd = evtPick->Electrons.at(i_ele);
		_elePt.push_back(tree->elePt_->at(eleInd));
		_elePhi.push_back(tree->elePhi_->at(eleInd));
		_eleSCEta.push_back(tree->eleSCEta_->at(eleInd));
		_elePFChIso.push_back(tree->elePFChIso_->at(eleInd));
		_elePFPhoIso.push_back(tree->elePFPhoIso_->at(eleInd));
		_elePFNeuIso.push_back(tree->elePFNeuIso_->at(eleInd));
	}

	for (int i_mu = 0; i_mu <_nMu; i_mu++){
		int muInd = evtPick->Muons.at(i_mu);
		_muPt.push_back(tree->muPt_->at(muInd));
		_muPhi.push_back(tree->muPhi_->at(muInd));
		_muEta.push_back(tree->muEta_->at(muInd));
		_muPFChIso.push_back(tree->muPFChIso_->at(muInd));
		_muPFPhoIso.push_back(tree->muPFPhoIso_->at(muInd));
		_muPFNeuIso.push_back(tree->muPFNeuIso_->at(muInd));
		_muPFPUIso.push_back(tree->muPFPUIso_->at(muInd));
	}

	_passPresel_Ele  = evtPick->passPresel_ele;
	_passPresel_Mu   = evtPick->passPresel_mu;
	_passAll_Ele     = evtPick->passAll_ele;
	_passAll_Mu      = evtPick->passAll_mu;
   
	for (int i_pho = 0; i_pho <_nPho; i_pho++){
		int phoInd = evtPick->Photons.at(i_pho);
		_phoEt.push_back(tree->phoEt_->at(phoInd));
		_phoEta.push_back(tree->phoEta_->at(phoInd));
		_phoPhi.push_back(tree->phoPhi_->at(phoInd));
		_phoSigmaIEtaIEtaFull5x5.push_back(tree->phoSigmaIEtaIEtaFull5x5_->at(phoInd));
		_phoPFChIso.push_back(tree->phoPFChIso_->at(phoInd));
		_phoPFPhoIso.push_back(tree->phoPFPhoIso_->at(phoInd));
		_phoPFNeuIso.push_back(tree->phoPFNeuIso_->at(phoInd));
	}



	for (int i_jet = 0; i_jet <_nJet; i_jet++){
		
		int jetInd = evtPick->Jets.at(i_jet);
		_jetPt.push_back(tree->jetPt_->at(jetInd));
		_jetEn.push_back(tree->jetEn_->at(jetInd));
		_jetEta.push_back(tree->jetEta_->at(jetInd));
		_jetPhi.push_back(tree->jetPhi_->at(jetInd));
		_jetRawPt.push_back(tree->jetRawPt_->at(jetInd));
		_jetArea.push_back(tree->jetArea_->at(jetInd));
		_jetpfCombinedMVAV2BJetTags.push_back(tree->jetpfCombinedMVAV2BJetTags_->at(jetInd));
		_jetPartonID.push_back(tree->jetPartonID_->at(jetInd));
		_jetGenJetPt.push_back(tree->jetGenJetPt_->at(jetInd));
		_jetGenPartonID.push_back(tree->jetGenPartonID_->at(jetInd));
		_jetGenPt.push_back(tree->jetGenPt_->at(jetInd));
		_jetGenEta.push_back(tree->jetGenEta_->at(jetInd));
		_jetGenPhi.push_back(tree->jetGenPhi_->at(jetInd));
	}	

}


// https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting
double makeAnalysisNtuple::SFtop(double pt){
	// if(top_sample_g==1) return exp(0.159 - 0.00141*pt);
	// if(top_sample_g==2) return exp(0.148 - 0.00129*pt);
	return 1.0;
}

double makeAnalysisNtuple::topPtWeight(){
	double toppt=0.0;
	double antitoppt=0.0;
	double weight = 1.0;
	for(int mcInd=0; mcInd<tree->nMC_; ++mcInd){
		if(tree->mcPID->at(mcInd)==6) toppt = tree->mcPt->at(mcInd);
		if(tree->mcPID->at(mcInd)==-6) antitoppt = tree->mcPt->at(mcInd);
	}
	if(toppt > 0.001 && antitoppt > 0.001)
		weight = sqrt( SFtop(toppt) * SFtop(antitoppt) );
	
	//This has been changed, the new prescription is to not use the top pt reweighting, and the syst is using it
	if(toppt012_g == 1) return 1.0;
	if(toppt012_g == 0) return weight;
	if(toppt012_g == 2) return weight;

	// should not get here
	return 1.0;
}

double makeAnalysisNtuple::getBtagSF(string sysType){
	
	double prod = 1.0;
	double jetpt;
	double jeteta;
	int jetflavor;
	double SFb;

	if(evtPick->bJets.size() == 0) return 1.0;

	for(std::vector<int>::const_iterator bjetInd = evtPick->bJets.begin(); bjetInd != evtPick->bJets.end(); bjetInd++){
		jetpt = tree->jetPt_->at(*bjetInd);
		jeteta = fabs(tree->jetEta_->at(*bjetInd));
		jetflavor = abs(tree->jetPartonID_->at(*bjetInd));
		
		if (jetflavor == 5) SFb = reader.eval_auto_bounds(sysType, BTagEntry::FLAV_B, jeteta, jetpt); 
		else if(jetflavor == 4) SFb = reader.eval_auto_bounds(sysType, BTagEntry::FLAV_C, jeteta, jetpt); 
		else SFb = reader.eval_auto_bounds(sysType, BTagEntry::FLAV_UDSG, jeteta, jetpt); 

		SFb = 1.;
		prod *= 1.0 - SFb;
	}
	return 1.0 - prod;
}

double makeAnalysisNtuple::WjetsBRreweight(){

	int countLeps = 0;

	//Need to try to avoid double counting of tau's (check if momPt is the same before counting, since status flag isn't there)
	double tauMomPt1 = -1.;
	double tauMomPt2 = -1.;
	
	for(int mcInd=0; mcInd<tree->nMC_; ++mcInd){
		if( (TMath::Abs(tree->mcPID->at(mcInd)) == 11 ||
			 TMath::Abs(tree->mcPID->at(mcInd)) == 13 ||
			 TMath::Abs(tree->mcPID->at(mcInd)) == 15 ) &&
			TMath::Abs(tree->mcMomPID->at(mcInd)) == 24 &&
			TMath::Abs(tree->mcGMomPID->at(mcInd)) == 6) {

			if (TMath::Abs(tree->mcPID->at(mcInd)) == 15){
				if (tauMomPt1==-1.){
					tauMomPt1 = tree->mcMomPt->at(mcInd);
					countLeps += 1;
				}
				else if (tauMomPt2==-1.){
					if (tree->mcMomPt->at(mcInd)!=tauMomPt1) {
						tauMomPt2 = tree->mcMomPt->at(mcInd);
						countLeps += 1;
					}
				}
				else{
					if (tree->mcMomPt->at(mcInd)!=tauMomPt1 && tree->mcMomPt->at(mcInd)!=tauMomPt2) {
						countLeps += 1;
					}
				}
			}
			else {
				countLeps += 1;
			}
		}
	}
	double reweight=1.;
	if (countLeps==0){reweight = .6741*.6741*9./4.;}
	else if(countLeps==1){reweight = .6741*.3259*2*9./4.;}
	else if(countLeps==2){reweight = .3259*.3259*9.;}
	else {
		std::cout << "MORE THAN TWO LEPTONS???????" << std::endl;
		std::cout << countLeps << std::endl;
	}
	
	return reweight;
	
}

#endif

int main(int ac, char** av){
  if(ac != 4){
    std::cout << "usage: ./makeAnalysisNtuple sampleName outputFile inputFile[s]" << std::endl;
    return -1;
  }

  makeAnalysisNtuple(ac, av);


  return 0;
}
