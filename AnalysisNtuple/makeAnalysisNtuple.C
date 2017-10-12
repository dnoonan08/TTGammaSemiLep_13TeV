#define makeAnalysisNtuple_cxx
#include "makeAnalysisNtuple.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <iostream>

#include"PUReweight.h"
//#include"JEC/JECvariation.h"
//#include"OverlapRemove.cpp"

#include "elemuSF.h"

std::string PUfilename = "Data_2016BCDGH_Pileup.root";
std::string PUfilename_up = "Data_2016BCDGH_Pileup_scaledUp.root";
std::string PUfilename_down = "Data_2016BCDGH_Pileup_scaledDown.root";

int jecvar012_g = 1; // 0:down, 1:norm, 2:up
int jervar012_g = 1; // 0:down, 1:norm, 2:up
int phosmear012_g = 1; // 0:down, 1:norm, 2:up 
int musmear012_g = 1; // 0:down, 1:norm, 2: up
int elesmear012_g = 1; // 0:down, 1:norm, 2: up

#include "BTagCalibrationStandalone.h"

bool overlapRemovalTT(EventTree* tree);
bool overlapRemovalWZ(EventTree* tree);
bool dileptonsample;



#ifdef makeAnalysisNtuple_cxx
makeAnalysisNtuple::makeAnalysisNtuple(int ac, char** av)
{

	tree = new EventTree(ac-3, av+3);

	sampleType = av[1];
	systematicType = "";
	cout << sampleType << endl;
	
	size_t pos = sampleType.find("__");
	if (pos != std::string::npos){
		systematicType = sampleType.substr(pos+2,sampleType.length());
		sampleType = sampleType.substr(0,pos);
	}

    cout << sampleType << "  " << systematicType << endl;

	if (std::end(allowedSampleTypes) == std::find(std::begin(allowedSampleTypes), std::end(allowedSampleTypes), sampleType)){
		cout << "This is not an allowed sample, please specify one from this list (or add to this list in the code):" << endl;
		for (int i =0; i < sizeof(allowedSampleTypes)/sizeof(allowedSampleTypes[0]); i++){
			cout << "    "<<allowedSampleTypes[i] << endl;
		}			
		return;
	}


	selector = new Selector();

	evtPick = new EventPick("");

	selector->pho_applyPhoID = false;
	selector->looseJetID = false;

	selector->useDeepCSVbTag = true;

	// selector->veto_pho_jet_dR = -1.; //remove jets which have a photon close to them 
	// selector->veto_jet_pho_dR = -1.; //remove photons which have a jet close to them (after having removed jets too close to photon from above cut)

	
	//	selector->jet_Pt_cut = 40.;
	evtPick->Njet_ge = 2;	
	evtPick->NBjet_ge = 1;	
	BTagCalibration calib;
	if (!selector->useDeepCSVbTag){
		calib = BTagCalibration("csvv2", "CSVv2_Moriond17_B_H.csv");
	} else {
		calib = BTagCalibration("deepcsv", "DeepCSV_Moriond17_B_H.csv");
	}

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
				"incl");               // measurement type


	bool doOverlapRemoval = false;
	bool doOverlapRemoval_WZ = false;	
	bool skipOverlap = false;
	if( sampleType == "TTbarPowheg" || sampleType == "TTbarMCatNLO" || sampleType == "TTbarMadgraph_SingleLeptFromT" || sampleType == "TTbarMadgraph_SingleLeptFromTbar" || sampleType == "TTbarMadgraph_Dilepton") doOverlapRemoval = true;

	if( sampleType == "W1jets" || sampleType == "W2jets" ||  sampleType == "W3jets" || sampleType == "W4jets" || sampleType=="DYjetsM10to50" || sampleType=="DYjetsM50") doOverlapRemoval_WZ = true;
	if(doOverlapRemoval || doOverlapRemoval_WZ) std::cout << "########## Will apply overlap removal ###########" << std::endl;



	dileptonsample = false;

	if( systematicType=="JEC_up")       {jecvar012_g = 2; selector->JECsystLevel=2;}
	if( systematicType=="JEC_down")     {jecvar012_g = 0; selector->JECsystLevel=0;}
	if( systematicType=="JER_up")       {jervar012_g = 2; selector->JERsystLevel=2;}
	if( systematicType=="JER_down")     {jervar012_g = 0; selector->JERsystLevel=0;}
	if( systematicType=="pho_up")       {phosmear012_g = 2;}
	if( systematicType=="pho_down")     {phosmear012_g = 0;}
	if( systematicType=="musmear_up")   {musmear012_g = 2;}
	if( systematicType=="musmear_down") {musmear012_g = 0;}
	if( systematicType=="elesmear_up")  {elesmear012_g = 2;}
	if( systematicType=="elesmear_down"){elesmear012_g = 0;}
	if( systematicType=="Dilep")     {dileptonsample =true; evtPick->Nmu_eq=2; evtPick->Nele_eq=2;}
	std::cout << "Dilepton Sample :" << dileptonsample << std::endl;
	std::cout << "JEC: " << jecvar012_g << "  JER: " << jervar012_g << "  ";
	std::cout << "  PhoSmear: " << phosmear012_g << "  muSmear: " << musmear012_g << "  eleSmear: " << elesmear012_g << endl;



	std::string outputDirectory(av[2]);
	std::string outputFileName = outputDirectory + "/" + sampleType+"_AnalysisNtuple.root";
	// char outputFileName[100];
	cout << av[2] << " " << sampleType << " " << systematicType << endl;
	//	outputFileName = sprintf("%s_AnalysisNtuple.root",sampleType);
	if (systematicType!=""){
		outputFileName = outputDirectory + "/"+systematicType + "_" +sampleType+"_AnalysisNtuple.root";
		//		sprintf(outputFileName,"%s/%s_%s_AnalysisNtuple.root",av[2],systematicType,sampleType);
	}
	cout << av[2] << " " << sampleType << " " << systematicType << endl;
	cout << outputFileName << endl;
	TFile *outputFile = new TFile(outputFileName.c_str(),"recreate");
	outputTree = new TTree("AnalysisTree","AnalysisTree");

	InitBranches();

	PUReweight* PUweighter = new PUReweight(ac-3, av+3, PUfilename);
	PUReweight* PUweighterUp = new PUReweight(ac-3, av+3, PUfilename_up);
	PUReweight* PUweighterDown = new PUReweight(ac-3, av+3, PUfilename_down);
	bool isMC;

	tree->GetEntry(0);
	isMC = !(tree->isData_);
	std::cout << "isMC: " << isMC << endl;

	// JECvariation* jecvar;
	// if (isMC) {
	// 	jecvar = new JECvariation("./jecFiles/Summer16_23Sep2016V4", isMC);
	// }

	_lumiWeight = getEvtWeight(sampleType);

	_muEffWeight    = 1.;
	_muEffWeight_Do = 1.;
	_muEffWeight_Up = 1.;
	_eleEffWeight    = 1.;
	_eleEffWeight_Up = 1.;
	_eleEffWeight_Do = 1.;

	Long64_t nEntr = tree->GetEntries();
	//	for(Long64_t entry=0; entry<100; entry++){

	//	nEntr = 10000;

	int dumpFreq = 1;
	if (nEntr >50)     { dumpFreq = 5; }
	if (nEntr >100)     { dumpFreq = 10; }
	if (nEntr >500)     { dumpFreq = 50; }
	if (nEntr >1000)    { dumpFreq = 100; }
	if (nEntr >5000)    { dumpFreq = 500; }
	if (nEntr >10000)   { dumpFreq = 1000; }
	if (nEntr >50000)   { dumpFreq = 5000; }
	if (nEntr >100000)  { dumpFreq = 10000; }
	if (nEntr >500000)  { dumpFreq = 50000; }
	if (nEntr >1000000) { dumpFreq = 100000; }
	if (nEntr >5000000) { dumpFreq = 500000; }
	if (nEntr >10000000){ dumpFreq = 1000000; }
	int count_overlapVJets=0;
	int count_overlapTTbar=0;
	for(Long64_t entry=0; entry<nEntr; entry++){
		if(entry%dumpFreq == 0) std::cout << "processing entry " << entry << " out of " << nEntr << std::endl;

		tree->GetEntry(entry);
		isMC = !(tree->isData_);

		if( isMC && doOverlapRemoval){
			if (overlapRemovalTT(tree)){
	
				count_overlapTTbar++;			
			//	cout << "removing event " << entry << endl;
				continue;
			}
		}
		if( isMC && doOverlapRemoval_WZ){
                        if (overlapRemovalWZ(tree)){
				count_overlapVJets++;
				continue;
			}
		}
		// //Apply systematics shifts where needed
		// if( isMC ){
		// 	jecvar->applyJEC(tree, jecvar012_g); // 0:down, 1:norm, 2:up

		// }


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

				_btagWeight    = getBtagSF("central", reader, _btagSF);
				_btagWeight_Up = getBtagSF("up", reader, _btagSF_Up);
				_btagWeight_Do = getBtagSF("down", reader, _btagSF_Do);				

				if (evtPick->passPresel_mu) {
					int muInd_ = evtPick->Muons.at(0);
					_muEffWeight    = getMuSF(tree->muPt_->at(muInd_),tree->muEta_->at(muInd_),1);
					_muEffWeight_Do = getMuSF(tree->muPt_->at(muInd_),tree->muEta_->at(muInd_),0);
					_muEffWeight_Up = getMuSF(tree->muPt_->at(muInd_),tree->muEta_->at(muInd_),2);
					_eleEffWeight    = 1.;
					_eleEffWeight_Up = 1.;
					_eleEffWeight_Do = 1.;
				}

				if (evtPick->passPresel_ele) {
					int eleInd_ = evtPick->Electrons.at(0);
					_muEffWeight    = 1.;
					_muEffWeight_Do = 1.;
					_muEffWeight_Up = 1.;
					_eleEffWeight    = getEleSF(tree->elePt_->at(eleInd_),tree->eleSCEta_->at(eleInd_),1);
					_eleEffWeight_Do = getEleSF(tree->elePt_->at(eleInd_),tree->eleSCEta_->at(eleInd_),0);
					_eleEffWeight_Up = getEleSF(tree->elePt_->at(eleInd_),tree->eleSCEta_->at(eleInd_),2);
				}
			}

			outputTree->Fill();
		}
	}
	if (doOverlapRemoval){
		std::cout << "Total number of events removed from TTbar:"<< count_overlapVJets <<std::endl;
	}
	if(doOverlapRemoval_WZ){
		 std::cout << "Total number of events removed from W/ZJets:"<< count_overlapVJets <<std::endl;
	}
		
	outputFile->cd();
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

	_evtWeight       = _lumiWeight *  ((tree->genWeight_ >= 0) ? 1 : -1);  //event weight needs to be positive or negative depending on sign of genWeight (to account for mc@nlo negative weights)

	_genMET		     = tree->genMET_;
	_pfMET		     = tree->pfMET_;
	_pfMETPhi	     = tree->pfMETPhi_;

	_nPho		     = evtPick->Photons.size();
	_nEle		     = evtPick->Electrons.size();
	_nMu		     = evtPick->Muons.size();
	_nJet            = evtPick->Jets.size();
	_nBJet           = evtPick->bJets.size();
	_nMC             = tree->nMC_;


	for (int i_ele = 0; i_ele <_nEle; i_ele++){
		int eleInd = evtPick->Electrons.at(i_ele);
		_elePt.push_back(tree->elePt_->at(eleInd));
		_elePhi.push_back(tree->elePhi_->at(eleInd));
		_eleSCEta.push_back(tree->eleSCEta_->at(eleInd));
		_elePFRelIso.push_back(selector->EleRelIso_corr.at(eleInd));
		lepVector.SetPtEtaPhiE(tree->elePt_->at(eleInd),
							   tree->eleSCEta_->at(eleInd),
							   tree->elePhi_->at(eleInd),
							   tree->eleEn_->at(eleInd));

	}


	for (int i_mu = 0; i_mu <_nMu; i_mu++){
		int muInd = evtPick->Muons.at(i_mu);
		_muPt.push_back(tree->muPt_->at(muInd));
		_muPhi.push_back(tree->muPhi_->at(muInd));
		_muEta.push_back(tree->muEta_->at(muInd));
		_muPFRelIso.push_back(selector->MuRelIso_corr.at(muInd));
		lepVector.SetPtEtaPhiE(tree->muPt_->at(muInd),
							   tree->muEta_->at(muInd),
							   tree->muPhi_->at(muInd),
							   tree->muEn_->at(muInd));
	}
//	std::cout << "number of muons:" <<_nMu << std::endl;
//	std::cout << "number of electrons:" <<_nEle << std::endl;
//	std::cout<<"dilepton?"<< dileptonsample <<std::endl;
	
	if (dileptonsample){
		if (_nMu==2) {
//		std::cout<<"doing muons"<<std::endl;

		int muInd1 = evtPick->Muons.at(0);
		int muInd2 = evtPick->Muons.at(1);

		lepVector.SetPtEtaPhiE(tree->muPt_->at(muInd1),
                                                           tree->muEta_->at(muInd1),
                                                           tree->muPhi_->at(muInd1),
                                                           tree->muEn_->at(muInd1));
		lepVector2.SetPtEtaPhiE(tree->muPt_->at(muInd2),
                                                           tree->muEta_->at(muInd2),
                                                           tree->muPhi_->at(muInd2),
                                                           tree->muEn_->at(muInd2));	
		_DilepMass = (lepVector+lepVector2).M();
		_DilepDelR = lepVector.DeltaR(lepVector2);
		
		}
		

	    	if (_nEle==2){
//		std::cout<<"doing electrons"<<std::endl;
		int eleInd1 = evtPick->Electrons.at(0);
                int eleInd2 = evtPick->Electrons.at(1);

		lepVector.SetPtEtaPhiE(tree->elePt_->at(eleInd1),
                                                           tree->eleEta_->at(eleInd1),
                                                           tree->elePhi_->at(eleInd1),
                                                           tree->eleEn_->at(eleInd1));
                lepVector2.SetPtEtaPhiE(tree->elePt_->at(eleInd2),
                                                           tree->eleEta_->at(eleInd2),
                                                           tree->elePhi_->at(eleInd2),
                                                           tree->eleEn_->at(eleInd2));
		
		_DilepMass = (lepVector+lepVector2).M();

		_DilepDelR = lepVector.DeltaR(lepVector2);
 
		}
	}
	
		
		

	_WtransMass = TMath::Sqrt(2*lepVector.Pt()*tree->pfMET_*( 1.0 - TMath::Cos(dR(0.0,lepVector.Phi(),0.0,tree->pfMETPhi_)) ));

	_passPresel_Ele  = evtPick->passPresel_ele;
	_passPresel_Mu   = evtPick->passPresel_mu;
	_passAll_Ele     = evtPick->passAll_ele;
	_passAll_Mu      = evtPick->passAll_mu;

	int countMediumIDPho = 0;
	int countTightIDPho = 0;
	for (int i_pho = 0; i_pho <_nPho; i_pho++){
		int phoInd = evtPick->Photons.at(i_pho);
		phoVector.SetPtEtaPhiM(tree->phoEt_->at(phoInd),
							   tree->phoEta_->at(phoInd),
							   tree->phoPhi_->at(phoInd),
							   0.0);

		_phoEt.push_back(tree->phoEt_->at(phoInd));
		_phoEta.push_back(tree->phoEta_->at(phoInd));
		_phoSCEta.push_back(tree->phoSCEta_->at(phoInd));
		_phoPhi.push_back(tree->phoPhi_->at(phoInd));
		_phoIsBarrel.push_back( abs(tree->phoSCEta_->at(phoInd))<1.47 );
		_phoHoverE.push_back(tree->phoHoverE_->at(phoInd));
		_phoSIEIE.push_back(tree->phoSigmaIEtaIEtaFull5x5_->at(phoInd));
		_phoPFChIso.push_back( selector->PhoChHadIso_corr.at(phoInd));
		_phoPFNeuIso.push_back(selector->PhoNeuHadIso_corr.at(phoInd));
		_phoPFPhoIso.push_back(selector->PhoPhoIso_corr.at(phoInd));
		_phoPFRandConeChIso.push_back( selector->PhoRandConeChHadIso_corr.at(phoInd));
		_phoPFChIsoUnCorr.push_back( tree->phoPFChIso_->at(phoInd));
		_phoPFNeuIsoUnCorr.push_back(tree->phoPFNeuIso_->at(phoInd));
		_phoPFPhoIsoUnCorr.push_back(tree->phoPFPhoIso_->at(phoInd));
		_phoPFRandConeChIsoUnCorr.push_back( tree->phoPFRandConeChIso_->at(phoInd) );
		_phoTightID.push_back(tree->phoIDbit_->at(phoInd)>>2&1);
		_phoMediumID.push_back(tree->phoIDbit_->at(phoInd)>>1&1);
		_phoLooseID.push_back(tree->phoIDbit_->at(phoInd)>>0&1);
		vector<bool> phoMediumCuts =  passPhoMediumID(phoInd);
		_phoMediumIDFunction.push_back(  phoMediumCuts.at(0));
		_phoMediumIDPassHoverE.push_back(phoMediumCuts.at(1));
		_phoMediumIDPassSIEIE.push_back( phoMediumCuts.at(2));
		_phoMediumIDPassChIso.push_back( phoMediumCuts.at(3));
		_phoMediumIDPassNeuIso.push_back(phoMediumCuts.at(4));
		_phoMediumIDPassPhoIso.push_back(phoMediumCuts.at(5));

		vector<bool> phoTightCuts =  passPhoTightID(phoInd);
		_phoTightIDFunction.push_back(  phoTightCuts.at(0));
		_phoTightIDPassHoverE.push_back(phoTightCuts.at(1));
		_phoTightIDPassSIEIE.push_back( phoTightCuts.at(2));
		_phoTightIDPassChIso.push_back( phoTightCuts.at(3));
		_phoTightIDPassNeuIso.push_back(phoTightCuts.at(4));
		_phoTightIDPassPhoIso.push_back(phoTightCuts.at(5));
			
		// _phoMediumIDFunction.push_back(   passPhoMediumID(phoInd,true,true,true) );
		// _phoMediumIDNoHoverECut.push_back(passPhoMediumID(phoInd,false,true,true));
		// _phoMediumIDNoSIEIECut.push_back( passPhoMediumID(phoInd,true,false,true));
		// _phoMediumIDNoIsoCut.push_back(   passPhoMediumID(phoInd,true,true,false));
		


		bool isGenuine = false;
		bool isMisIDEle = false;
		bool isHadronicPhoton = false;
		bool isHadronicFake = false;

		findPhotonCategory(phoInd, tree, &isGenuine, &isMisIDEle, &isHadronicPhoton, &isHadronicFake);
		_photonIsGenuine.push_back(isGenuine);
		_photonIsMisIDEle.push_back(isMisIDEle);
		_photonIsHadronicPhoton.push_back(isHadronicPhoton);
		_photonIsHadronicFake.push_back(isHadronicFake);


		//		Make the decision on the photon category based on the leading photon that has passed the mediumID
		if (tree->phoIDbit_->at(phoInd)>>1&1){
			countMediumIDPho++;
			if (countMediumIDPho==1){
				_eventCategoryMediumID = isGenuine + 2 * isMisIDEle + 3*(isHadronicPhoton || isHadronicFake);
			}
		}

		//		Make the decision on the photon category based on the leading photon that has passed the tightID
		if (tree->phoIDbit_->at(phoInd)>>2&1){
			countTightIDPho++;
			if (countTightIDPho==1){
				_eventCategoryTightID = isGenuine + 2 * isMisIDEle + 3*(isHadronicPhoton || isHadronicFake);
			}
		}

		

		_dRPhotonJet.push_back(minDr(tree->phoEta_->at(phoInd),tree->phoPhi_->at(phoInd),evtPick->Jets,tree->jetEta_,tree->jetPhi_));
		_dRPhotonLepton.push_back(phoVector.DeltaR(lepVector));
		_MPhotonLepton.push_back((phoVector+lepVector).M());
		_AnglePhotonLepton.push_back(phoVector.Angle(lepVector.Vect()));


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
		_jetCSV2BJetTags.push_back(tree->jetCSV2BJetTags_->at(jetInd));
		_jetDeepCSVTags_b.push_back(tree->jetDeepCSVTags_b_->at(jetInd));
		_jetDeepCSVTags_bb.push_back(tree->jetDeepCSVTags_bb_->at(jetInd));

		if (!tree->isData_){
			_jetPartonID.push_back(tree->jetPartonID_->at(jetInd));
			_jetGenJetPt.push_back(tree->jetGenJetPt_->at(jetInd));
			_jetGenPartonID.push_back(tree->jetGenPartonID_->at(jetInd));
			_jetGenPt.push_back(tree->jetGenPt_->at(jetInd));
			_jetGenEta.push_back(tree->jetGenEta_->at(jetInd));
			_jetGenPhi.push_back(tree->jetGenPhi_->at(jetInd));
		}

	}	

	//Compute M3
	_M3 = -1.;
	double maxPt = -1;
	if (_nJet>2) {
		TLorentzVector jet1;
		TLorentzVector jet2;
		TLorentzVector jet3;
		for (int i_jet1 = 0; i_jet1 <_nJet-2; i_jet1++){
			int jetInd1 = evtPick->Jets.at(i_jet1);
			jet1.SetPtEtaPhiM(tree->jetPt_->at(jetInd1),tree->jetEta_->at(jetInd1),tree->jetPhi_->at(jetInd1),0.0);

			for (int i_jet2 = i_jet1+1; i_jet2 <_nJet-1; i_jet2++){
				int jetInd2 = evtPick->Jets.at(i_jet2);
				jet2.SetPtEtaPhiM(tree->jetPt_->at(jetInd2),tree->jetEta_->at(jetInd2),tree->jetPhi_->at(jetInd2),0.0);

				for (int i_jet3 = i_jet2+1; i_jet3 <_nJet; i_jet3++){
					int jetInd3 = evtPick->Jets.at(i_jet3);
					jet3.SetPtEtaPhiM(tree->jetPt_->at(jetInd3),tree->jetEta_->at(jetInd3),tree->jetPhi_->at(jetInd3),0.0);

					if ((jet1 + jet2 + jet3).Pt()>maxPt){
						_M3 = (jet1 + jet2 + jet3).M();
						maxPt=(jet1 + jet2 + jet3).Pt();
					}

				}
			}
		}
	}
	if (!tree->isData_){
		for (int i_mc = 0; i_mc <_nMC; i_mc++){
			_mcPt.push_back(tree->mcPt->at(i_mc));
			_mcPhi.push_back(tree->mcPhi->at(i_mc));
			_mcEta.push_back(tree->mcEta->at(i_mc));
			_mcMass.push_back(tree->mcMass->at(i_mc));
			_mcStatus.push_back(tree->mcStatus->at(i_mc));
			_mcPID.push_back(tree->mcPID->at(i_mc));
			_mcMomPID.push_back(tree->mcMomPID->at(i_mc));
			_mcGMomPID.push_back(tree->mcGMomPID->at(i_mc));
			_mcParentage.push_back(tree->mcParentage->at(i_mc));
		}
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
	return weight;

}

vector<float> makeAnalysisNtuple::getBtagSF(string sysType, BTagCalibrationReader reader, vector<float> &btagSF){

	// Saving weights w(0|n), w(1|n), w(2|n)
	vector<float> btagWeights;

	double weight0tag = 1.0; 		//w(0|n)
	double weight1tag = 0.0;		//w(1|n)

	double jetpt;
	double jeteta;
	int jetflavor;
	double SFb;
	double SFb2;


	for(std::vector<int>::const_iterator bjetInd = evtPick->bJets.begin(); bjetInd != evtPick->bJets.end(); bjetInd++){
		jetpt = tree->jetPt_->at(*bjetInd);
		jeteta = fabs(tree->jetEta_->at(*bjetInd));
		jetflavor = abs(tree->jetPartonID_->at(*bjetInd));
		
		if (jetflavor == 5) SFb = reader.eval_auto_bounds(sysType, BTagEntry::FLAV_B, jeteta, jetpt); 
		else if(jetflavor == 4) SFb = reader.eval_auto_bounds(sysType, BTagEntry::FLAV_C, jeteta, jetpt); 
		else {
			SFb = reader.eval_auto_bounds(sysType, BTagEntry::FLAV_UDSG, jeteta, jetpt); 
			//			if (sysType=="central") cout << tree->event_ << " " << *bjetInd << " " << jetpt << " " << jeteta << " " << jetflavor << " " << SFb<<endl;
		}

		// if 
		// if (SFb==0 && sysType=="central"){
		// 	cout << tree->event_ << " " << *bjetInd << " " << jetpt << " " << jeteta << " " << jetflavor << endl;
		// }
		btagSF.push_back(SFb);
	}

	if(evtPick->bJets.size() == 0) {
		std::cout << "No bJets" << std::endl;
		btagWeights.push_back(1.0);
		btagWeights.push_back(0.0);
		btagWeights.push_back(0.0);

		return btagWeights;

	} else if (evtPick->bJets.size() == 1) {
		btagWeights.push_back(1-btagSF.at(0));
		btagWeights.push_back(btagSF.at(0));
		btagWeights.push_back(0.0);
		
		return btagWeights;

	} else {

		// We are following the method 1SFc from the twiki
		// https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagSFMethods#1c_Event_reweighting_using_scale
		for (int i = 0; i < evtPick->bJets.size(); i++){
			SFb = btagSF.at(i);
			weight0tag *= 1.0 - SFb;
			double prod = SFb;
			for (int j = 0; j < evtPick->bJets.size(); j++){
				if (j==i) {continue;}
				prod *= (1.-btagSF.at(j));
			}
			weight1tag += prod;
		}
		btagWeights.push_back(weight0tag);
		btagWeights.push_back(weight1tag);
		btagWeights.push_back(1.0 - weight0tag - weight1tag);
		return btagWeights;
	}
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


vector<bool> makeAnalysisNtuple::passPhoMediumID(int phoInd){

	double pt = tree->phoEt_->at(phoInd);
    double eta = TMath::Abs(tree->phoSCEta_->at(phoInd));
    bool passMediumID = false;

	int region = 0;
	if( eta >= 1.0  ) region++;
	if( eta >= 1.479) region++;
	if( eta >= 2.0  ) region++;
	if( eta >= 2.2  ) region++;
	if( eta >= 2.3  ) region++;
	if( eta >= 2.4  ) region++;

	double rhoCorrPFChIso  = max(0.0, tree->phoPFChIso_->at(phoInd)  - photonEA[region][0] *tree->rho_);
	double rhoCorrPFNeuIso = max(0.0, tree->phoPFNeuIso_->at(phoInd) - photonEA[region][1] *tree->rho_);
	double rhoCorrPFPhoIso = max(0.0, tree->phoPFPhoIso_->at(phoInd) - photonEA[region][2] *tree->rho_);

	bool passHoverE = false;
	bool passSIEIE  = false;
	bool passChIso  = false;
	bool passNeuIso  = false;
	bool passPhoIso  = false;
	
	
    if (eta < 1.47){
		if (tree->phoHoverE_->at(phoInd) < 0.0396 )               passHoverE = true;
		if (tree->phoSigmaIEtaIEtaFull5x5_->at(phoInd) < 0.01022) passSIEIE  = true;
		if (rhoCorrPFChIso  < 0.441  )                            passChIso  = true;
		if (rhoCorrPFNeuIso < 2.725+0.0148*pt+0.000017*pt*pt)     passNeuIso = true;
		if (rhoCorrPFPhoIso < 2.571+0.0047*pt)                    passPhoIso = true;
    } else {
		if (tree->phoHoverE_->at(phoInd) < 0.0219 )                passHoverE = true;
		if (tree->phoSigmaIEtaIEtaFull5x5_->at(phoInd)  < 0.03001) passSIEIE  = true;
		if (rhoCorrPFChIso < 0.442) 							   passChIso  = true;
		if (rhoCorrPFNeuIso < 1.715+0.0163*pt+0.000014*pt*pt)	   passNeuIso = true;
		if (rhoCorrPFPhoIso < 3.863+0.0034*pt)					   passPhoIso = true;
	}

	passMediumID = passHoverE && passSIEIE && passChIso && passNeuIso && passPhoIso;

	vector<bool> cuts;
	cuts.push_back(passMediumID);
	cuts.push_back(passHoverE);
	cuts.push_back(passSIEIE);
	cuts.push_back(passChIso);
	cuts.push_back(passNeuIso);
	cuts.push_back(passPhoIso);

	return cuts;

    // if (eta < 1.47){
	// 	if ((!cutHoverE || tree->phoHoverE_->at(phoInd)                < 0.0396  ) &&
	// 		(!cutSIEIE  || tree->phoSigmaIEtaIEtaFull5x5_->at(phoInd)  < 0.01022 ) &&
	// 		(!cutIso    || (rhoCorrPFChIso                              < 0.441 &&
	// 						rhoCorrPFNeuIso                             < 2.725+0.0148*pt+0.000017*pt*pt &&
	// 						rhoCorrPFPhoIso                             < 2.571+0.0047*pt))){
	// 		passMediumID = true;
	// 	}
    // } else {
	// 	if ((!cutHoverE || tree->phoHoverE_->at(phoInd)                < 0.0219  ) &&
	// 		(!cutSIEIE  || tree->phoSigmaIEtaIEtaFull5x5_->at(phoInd)  < 0.03001 ) &&
	// 		(!cutIso    || (rhoCorrPFChIso                              < 0.442 &&
	// 						rhoCorrPFNeuIso                             < 1.715+0.0163*pt+0.000014*pt*pt &&
	// 						rhoCorrPFPhoIso                             < 3.863+0.0034*pt))){
	// 		passMediumID = true;
	// 	}
    // }
    // return passMediumID;
}


vector<bool> makeAnalysisNtuple::passPhoTightID(int phoInd){

	double pt = tree->phoEt_->at(phoInd);
    double eta = TMath::Abs(tree->phoSCEta_->at(phoInd));
    bool passTightID = false;

	int region = 0;
	if( eta >= 1.0  ) region++;
	if( eta >= 1.479) region++;
	if( eta >= 2.0  ) region++;
	if( eta >= 2.2  ) region++;
	if( eta >= 2.3  ) region++;
	if( eta >= 2.4  ) region++;

	double rhoCorrPFChIso  = max(0.0, tree->phoPFChIso_->at(phoInd)  - photonEA[region][0] *tree->rho_);
	double rhoCorrPFNeuIso = max(0.0, tree->phoPFNeuIso_->at(phoInd) - photonEA[region][1] *tree->rho_);
	double rhoCorrPFPhoIso = max(0.0, tree->phoPFPhoIso_->at(phoInd) - photonEA[region][2] *tree->rho_);

	bool passHoverE = false;
	bool passSIEIE  = false;
	bool passChIso  = false;
	bool passNeuIso  = false;
	bool passPhoIso  = false;
	
	
    if (eta < 1.47){
		if (tree->phoHoverE_->at(phoInd) < 0.0269 )               passHoverE = true;
		if (tree->phoSigmaIEtaIEtaFull5x5_->at(phoInd) < 0.00994) passSIEIE  = true;
		if (rhoCorrPFChIso  < 0.202  )                            passChIso  = true;
		if (rhoCorrPFNeuIso < 0.264+0.0148*pt+0.000017*pt*pt)     passNeuIso = true;
		if (rhoCorrPFPhoIso < 2.362+0.0047*pt)                    passPhoIso = true;
    } else {
		if (tree->phoHoverE_->at(phoInd) < 0.0213 )                passHoverE = true;
		if (tree->phoSigmaIEtaIEtaFull5x5_->at(phoInd)  < 0.03000) passSIEIE  = true;
		if (rhoCorrPFChIso < 0.034) 							   passChIso  = true;
		if (rhoCorrPFNeuIso < 0.586+0.0163*pt+0.000014*pt*pt)	   passNeuIso = true;
		if (rhoCorrPFPhoIso < 2.617+0.0034*pt)					   passPhoIso = true;
	}

	passTightID = passHoverE && passSIEIE && passChIso && passNeuIso && passPhoIso;

	vector<bool> cuts;
	cuts.push_back(passTightID);
	cuts.push_back(passHoverE);
	cuts.push_back(passSIEIE);
	cuts.push_back(passChIso);
	cuts.push_back(passNeuIso);
	cuts.push_back(passPhoIso);

	return cuts;

}


// void makeAnalysisNtuple::findPhotonCategory(int phoInd, EventTree* tree, bool* genuine, bool *misIDele, bool *hadronicphoton, bool *hadronicfake){

// 	*genuine        = false;
// 	*misIDele       = false;
// 	*hadronicphoton = false;
// 	*hadronicfake   = false;

// 	int mcPhotonInd = -1;
// 	int mcEleInd = -1;

// 	for(int mcInd=0; mcInd<tree->nMC_; ++mcInd){

// 		// crude matching to get candidates
// 		bool etetamatch = (dR(tree->mcEta->at(mcInd),tree->mcPhi->at(mcInd),tree->phoEta_->at(phoInd),tree->phoPhi_->at(phoInd)) < 0.3 && 
// 						   (fabs(tree->phoEt_->at(phoInd) - tree->mcPt->at(mcInd)) / tree->mcPt->at(mcInd)) < 1.0);
		
// 		if( etetamatch && mcPhotonInd < 0 && tree->mcPID->at(mcInd) == 22)
// 			if (abs(tree->mcMomPID->at(mcInd)) < 25){
// 				mcPhotonInd = mcInd; 
// 			}
// 		if( etetamatch && mcEleInd < 0 && abs(tree->mcPID->at(mcInd)) == 11 )
// 			mcEleInd = mcInd;
// 	}
// 	// cout << "----------" << endl;
// 	// cout << mcPhotonInd << " " << mcEleInd << endl;

// 	if(mcPhotonInd >= 0){
// 		*genuine=true;
// 	} else{
// 		if(mcEleInd >= 0 && isGoodElectron(tree, mcEleInd, phoInd)){
// 			*misIDele = true;
// 		} else {
// 			*hadronicfake = true;
// 		}
// 	}

// 	// cout << genuine << misIDele << hadronicphoton << hadronicfake << endl;
// }

void makeAnalysisNtuple::findPhotonCategory(int phoInd, EventTree* tree, bool* genuine, bool *misIDele, bool *hadronicphoton, bool *hadronicfake){

	*genuine        = false;
	*misIDele       = false;
	*hadronicphoton = false;
	*hadronicfake   = false;

	int mcPhotonInd = -1;
	int mcEleInd = -1;

	for(int mcInd=0; mcInd<tree->nMC_; ++mcInd){
		// crude matching to get candidates
		bool etetamatch = (dR(tree->mcEta->at(mcInd),tree->mcPhi->at(mcInd),tree->phoEta_->at(phoInd),tree->phoPhi_->at(phoInd)) < 0.2 && 
						   (fabs(tree->phoEt_->at(phoInd) - tree->mcPt->at(mcInd)) / tree->mcPt->at(mcInd)) < 1.0);
		
		if( etetamatch && mcPhotonInd < 0 && tree->mcPID->at(mcInd) == 22)
			mcPhotonInd = mcInd; 
		if( etetamatch && mcEleInd < 0 && abs(tree->mcPID->at(mcInd)) == 11 )
			mcEleInd = mcInd;
	}
	// cout << "----------" << endl;
	// cout << mcPhotonInd << " " << mcEleInd << endl;

	if(mcPhotonInd >= 0){
		if(isSignalPhoton(tree,mcPhotonInd,phoInd)){
			*genuine=true;
		} else {
			*hadronicphoton = true;
		}
	} else{
		if(mcEleInd >= 0 && isGoodElectron(tree, mcEleInd, phoInd)){
			*misIDele = true;
		} else {
			*hadronicfake = true;
		}
	}

	// cout << genuine << misIDele << hadronicphoton << hadronicfake << endl;
}

//This is defined in OverlapRemoval.cpp
double minGenDr(int myInd, const EventTree* tree);

bool makeAnalysisNtuple::isSignalPhoton(EventTree* tree, int mcInd, int recoPhoInd){
    bool parentagePass = tree->mcParentage->at(mcInd)==2 || tree->mcParentage->at(mcInd)==10 || tree->mcParentage->at(mcInd)==26;
    double dptpt = (tree->phoEt_->at(recoPhoInd) - tree->mcPt->at(mcInd)) / tree->mcPt->at(mcInd);
    bool dptptPass = dptpt < 0.1;
    bool drotherPass = minGenDr(mcInd, tree) > 0.2;
    bool detarecogenPass = fabs(tree->phoEta_->at(recoPhoInd) - tree->mcEta->at(mcInd)) < 0.005;
    bool drrecogenPass = dR(tree->mcEta->at(mcInd),tree->mcPhi->at(mcInd),tree->phoEta_->at(recoPhoInd),tree->phoPhi_->at(recoPhoInd)) < 0.01;
	// cout << "-----------------------------------" << endl;
	// cout << "eventnum "<<tree->event_<<endl;
	// cout << "recoPhoInd " << recoPhoInd << " mcInd " << mcInd << endl;
	// cout << "parentagePass " << parentagePass <<endl;
	// cout << "dptpt " << dptpt <<endl;
	// cout << "dptptPass " << dptptPass <<endl;
	// cout << "drotherPass " << drotherPass <<endl;
	// cout << "detarecogenPass " << detarecogenPass << "     " << tree->phoEta_->at(recoPhoInd) << "  " << tree->mcEta->at(mcInd) <<endl;
	// cout << "drrecogenPass " << drrecogenPass << tree->mcEta->at(mcInd)<< "  " <<tree->mcPhi->at(mcInd)<< "  " <<tree->phoEta_->at(recoPhoInd)<< "  " <<tree->phoPhi_->at(recoPhoInd) << endl;
    if(parentagePass && dptptPass && drotherPass && detarecogenPass && drrecogenPass) return true;
    else return false;
}

bool makeAnalysisNtuple::isGoodElectron(EventTree* tree, int mcInd, int recoPhoInd){
    bool parentagePass = tree->mcParentage->at(mcInd)==10;
    double dptpt = (tree->phoEt_->at(recoPhoInd) - tree->mcPt->at(mcInd)) / tree->mcPt->at(mcInd);
    bool dptptPass = dptpt < 0.1;
    bool drotherPass = minGenDr(mcInd, tree) > 0.2;
    bool detarecogenPass = fabs(tree->phoEta_->at(recoPhoInd) - tree->mcEta->at(mcInd)) < 0.005;
    bool drrecogenPass = dR(tree->mcEta->at(mcInd),tree->mcPhi->at(mcInd),tree->phoEta_->at(recoPhoInd),tree->phoPhi_->at(recoPhoInd)) < 0.04;
    if(parentagePass && dptptPass && drotherPass && detarecogenPass && drrecogenPass) return true;
    else return false;
}

int makeAnalysisNtuple::minDrIndex(double myEta, double myPhi, std::vector<int> Inds, std::vector<float> *etas, std::vector<float> *phis){
	double mindr = 999.0;
	double dr;
	int bestInd = -1;
	for( std::vector<int>::iterator it = Inds.begin(); it != Inds.end(); ++it){
		dr = dR(myEta, myPhi, etas->at(*it), phis->at(*it));
		if( mindr > dr ) {
			mindr = dr;
			bestInd = *it;
		}
	}
	return bestInd;
}

double makeAnalysisNtuple::minDr(double myEta, double myPhi, std::vector<int> Inds, std::vector<float> *etas, std::vector<float> *phis){
	int ind = minDrIndex(myEta, myPhi, Inds, etas, phis);
	if(ind>=0) return dR(myEta, myPhi, etas->at(ind), phis->at(ind));
	else return 999.0;
}



#endif

int main(int ac, char** av){
  if(ac != 4){
    std::cout << "usage: ./makeAnalysisNtuple sampleName outputFileDir inputFile[s]" << std::endl;
    return -1;
  }

  makeAnalysisNtuple(ac, av);


  return 0;
}
