#include<iostream>
#include<string>
#include"EventTree.h"
#include"Selector.h"
#include"EventPick.h"
#include<TFile.h>
#include<TTree.h>
#include<TDirectory.h>
#include<TObject.h>
#include<TH1F.h>
#include<TCanvas.h>

std::string PUfilename = "Data_2016BCDGH_Pileup.root";
std::string PUfilename_up = "Data_2016BCDGH_Pileup_scaledUp.root";
std::string PUfilename_down = "Data_2016BCDGH_Pileup_scaledDown.root";

#include"PUReweight.h"
#include "BTagCalibrationStandalone.h"
#include "ScaleFactors.h"

bool overlapRemovalTT(EventTree* tree);


int main(int ac, char** av){
	if(ac < 4){
		std::cout << "usage: ./makeCutflows sampleType outputFile inputFile[s]" << std::endl;
		return -1;
	}

	string sampleType = av[1];
	cout << sampleType << endl;

	if (std::end(allowedSampleTypes) == std::find(std::begin(allowedSampleTypes), std::end(allowedSampleTypes), sampleType)){
		cout << "This is not an allowed sample, please specify one from this list (or add to this list in the code):" << endl;
		for (int i =0; i < sizeof(allowedSampleTypes)/sizeof(allowedSampleTypes[0]); i++){
			cout << "    "<<allowedSampleTypes[i] << endl;
		}			
		return -1;
	}


	// input: dealing with TTree first
	bool isMC = true;

	PUReweight* PUweighter = new PUReweight(ac-3, av+3, PUfilename);

	EventTree* tree = new EventTree(ac-3, av+3);
	Selector* selector = new Selector();
	double _evtWeight = getEvtWeight(sampleType);



	EventPick* evtPick = new EventPick("nominal");
	// evtPick->MET_cut = 0;

	selector->looseJetID = false;

	evtPick->Njet_ge = 4;	
	evtPick->NBjet_ge = 2;	


	BTagCalibration calib("csvv2", "CSVv2_Moriond17_B_H.csv");

	BTagCalibrationReader reader(BTagEntry::OP_MEDIUM,  // operating point
								 "central");             // central sys type


	// if( outDirName.find("TTgamma") != std::string::npos){
	// 	std::cout << "Skipping Trigger Selection for TTGamma" << std::endl;
	// 	evtPick->no_trigger = true;
	// }

	// reduce the pt cuts by 10% in the skim, so that energy corrections can still be done on same skims
	// selector->jet_Pt_cut = 30.;
	// selector->ele_Pt_cut = 35.;
	// selector->mu_Pt_cut = 30.;

	//	selector->smearJetPt = false;

	Long64_t nEntr = tree->GetEntries();
	std::string outDirName(av[2]);

	int dumpFreq = 100;
	if (nEntr >5000)    { dumpFreq = 500; }
	if (nEntr >10000)   { dumpFreq = 1000; }
	if (nEntr >50000)   { dumpFreq = 5000; }
	if (nEntr >100000)  { dumpFreq = 10000; }
	if (nEntr >500000)  { dumpFreq = 50000; }
	if (nEntr >1000000) { dumpFreq = 100000; }
	if (nEntr >5000000) { dumpFreq = 500000; }
	if (nEntr >10000000){ dumpFreq = 1000000; }
	

	for(Long64_t entry= 0; entry < nEntr; entry++){
		if(entry%dumpFreq == 0) {
			std::cout << "processing entry " << entry << " out of " << nEntr << std::endl;
		}
		tree->GetEntry(entry);
		
		selector->process_objects(tree);
	   
		//
		                              
		evtPick->process_event(tree,selector);
	}

	std::cout << "e+jets cutflow" << std::endl;
	evtPick->print_cutflow_ele(evtPick->cutFlow_ele);

	std::cout << "mu+jets cutflow" << std::endl;
	evtPick->print_cutflow_mu(evtPick->cutFlow_mu);

	TFile* outputFile = TFile::Open(av[2],"RECREATE");

	outputFile->cd();
	evtPick->cutFlow_mu->Write();
	evtPick->cutFlow_ele->Write();
	outputFile->Close();


	// std::map<std::string, TH1F*> histMap;
	// // copy histograms
	// for(int fileInd = 3; fileInd < ac; ++fileInd){
	// 	TFile* tempFile = TFile::Open(av[fileInd], "READ");
	// 	TIter next(((TDirectory*)tempFile->Get("ggNtuplizer"))->GetListOfKeys());
	// 	TObject* obj;
	// 	while ((obj = next())){
	// 		std::string objName(obj->GetName());
	// 		if( objName != "EventTree"){
	// 			TH1F* hist = (TH1F*)tempFile->Get(("ggNtuplizer/"+objName).c_str());
	// 			if( histMap.find(objName) != histMap.end() ){
	// 				histMap[objName]->Add(hist);
	// 			}
	// 			else {
	// 				hist->SetDirectory(0);
	// 				histMap[objName] = hist;
	// 			}
	// 		}
	// 	}
	// 	tempFile->Close();
	// }
	
	// ggDir->cd();
	// for(std::map<std::string, TH1F*>::iterator it = histMap.begin(); it!= histMap.end(); ++it){
	// 	it->second->SetDirectory(ggDir);
	// 	it->second->Write();
	// }
	// outFile->Close();
	
	return 0;
}

double getBtagSF(EventTree* tree, EventPick* evtPick, string sysType, BTagCalibrationReader reader){
	
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


