#include "makeAnalysisNtuple.h"
#define makeAnalysisNtuple_cxx
#include <boost/program_options.hpp>

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <iostream>
#include <ctime>
#include "TRandom3.h"
#include "ParsePhotonID.h"
#include "PUReweight.h"
#include "METzCalculator.h"
#include "TopEventCombinatorics.h"
#include "JetResolutions.h"
#include "JEC/JECvariation.h"
//#include"OverlapRemove.cpp"
#include <cmath>

int jecvar012_g = 1; // 0:down, 1:norm, 2:up
int jervar012_g = 1; // 0:down, 1:norm, 2:up
int phosmear012_g = 1; // 0:down, 1:norm, 2:up 
int musmear012_g = 1; // 0:down, 1:norm, 2: up
int elesmear012_g = 1; // 0:down, 1:norm, 2: up
int phoscale012_g = 1;
int elescale012_g = 1;
#include "BTagCalibrationStandalone.h"

bool overlapRemovalTT(EventTree* tree);
bool overlapRemovalZJets(EventTree* tree);
bool overlapRemovalWJets(EventTree* tree);
bool overlapRemoval_Tchannel(EventTree* tree);
double getJetResolution(double, double, double);


bool dileptonsample;

auto startClock = std::chrono::high_resolution_clock::now();

//std::clock_t startClock;
//double duration;

#ifdef makeAnalysisNtuple_cxx
makeAnalysisNtuple::makeAnalysisNtuple(int ac, char** av)
{
    startClock = std::chrono::high_resolution_clock::now();
    printf("Git Commit Number: %s\n", VERSION);
    printf("Git Commit Time: %s\n", COMMITTIME);
    printf("Git Branch: %s\n", BRANCH);
    printf("Git Status: %s\n", STATUS);

    if (STATUS != ""){
	cout << endl;
	cout <<"=============================================" << endl;
	cout <<"=============================================" << endl;
	cout <<"Warning, files are missing from github" << endl;
	cout <<"=============================================" << endl;
	cout <<"=============================================" << endl;
	cout << endl;
    }

    int eventNum = -1;
    std::string eventStr = "-1";

    if(ac < 5){
	std::cout << "usage: ./makeAnalysisNtuple year sampleName outputFileDir inputFile[s]" << std::endl;
	return;
    }


    if (std::string(av[1])=="event"){
	
	std::string tempEventStr(av[2]);
	eventNum = std::stoi(tempEventStr);
	for (int i = 1; i < ac-2; i++){
	    av[i] = av[i+2];
	    //cout << av[i] << " ";
	}
	ac = ac-2;
	//	cout  << endl;
	eventStr = tempEventStr;
	//cout << eventStr << "  "  << eventNum << endl;
    }

    //check if NofM type format is before output name (for splitting jobs)
    int nJob = -1;
    int totJob = -1;
    std::string checkJobs(av[3]);
    size_t pos = checkJobs.find("of");
    if (pos != std::string::npos){
	nJob = std::stoi(checkJobs.substr(0,pos));
	totJob = std::stoi(checkJobs.substr(pos+2,checkJobs.length()));
	for (int i = 3; i < ac-1; i++){
	    av[i] = av[i+1];
	    //cout << av[i] << " ";
	}
	ac = ac-1;
    }
    cout << nJob << " of " << totJob << endl;



    std::string year(av[1]);
    tree = new EventTree(ac-4, false, year, av+4);

    sampleType = av[2];

    systematicType = "";
    cout << sampleType << endl;


    isMC = true;
    if (sampleType.find("Data") != std::string::npos){
	isMC = false;
    }

    tree->isData_ = !isMC;
    
    isSystematicRun = false;

    
    pos = sampleType.find("__");
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
    
    std::string PUfilename; 
    std::string PUfilename_up;
    std::string PUfilename_down;



    if (year=="2016"){
	PUfilename      = "PileupHists/Data_2016BCDGH_Pileup.root";
	PUfilename_up   = "PileupHists/Data_2016BCDGH_Pileup_scaledUp.root";
	PUfilename_down = "PileupHists/Data_2016BCDGH_Pileup_scaledDown.root";
    }
    if (year=="2017"){
	//THIS NEEDS TO BE UPDATED WITH 2017 PILEUP FILES
	PUfilename      = "PileupHists/Data_2017BCDEF_Pileup.root";
	PUfilename_up   = "PileupHists/Data_2017BCDEF_Pileup_scaledUp.root";
	PUfilename_down = "PileupHists/Data_2017BCDEF_Pileup_scaledDown.root";
    }
    if (year=="2018"){
	//THIS NEEDS TO BE UPDATED WITH 2018 PILEUP FILES
	PUfilename      = "PileupHists/Data_2018ABCD_Pileup.root";
	PUfilename_up   = "PileupHists/Data_2018ABCD_Pileup_scaledUp.root";
	PUfilename_down = "PileupHists/Data_2018ABCD_Pileup_scaledDown.root";
    }
    if (eventNum > -1) {
	string cut = "event=="+eventStr;
	cout << "Selecting only entries with " << cut << endl;
	tree->chain = (TChain*) tree->chain->CopyTree(cut.c_str());
    }

    selector = new Selector();
    
    evtPick = new EventPick("");
    
    selector->year = year;
    evtPick->year = year;
    
    selector->printEvent = eventNum;
    evtPick->printEvent = eventNum;

    

    selector->pho_applyPhoID = false;
    selector->looseJetID = false;
    
    selector->useDeepCSVbTag = true;
    
    // selector->veto_pho_jet_dR = -1.; //remove jets which have a photon close to them 
    selector->veto_jet_pho_dR = -1.; //remove photons which have a jet close to them (after having removed jets too close to photon from above cut)


    if (year=="2016") selector->btag_cut_DeepCSV = 0.6321;
    if (year=="2017") selector->btag_cut_DeepCSV = 0.4941;
    if (year=="2018") selector->btag_cut_DeepCSV = 0.4184;
    
    //	selector->jet_Pt_cut = 40.;
    evtPick->Njet_ge = 2;	
    evtPick->NBjet_ge = 0;	

    evtPick->applyMetFilter = true;	

    BTagCalibration calib;
    if (!selector->useDeepCSVbTag){
	if (year=="2016") calib = BTagCalibration("csvv2", "BtagSF/CSVv2_Moriond17_B_H.csv");
	if (year=="2017") calib = BTagCalibration("csvv2", "BtagSF/CSVv2_94XSF_V2_B_F.csv");
	if (year=="2018") calib = BTagCalibration("csvv2", "BtagSF/CSVv2_94XSF_V2_B_F.csv");
    } else {
	if (year=="2016"){ calib = BTagCalibration("deepcsv", "BtagSF/DeepCSV_2016LegacySF_V1.csv");}
	if (year=="2017"){ calib = BTagCalibration("deepcsv", "BtagSF/DeepCSV_94XSF_V3_B_F.csv");}
	if (year=="2018"){ calib = BTagCalibration("deepcsv", "BtagSF/DeepCSV_102XSF_V1.csv");} //DeepCSV_102XSF_V1.csv

	loadBtagEff(sampleType,year);

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
    
    bool doOverlapRemoval_TT = false;
    bool doOverlapRemoval_W = false;	
    bool doOverlapRemoval_Z = false;	
    bool doOverlapRemoval_Tchannel = false;	
    
    bool invertOverlap = false;
    
    bool skipOverlap = false;
    //    applypdfweight = false;
    //    applyqsquare  = false;
    //    if( sampleType == "TTbarPowheg" || sampleType=="isr_up_TTbarPowheg" || sampleType=="fsr_up_TTbarPowheg"|| sampleType=="isr_down_TTbarPowheg"|| sampleType=="fsr_down_TTbarPowheg"|| sampleType == "TTbarPowheg1" || sampleType == "TTbarPowheg2" || sampleType == "TTbarPowheg3" || sampleType == "TTbarPowheg4" || sampleType == "TTbarMCatNLO" || sampleType == "TTbarMadgraph_SingleLeptFromT" || sampleType == "TTbarMadgraph_SingleLeptFromTbar" || sampleType == "TTbarMadgraph_Dilepton" || sampleType == "TTbarMadgraph" ) doOverlapRemoval = true;


    if (sampleType.find("TTbarPowheg")!= std::string::npos) {
	doOverlapRemoval_TT = true;
    }
    
    if( sampleType == "W1jets" || sampleType == "W2jets" ||  sampleType == "W3jets" || sampleType == "W4jets"){
	doOverlapRemoval_W = true;
    }

    if (sampleType=="DYjetsM10to50" || sampleType=="DYjetsM50" || sampleType=="DYjetsM10to50_MLM" || sampleType=="DYjetsM50_MLM"){
	doOverlapRemoval_Z = true;
    }
    
    if( sampleType == "ST_t-channel" || sampleType == "ST_tbar-channel") {
	doOverlapRemoval_Tchannel = true;
    }

    if(doOverlapRemoval_TT || doOverlapRemoval_W || doOverlapRemoval_Z || doOverlapRemoval_Tchannel) {
	std::cout << "########## Will apply overlap removal ###########" << std::endl;
    }
    

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
    if( systematicType=="QCDcr")       {selector->QCDselect = true; evtPick->ZeroBExclusive=true; evtPick->QCDselect = true;}
    std::cout << "Dilepton Sample :" << dileptonsample << std::endl;
    std::cout << "JEC: " << jecvar012_g << "  JER: " << jervar012_g << " eleScale "<< elescale012_g << " phoScale" << phoscale012_g << "   ";
    std::cout << "  PhoSmear: " << phosmear012_g << "  muSmear: " << musmear012_g << "  eleSmear: " << elesmear012_g << std::endl;

    if (isSystematicRun){
	std::cout << "  Systematic Run : Dropping genMC variables from tree" << endl;
    }


    std::string outputDirectory(av[3]);

    std::string outputFileName;

    if (nJob==-1){
	outputFileName = outputDirectory + "/" + sampleType+"_"+year+"_AnalysisNtuple.root";
    } else {
	outputFileName = outputDirectory + "/" + sampleType+"_"+year+"_AnalysisNtuple_"+to_string(nJob)+"of"+to_string(totJob)+".root";
    }
    // char outputFileName[100];
    cout << av[3] << " " << sampleType << " " << systematicType << endl;
    //	outputFileName = sprintf("%s_AnalysisNtuple.root",sampleType);
    if (systematicType!=""){
	outputFileName = outputDirectory + "/"+systematicType + "_" +sampleType+"_"+year+"_AnalysisNtuple.root";
	//		sprintf(outputFileName,"%s/%s_%s_AnalysisNtuple.root",av[3],systematicType,sampleType);
    }
    cout << av[3] << " " << sampleType << " " << systematicType << endl;
    cout << outputFileName << endl;
    TFile *outputFile = new TFile(outputFileName.c_str(),"recreate");
    outputTree = new TTree("AnalysisTree","AnalysisTree");

    PUReweight* PUweighter = new PUReweight(ac-4, av+4, PUfilename);
    PUReweight* PUweighterUp = new PUReweight(ac-4, av+4, PUfilename_up);
    PUReweight* PUweighterDown = new PUReweight(ac-4, av+4, PUfilename_down);
    tree->GetEntry(0);
        
    std::cout << "isMC: " << isMC << endl;

    InitBranches();

    JECvariation* jecvar;
    if (isMC && jecvar012_g!=1) {
	//		jecvar = new JECvariation("./jecFiles/Summer16_23Sep2016V4", isMC, "Total");//SubTotalAbsolute");
	cout << "Applying JEC uncertainty variations : " << JECsystLevel << endl;
	if (year=="2016") jecvar = new JECvariation("./jecFiles/Summer16_23Sep2016V4", isMC, JECsystLevel);
	// THIS NEEDS TO BE UPDATED TO GET 2017 JEC FILES ///it will be Fall17_17NOV_2017_V*
	if (year=="2017") jecvar = new JECvariation("./jecFiles/Summer16_23Sep2016V4", isMC, JECsystLevel);
	if (year=="2018") jecvar = new JECvariation("./jecFiles/Summer16_23Sep2016V4", isMC, JECsystLevel);
    }

    double luminosity = 1.;
    if (year=="2016") luminosity=35860;
    if (year=="2017") luminosity=41529;
    if (year=="2018") luminosity=58877;

    double nMC_total = 0.;
    char** fileNames = av+4;
    for(int fileI=0; fileI<ac-4; fileI++){
	TFile *_file = TFile::Open(fileNames[fileI],"read");
	TH1D *hEvents = (TH1D*) _file->Get("hEvents");
	nMC_total += (hEvents->GetBinContent(3) - hEvents->GetBinContent(1));
    }
	
    if (nMC_total==0){
	nMC_total=1;
    }

    _lumiWeight = getEvtWeight(sampleType, luminosity, nMC_total);
    // _lumiWeightAlt = _lumiWeight;

    // if (isTTGamma){
    // 	_lumiWeightAlt = getEvtWeight("alt_"+sampleType, luminosity, nMC_total);
    // }

    _PUweight       = 1.;
    _muEffWeight    = 1.;
    _muEffWeight_Do = 1.;
    _muEffWeight_Up = 1.;
    _eleEffWeight    = 1.;
    _eleEffWeight_Up = 1.;
    _eleEffWeight_Do = 1.;

    Long64_t nEntr = tree->GetEntries();

    bool saveAllEntries = false;

    if (sampleType=="Test") {
	if (nEntr > 20000) nEntr = 20000;
    }
    if (sampleType=="TestAll") {
	if (nEntr > 1000) nEntr = 10;
	saveAllEntries = true;
    }
    //    nEntr = 4000;



    if (year=="2016"){
	muSFa = new MuonSF("MuEGammaScaleFactors/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ID.root", "NUM_TightID_DEN_genTracks_eta_pt",
			   "MuEGammaScaleFactors/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ISO.root", "NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt",
			   "MuEGammaScaleFactors/mu2016/EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunBtoF.root", "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
	
	muSFb = new MuonSF("MuEGammaScaleFactors/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ID.root", "NUM_TightID_DEN_genTracks_eta_pt",
			   "MuEGammaScaleFactors/mu2016/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ISO.root", "NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt",
			   "MuEGammaScaleFactors/mu2016/EfficienciesStudies_2016_trigger_EfficienciesAndSF_RunGtoH.root", "IsoMu24_OR_IsoTkMu24_PtEtaBins/abseta_pt_ratio");
	
	eleSF = new ElectronSF("MuEGammaScaleFactors/ele2016/2016LegacyReReco_ElectronTight_Fall17V2.root",
			       "MuEGammaScaleFactors/ele2016/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root",
			       "MuEGammaScaleFactors/ele2016/sf_ele_2016_trig_v5.root");
	
	phoSF = new PhotonSF("MuEGammaScaleFactors/pho2016/Fall17V2_2016_Tight_photons.root");


    } else if (year=="2017") {
	
	muSFa = new MuonSF("MuEGammaScaleFactors/mu2017/RunBCDEF_SF_ID.root", "NUM_TightID_DEN_genTracks_pt_abseta",
			   "MuEGammaScaleFactors/mu2017/RunBCDEF_SF_ISO.root", "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta",
			   "MuEGammaScaleFactors/mu2017/EfficienciesAndSF_RunBtoF_Nov17Nov2017.root", "IsoMu27_PtEtaBins/abseta_pt_ratio");
	
	eleSF = new ElectronSF("MuEGammaScaleFactors/ele2017/2017_ElectronTight.root",
			       "MuEGammaScaleFactors/ele2017/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root",
			       "MuEGammaScaleFactors/ele2017/sf_ele_2017_trig_v5.root");

	
	phoSF = new PhotonSF("MuEGammaScaleFactors/pho2017/2017_PhotonsTight.root");
	
	
    } else if (year=="2018") {

	muSFa = new MuonSF("MuEGammaScaleFactors/mu2018/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ID.root",  "NUM_TightID_DEN_TrackerMuons_pt_abseta",
			   "MuEGammaScaleFactors/mu2018/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ISO.root", "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta",
			   "MuEGammaScaleFactors/mu2018/EfficienciesStudies_2018_trigger_EfficienciesAndSF_2018Data_BeforeMuonHLTUpdate.root", "IsoMu24_PtEtaBins/abseta_pt_ratio");
	
	muSFb = new MuonSF("MuEGammaScaleFactors/mu2018/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ID.root",  "NUM_TightID_DEN_TrackerMuons_pt_abseta",
			   "MuEGammaScaleFactors/mu2018/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ISO.root", "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta",
			   "MuEGammaScaleFactors/mu2018/EfficienciesStudies_2018_trigger_EfficienciesAndSF_2018Data_AfterMuonHLTUpdate.root", "IsoMu24_PtEtaBins/abseta_pt_ratio");

	eleSF = new ElectronSF("MuEGammaScaleFactors/ele2018/2018_ElectronTight.root",
			       "MuEGammaScaleFactors/ele2018/egammaEffi.txt_EGM2D_updatedAll.root",
			       "MuEGammaScaleFactors/ele2018/sf_ele_2018_trig_v5.root");


	phoSF = new PhotonSF("MuEGammaScaleFactors/pho2018/2018_PhotonsTight.root");

    }

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

    int entryStart;
    int entryStop;
    if (nJob==-1){
	entryStart = 0;
	entryStop=nEntr;
    }
    else {
	int evtPerJob = nEntr/totJob;
	entryStart = (nJob-1) * evtPerJob;
	entryStop = (nJob) * evtPerJob;
	if (nJob==totJob){
	    entryStop = nEntr;
	}
    }


    for(Long64_t entry=entryStart; entry<entryStop; entry++){
	if(entry%dumpFreq == 0){
	    // duration =  ( clock() - startClock ) / (double) CLOCKS_PER_SEC;
	    // std::cout << "processing entry " << entry << " out of " << nEntr << " : " << duration << " seconds since last progress" << std::endl;
	    // startClock = clock();

	    std::cout << "processing entry " << entry << " out of " << nEntr << " : " 
		      << std::chrono::duration<double>(std::chrono::high_resolution_clock::now()-startClock).count()
		      << " seconds since last progress" << std::endl;
	    
	    startClock = std::chrono::high_resolution_clock::now();			

	}
	//  cout << entry << endl;
	tree->GetEntry(entry);

	if( isMC && doOverlapRemoval_TT){
	    if (!invertOverlap){
		if (overlapRemovalTT(tree)){	
		    count_overlapTTbar++;			
		    continue;
		}
	    } else {
		if (!overlapRemovalTT(tree)){	
		    count_overlapTTbar++;			
		    continue;
		}
	    }
	}
	if( isMC && doOverlapRemoval_W){
	    if (overlapRemovalWJets(tree)){
		count_overlapVJets++;
		continue;
	    }
	}
	if( isMC && doOverlapRemoval_Z){
	    if (overlapRemovalZJets(tree)){
		count_overlapVJets++;
		continue;
	    }
	}
	if( isMC && doOverlapRemoval_Tchannel){
	    if (overlapRemoval_Tchannel(tree)){
		count_overlapTchannel++;
		continue;
	    }
	}

	// //		Apply systematics shifts where needed
	if( isMC ){
	    if (jecvar012_g != 1){
		jecvar->applyJEC(tree, jecvar012_g); // 0:down, 1:norm, 2:up
	    }
	}

	selector->clear_vectors();

	evtPick->process_event(tree, selector, _PUweight);

	if ( evtPick->passPresel_ele || evtPick->passPresel_mu || saveAllEntries) {

	    InitVariables();
	    FillEvent(year);

	    if(isMC) {
		_PUweight    = PUweighter->getWeight(tree->nPUTrue_);
		_PUweight_Up = PUweighterUp->getWeight(tree->nPUTrue_);
		_PUweight_Do = PUweighterDown->getWeight(tree->nPUTrue_);

		_btagWeight_1a      = getBtagSF_1a("central", reader);
		_btagWeight_1a_b_Up = getBtagSF_1a("b_up",    reader);
		_btagWeight_1a_b_Do = getBtagSF_1a("b_down",  reader);
		_btagWeight_1a_l_Up = getBtagSF_1a("l_up",    reader);
		_btagWeight_1a_l_Do = getBtagSF_1a("l_down",  reader);
				
		_btagWeight      = getBtagSF_1c("central", reader, _btagSF);
		_btagWeight_b_Up = getBtagSF_1c("b_up",    reader, _btagSF_b_Up);
		_btagWeight_b_Do = getBtagSF_1c("b_down",  reader, _btagSF_b_Do);				
		_btagWeight_l_Up = getBtagSF_1c("l_up",    reader, _btagSF_l_Up);
		_btagWeight_l_Do = getBtagSF_1c("l_down",  reader, _btagSF_l_Do);				
				
		if (evtPick->passPresel_mu) {
		    int muInd_ = selector->Muons.at(0);
		    if (year=="2016"){
			_muEffWeight    = (muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],1, 2016) * 19.656062760/35.882515396 + 
					   muSFb->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],1, 2016) * 16.226452636/35.882515396);

			_muEffWeight_Do = (muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],0, 2016) * 19.656062760/35.882515396 + 
					   muSFb->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],0, 2016) * 16.226452636/35.882515396);

			_muEffWeight_Up = (muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],2, 2016) * 19.656062760/35.882515396 + 
					   muSFb->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],2, 2016) * 16.226452636/35.882515396);

		    }
		    if (year=="2017"){    
			_muEffWeight    = (muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],1, 2017));
			_muEffWeight_Do = (muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],0, 2017));
			_muEffWeight_Up = (muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],2, 2017));
		    }
                    if(year=="2018"){
			_muEffWeight    = (muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],1, 2018) * 8.950818835/59.688059536 + 
					   muSFb->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],1, 2018) * 50.737240701/59.688059536);

			_muEffWeight_Do = (muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],0, 2018) * 8.950818835/59.688059536 + 
					   muSFb->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],0, 2018) * 50.737240701/59.688059536);

			_muEffWeight_Up = (muSFa->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],2, 2018) * 8.950818835/59.688059536 + 
					   muSFb->getMuSF(tree->muPt_[muInd_],tree->muEta_[muInd_],2, 2018) * 50.737240701/59.688059536);

		    }
		    _eleEffWeight    = 1.;
		    _eleEffWeight_Up = 1.;
		    _eleEffWeight_Do = 1.;
		}
		if (evtPick->passPresel_ele) {
		    int eleInd_ = selector->Electrons.at(0);
		    _muEffWeight    = 1.;
		    _muEffWeight_Do = 1.;
		    _muEffWeight_Up = 1.;

		    _eleEffWeight    = eleSF->getEleSF(tree->elePt_[eleInd_],tree->eleEta_[eleInd_] + tree->eleDeltaEtaSC_[eleInd_],1);
		    _eleEffWeight_Do = eleSF->getEleSF(tree->elePt_[eleInd_],tree->eleEta_[eleInd_] + tree->eleDeltaEtaSC_[eleInd_],0);
		    _eleEffWeight_Up = eleSF->getEleSF(tree->elePt_[eleInd_],tree->eleEta_[eleInd_] + tree->eleDeltaEtaSC_[eleInd_],2);

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
	}
    }
    if (doOverlapRemoval_TT){
	std::cout << "Total number of events removed from TTbar:"<< count_overlapTTbar <<std::endl;
    }
    if(doOverlapRemoval_W || doOverlapRemoval_Z){
	std::cout << "Total number of events removed from W/ZJets:"<< count_overlapVJets <<std::endl;
    }
    if(doOverlapRemoval_Tchannel){
	std::cout << "Total number of events removed from t-channel:"<< count_overlapTchannel <<std::endl;
    }

    outputFile->cd();

    outputTree->Write();
    
    TNamed gitCommit("Git_Commit", VERSION);
    TNamed gitTime("Git_Commit_Time", COMMITTIME);
    TNamed gitBranch("Git_Branch", BRANCH);
    TNamed gitStatus("Git_Status", STATUS);

    gitCommit.Write();
    gitTime.Write();
    gitBranch.Write();
    gitStatus.Write();
    
    outputFile->Close();

}


void makeAnalysisNtuple::FillEvent(std::string year)
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
    //    _evtWeightAlt    = _lumiWeightAlt *  ((tree->genWeight_ >= 0) ? 1 : -1);  //event weight needs to be positive or negative depending on sign of genWeight (to account for mc@nlo negative weights)

    if (_isData) {
	_evtWeight= 1.;
	//	_evtWeightAlt= 1.;
    }
    
    _genMET		     = tree->GenMET_pt_;
    _pfMET		     = tree->MET_pt_;
    _pfMETPhi    	     = tree->MET_phi_;
    
    _nPho		     = selector->Photons.size();
    _nLoosePho	             = selector->LoosePhotons.size();
    _nPhoNoID	             = selector->PhotonsNoID.size();
    _nEle		     = selector->Electrons.size();
    _nEleLoose               = selector->ElectronsLoose.size();
    _nMu		     = selector->Muons.size();
    _nMuLoose                = selector->MuonsLoose.size();
    
    _nJet            = selector->Jets.size();
    _nfwdJet         = selector->FwdJets.size();
    _nBJet           = selector->bJets.size();

    _nGenPart        = tree->nGenPart_;
    _nGenJet         = tree->nGenJet_;

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
	    _phoEffWeight.push_back(phoSF->getPhoSF(tree->phoEt_[phoInd],tree->phoEta_[phoInd],1));
	    _phoEffWeight_Do.push_back(phoSF->getPhoSF(tree->phoEt_[phoInd],tree->phoEta_[phoInd],0));
	    _phoEffWeight_Up.push_back(phoSF->getPhoSF(tree->phoEt_[phoInd],tree->phoEta_[phoInd],2));
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

	    findPhotonCategory(phoGenMatchInd, tree, &isGenuine, &isMisIDEle, &isHadronicPhoton, &isHadronicFake); //as we are using phogenmatch defined in nanontuple

	  //  findPhotonCategory(phoInd, tree, &isGenuine, &isMisIDEle, &isHadronicPhoton, &isHadronicFake); //In order to use our own phogenmatch defined 

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

	    _loosePhoEffWeight.push_back(phoSF->getPhoSF(tree->phoEt_[phoInd],tree->phoEta_[phoInd],1));
	    _loosePhoEffWeight_Do.push_back(phoSF->getPhoSF(tree->phoEt_[phoInd],tree->phoEta_[phoInd],0));
	    _loosePhoEffWeight_Up.push_back(phoSF->getPhoSF(tree->phoEt_[phoInd],tree->phoEta_[phoInd],2));

	}
	
	
	_loosePhoTightID.push_back(tree->phoIDcutbased_[phoInd]>=3);
	_loosePhoMediumID.push_back(tree->phoIDcutbased_[phoInd]>=2);
	_loosePhoLooseID.push_back(tree->phoIDcutbased_[phoInd]>=1);

	_loosePhoMVAID.push_back(tree->phoMVAId_[phoInd]);
	_loosePhoMVAID17v1.push_back(tree->phoMVAId17V1_[phoInd]);
	_loosePhoMediumID.push_back(tree->phoIDcutbased_[phoInd]>=2);

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

	if (!tree->isData_){
	    //phoGenMatchInd = findPhotonGenMatch(phoInd, tree);
	    phoGenMatchInd = tree->phoGenPartIdx_[phoInd];
            
	    _loosePhoGenMatchInd.push_back(phoGenMatchInd);

	    findPhotonCategory(phoGenMatchInd, tree, &isGenuine, &isMisIDEle, &isHadronicPhoton, &isHadronicFake);

	    _loosePhotonIsGenuine.push_back(isGenuine);
	    _loosePhotonIsMisIDEle.push_back(isMisIDEle);
	    _loosePhotonIsHadronicPhoton.push_back(isHadronicPhoton);
	    _loosePhotonIsHadronicFake.push_back(isHadronicFake);

	}

	
    }

    for (int i_pho = 0; i_pho <_nPhoNoID; i_pho++){
	int phoInd = selector->PhotonsNoID.at(i_pho);
	phoVector.SetPtEtaPhiM(tree->phoEt_[phoInd],
			       tree->phoEta_[phoInd],
			       tree->phoPhi_[phoInd],
			       0.0);
	
	_phoNoIDEt.push_back(tree->phoEt_[phoInd]);
	_phoNoIDEta.push_back(tree->phoEta_[phoInd]);
	_phoNoIDPhi.push_back(tree->phoPhi_[phoInd]);
	_phoNoIDIsBarrel.push_back( abs(tree->phoEta_[phoInd])<1.47 );

	_phoNoIDHoverE.push_back(tree->phoHoverE_[phoInd]);
	_phoNoIDSIEIE.push_back(tree->phoSIEIE_[phoInd]);


	_phoNoIDPFRelIso.push_back( tree->phoPFRelIso_[phoInd]);
	_phoNoIDPFRelChIso.push_back( tree->phoPFRelChIso_[phoInd]);
	_phoNoIDPFChIso.push_back( tree->phoPFRelChIso_[phoInd] * tree->phoEt_[phoInd]);

	if (tree->isData_){
	    _phoNoIDEffWeight.push_back(1.);
	    _phoNoIDEffWeight_Do.push_back(1.);
	    _phoNoIDEffWeight_Up.push_back(1.);
	} else {

	    _phoNoIDEffWeight.push_back(phoSF->getPhoSF(tree->phoEt_[phoInd],tree->phoEta_[phoInd],1));
	    _phoNoIDEffWeight_Do.push_back(phoSF->getPhoSF(tree->phoEt_[phoInd],tree->phoEta_[phoInd],0));
	    _phoNoIDEffWeight_Up.push_back(phoSF->getPhoSF(tree->phoEt_[phoInd],tree->phoEta_[phoInd],2));

	}
	
	
	_phoNoIDTightID.push_back(tree->phoIDcutbased_[phoInd]>=3);
	_phoNoIDMediumID.push_back(tree->phoIDcutbased_[phoInd]>=2);
	_phoNoIDLooseID.push_back(tree->phoIDcutbased_[phoInd]>=1);

	_phoNoIDMVAID.push_back(tree->phoMVAId_[phoInd]);
	_phoNoIDMVAID17v1.push_back(tree->phoMVAId17V1_[phoInd]);
	_phoNoIDMediumID.push_back(tree->phoIDcutbased_[phoInd]>=2);

	vector<bool> phoMediumCuts =  passPhoMediumID(phoInd);
	_phoNoIDMediumIDFunction.push_back(  phoMediumCuts.at(0));
	_phoNoIDMediumIDPassHoverE.push_back(phoMediumCuts.at(1));
	_phoNoIDMediumIDPassSIEIE.push_back( phoMediumCuts.at(2));
	_phoNoIDMediumIDPassChIso.push_back( phoMediumCuts.at(3));
	_phoNoIDMediumIDPassNeuIso.push_back(phoMediumCuts.at(4));
	_phoNoIDMediumIDPassPhoIso.push_back(phoMediumCuts.at(5));
	
	vector<bool> phoTightCuts =  passPhoTightID(phoInd);
	_phoNoIDTightIDFunction.push_back(  phoTightCuts.at(0));
	_phoNoIDTightIDPassHoverE.push_back(phoTightCuts.at(1));
	_phoNoIDTightIDPassSIEIE.push_back( phoTightCuts.at(2));
	_phoNoIDTightIDPassChIso.push_back( phoTightCuts.at(3));
	_phoNoIDTightIDPassNeuIso.push_back(phoTightCuts.at(4));
	_phoNoIDTightIDPassPhoIso.push_back(phoTightCuts.at(5));
	
	_phoNoIDMassLepGamma.push_back( (phoVector+lepVector).M() );
	
	bool isGenuine = false;
	bool isMisIDEle = false;
	bool isHadronicPhoton = false;
	bool isHadronicFake = false;

	int phoGenMatchInd = -1.;

	// TODO Reimplement with NANOAOD

	if (!tree->isData_){
	    //phoGenMatchInd = findPhotonGenMatch(phoInd, tree);
	    phoGenMatchInd = tree->phoGenPartIdx_[phoInd];
            
	    _phoNoIDGenMatchInd.push_back(phoGenMatchInd);

	    findPhotonCategory(phoGenMatchInd, tree, &isGenuine, &isMisIDEle, &isHadronicPhoton, &isHadronicFake);

	    _photonNoIDIsGenuine.push_back(isGenuine);
	    _photonNoIDIsMisIDEle.push_back(isMisIDEle);
	    _photonNoIDIsHadronicPhoton.push_back(isHadronicPhoton);
	    _photonNoIDIsHadronicFake.push_back(isHadronicFake);

	}

	
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
	
	_jetGenJetIdx.push_back(tree->jetGenJetIdx_[jetInd]);
	// TODO Reimplement with NANOAOD

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

    // // Calculate MET z

    metZ.SetLepton(lepVector);

    METVector.SetPtEtaPhiM(tree->MET_pt_,
			   0.,
			   tree->MET_phi_,
			   0.);
	
    metZ.SetMET(METVector);

    //Calculate transverse mass variables
    //W transverse mass		

    _WtransMass = TMath::Sqrt(2*lepVector.Pt()*tree->MET_pt_*( 1.0 - TMath::Cos( lepVector.DeltaPhi(METVector))));


    // TLorentzVector tempLep;
    // tempLep.SetPtEtaPhiM(lepVector.Pt(),
    // 			 lepVector.Eta(),
    // 			 lepVector.Phi(),
    // 			 0.1056);

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

	if (tree->nLHEScaleWeight_==44){
	    _genScaleSystWeights.push_back(tree->LHEScaleWeight_[0]);
	    _genScaleSystWeights.push_back(tree->LHEScaleWeight_[5]);
	    _genScaleSystWeights.push_back(tree->LHEScaleWeight_[15]);
	    _genScaleSystWeights.push_back(tree->LHEScaleWeight_[24]);
	    _genScaleSystWeights.push_back(tree->LHEScaleWeight_[34]);
	    _genScaleSystWeights.push_back(tree->LHEScaleWeight_[39]);

	    _q2weight_Up = *max_element(_genScaleSystWeights.begin(), _genScaleSystWeights.end());
	    _q2weight_Do = *min_element(_genScaleSystWeights.begin(), _genScaleSystWeights.end());
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

	_ISRweight_Up = 1.;
	_ISRweight_Do = 1.;

	_FSRweight_Up = 1.;
	_FSRweight_Do = 1.;
	
	if (tree->nPSWeight_==4){
	    _ISRweight_Up = tree->PSWeight_[2] * tree->LHEWeight_originalXWGTUP_ / tree->genWeight_;
	    _ISRweight_Do = tree->PSWeight_[0] * tree->LHEWeight_originalXWGTUP_ / tree->genWeight_;

	    _FSRweight_Up = tree->PSWeight_[3] * tree->LHEWeight_originalXWGTUP_ / tree->genWeight_;
	    _FSRweight_Do = tree->PSWeight_[0] * tree->LHEWeight_originalXWGTUP_ / tree->genWeight_;
	}

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
    }

    for (int i_genJet = 0; i_genJet < _nGenJet; i_genJet++){
	_genJetPt.push_back(tree->GenJet_pt_[i_genJet]);
	_genJetEta.push_back(tree->GenJet_eta_[i_genJet]);
	_genJetPhi.push_back(tree->GenJet_phi_[i_genJet]);
	_genJetMass.push_back(tree->GenJet_mass_[i_genJet]);
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
    	if(tree->GenPart_pdgId_[mcInd]==6  && tree->GenPart_statusFlags_[mcInd]>>13&1) toppt = tree->GenPart_pt_[mcInd];
    	if(tree->GenPart_pdgId_[mcInd]==-6 && tree->GenPart_statusFlags_[mcInd]>>13&1) antitoppt = tree->GenPart_pt_[mcInd];
    }
    if(toppt > 0.001 && antitoppt > 0.001)
	weight = sqrt( SFtop(toppt) * SFtop(antitoppt) );
    
    //This has been changed, the new prescription is to not use the top pt reweighting, and the syst is using it
    return weight;
    
}

void makeAnalysisNtuple::loadBtagEff(string sampleName, string year){
    std::string fName = "BtagSF/efficiencies_"+year+".root";
    if (sampleName=="Test" || sampleName=="TestAll"){
	sampleName = "TTGamma_SingleLept";
    }
    std::string leffName = sampleName+"_"+year+"_l_efficiency";
    std::string ceffName = sampleName+"_"+year+"_c_efficiency";
    std::string beffName = sampleName+"_"+year+"_b_efficiency";

    TFile* inputFile = TFile::Open(fName.c_str(),"read");
    l_eff = (TH2D*) inputFile->Get(leffName.c_str());
    c_eff = (TH2D*) inputFile->Get(ceffName.c_str());
    b_eff = (TH2D*) inputFile->Get(beffName.c_str());
}				   

float makeAnalysisNtuple::getBtagSF_1a(string sysType, BTagCalibrationReader reader){

    double weight = 1.0;

    double jetPt;
    double jetEta;
    double jetBtag;
    int jetFlavor;
    double SFb;
    double Eff;

    double pMC=1;
    double pData=1;
	
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

    for(std::vector<int>::const_iterator jetInd = selector->Jets.begin(); jetInd != selector->Jets.end(); jetInd++){
	jetPt = tree->jetPt_[*jetInd];
	jetEta = fabs(tree->jetEta_[*jetInd]);
	jetFlavor = abs(tree->jetHadFlvr_[*jetInd]);
	jetBtag = tree->jetBtagDeepB_[*jetInd];

	if (jetFlavor == 5){
	    SFb = reader.eval_auto_bounds(b_sysType, BTagEntry::FLAV_B, jetEta, jetPt); 
	    int xbin = b_eff->GetXaxis()->FindBin(jetPt);
	    int ybin = b_eff->GetYaxis()->FindBin(abs(jetEta));
	    Eff = b_eff->GetBinContent(xbin,ybin);
	}
	else if(jetFlavor == 4){
	    SFb = reader.eval_auto_bounds(b_sysType, BTagEntry::FLAV_C, jetEta, jetPt); 
	    int xbin = c_eff->GetXaxis()->FindBin(jetPt);
	    int ybin = c_eff->GetYaxis()->FindBin(abs(jetEta));
	    Eff = c_eff->GetBinContent(xbin,ybin);
	}
	else {
	    SFb = reader.eval_auto_bounds(l_sysType, BTagEntry::FLAV_UDSG, jetEta, jetPt); 
	    int xbin = l_eff->GetXaxis()->FindBin(jetPt);
	    int ybin = l_eff->GetYaxis()->FindBin(abs(jetEta));
	    Eff = l_eff->GetBinContent(xbin,ybin);
	}

	if (jetBtag>selector->btag_cut_DeepCSV){
	    pMC *= Eff;
	    pData *= Eff*SFb;
	} else {
	    pMC *= 1. - Eff;
	    pData *= 1. - (Eff*SFb);
	}

    }

    //    weight = pData/pMC;
    if (pMC==0){
	//      cout << "Inf weight" << endl;
	//	cout << pData << " / " << pMC << endl;
	weight = 0.;
    } else {
	weight = pData/pMC;
    }
    return weight;

}


vector<float> makeAnalysisNtuple::getBtagSF_1c(string sysType, BTagCalibrationReader reader, vector<float> &btagSF){

    // Saving weights w(0|n), w(1|n), w(2|n)
    vector<float> btagWeights;

    double weight0tag = 1.0; 		//w(0|n)
    double weight1tag = 0.0;		//w(1|n)

    double jetPt;
    double jetEta;
    int jetFlavor;
    double SFb;
	
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
	jetPt = tree->jetPt_[*bjetInd];
	jetEta = fabs(tree->jetEta_[*bjetInd]);
	jetFlavor = abs(tree->jetHadFlvr_[*bjetInd]);
		
	if (jetFlavor == 5) SFb = reader.eval_auto_bounds(b_sysType, BTagEntry::FLAV_B, jetEta, jetPt); 
	else if(jetFlavor == 4) SFb = reader.eval_auto_bounds(b_sysType, BTagEntry::FLAV_C, jetEta, jetPt); 
	else {
	    SFb = reader.eval_auto_bounds(l_sysType, BTagEntry::FLAV_UDSG, jetEta, jetPt); 
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

    Int_t bitMap = tree->phoVidWPBitmap_[phoInd];

    vector<bool> cuts = parsePhotonVIDCuts(bitMap, 2);

    return cuts;

}

vector<bool> makeAnalysisNtuple::passPhoTightID(int phoInd){

    Int_t bitMap = tree->phoVidWPBitmap_[phoInd];

    vector<bool> cuts = parsePhotonVIDCuts(bitMap, 3);

    return cuts;

}



//This is defined in OverlapRemoval.cpp
double minGenDr(int myInd, const EventTree* tree);


//void makeAnalysisNtuple::findPhotonCategory(int phoInd, EventTree* tree, bool* genuine, bool *misIDele, bool *hadronicphoton, bool *hadronicfake){ // to use our own phoGenMatch
void makeAnalysisNtuple::findPhotonCategory(int mcMatchInd, EventTree* tree, bool* genuine, bool *misIDele, bool *hadronicphoton, bool *hadronicfake){ // to use official phoGenMatch

	*genuine        = false;
	*misIDele       = false;
	*hadronicphoton = false;
	*hadronicfake   = false;

//	int mcMatchInd = findPhotonGenMatch( phoInd, tree); //to use our own phoGenMatch 
	       
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

	// bool parentagePass = (fabs(tree->mcMomPID->at(mcMatchInd))<37 || tree->mcMomPID->at(mcMatchInd) == -999);

	if (mcMatchPDGID==22){
	    if (parentagePass){ 
		*genuine = true;
	    }
	    else {
		*hadronicphoton = true;
	    }
	}
	else if ( abs(mcMatchPDGID ) == 11 ) {
	    *misIDele = true;
	} 
	else {
	    *hadronicfake = true;
	}
	

}

//our own pho Gen Match code
			
 int makeAnalysisNtuple::findPhotonGenMatch(int phoInd, EventTree* tree){

 	double minDR = 999.;
 	int matchInd = -1;

         // TODO needs to be reimplemented with NANOAOD                                                                                                      
 	 for(int mcInd=0; mcInd<tree->nGenPart_; ++mcInd){
 	 	if (tree->GenPart_status_[mcInd] == 1 || tree->GenPart_status_[mcInd] == 71){ 
 	 		double dRValue = dR(tree->GenPart_eta_[mcInd],tree->GenPart_phi_[mcInd],tree->phoEta_[phoInd],tree->phoPhi_[phoInd]);
	 		if (dRValue < minDR){
 	 			if ( (fabs(tree->phoEt_[phoInd] - tree->GenPart_pt_[mcInd]) / tree->GenPart_pt_[mcInd]) < 0.5 ){
 					minDR = dRValue;
 					matchInd = mcInd;
 				}
 			}
 		}
	}

 	 if (minDR > 0.3){	matchInd = -1.; }  //Only consider matches with dR < 0.1

 	return matchInd;
 }




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

  makeAnalysisNtuple(ac, av);


  return 0;
}
