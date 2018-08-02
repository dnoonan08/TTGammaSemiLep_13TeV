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


// bool overlapRemovalTT(EventTree* tree);
// bool overlapRemovalWZ(EventTree* tree);
// bool overlapRemoval_Tchannel(EventTree* tree);


int main(int ac, char** av){
	if(ac < 4){
		std::cout << "usage: ./makeSkim channel outputFileName inputFile[s]" << std::endl;
		return -1;
	}
	// input: dealing with TTree first
	bool isMC = true;
	EventTree* tree = new EventTree(ac-3, av+3);
	Selector* selector = new Selector();

	selector->smearJetPt = false;

	selector->smearEle = false;
	selector->smearPho = false;

	selector->scaleEle = false;
	selector->scalePho = false;

	EventPick* evtPick = new EventPick("nominal");
	evtPick->MET_cut = -1.0;	
	std::string outDirName(av[2]);
	// antiselection for QCD fit
	// if( outDirName.find("QCD") != std::string::npos){
	// 	std::cout << "muon antiselection is on" << std::endl;
	// 	selector->mu_RelIso_range[0] = 0.25; 
	// 	selector->mu_RelIso_range[1] = 1.;
	// 	selector->mu_Iso_invert = true;
	// }

	// if( outDirName.find("TTgamma") != std::string::npos){
	// 	std::cout << "Skipping Trigger Selection for TTGamma" << std::endl;
	// 	evtPick->no_trigger = true;
	// }

	// reduce the pt cuts by 10% in the skim, so that energy corrections can still be done on same skims
	selector->jet_Pt_cut = 27.;
	selector->ele_Pt_cut = 32.;
	selector->mu_Pt_cut = 27.;

	// remove the jet dR cuts, so we can play with these levels later on
	selector->veto_lep_jet_dR = -1;
	selector->veto_pho_jet_dR = -1;

	evtPick->SkimNjet_ge = 2;
	evtPick->SkimNBjet_ge = 0;
	std::string channel(av[1]);

	if (channel=="ele"){
		evtPick->skimEle = true;
	} else if (channel=="mu"){
		evtPick->skimMu = true;
	} else if (channel=="dimu"){
		evtPick->skimMu = true;
		evtPick->Nmu_eq = 2;
	} else if (channel=="diele"){
		evtPick->skimEle=true;
		evtPick->Nele_eq = 2;
	} else if (channel=="qcdele"){
		evtPick->skimEle=true;
		evtPick->Nele_eq = 1;
		selector->QCDselect = true;
	} else if (channel=="qcdmu"){
		evtPick->skimMu=true;
		evtPick->Nmu_eq = 1;
		selector->QCDselect = true;
	}else if (channel=="qcdDimu"){
		evtPick->skimMu=true;
		evtPick->Nele_eq = 2;
		selector->QCDselect = true;
	}else if (channel=="qcdDiele"){
		evtPick->skimEle=true;
		evtPick->Nele_eq = 2;
		selector->QCDselect = true;
	}else {
		cout << av[1] << endl;
		cout << (av[1]=="ele") << endl;
		cout << (channel=="ele") << endl;
		cout << "please specify either ele or mu for the skim channel (or diele/dimu)" << endl;
		return -1;		
	}

	// TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",1000,500);
	// c1->SetFillColor(42);
	// c1->SetGrid();

	// TCanvas *c2 = new TCanvas("c2","A Simple Graph Example",1000,500);
	// c2->SetFillColor(42);
	// c2->SetGrid();
	

	// TCanvas *c3 = new TCanvas("c3","A Simple Graph Example",1000,500);
	// c3->SetFillColor(42);
	// c3->SetGrid();
	
	//TFile *theFile = TFile::Open("root://cmsxrootd.fnal.gov//store/user/troy2012/rootFile.root");

	std::clock_t startClock;
	double duration;
	startClock = clock();

	TFile* outFile = TFile::Open( av[2] ,"RECREATE" );
	TDirectory* ggDir = outFile->mkdir("ggNtuplizer","ggNtuplizer");
	ggDir->cd();
	TTree* newTree = tree->chain->CloneTree(0);

	Long64_t nEntr = tree->GetEntries();

	if( outDirName.find("Test") != std::string::npos || outDirName.find("test") != std::string::npos || outDirName.find("TEST") != std::string::npos){
		if (selector->QCDselect){
			std::cout << "-------------------------------------------------------------------------" << std::endl;
			std::cout << "Since this is a Test (based on output name) only running on 100,000 events" << std::endl;
			std::cout << "-------------------------------------------------------------------------" << std::endl;
			nEntr = 100000;
		}
		else{
			std::cout << "-------------------------------------------------------------------------" << std::endl;
			std::cout << "Since this is a Test (based on output name) only running on 10,000 events" << std::endl;
			std::cout << "-------------------------------------------------------------------------" << std::endl;
			nEntr = 100000;
		}
	}



	int dumpFreq = 100;
	if (nEntr >5000)   { dumpFreq = 1000; }
	if (nEntr >50000)  { dumpFreq = 10000; }
	if (nEntr >500000) { dumpFreq = 100000; }
	if (nEntr >5000000){ dumpFreq = 1000000; }
	

	for(Long64_t entry= 0; entry < nEntr; entry++){
	//	for(Long64_t entry= 0; entry < 300; entry++){ 	
		if(entry%dumpFreq == 0) {
			duration =  ( clock() - startClock ) / (double) CLOCKS_PER_SEC;
			std::cout << "processing entry " << entry << " out of " << nEntr << " : " << duration << " seconds since last progress" << std::endl;
			startClock = clock();
		}
		tree->GetEntry(entry);

		isMC = !(tree->isData_);


		//selector->process_objects(tree);
		selector->clear_vectors();
		                              
		evtPick->process_event(tree,selector);

		if( evtPick->passSkim ){
			newTree->Fill();
		}
		
	        //std::cout << "finished with entry " <<  entry << std::endl;	
	}

	newTree->Write();

	std::map<std::string, TH1F*> histMap;
	// copy histograms
	for(int fileInd = 3; fileInd < ac; ++fileInd){
		TFile* tempFile = TFile::Open(av[fileInd], "READ");
		TIter next(((TDirectory*)tempFile->Get("ggNtuplizer"))->GetListOfKeys());
		TObject* obj;
		while ((obj = next())){
			std::string objName(obj->GetName());
			if( objName != "EventTree"){
				TH1F* hist = (TH1F*)tempFile->Get(("ggNtuplizer/"+objName).c_str());
				if( histMap.find(objName) != histMap.end() ){
					histMap[objName]->Add(hist);
				}
				else {
					hist->SetDirectory(0);
					histMap[objName] = hist;
				}
			}
		}
		tempFile->Close();
	}
	
	ggDir->cd();
	for(std::map<std::string, TH1F*>::iterator it = histMap.begin(); it!= histMap.end(); ++it){
		it->second->SetDirectory(ggDir);
		it->second->Write();
	}
	outFile->Close();

	
	return 0;
}
