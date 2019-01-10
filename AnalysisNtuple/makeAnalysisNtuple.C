#define makeAnalysisNtuple_cxx
#include "makeAnalysisNtuple.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <iostream>
#include <ctime>
#include "TRandom3.h"
#include"PUReweight.h"
#include "METzCalculator.h"
#include "TopEventCombinatorics.h"
#include "JetResolutions.h"
#include"JEC/JECvariation.h"
//#include"OverlapRemove.cpp"
#include <cmath>
#include "elemuSF.h"

std::string PUfilename = "PileupHists/Data_2016BCDGH_Pileup.root";
std::string PUfilename_up = "PileupHists/Data_2016BCDGH_Pileup_scaledUp.root";
std::string PUfilename_down = "PileupHists/Data_2016BCDGH_Pileup_scaledDown.root";

int jecvar012_g = 1; // 0:down, 1:norm, 2:up
int jervar012_g = 1; // 0:down, 1:norm, 2:up
int phosmear012_g = 1; // 0:down, 1:norm, 2:up 
int musmear012_g = 1; // 0:down, 1:norm, 2: up
int elesmear012_g = 1; // 0:down, 1:norm, 2: up
int phoscale012_g = 1;
int elescale012_g = 1;
#include "BTagCalibrationStandalone.h"

bool overlapRemovalTT(EventTree* tree);
bool overlapRemovalWZ(EventTree* tree);
//bool overlapRemoval_Tchannel(EventTree* tree);
double getJetResolution(double, double, double);

bool dileptonsample;
std::clock_t startClock;
double duration;

#ifdef makeAnalysisNtuple_cxx
makeAnalysisNtuple::makeAnalysisNtuple(int ac, char** av)
{
    startClock = clock();
    tree = new EventTree(ac-3, false, av+3);

    sampleType = av[1];
    systematicType = "";
    cout << sampleType << endl;
    
    isSystematicRun = false;
    
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
    selector->veto_jet_pho_dR = -1.; //remove photons which have a jet close to them (after having removed jets too close to photon from above cut)
    
    
    //	selector->jet_Pt_cut = 40.;
    evtPick->Njet_ge = 2;	
    evtPick->NBjet_ge = 0;	
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
    
    getGenScaleWeights = false;
    if( sampleType.substr(0,5)=="TTbar" || sampleType.substr(0,7)=="TTGamma"){
	getGenScaleWeights = true;
    }
    
    bool doOverlapRemoval = false;
    bool doOverlapRemoval_WZ = false;	
    bool doOverlapRemoval_Tchannel = false;	
    
    bool invertOverlap = false;
    
    bool skipOverlap = false;
    applypdfweight = false;
    applyqsquare  = false;
    if( sampleType == "TTbarPowheg" || sampleType=="isr_up_TTbarPowheg" || sampleType=="fsr_up_TTbarPowheg"|| sampleType=="isr_down_TTbarPowheg"|| sampleType=="fsr_down_TTbarPowheg"|| sampleType == "TTbarPowheg1" || sampleType == "TTbarPowheg2" || sampleType == "TTbarPowheg3" || sampleType == "TTbarPowheg4" || sampleType == "TTbarMCatNLO" || sampleType == "TTbarMadgraph_SingleLeptFromT" || sampleType == "TTbarMadgraph_SingleLeptFromTbar" || sampleType == "TTbarMadgraph_Dilepton" || sampleType == "TTbarMadgraph" ) doOverlapRemoval = true;
    
    if( sampleType == "W1jets" || sampleType == "W2jets" ||  sampleType == "W3jets" || sampleType == "W4jets" || sampleType=="DYjetsM10to50" || sampleType=="DYjetsM50" || sampleType=="DYjetsM10to50_MLM" || sampleType=="DYjetsM50_MLM") doOverlapRemoval_WZ = true;
    
    if( sampleType == "ST_t-channel" || sampleType == "ST_tbar-channel") doOverlapRemoval_Tchannel = true;
    if(doOverlapRemoval || doOverlapRemoval_WZ || doOverlapRemoval_Tchannel) std::cout << "########## Will apply overlap removal ###########" << std::endl;
    if( sampleType == "TTbarPowheg" || sampleType == "TTbarPowheg1" || sampleType == "TTbarPowheg2" || sampleType == "TTbarPowheg3" || sampleType == "TTbarPowheg4" || sampleType=="TTGamma_Dilepton" || sampleType == "TTGamma_SingleLeptFromT" || sampleType == "TTGamma_SingleLeptFromTbar" || sampleType == "TTGamma_Hadronic" || sampleType == "TTGJets"){
	applypdfweight = true; 	
	applyqsquare = true;
    }
    
    if (applypdfweight||applyqsquare)  std::cout<<"###### Will apply pdfWeights and Q2 weights ######"<< std::endl;
    
    dileptonsample = false;
    string JECsystLevel = "";
    if( systematicType.substr(0,3)=="JEC" ){
	int pos = systematicType.find("_");
	JECsystLevel = systematicType.substr(3,pos-3);
	if (std::end(allowedJECUncertainties) == std::find(std::begin(allowedJECUncertainties), std::end(allowedJECUncertainties), JECsystLevel)){
	    cout << "The JEC systematic source, " << JECsystLevel << ", is not in the list of allowed sources (found in JEC/UncertaintySourcesList.h" << endl;
	    cout << "Exiting" << endl;
	    return;
	}
	if (systematicType.substr(pos+1,2)=="up"){ jecvar012_g = 2; }
	if (systematicType.substr(pos+1,2)=="do"){ jecvar012_g = 0; }
	// evtPick->Njet_ge = 3;	
	// evtPick->NBjet_ge = 1;	
	isSystematicRun = true;
    }
    
    bool isTTGamma = false;
    
    size_t ttgamma_pos = sampleType.find("TTGamma");
    if (ttgamma_pos != std::string::npos){
	isTTGamma = true;
    }
    
    // if( systematicType=="JEC_up")       {jecvar012_g = 2; selector->JECsystLevel=2;}
    // if( systematicType=="JEC_down")     {jecvar012_g = 0; selector->JECsystLevel=0;}
    if( systematicType=="JER_up")       {jervar012_g = 2; selector->JERsystLevel=2; isSystematicRun = true;}
    if( systematicType=="JER_down")     {jervar012_g = 0; selector->JERsystLevel=0; isSystematicRun = true;}
    if(systematicType=="phosmear_down") {phosmear012_g=0;selector->phosmearLevel=0; isSystematicRun = true;}
    if(systematicType=="phosmear_up") {phosmear012_g=2;selector->phosmearLevel=2; isSystematicRun = true;}
    if(systematicType=="elesmear_down") {elesmear012_g=0;selector->elesmearLevel=0; isSystematicRun = true;}
    if(systematicType=="elesmear_up") {elesmear012_g=2;selector->elesmearLevel=2; isSystematicRun = true;}
    if(systematicType=="phoscale_down") {phoscale012_g=0;selector->phoscaleLevel=0; isSystematicRun = true;} 
    if(systematicType=="phoscale_up") {phoscale012_g=2;selector->phoscaleLevel=2; isSystematicRun = true;}
    if(systematicType=="elescale_down") {elescale012_g=0;selector->elescaleLevel=0; isSystematicRun = true;}
    if(systematicType=="elescale_up") {elescale012_g=2;  selector->elescaleLevel=2; isSystematicRun = true;}

    // if( systematicType=="pho_up")       {phosmear012_g = 2;}
    // if( systematicType=="pho_down")     {phosmear012_g = 0;}
    if( systematicType=="musmear_up")   {musmear012_g = 2; isSystematicRun = true;}
    if( systematicType=="musmear_down") {musmear012_g = 0; isSystematicRun = true;}
    //	if( systematicType=="elesmear_up")  {elesmear012_g = 2;}
    //	if( systematicType=="elesmear_down"){elesmear012_g = 0;}
    if( systematicType=="Dilep")     {dileptonsample =true; evtPick->Nmu_eq=2; evtPick->Nele_eq=2;}
    if( systematicType=="QCDcr")       {selector->QCDselect = true; evtPick->ZeroBExclusive=true;}
    std::cout << "Dilepton Sample :" << dileptonsample << std::endl;
    std::cout << "JEC: " << jecvar012_g << "  JER: " << jervar012_g << " eleScale "<< elescale012_g << " phoScale" << phoscale012_g << "   ";
    std::cout << "  PhoSmear: " << phosmear012_g << "  muSmear: " << musmear012_g << "  eleSmear: " << elesmear012_g << endl;

    if (isSystematicRun){
	std::cout << "  Systematic Run : Dropping genMC variables from tree" << endl;
    }
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

    PUReweight* PUweighter = new PUReweight(ac-3, av+3, PUfilename);
    PUReweight* PUweighterUp = new PUReweight(ac-3, av+3, PUfilename_up);
    PUReweight* PUweighterDown = new PUReweight(ac-3, av+3, PUfilename_down);
    tree->GetEntry(0);
        
    isMC = tree->nGenPart_>0;

    std::cout << "isMC: " << isMC << endl;

    tree->isData_ = !isMC;

    InitBranches();

    JECvariation* jecvar;
    if (isMC && jecvar012_g!=1) {
	//		jecvar = new JECvariation("./jecFiles/Summer16_23Sep2016V4", isMC, "Total");//SubTotalAbsolute");
	cout << "Applying JEC uncertainty variations : " << JECsystLevel << endl;
	jecvar = new JECvariation("./jecFiles/Summer16_23Sep2016V4", isMC, JECsystLevel);//SubTotalAbsolute");
    }

    _lumiWeight = getEvtWeight(sampleType);
    _lumiWeightAlt = _lumiWeight;

    if (isTTGamma){
	_lumiWeightAlt = getEvtWeight("alt_"+sampleType);
    }


    _PUweight       = 1.;
    _muEffWeight    = 1.;
    _muEffWeight_Do = 1.;
    _muEffWeight_Up = 1.;
    _eleEffWeight    = 1.;
    _eleEffWeight_Up = 1.;
    _eleEffWeight_Do = 1.;

    Long64_t nEntr = tree->GetEntries();

    bool saveAllEntries = false;

    if (sampleType=="Test") nEntr = 10000;
    if (sampleType=="TestAll") {
	nEntr = 1000;
	saveAllEntries = true;
    }
    //nEntr = 10000;

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
    int count_overlapTchannel=0;
    int count_overlapVJets=0;
    int count_overlapTTbar=0;

    for(Long64_t entry=0; entry<nEntr; entry++){
	if(entry%dumpFreq == 0){
	    duration =  ( clock() - startClock ) / (double) CLOCKS_PER_SEC;
	    std::cout << "processing entry " << entry << " out of " << nEntr << " : " << duration << " seconds since last progress" << std::endl;
	    startClock = clock();

	}
	//  cout << entry << endl;
	tree->GetEntry(entry);

	if( isMC && doOverlapRemoval){
	    if (!invertOverlap){
		if (overlapRemovalTT(tree)){	
		    count_overlapTTbar++;			
		    //	cout << "removing event " << entry << endl;
		    continue;
		}
	    } else {
		if (!overlapRemovalTT(tree)){	
		    count_overlapTTbar++;			
		    //	cout << "removing event " << entry << endl;
		    continue;
		}
	    }
	}
	if( isMC && doOverlapRemoval_WZ){
	    if (overlapRemovalWZ(tree)){
		count_overlapVJets++;
		continue;
	    }
	}
	// if( isMC && doOverlapRemoval_Tchannel){
	// 	if (overlapRemoval_Tchannel(tree)){
	// 		count_overlapTchannel++;
	// 		continue;
	// 	}
	// }

	// //		Apply systematics shifts where needed
	if( isMC ){
	    if (jecvar012_g != 1){
		jecvar->applyJEC(tree, jecvar012_g); // 0:down, 1:norm, 2:up
	    }
	}

	
				

	//		selector->process_objects(tree);
	selector->clear_vectors();

	evtPick->process_event(tree, selector, _PUweight);

	//    cout << "HERE" << endl;
	if ( evtPick->passPresel_ele || evtPick->passPresel_mu || saveAllEntries) {

	    InitVariables();
	    FillEvent();

	    if(isMC) {
		_PUweight    = PUweighter->getWeight(tree->nPUTrue_);
		_PUweight_Up = PUweighterUp->getWeight(tree->nPUTrue_);
		_PUweight_Do = PUweighterDown->getWeight(tree->nPUTrue_);

		_btagWeight      = getBtagSF("central", reader, _btagSF);
		_btagWeight_b_Up = getBtagSF("b_up",    reader, _btagSF_b_Up);
		_btagWeight_b_Do = getBtagSF("b_down",  reader, _btagSF_b_Do);				
		_btagWeight_l_Up = getBtagSF("l_up",    reader, _btagSF_l_Up);
		_btagWeight_l_Do = getBtagSF("l_down",  reader, _btagSF_l_Do);				
				
		if (evtPick->passPresel_mu) {
		    int muInd_ = selector->Muons.at(0);
		    _muEffWeight    = getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],1);
		    _muEffWeight_Do = getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],0);
		    _muEffWeight_Up = getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],2);
		    _eleEffWeight    = 1.;
		    _eleEffWeight_Up = 1.;
		    _eleEffWeight_Do = 1.;
		}
		if (evtPick->passPresel_ele) {
		    int eleInd_ = selector->Electrons.at(0);
		    _muEffWeight    = 1.;
		    _muEffWeight_Do = 1.;
		    _muEffWeight_Up = 1.;
		    _eleEffWeight    = getEleSF(tree->elePt_[eleInd_],tree->eleEta_[eleInd_] + tree->eleDeltaEtaSC_[eleInd_],1);
		    _eleEffWeight_Do = getEleSF(tree->elePt_[eleInd_],tree->eleEta_[eleInd_] + tree->eleDeltaEtaSC_[eleInd_],0);
		    _eleEffWeight_Up = getEleSF(tree->elePt_[eleInd_],tree->eleEta_[eleInd_] + tree->eleDeltaEtaSC_[eleInd_],2);
		    //               std::cout<<"done with Ele scaling"<<std::endl;
                                     
		}

	    }

	    if (!isMC){
		if (selector->bJets.size() == 0){
		    _btagWeight.push_back(1.0);
		    _btagWeight.push_back(0.0);
		    _btagWeight.push_back(0.0);
		}				
		if (selector->bJets.size() == 1){
		    _btagWeight.push_back(0.0);
		    _btagWeight.push_back(1.0);
		    _btagWeight.push_back(0.0);
		}				
		if (selector->bJets.size() >= 2){
		    _btagWeight.push_back(0.0);
		    _btagWeight.push_back(0.0);
		    _btagWeight.push_back(1.0);
		}				
	    }
	    outputTree->Fill();
	    //		std::cout<<"done with filling"<<std::endl;
	}
    }
    if (doOverlapRemoval){
	std::cout << "Total number of events removed from TTbar:"<< count_overlapTTbar <<std::endl;
    }
    if(doOverlapRemoval_WZ){
	std::cout << "Total number of events removed from W/ZJets:"<< count_overlapVJets <<std::endl;
    }
    if(doOverlapRemoval_Tchannel){
	std::cout << "Total number of events removed from t-channel:"<< count_overlapTchannel <<std::endl;
    }

    outputFile->cd();

    outputTree->Write();

    outputFile->Close();

}


void makeAnalysisNtuple::FillEvent()
{

    _run             = tree->run_;
    _event           = tree->event_;
    _lumis           = tree->lumis_;
    _isData	         = !isMC;
    _nVtx		 = tree->nVtx_;
    _nGoodVtx	 = tree->nGoodVtx_;
    // _isPVGood	 = tree->isPVGood_;
    // _rho		 = tree->rho_;
    
    _evtWeight       = _lumiWeight *  ((tree->genWeight_ >= 0) ? 1 : -1);  //event weight needs to be positive or negative depending on sign of genWeight (to account for mc@nlo negative weights)
    _evtWeightAlt    = _lumiWeightAlt *  ((tree->genWeight_ >= 0) ? 1 : -1);  //event weight needs to be positive or negative depending on sign of genWeight (to account for mc@nlo negative weights)

    if (_isData) {
	_evtWeight= 1.;
	_evtWeightAlt= 1.;
    }

    _genMET		     = tree->GenMET_pt_;
    _pfMET		     = tree->MET_pt_;
    _pfMETPhi    	     = tree->MET_phi_;

    _nPho		     = selector->Photons.size();
    _nLoosePho	             = selector->LoosePhotons.size();
    _nEle		     = selector->Electrons.size();
    _nEleLoose               = selector->ElectronsLoose.size();
    _nMu		     = selector->Muons.size();
    _nMuLoose                = selector->MuonsLoose.size();

    _nJet            = selector->Jets.size();
    _nfwdJet         = selector->FwdJets.size();
    _nBJet           = selector->bJets.size();

    _nGenPart        = tree->nGenPart_;

    //TODO
    //        _pdfWeight       = tree->pdfWeight_;	


    double ht = 0.0;
    ht += tree->MET_pt_;

    for( int i_jet = 0; i_jet < _nJet; i_jet++)
	ht += tree->jetPt_[i_jet];
	
    _HT = ht; 


    for (int i_ele = 0; i_ele <_nEle; i_ele++){
	int eleInd = selector->Electrons.at(i_ele);
	_elePt.push_back(tree->elePt_[eleInd]);
	_elePhi.push_back(tree->elePhi_[eleInd]);
	_eleSCEta.push_back(tree->eleEta_[eleInd] + tree->eleDeltaEtaSC_[eleInd]);

	_elePFRelIso.push_back(tree->elePFRelIso_[eleInd]);

	lepVector.SetPtEtaPhiM(tree->elePt_[eleInd],
			       tree->eleEta_[eleInd] + tree->eleDeltaEtaSC_[eleInd],
			       tree->elePhi_[eleInd],
			       tree->eleMass_[eleInd]);
    }


    for (int i_mu = 0; i_mu <_nMu; i_mu++){
	int muInd = selector->Muons.at(i_mu);
	_muPt.push_back(tree->muPt_[muInd]);
	_muPhi.push_back(tree->muPhi_[muInd]);
	_muEta.push_back(tree->muEta_[muInd]);
	_muPFRelIso.push_back(tree->muPFRelIso_[muInd]);

	lepVector.SetPtEtaPhiM(tree->muPt_[muInd],
			       tree->muEta_[muInd],
			       tree->muPhi_[muInd],
			       tree->muMass_[muInd]);
    }
	
    if (dileptonsample){
	if (_nMu==2) {

	    int muInd1 = selector->Muons.at(0);
	    int muInd2 = selector->Muons.at(1);

	    lepVector.SetPtEtaPhiM(tree->muPt_[muInd1],
				   tree->muEta_[muInd1],
				   tree->muPhi_[muInd1],
				   tree->muMass_[muInd1]);
	    lepVector2.SetPtEtaPhiM(tree->muPt_[muInd2],
				    tree->muEta_[muInd2],
				    tree->muPhi_[muInd2],
				    tree->muMass_[muInd2]);	

	    _DilepMass = (lepVector+lepVector2).M();
	    _DilepDelR = lepVector.DeltaR(lepVector2);
	    
	}
	
	
	if (_nEle==2){
	    int eleInd1 = selector->Electrons.at(0);
	    int eleInd2 = selector->Electrons.at(1);
	    
	    lepVector.SetPtEtaPhiM(tree->elePt_[eleInd1],
				   tree->eleEta_[eleInd1],
				   tree->elePhi_[eleInd1],
				   tree->eleMass_[eleInd1]);
	    lepVector2.SetPtEtaPhiM(tree->elePt_[eleInd2],
				    tree->eleEta_[eleInd2],
				    tree->elePhi_[eleInd2],
				    tree->eleMass_[eleInd2]);
	    
	    _DilepMass = (lepVector+lepVector2).M();
	    _DilepDelR = lepVector.DeltaR(lepVector2);
	    
	}
    }
    
    //dipho Mass
    if (_nPho>1){
	//	std::cout<<_nPho<<std::endl;
	int phoInd1 = selector->Photons.at(0);
	int phoInd2 = selector->Photons.at(1);

	phoVector1.SetPtEtaPhiM(tree->phoEt_[phoInd1],
				tree->phoEta_[phoInd1],
				tree->phoPhi_[phoInd1],
				0.0);
	phoVector2.SetPtEtaPhiM(tree->phoEt_[phoInd2],
				tree->phoEta_[phoInd2],
				tree->phoPhi_[phoInd2],
				0.0);
	
	
	_DiphoMass = (phoVector1+phoVector2).M();
    }
	

    _passPresel_Ele  = evtPick->passPresel_ele;
    _passPresel_Mu   = evtPick->passPresel_mu;
    _passAll_Ele     = evtPick->passAll_ele;
    _passAll_Mu      = evtPick->passAll_mu;
    

    _nPhoBarrel=0.;
    _nPhoEndcap=0.;

    int parentPID = -1;

    for (int i_pho = 0; i_pho <_nPho; i_pho++){
	int phoInd = selector->Photons.at(i_pho);

	phoVector.SetPtEtaPhiM(tree->phoEt_[phoInd],
			       tree->phoEta_[phoInd],
			       tree->phoPhi_[phoInd],
			       0.0);

	_phoEt.push_back(tree->phoEt_[phoInd]);
	_phoEta.push_back(tree->phoEta_[phoInd]);
	_phoPhi.push_back(tree->phoPhi_[phoInd]);
	//	_phoSCEta.push_back(tree->phoEta_[phoInd]);

	_phoR9.push_back(tree->phoR9_[phoInd]);		
	_phoSIEIE.push_back(tree->phoSIEIE_[phoInd]);
	_phoHoverE.push_back(tree->phoHoverE_[phoInd]);

	_phoIsBarrel.push_back( abs(tree->phoEta_[phoInd])<1.47 );

	_phoPFRelIso.push_back( tree->phoPFRelIso_[phoInd]);
	_phoPFRelChIso.push_back( tree->phoPFRelChIso_[phoInd]);
	_phoPFChIso.push_back( tree->phoPFRelChIso_[phoInd] * tree->phoEt_[phoInd]);

	if (abs(tree->phoEta_[phoInd])<1.47){
	    _nPhoBarrel++;
	}else{
	    _nPhoEndcap++;
	} 

	if (tree->isData_){
	    _phoEffWeight.push_back(1.);
	    _phoEffWeight_Do.push_back(1.);
	    _phoEffWeight_Up.push_back(1.);
	} else {
	    _phoEffWeight.push_back(getPhoSF(tree->phoEt_[phoInd],tree->phoEta_[phoInd],1));
	    _phoEffWeight_Do.push_back(getPhoSF(tree->phoEt_[phoInd],tree->phoEta_[phoInd],0));
	    _phoEffWeight_Up.push_back(getPhoSF(tree->phoEt_[phoInd],tree->phoEta_[phoInd],2));
	}
	
	_phoTightID.push_back(tree->phoIDcutbased_[phoInd]>=3);
	_phoMediumID.push_back(tree->phoIDcutbased_[phoInd]>=2);

	_phoMassLepGamma.push_back( (phoVector+lepVector).M() );


	bool isGenuine = false;
	bool isMisIDEle = false;
	bool isHadronicPhoton = false;
	bool isHadronicFake = false;
	int phoGenMatchInd = -1.;

	// TODO needs to be reimplemented with NANOAOD
	if (!tree->isData_){
	    phoGenMatchInd = tree->phoGenPartIdx_[phoInd];

	    _phoGenMatchInd.push_back(phoGenMatchInd);

	    findPhotonCategory(phoGenMatchInd, tree, &isGenuine, &isMisIDEle, &isHadronicPhoton, &isHadronicFake);
	    _photonIsGenuine.push_back(isGenuine);
	    _photonIsMisIDEle.push_back(isMisIDEle);
	    _photonIsHadronicPhoton.push_back(isHadronicPhoton);
	    _photonIsHadronicFake.push_back(isHadronicFake);
	}

	_dRPhotonLepton.push_back(phoVector.DeltaR(lepVector));
	_MPhotonLepton.push_back((phoVector+lepVector).M());
	_AnglePhotonLepton.push_back(phoVector.Angle(lepVector.Vect())); 
	
    }


    for (int i_pho = 0; i_pho <_nLoosePho; i_pho++){
	int phoInd = selector->LoosePhotons.at(i_pho);
	phoVector.SetPtEtaPhiM(tree->phoEt_[phoInd],
			       tree->phoEta_[phoInd],
			       tree->phoPhi_[phoInd],
			       0.0);
	
	_loosePhoEt.push_back(tree->phoEt_[phoInd]);
	_loosePhoEta.push_back(tree->phoEta_[phoInd]);
	_loosePhoPhi.push_back(tree->phoPhi_[phoInd]);
	_loosePhoIsBarrel.push_back( abs(tree->phoEta_[phoInd])<1.47 );

	_loosePhoHoverE.push_back(tree->phoHoverE_[phoInd]);
	_loosePhoSIEIE.push_back(tree->phoSIEIE_[phoInd]);


	_loosePhoPFRelIso.push_back( tree->phoPFRelIso_[phoInd]);
	_loosePhoPFRelChIso.push_back( tree->phoPFRelChIso_[phoInd]);
	_loosePhoPFChIso.push_back( tree->phoPFRelChIso_[phoInd] * tree->phoEt_[phoInd]);

	if (tree->isData_){
	    _loosePhoEffWeight.push_back(1.);
	    _loosePhoEffWeight_Do.push_back(1.);
	    _loosePhoEffWeight_Up.push_back(1.);
	} else {
	    _loosePhoEffWeight.push_back(getPhoSF(tree->phoEt_[phoInd],tree->phoEta_[phoInd],1));
	    _loosePhoEffWeight_Do.push_back(getPhoSF(tree->phoEt_[phoInd],tree->phoEta_[phoInd],0));
	    _loosePhoEffWeight_Up.push_back(getPhoSF(tree->phoEt_[phoInd],tree->phoEta_[phoInd],2));
	}
	

	_loosePhoTightID.push_back(tree->phoIDcutbased_[phoInd]>=3);
	_loosePhoMediumID.push_back(tree->phoIDcutbased_[phoInd]>=2);
	_loosePhoLooseID.push_back(tree->phoIDcutbased_[phoInd]>=1);

	vector<bool> phoMediumCuts =  passPhoMediumID(phoInd);
	_loosePhoMediumIDFunction.push_back(  phoMediumCuts.at(0));
	_loosePhoMediumIDPassHoverE.push_back(phoMediumCuts.at(1));
	_loosePhoMediumIDPassSIEIE.push_back( phoMediumCuts.at(2));
	_loosePhoMediumIDPassChIso.push_back( phoMediumCuts.at(3));
	_loosePhoMediumIDPassNeuIso.push_back(phoMediumCuts.at(4));
	_loosePhoMediumIDPassPhoIso.push_back(phoMediumCuts.at(5));
	
	vector<bool> phoTightCuts =  passPhoTightID(phoInd);
	_loosePhoTightIDFunction.push_back(  phoTightCuts.at(0));
	_loosePhoTightIDPassHoverE.push_back(phoTightCuts.at(1));
	_loosePhoTightIDPassSIEIE.push_back( phoTightCuts.at(2));
	_loosePhoTightIDPassChIso.push_back( phoTightCuts.at(3));
	_loosePhoTightIDPassNeuIso.push_back(phoTightCuts.at(4));
	_loosePhoTightIDPassPhoIso.push_back(phoTightCuts.at(5));
	
	_loosePhoMassLepGamma.push_back( (phoVector+lepVector).M() );
	
	bool isGenuine = false;
	bool isMisIDEle = false;
	bool isHadronicPhoton = false;
	bool isHadronicFake = false;
	int phoGenMatchInd = -1.;

	// TODO Reimplement with NANOAOD

	// if (!tree->isData_){
	//     phoGenMatchInd = findPhotonGenMatch(phoInd, tree);
	    
	//     _loosePhoGenMatchInd.push_back(phoGenMatchInd);
	    
	//     findPhotonCategory(phoGenMatchInd, tree, &isGenuine, &isMisIDEle, &isHadronicPhoton, &isHadronicFake);
	//     _loosePhotonIsGenuine.push_back(isGenuine);
	//     _loosePhotonIsMisIDEle.push_back(isMisIDEle);
	//     _loosePhotonIsHadronicPhoton.push_back(isHadronicPhoton);
	//     _loosePhotonIsHadronicFake.push_back(isHadronicFake);
	// }
	
    }
    
    for (int i_jet = 0; i_jet < _nfwdJet; i_jet++){
	int jetInd = selector->FwdJets.at(i_jet);
	_fwdJetPt.push_back(tree->jetPt_[jetInd]);
	_fwdJetEta.push_back(tree->jetEta_[jetInd]);
	_fwdJetPhi.push_back(tree->jetPhi_[jetInd]);
	_fwdJetMass.push_back(tree->jetMass_[jetInd]);
    }

    for (int i_jet = 0; i_jet <_nJet; i_jet++){
		
	int jetInd = selector->Jets.at(i_jet);
	_jetPt.push_back(tree->jetPt_[jetInd]);
	_jetEta.push_back(tree->jetEta_[jetInd]);
	_jetPhi.push_back(tree->jetPhi_[jetInd]);
	_jetMass.push_back(tree->jetMass_[jetInd]);

	_jetCMVA.push_back(tree->jetBtagCMVA_[jetInd]);
	_jetCSVV2.push_back(tree->jetBtagCSVV2_[jetInd]);
	_jetDeepB.push_back(tree->jetBtagDeepB_[jetInd]);
	_jetDeepC.push_back(tree->jetBtagDeepC_[jetInd]);
	
	jetVector.SetPtEtaPhiM(tree->jetPt_[jetInd], tree->jetEta_[jetInd], tree->jetPhi_[jetInd], tree->jetMass_[jetInd]);
	

	// TODO Reimplement with NANOAOD
	// if (!tree->isData_){
	//     _jetPartonID.push_back(tree->jetPartonID_[jetInd]);
	//     _jetGenJetPt.push_back(tree->jetGenJetPt_[jetInd]);
	//     _jetGenPartonID.push_back(tree->jetGenPartonID_[jetInd]);
	//     _jetGenPt.push_back(tree->jetGenPt_[jetInd]);
	//     _jetGenEta.push_back(tree->jetGenEta_[jetInd]);
	//     _jetGenPhi.push_back(tree->jetGenPhi_[jetInd]);
	// }

	// double resolution = getJetResolution(tree->jetPt_[jetInd], tree->jetEta_[jetInd], tree->rho_);
	// if (tree->jetDeepCSVTags_b_[jetInd] + tree->jetDeepCSVTags_bb_[jetInd] > selector->btag_cut_DeepCSV){
	//     bjetVectors.push_back(jetVector);
	//     bjetResVectors.push_back(resolution);
	// } else {
	//     ljetVectors.push_back(jetVector);
	//     ljetResVectors.push_back(resolution);
	// }
    }	

    //Compute M3
    _M3 = -1.;
    _M3_gamma =-1;
    double maxPt = -1;
    if (_nJet>2) {
	TLorentzVector jet1;
	TLorentzVector jet2;
	TLorentzVector jet3;
	for (int i_jet1 = 0; i_jet1 <_nJet-2; i_jet1++){
	    int jetInd1 = selector->Jets.at(i_jet1);
	    jet1.SetPtEtaPhiM(tree->jetPt_[jetInd1],tree->jetEta_[jetInd1],tree->jetPhi_[jetInd1],tree->jetMass_[jetInd1]);
	    
	    for (int i_jet2 = i_jet1+1; i_jet2 <_nJet-1; i_jet2++){
		int jetInd2 = selector->Jets.at(i_jet2);
		jet2.SetPtEtaPhiM(tree->jetPt_[jetInd2],tree->jetEta_[jetInd2],tree->jetPhi_[jetInd2],tree->jetMass_[jetInd2]);

		for (int i_jet3 = i_jet2+1; i_jet3 <_nJet; i_jet3++){
		    int jetInd3 = selector->Jets.at(i_jet3);
		    jet3.SetPtEtaPhiM(tree->jetPt_[jetInd3],tree->jetEta_[jetInd3],tree->jetPhi_[jetInd3],tree->jetMass_[jetInd3]);

		    if ((jet1 + jet2 + jet3).Pt()>maxPt){
			_M3 = (jet1 + jet2 + jet3).M();
			if (_nPho>0) {
			    
			    _M3_gamma = (jet1 + jet2 + jet3 + phoVector ).M();
			}
			maxPt=(jet1 + jet2 + jet3).Pt();
		    }
		    
		}
	    }
	}
    }

    //Calculate transverse mass variables
    //W transverse mass		

    _WtransMass = TMath::Sqrt(2*lepVector.Pt()*tree->MET_pt_*( 1.0 - TMath::Cos( lepVector.DeltaPhi(METVector))));


    // // Calculate MET z

    metZ.SetLepton(lepVector);

    METVector.SetPtEtaPhiM(tree->MET_pt_,
			   0.,
			   tree->MET_phi_,
			   0.);
	
    metZ.SetMET(METVector);

    TLorentzVector tempLep;
    tempLep.SetPtEtaPhiM(lepVector.Pt(),
			 lepVector.Eta(),
			 lepVector.Phi(),
			 0.1056);

    double _met_px = METVector.Px();
    double _met_py = METVector.Py();

    double _met_pz = metZ.Calculate();
    double _met_pz_other = metZ.getOther();


    // for (int __j = 0; __j < isBjet.size(); __j++){
    // 	if (isBjet.at(__j)) b_ind.push_back(__j);
    // 	else j_ind.push_back(__j);
    // }
    

    topEvent.SetBJetVector(bjetVectors);
    topEvent.SetLJetVector(ljetVectors);
    topEvent.SetLepton(lepVector);
    topEvent.SetMET(METVector);
    
    topEvent.SetBJetResVector(bjetResVectors);
    topEvent.SetLJetResVector(ljetResVectors);
    topEvent.SetIgnoreBtag(true);
    
    topEvent.Calculate();
    if (topEvent.GoodCombination()){
	bhad = topEvent.getBHad();
	blep = topEvent.getBLep();
	Wj1 = topEvent.getJ1();
	Wj2 = topEvent.getJ2();
	
	_Mt_blgammaMET = TMath::Sqrt( pow(TMath::Sqrt( pow( (blep + lepVector + phoVector).Pt(),2) + pow( (blep + lepVector + phoVector).M(),2) ) + METVector.Pt(), 2) - pow((blep + lepVector + phoVector + METVector ).Pt(),2) );
	_Mt_lgammaMET = TMath::Sqrt( pow(TMath::Sqrt( pow( (lepVector + phoVector).Pt(),2) + pow( (lepVector + phoVector).M(),2) ) + METVector.Pt(), 2) - pow((lepVector + phoVector + METVector ).Pt(),2) );
	_M_bjj = ( bhad + Wj1 + Wj2 ).M();
	_M_bjjgamma = ( bhad + Wj1 + Wj2 + phoVector).M();
	_M_jj  = ( Wj1 + Wj2 ).M();
	


	_MassCuts = ( _Mt_blgammaMET > 180 &&
		      _Mt_lgammaMET > 90 && 
		      _M_bjj > 160 && 
		      _M_bjj < 180 && 
		      _M_jj > 70 &&
		      _M_jj < 90 &&
		      _nPho > 0);
	
    }
    
    ljetVectors.clear();
    bjetVectors.clear();
    
    ljetResVectors.clear();
    bjetResVectors.clear();
    
    
    if (isMC){

	// Float_t LHE scale variation weights (w_var / w_nominal); 
	// [0] is mur=0.5 muf=0.5 ; 
	// [1] is mur=0.5 muf=1 ; 
	// [2] is mur=0.5 muf=2 ; 
	// [3] is mur=1 muf=0.5 ; 
	// [4] is mur=1 muf=1 ; 
	// [5] is mur=1 muf=2 ; 
	// [6] is mur=2 muf=0.5 ; 
	// [7] is mur=2 muf=1 ; 
	// [8] is mur=2 muf=2 

	_q2weight_Up = 1.;
	_q2weight_Do = 1.;

	if (tree->nLHEScaleWeight_==9){
	    for (int i = 0; i < 9; i++){
		if(i==2||i==6){continue;}
		_genScaleSystWeights.push_back(tree->LHEScaleWeight_[i]);
	    }
	    _q2weight_Up = *max_element(_genScaleSystWeights.begin(), _genScaleSystWeights.end())/tree->LHEScaleWeight_[4];
	    _q2weight_Do = *min_element(_genScaleSystWeights.begin(), _genScaleSystWeights.end())/tree->LHEScaleWeight_[4];
	}

	_pdfWeight = tree->LHEPdfWeight_[0];
	double pdfMean = 0.;
	for (int j=1; j < tree->nLHEPdfWeight_; j++ ){
	    _pdfSystWeight.push_back(tree->LHEPdfWeight_[j]);
	    pdfMean += tree->LHEPdfWeight_[j];
	}
	pdfMean = pdfMean/_pdfSystWeight.size();
	    
	double pdfVariance = 0.;
	for (int j=0; j < _pdfSystWeight.size(); j++){
	    pdfVariance += pow((_pdfSystWeight[j]-pdfMean),2.);
	}

	_pdfuncer = sqrt(pdfVariance/_pdfSystWeight.size());
	_pdfweight_Up = (_pdfWeight + _pdfuncer)/_pdfWeight;
	_pdfweight_Do = (_pdfWeight - _pdfuncer)/_pdfWeight;

    }

    
    
    for (int i_mc = 0; i_mc <_nGenPart; i_mc++){
	_genPt.push_back(tree->GenPart_pt_[i_mc]);
	_genPhi.push_back(tree->GenPart_phi_[i_mc]);
	_genEta.push_back(tree->GenPart_eta_[i_mc]);
	_genMass.push_back(tree->GenPart_mass_[i_mc]);
	_genStatus.push_back(tree->GenPart_status_[i_mc]);
	_genStatusFlag.push_back(tree->GenPart_statusFlags_[i_mc]);
	_genPDGID.push_back(tree->GenPart_pdgId_[i_mc]);
	_genMomIdx.push_back(tree->GenPart_genPartIdxMother_[i_mc]);
	// _genMomPID.push_back(tree->mcMomPID[i_mc]);
	// _genGMomPID.push_back(tree->mcGMomPID[i_mc]);
    }

}

// https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting
double makeAnalysisNtuple::SFtop(double pt){
    return exp(0.0615 - 0.0005*pt);
}

double makeAnalysisNtuple::topPtWeight(){
    double toppt=0.0;
    double antitoppt=0.0;
    double weight = 1.0;

    // TODO needs to be reimplemented with NANOAOD
    for(int mcInd=0; mcInd<tree->nGenPart_; ++mcInd){
    	if(tree->GenPart_pdgId_[mcInd]==6  && tree->GenPart_statusFlags_[mcInd]>>13&1) toppt = tree->mcPt->at(mcInd);
    	if(tree->GenPart_pdgId_[mcInd]==-6 && tree->GenPart_statusFlags_[mcInd]>>13&1) antitoppt = tree->mcPt->at(mcInd);
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
	
    string b_sysType = "central";
    string l_sysType = "central";
    if (sysType=="b_up"){
	b_sysType = "up";
    } else if (sysType=="b_down"){
	b_sysType = "down";
    } else if (sysType=="l_up"){
	l_sysType = "up";
    } else if (sysType=="l_down"){
	l_sysType = "down";
    }	


    for(std::vector<int>::const_iterator bjetInd = selector->bJets.begin(); bjetInd != selector->bJets.end(); bjetInd++){
	jetpt = tree->jetPt_[*bjetInd];
	jeteta = fabs(tree->jetEta_[*bjetInd]);
	jetflavor = abs(tree->jetHadFlvr_[*bjetInd]);
		
	if (jetflavor == 5) SFb = reader.eval_auto_bounds(b_sysType, BTagEntry::FLAV_B, jeteta, jetpt); 
	else if(jetflavor == 4) SFb = reader.eval_auto_bounds(b_sysType, BTagEntry::FLAV_C, jeteta, jetpt); 
	else {
	    SFb = reader.eval_auto_bounds(l_sysType, BTagEntry::FLAV_UDSG, jeteta, jetpt); 
	}

	btagSF.push_back(SFb);
    }

    if(selector->bJets.size() == 0) {
	btagWeights.push_back(1.0);
	btagWeights.push_back(0.0);
	btagWeights.push_back(0.0);

	return btagWeights;

    } else if (selector->bJets.size() == 1) {
	btagWeights.push_back(1-btagSF.at(0));
	btagWeights.push_back(btagSF.at(0));
	btagWeights.push_back(0.0);
		
	return btagWeights;

    } else {

	// We are following the method 1SFc from the twiki
	// https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagSFMethods#1c_Event_reweighting_using_scale
	for (int i = 0; i < selector->bJets.size(); i++){
	    SFb = btagSF.at(i);
	    weight0tag *= 1.0 - SFb;
	    double prod = SFb;
	    for (int j = 0; j < selector->bJets.size(); j++){
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


vector<bool> makeAnalysisNtuple::passPhoMediumID(int phoInd){

    bool passMediumID = false;
    bool passHoverE = false;
    bool passSIEIE  = false;
    bool passChIso  = false;
    bool passNeuIso  = false;
    bool passPhoIso  = false;
	
    //    *         | Int_t VID compressed bitmap (MinPtCut,PhoSCEtaMultiRangeCut,PhoSingleTowerHadOverEmCut,PhoFull5x5SigmaIEtaIEtaCut,PhoAnyPFIsoWithEACut,PhoAnyPFIsoWithEAAndQuadScalingCut,PhoAnyPFIsoWithEACut), 2 bits per cut*


    Int_t bitMap = tree->Photon_vidNestedWPBitmap_[phoInd];

    passHoverE  = (bitMap>>4&3)  >= 2;
    passSIEIE   = (bitMap>>6&3)  >= 2;
    passChIso   = (bitMap>>8&3)  >= 2;
    passNeuIso  = (bitMap>>10&3) >= 2;
    passPhoIso  = (bitMap>>12&3) >= 2;


    passMediumID = passHoverE && passSIEIE && passChIso && passNeuIso && passPhoIso;

    vector<bool> cuts;
    cuts.push_back(passMediumID);
    cuts.push_back(passHoverE);
    cuts.push_back(passSIEIE);
    cuts.push_back(passChIso);
    cuts.push_back(passNeuIso);
    cuts.push_back(passPhoIso);

    return cuts;

}


vector<bool> makeAnalysisNtuple::passPhoTightID(int phoInd){

    bool passTightId = false;
    bool passHoverE = false;
    bool passSIEIE  = false;
    bool passChIso  = false;
    bool passNeuIso  = false;
    bool passPhoIso  = false;
	
    //    *         | Int_t VID compressed bitmap (MinPtCut,PhoSCEtaMultiRangeCut,PhoSingleTowerHadOverEmCut,PhoFull5x5SigmaIEtaIEtaCut,PhoAnyPFIsoWithEACut,PhoAnyPFIsoWithEAAndQuadScalingCut,PhoAnyPFIsoWithEACut), 2 bits per cut*

    // 0 = fail all
    // 1 = pass loose
    // 2 = pass medium
    // 3 = pass tight

    Int_t bitMap = tree->Photon_vidNestedWPBitmap_[phoInd];

    passHoverE  = (bitMap>>4&3)  >= 3;
    passSIEIE   = (bitMap>>6&3)  >= 3;
    passChIso   = (bitMap>>8&3)  >= 3;
    passNeuIso  = (bitMap>>10&3) >= 3;
    passPhoIso  = (bitMap>>12&3) >= 3;


    passTightId = passHoverE && passSIEIE && passChIso && passNeuIso && passPhoIso;

    vector<bool> cuts;
    cuts.push_back(passTightId);
    cuts.push_back(passHoverE);
    cuts.push_back(passSIEIE);
    cuts.push_back(passChIso);
    cuts.push_back(passNeuIso);
    cuts.push_back(passPhoIso);

    return cuts;

}



//This is defined in OverlapRemoval.cpp
double minGenDr(int myInd, const EventTree* tree);


void makeAnalysisNtuple::findPhotonCategory(int mcMatchInd, EventTree* tree, bool* genuine, bool *misIDele, bool *hadronicphoton, bool *hadronicfake){

	*genuine        = false;
	*misIDele       = false;
	*hadronicphoton = false;
	*hadronicfake   = false;

        // TODO needs to be reimplemented with NANOAOD                                                                                                      
	// If no match, it's hadronic fake
	if (mcMatchInd== -1) {
		*hadronicfake = true;
		return;
	}

	int mcMatchPDGID = tree->GenPart_pdgId_[mcMatchInd];

	Int_t parentIdx = mcMatchInd;
	int maxPDGID = 0;
	int motherPDGID = 0;
	while (parentIdx != -1){
	    motherPDGID = std::abs(tree->GenPart_pdgId_[parentIdx]);
	    maxPDGID = std::max(maxPDGID,motherPDGID);
	    parentIdx = tree->GenPart_genPartIdxMother_[parentIdx];
	}

	bool parentagePass = maxPDGID < 37;

	// //	mcMatchInd = findPhotonGenMatch(int phoInd, EventTree* tree);
	// bool parentagePass = (fabs(tree->mcMomPID->at(mcMatchInd))<37 || tree->mcMomPID->at(mcMatchInd) == -999);

	if (mcMatchPDGID==22){
	    bool drotherPass = minGenDr(mcMatchInd, tree) > 0.2;
	    if (parentagePass && drotherPass){ 
		*genuine = true;
	    }
	    else {
		*hadronicphoton = true;
	    }
	}
	else if ( abs(mcMatchPDGID ) == 11 && parentagePass && minGenDr(mcMatchInd, tree) > 0.2 ) {
	    *misIDele = true;
	} 
	else {
	    *hadronicfake = true;
	}
	

}
			
// int makeAnalysisNtuple::findPhotonGenMatch(int phoInd, EventTree* tree){

// 	double minDR = 999.;
// 	int matchInd = -1;

//         // TODO needs to be reimplemented with NANOAOD                                                                                                      
// 	// for(int mcInd=0; mcInd<tree->nMC_; ++mcInd){
// 	// 	if (tree->mcStatus->at(mcInd) == 1 || tree->mcStatus->at(mcInd) == 71){ 
// 	// 		double dRValue = dR(tree->mcEta->at(mcInd),tree->mcPhi->at(mcInd),tree->phoEta_->at(phoInd),tree->phoPhi_->at(phoInd));
// 	// 		if (dRValue < minDR){
// 	// 			if ( (fabs(tree->phoEt_->at(phoInd) - tree->mcPt->at(mcInd)) / tree->mcPt->at(mcInd)) < 0.5 ){
// 	// 				minDR = dRValue;
// 	// 				matchInd = mcInd;
// 	// 			}
// 	// 		}
// 	// 	}
// 	// }

// 	// if (minDR > 0.1){	matchInd = -1.; }  //Only consider matches with dR < 0.1

// 	return matchInd;
// }




// int makeAnalysisNtuple::minDrIndex(double myEta, double myPhi, std::vector<int> Inds, std::vector<float> *etas, std::vector<float> *phis){
// 	double mindr = 999.0;
// 	double dr;
// 	int bestInd = -1;
// 	for( std::vector<int>::iterator it = Inds.begin(); it != Inds.end(); ++it){
// 		dr = dR(myEta, myPhi, etas->at(*it), phis->at(*it));
// 		if( mindr > dr ) {
// 			mindr = dr;
// 			bestInd = *it;
// 		}
// 	}
// 	return bestInd;
// }

// double makeAnalysisNtuple::minDr(double myEta, double myPhi, std::vector<int> Inds, std::vector<float> *etas, std::vector<float> *phis){
// 	int ind = minDrIndex(myEta, myPhi, Inds, etas, phis);
// 	if(ind>=0) return dR(myEta, myPhi, etas->at(ind), phis->at(ind));
// 	else return 999.0;
// }



#endif

int main(int ac, char** av){
  if(ac != 4){
    std::cout << "usage: ./makeAnalysisNtuple sampleName outputFileDir inputFile[s]" << std::endl;
    return -1;
  }

  makeAnalysisNtuple(ac, av);


  return 0;
}
