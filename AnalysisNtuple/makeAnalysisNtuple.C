#define makeAnalysisNtuple_cxx
#include "makeAnalysisNtuple.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

#include"PUReweight.h"

#include "elemuSF.h"

std::string PUfilename = "Data_2016BCDGH_Pileup.root";
std::string PUfilename_up = "Data_2016BCDGH_Pileup_scaledUp.root";
std::string PUfilename_down = "Data_2016BCDGH_Pileup_scaledDown.root";
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


#ifdef makeAnalysisNtuple_cxx
makeAnalysisNtuple::makeAnalysisNtuple(int ac, char** av)
{

	tree = new EventTree(ac-3, av+3);

	selector = new Selector();
	evtPick = new EventPick("");

	BTagCalibration calib("csvv2", "CSVv2_Moriond17_B_H.csv");

	BTagCalibrationReader reader(BTagEntry::OP_MEDIUM,  // operating point
								 "central",             // central sys type
								 {"up", "down"});      // other sys types

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

	InitBranches();

	PUReweight* PUweighter = new PUReweight(ac-3, av+3, PUfilename);
	PUReweight* PUweighterUp = new PUReweight(ac-3, av+3, PUfilename_up);
	PUReweight* PUweighterDown = new PUReweight(ac-3, av+3, PUfilename_down);
	bool isMC;


	_evtWeight = getEvtWeight(outDirName);

	_muEffWeight    = 1.;
	_muEffWeight_Do = 1.;
	_muEffWeight_Up = 1.;
	_eleEffWeight    = 1.;
	_eleEffWeight_Up = 1.;
	_eleEffWeight_Do = 1.;

	Long64_t nEntr = tree->GetEntries();
	//	for(Long64_t entry=0; entry<100; entry++){
	for(Long64_t entry=0; entry<nEntr; entry++){
		if(entry%1000 == 0) std::cout << "processing entry " << entry << " out of " << nEntr << std::endl;

		tree->GetEntry(entry);
		isMC = !(tree->isData_);

		selector->process_objects(tree);

		evtPick->process_event(tree, selector, _PUweight);

		if ( evtPick->passPresel_ele || evtPick->passPresel_mu ) {
			InitVariables();
			FillEvent();

			if(isMC) {

				_PUweight    = PUweighter->getWeight(tree->nPUInfo_, tree->puBX_, tree->puTrue_);
				//				std::cout << "PUweight " << _PUweight << std::endl;
				_PUweight_Up = PUweighterUp->getWeight(tree->nPUInfo_, tree->puBX_, tree->puTrue_);
				_PUweight_Do = PUweighterDown->getWeight(tree->nPUInfo_, tree->puBX_, tree->puTrue_);

				_btagWeight    = getBtagSF("central", reader);
				_btagWeight_Up = getBtagSF("up", reader);
				_btagWeight_Do = getBtagSF("down", reader);				

				if (evtPick->passPresel_mu) {
					_muEffWeight    = getMuSF(evtPick->Muons.at(0),1);
					_muEffWeight_Do = getMuSF(evtPick->Muons.at(0),0);
					_muEffWeight_Up = getMuSF(evtPick->Muons.at(0),2);
					_eleEffWeight    = 1.;
					_eleEffWeight_Up = 1.;
					_eleEffWeight_Do = 1.;
				}

				if (evtPick->passPresel_ele) {
					_muEffWeight    = 1.;
					_muEffWeight_Do = 1.;
					_muEffWeight_Up = 1.;
					_eleEffWeight    = getEleSF(evtPick->Electrons.at(0),1);
					_eleEffWeight_Do = getEleSF(evtPick->Electrons.at(0),0);
					_eleEffWeight_Up = getEleSF(evtPick->Electrons.at(0),2);
				}
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
	_rho		     = tree->rho_;

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
		_elePFRelIso.push_back(selector->EleRelIso_corr.at(eleInd));
	}


	for (int i_mu = 0; i_mu <_nMu; i_mu++){
		int muInd = evtPick->Muons.at(i_mu);
		_muPt.push_back(tree->muPt_->at(muInd));
		_muPhi.push_back(tree->muPhi_->at(muInd));
		_muEta.push_back(tree->muEta_->at(muInd));
		_muPFRelIso.push_back(selector->MuRelIso_corr.at(muInd));
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
		_phoPFChIso.push_back( selector->PhoChHadIso_corr.at(phoInd));
		_phoPFNeuIso.push_back(selector->PhoNeuHadIso_corr.at(phoInd));
		_phoPFPhoIso.push_back(selector->PhoPhoIso_corr.at(phoInd));
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

double makeAnalysisNtuple::getBtagSF(string sysType, BTagCalibrationReader reader){
	
	double prod = 1.0;
	double jetpt;
	double jeteta;
	int jetflavor;
	double SFb;

	if(evtPick->bJets.size() == 0) {
		std::cout << "No bJets" << std::endl;
		return 1.0;
	}

	for(std::vector<int>::const_iterator bjetInd = evtPick->bJets.begin(); bjetInd != evtPick->bJets.end(); bjetInd++){
		jetpt = tree->jetPt_->at(*bjetInd);
		jeteta = fabs(tree->jetEta_->at(*bjetInd));
		jetflavor = abs(tree->jetPartonID_->at(*bjetInd));
		
		if (jetflavor == 5) SFb = reader.eval_auto_bounds(sysType, BTagEntry::FLAV_B, jeteta, jetpt); 
		else if(jetflavor == 4) SFb = reader.eval_auto_bounds(sysType, BTagEntry::FLAV_C, jeteta, jetpt); 
		else SFb = reader.eval_auto_bounds(sysType, BTagEntry::FLAV_UDSG, jeteta, jetpt); 

		//		SFb = 1.;
		prod *= 1.0 - SFb;
	}

	return 1.0 - prod;
}



double makeAnalysisNtuple::getMuSF(int muInd, int systLevel){
	double abseta = abs(tree->muEta_->at(muInd));
	double pt = tree->muPt_->at(muInd);

	//binned in 0.2 in absEta
	int muTrackEtaRegion = int(abseta/0.2);

	int muEtaRegion = -1;
	if (abseta < 0.9) {muEtaRegion = 0;}
	else if (abseta < 1.2) {muEtaRegion = 1;}
	else if (abseta < 2.1) {muEtaRegion = 2;}
	else {muEtaRegion = 3;}

	int muPtRegion_Trigger = -1;
	if (pt < 30){muPtRegion_Trigger = 0;}
	else if (pt < 40){muPtRegion_Trigger = 1;}
	else if (pt < 50){muPtRegion_Trigger = 2;}
	else if (pt < 60){muPtRegion_Trigger = 3;}
	else if (pt < 120){muPtRegion_Trigger = 4;}
	else if (pt < 200){muPtRegion_Trigger = 5;}
	else {muPtRegion_Trigger = 6;}

	int muPtRegion_IDIso = -1;
	if (pt < 25){muPtRegion_IDIso = 0;}
	else if (pt < 30){muPtRegion_IDIso = 1;}
	else if (pt < 40){muPtRegion_IDIso = 2;}
	else if (pt < 50){muPtRegion_IDIso = 3;}
	else if (pt < 60){muPtRegion_IDIso = 4;}
	else {muPtRegion_IDIso = 5;}

	double muEffSF = muTrackingSF[muTrackEtaRegion][systLevel] * muIdIsoSF[muPtRegion_IDIso][muEtaRegion][systLevel] * muTrigSF[muPtRegion_Trigger][muEtaRegion][systLevel];

	return muEffSF;
}


double makeAnalysisNtuple::getEleSF(int eleInd, int systLevel){

	double eta = tree->eleSCEta_->at(eleInd);
	double pt = tree->elePt_->at(eleInd);
	
	int eleRecoEtaRegion = 0;
	int eleIDEtaRegion = 0;

	if (eta > -2.45 ){eleRecoEtaRegion++;}
	if (eta > -2.4	){eleRecoEtaRegion++;}
	if (eta > -2.3	){eleRecoEtaRegion++;}
	if (eta > -2.2	){eleRecoEtaRegion++;}
	if (eta > -2.0	){eleRecoEtaRegion++; eleIDEtaRegion++;}
	if (eta > -1.8	){eleRecoEtaRegion++;}
	if (eta > -1.63	){eleRecoEtaRegion++;}
	if (eta > -1.566){eleRecoEtaRegion++; eleIDEtaRegion++;}
	if (eta > -1.444){eleRecoEtaRegion++; eleIDEtaRegion++;}
	if (eta > -1.2	){eleRecoEtaRegion++;}
	if (eta > -1.0	){eleRecoEtaRegion++;}
	if (eta > -0.8	){eleIDEtaRegion++;}
	if (eta > -0.6	){eleRecoEtaRegion++;}
	if (eta > -0.4	){eleRecoEtaRegion++;}
	if (eta > -0.2	){eleRecoEtaRegion++;}
	if (eta > 0.0	){eleRecoEtaRegion++; eleIDEtaRegion++;}
	if (eta > 0.2	){eleRecoEtaRegion++;}
	if (eta > 0.4	){eleRecoEtaRegion++;}
	if (eta > 0.6	){eleRecoEtaRegion++;}
	if (eta > 0.8	){eleIDEtaRegion++;}
	if (eta > 1.0	){eleRecoEtaRegion++;}
	if (eta > 1.2	){eleRecoEtaRegion++;}
	if (eta > 1.444	){eleRecoEtaRegion++; eleIDEtaRegion++;}
	if (eta > 1.566	){eleRecoEtaRegion++; eleIDEtaRegion++;}
	if (eta > 1.63	){eleRecoEtaRegion++;}
	if (eta > 1.8	){eleRecoEtaRegion++;}
	if (eta > 2.0	){eleRecoEtaRegion++; eleIDEtaRegion++;}
	if (eta > 2.2	){eleRecoEtaRegion++;}
	if (eta > 2.3	){eleRecoEtaRegion++;}
	if (eta > 2.4	){eleRecoEtaRegion++;}
	if (eta > 2.45	){eleRecoEtaRegion++;}

	int eleIDPtRegion = 0;

	if (pt > 20.0  ){eleIDPtRegion++;}
	if (pt > 35.0  ){eleIDPtRegion++;}
	if (pt > 50.0  ){eleIDPtRegion++;}
	if (pt > 90.0  ){eleIDPtRegion++;}
	if (pt > 150.0 ){eleIDPtRegion++;}
	

	int eleTrigEtaRegion = eleIDEtaRegion;
	int eleTrigPtRegion  = eleIDPtRegion;


	double eleEffSF = eleTrigSF[eleTrigEtaRegion][eleTrigPtRegion][systLevel] * eleIDSF[eleIDEtaRegion][eleIDPtRegion][systLevel] * eleRecoSF[eleRecoEtaRegion][systLevel];

	return eleEffSF;


}

double makeAnalysisNtuple::getEvtWeight(string outputName){
	double evtWeight = -1.;
	if( outputName.find("Data") != std::string::npos) {evtWeight = 1.;}
	else if( outputName.find("TTGamma_hadronic") != std::string::npos) {evtWeight = TTGamma_hadronic_SF;}
	else if( outputName.find("TTGamma_semilept") != std::string::npos) {evtWeight = TTGamma_semilept_SF;}
	else if( outputName.find("TTGamma_dilept") != std::string::npos) {evtWeight = TTGamma_dilept_SF;}
	else if( outputName.find("TTbar") != std::string::npos) {evtWeight = TTbar_SF;}
	else if( outputName.find("W1jets") != std::string::npos) {evtWeight = W1jets_SF;}
	else if( outputName.find("W2jets") != std::string::npos) {evtWeight = W2jets_SF;}
	else if( outputName.find("W3jets") != std::string::npos) {evtWeight = W3jets_SF;}
	else if( outputName.find("W4jets") != std::string::npos) {evtWeight = W4jets_SF;}
	else if( outputName.find("DYjets") != std::string::npos) {evtWeight = DYjets_SF;}
	else if( outputName.find("ST_tW") != std::string::npos) {evtWeight = ST_tW_SF;}
	else if( outputName.find("ST_tbarW") != std::string::npos) {evtWeight = ST_tbarW_SF;}
	else if( outputName.find("ST_tchannel") != std::string::npos) {evtWeight = ST_tchannel_SF;}
	else if( outputName.find("ST_tbarchannel") != std::string::npos) {evtWeight = ST_tbarchannel_SF;}
	else if( outputName.find("ST_schannel") != std::string::npos) {evtWeight = ST_schannel_SF;}
	else {
		cout << "-------------------------------------------------" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "-- Unable to find event weight for this sample --" << endl;
		cout << "-- Sample will be saved with a weight of -1    --" << endl;
		cout << "-------------------------------------------------" << endl;
		cout << "-------------------------------------------------" << endl;
	}

	cout << "Using event weight " << evtWeight << endl;

	return evtWeight;
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
