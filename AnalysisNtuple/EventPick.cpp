#include"EventPick.h"
#include <iostream> 
#include <iomanip>


//double secondMinDr(int myInd, const EventTree* tree);

EventPick::EventPick(std::string titleIn){
	title = titleIn;
	year = "2016";
	saveCutflows = false;

	printEvent = -1;

	cutFlow_ele = new TH1D("cut_flow_ele","cut flow e+jets",15,-0.5,14.5);
	cutFlow_ele->SetDirectory(0);
	set_cutflow_labels_ele(cutFlow_ele); 

	cutFlow_mu = new TH1D("cut_flow_mu","cut flow mu+jets",15,-0.5,14.5);
	cutFlow_mu->SetDirectory(0);
	set_cutflow_labels_mu(cutFlow_mu); 
	
	cutFlowWeight_ele = new TH1D("cut_flow_weight_ele","cut flow with PU weight e+jets",15,-0.5,14.5);
	cutFlowWeight_ele->SetDirectory(0);
	set_cutflow_labels_ele(cutFlowWeight_ele);

	cutFlowWeight_mu = new TH1D("cut_flow_weight_mu","cut flow with PU weight mu+jets",15,-0.5,14.5);
	cutFlowWeight_mu->SetDirectory(0);
	set_cutflow_labels_mu(cutFlowWeight_mu);




	// Cut levels
	Nmu_eq = 1;
	Nele_eq = 1;
	NlooseMuVeto_le = 0;
	NlooseEleVeto_le = 0;


	// These dR cuts are all done at selection level now
	// assign cut values
	//	veto_jet_dR = 0.1;
	// veto_lep_jet_dR = 0.4;
	// veto_pho_jet_dR = 0.7;
	// veto_pho_lep_dR = 0.7;

	MET_cut = 0.0;
	no_trigger = false;
	
	skimEle = false;
	skimMu = false;

	Njet_ge = 3;
	SkimNjet_ge = 2;

	NBjet_ge = 1;
	SkimNBjet_ge = 1;
	Nlep_eq = 1;

	ZeroBExclusive = false;

	Npho_ge = 1;
	NlooseMuVeto_le = 0;
	NlooseEleVeto_le = 0;

}

EventPick::~EventPick(){
}

void EventPick::process_event(EventTree* tree, Selector* selector, double weight){

	//	clear_vectors();
	passSkim = false;
	passPresel_ele = false;
	passPresel_mu = false;
	passAll_ele = false;
	passAll_mu = false;

	if (tree->event_==printEvent){
	    cout << "Found Event Number " << printEvent << endl;
	}

	bool Pass_trigger_mu  = false;
	bool Pass_trigger_ele = false;

	if (year=="2016") {
	    Pass_trigger_mu = (tree->HLT_IsoMu24_ || tree->HLT_IsoTkMu24_) || no_trigger;
	    Pass_trigger_ele = tree->HLT_Ele32_eta2p1_WPTight_Gsf_ || no_trigger;
	}
	if (year=="2017"){
	    Pass_trigger_mu = (tree->HLT_IsoMu24_ || tree->HLT_IsoTkMu24_ || tree->HLT_IsoMu24_eta2p1_ || tree->HLT_IsoMu27_) || no_trigger;
	    Pass_trigger_ele = tree->HLT_Ele32_WPTight_Gsf_L1DoubleEG_ || no_trigger;
	}
	if (year=="2018"){
	    Pass_trigger_mu = (tree->HLT_IsoMu24_) || no_trigger;
	    Pass_trigger_ele = tree->HLT_Ele32_WPTight_Gsf_ || no_trigger;
	}

	if (saveCutflows) {
		cutFlow_ele->Fill(0.0); // Input events
		cutFlow_mu->Fill(0.0); // Input events
		cutFlowWeight_ele->Fill(0.0,weight);
		cutFlowWeight_mu->Fill(0.0,weight);
	}

	if (tree->event_==printEvent){
	    cout << "TriggerMu "<< Pass_trigger_mu << endl;
	    cout << "TriggerEle "<< Pass_trigger_ele << endl;
	}


	passPresel_mu  = true;
	passPresel_ele = true;
	//	cout << "-------" << endl;


        bool isPVGood = (tree->pvNDOF_>4 && 
                         sqrt(tree->pvX_ * tree->pvX_ + tree->pvY_ * tree->pvY_)<2. &&
                         abs(tree->pvZ_) < 24.);

	if (tree->event_==printEvent){
	    cout << "PV "<< isPVGood << endl;
	    if (!isPVGood){
		cout << "    ndof="<<tree->pvNDOF_ << "   (>4)" << endl;
		cout << "    pX="<<tree->pvX_ <<  "   (<2)" << endl;
		cout << "    pY="<<tree->pvY_ <<  "   (<2)" << endl;
		cout << "    pZ="<<tree->pvZ_ <<  "   (<2)" << endl;
	    }
	}

	// Cut events that fail ele trigger
	if( passPresel_mu &&  Pass_trigger_mu) { if (saveCutflows) {cutFlow_mu->Fill(1); cutFlowWeight_mu->Fill(1,weight); } }
	else { passPresel_mu = false;}
	if( passPresel_mu && isPVGood) { if (saveCutflows) {cutFlow_mu->Fill(2); cutFlowWeight_mu->Fill(2,weight); } }
	else { passPresel_mu = false;}

	// Cut events that fail ele trigger
	if( passPresel_ele &&  Pass_trigger_ele) { if (saveCutflows) {cutFlow_ele->Fill(1); cutFlowWeight_ele->Fill(1,weight);}}
	else { passPresel_ele = false;}
	if( passPresel_ele && isPVGood) { if (saveCutflows) {cutFlow_ele->Fill(2); cutFlowWeight_ele->Fill(2,weight);} }
	else { passPresel_ele = false; }


	if ( passPresel_ele || passPresel_mu ) {
          selector->process_objects(tree);
	}
	else {
          return;
	}


	if (tree->event_==printEvent){
	    cout << "Muons "<< selector->Muons.size() << endl;
	    cout << "  MuonsLoose "<< selector->MuonsLoose.size() << endl;
	    cout << "Electrons "<< selector->Electrons.size() << endl;
	    cout << "  ElectronsLoose "<< selector->ElectronsLoose.size() << endl;
	    cout << "Jets "<< selector->Jets.size() << endl;
	    cout << "BJets "<< selector->bJets.size() << endl;
	}

	// Cut on events with ==1 muon, no loose muons, no loose or tight electrons
	if( passPresel_mu && selector->Muons.size() == Nmu_eq){
            if (Nmu_eq==2) { 
                int mu1 = selector->Muons.at(0); 
                int mu2 = selector->Muons.at(1);
                if(tree->muCharge_[mu1]*tree->muCharge_[mu2] ==1){
                    passPresel_mu = false;
                }
            }
            if (saveCutflows){cutFlow_mu->Fill(3); cutFlowWeight_mu->Fill(3,weight); } 
	}
	else { passPresel_mu = false;}

	if( passPresel_mu && selector->MuonsLoose.size() <=  NlooseMuVeto_le ) { if (saveCutflows) {cutFlow_mu->Fill(4); cutFlowWeight_mu->Fill(4,weight); } }
	else { passPresel_mu = false;}
	if( passPresel_mu && (selector->ElectronsLoose.size() + selector->Electrons.size() ) <=  NlooseEleVeto_le ) {if (saveCutflows) {cutFlow_mu->Fill(5); cutFlowWeight_mu->Fill(5,weight);} }
	else { passPresel_mu = false;}

	// Cut on events with ==1 muon, no loose muons, no loose or tight electrons
	if( passPresel_ele && selector->Electrons.size() == Nele_eq) { 
            if (Nele_eq==2) {
                int ele1 = selector->Electrons.at(0);
                int ele2 = selector->Electrons.at(1);
                if((tree->eleCharge_[ele1])*(tree->eleCharge_[ele2]) == 1){
                  passPresel_ele = false;
                }
            }		
            if (saveCutflows) {cutFlow_ele->Fill(3); cutFlowWeight_ele->Fill(3,weight);}
	}

	else { passPresel_ele = false;}
	if( passPresel_ele && selector->ElectronsLoose.size() <=  NlooseEleVeto_le ) { if (saveCutflows) {cutFlow_ele->Fill(4); cutFlowWeight_ele->Fill(4,weight);}}
	else { passPresel_ele = false;}
	if( passPresel_ele && (selector->MuonsLoose.size() + selector->Muons.size() ) <=  NlooseMuVeto_le ) { if (saveCutflows) {cutFlow_ele->Fill(5); cutFlowWeight_ele->Fill(5,weight);}}
	else { passPresel_ele = false;}

	// split skim into ele and mu
	if ( (skimEle && passPresel_ele) || (skimMu && passPresel_mu) && selector->Jets.size() >= SkimNjet_ge && selector->bJets.size() >= SkimNBjet_ge ){ passSkim = true; }




	// NJet cuts for electrons
	// Implemented in this way (with a loop) to check for numbers failing each level of cut < Njet cut, and filling cutflow histo
	// cutflow histo will not be filled for bins where the cut is > Njet_ge (ex, if cut is at 3, Njets>=4 bin is left empty)
	for (int ijetCut = 1; ijetCut <= Njet_ge; ijetCut++){
          if(passPresel_ele && selector->Jets.size() >= ijetCut ) { if (saveCutflows) {cutFlow_ele->Fill(5+ijetCut); cutFlowWeight_ele->Fill(5+ijetCut,weight);}}
          else passPresel_ele = false;
	}

	// Nbtag cuts for electrons
	if (!ZeroBExclusive){
          for (int ibjetCut = 1; ibjetCut <= NBjet_ge; ibjetCut++){
            if(passPresel_ele && selector->bJets.size() >= ibjetCut ) { if (saveCutflows) {cutFlow_ele->Fill(9+ibjetCut); cutFlowWeight_ele->Fill(9+ibjetCut,weight);}}
            else passPresel_ele = false;
          }
	} else {
          if(passPresel_ele && selector->bJets.size() !=0) passPresel_ele = false;
	}
        
        
	// MET cut for electrons
	if(passPresel_ele && tree->MET_pt_ >= MET_cut) { if (saveCutflows) {cutFlow_ele->Fill(13); cutFlowWeight_ele->Fill(13,weight);}}
	else passPresel_ele = false;

	// Photon cut for electrons
	if(passPresel_ele && selector->Photons.size() >= 1) {  if (saveCutflows) {cutFlow_ele->Fill(14); cutFlowWeight_ele->Fill(14,weight); passAll_ele = true;}}
	else passAll_ele = false ; 



	if (tree->event_==printEvent){
	    cout << "PassLepMu  "<< passPresel_mu << endl;
	    cout << "PassLepEle "<< passPresel_ele << endl;
	}

	// NJet cuts for muons
	// Implemented in this way (with a loop) to check for numbers failing each level of cut < Njet cut, and filling cutflow histo
	// cutflow histo will not be filled for bins where the cut is > Njet_ge (ex, if cut is at 3, Njet>=4 bin is left empty)
	for (int ijetCut = 1; ijetCut <= Njet_ge; ijetCut++){
          if(passPresel_mu && selector->Jets.size() >= ijetCut ) { if (saveCutflows) {cutFlow_mu->Fill(5+ijetCut); cutFlowWeight_mu->Fill(5+ijetCut,weight);}}
          else passPresel_mu = false;
	}

	if (tree->event_==printEvent){
	    cout << "PassJetMu  "<< passPresel_mu << endl;
	    cout << "PassJetEle "<< passPresel_ele << endl;
	}


	// Nbtag cuts for muons
	if (!ZeroBExclusive){
          for (int ibjetCut = 1; ibjetCut <= NBjet_ge; ibjetCut++){
            if(passPresel_mu && selector->bJets.size() >= ibjetCut ) { if (saveCutflows) {cutFlow_mu->Fill(9+ibjetCut); cutFlowWeight_mu->Fill(9+ibjetCut,weight);}}
            else passPresel_mu = false;
          }
	} else {
          if(passPresel_mu && selector->bJets.size() !=0) passPresel_mu = false;
	}

	if (tree->event_==printEvent){
	    cout << "PassBMu  "<< passPresel_mu << endl;
	    cout << "PassBEle "<< passPresel_ele << endl;

	    exit (EXIT_FAILURE);

	}


	// MET cut for muons
	if(passPresel_mu && tree->MET_pt_ >= MET_cut) { if (saveCutflows) {cutFlow_mu->Fill(13); cutFlowWeight_mu->Fill(13,weight);}}
	else passPresel_mu = false;

	// Photon cut for muons
	if(passPresel_mu && selector->Photons.size() >= Npho_ge) { if (saveCutflows) {cutFlow_mu->Fill(14); cutFlowWeight_mu->Fill(14,weight); passAll_mu = true;}}
	else passAll_mu = false ; 
	
}

void EventPick::print_cutflow_mu(TH1D* _cutflow){
	std::cout << "Cut-Flow for the event selector: " << title << std::endl;
	std::cout << "Input Events :                " << _cutflow->GetBinContent(1) << std::endl;
	std::cout << "Passing Trigger               " << _cutflow->GetBinContent(2) << std::endl;
	std::cout << "Has Good Vtx               " << _cutflow->GetBinContent(3) << std::endl;
	std::cout << "Events with 1 muon     " << _cutflow->GetBinContent(4) << std::endl;
	std::cout << "Events with no loose muons " << _cutflow->GetBinContent(5) << std::endl;
	std::cout << "Events with no electrons " << _cutflow->GetBinContent(6) << std::endl;
	std::cout << "Events with >= " << 1 << " jets        " << _cutflow->GetBinContent(7) << std::endl;
	std::cout << "Events with >= " << 2 << " jets        " << _cutflow->GetBinContent(8) << std::endl;
 	std::cout << "Events with >= " << 3 << " jets     " << _cutflow->GetBinContent(9) << std::endl;
	std::cout << "Events with >= " << 4 << " jets "<< _cutflow->GetBinContent(10) << std::endl;
	std::cout << "Events with >= " << 1 <<     " bjets "<< _cutflow->GetBinContent(11) << std::endl;
	std::cout << "Events with >= " << 2 << " bjets       " << _cutflow->GetBinContent(12) << std::endl;
	std::cout << "Events passing MET cut       " << _cutflow->GetBinContent(14) << std::endl;
	std::cout << "Events with >= 1 photon      " << _cutflow->GetBinContent(15) << std::endl;
	std::cout << std::endl;
}

void EventPick::print_cutflow_ele(TH1D* _cutflow){
	std::cout << "Cut-Flow for the event selector: " << title << std::endl;
	std::cout << "Input Events :                " << _cutflow->GetBinContent(1) << std::endl;
	std::cout << "Passing Trigger               " << _cutflow->GetBinContent(2) << std::endl;
	std::cout << "Has Good Vtx               " << _cutflow->GetBinContent(3) << std::endl;
	std::cout << "Events with 1 electron     " << _cutflow->GetBinContent(4) << std::endl;
	std::cout << "Events with no loose electrons " << _cutflow->GetBinContent(5) << std::endl;
	std::cout << "Events with no muons " << _cutflow->GetBinContent(6) << std::endl;
	std::cout << "Events with >= " << 1 << " jets        " << _cutflow->GetBinContent(7) << std::endl;
	std::cout << "Events with >= " << 2 << " jets        " << _cutflow->GetBinContent(8) << std::endl;
 	std::cout << "Events with >= " << 3 << " jets     " << _cutflow->GetBinContent(9) << std::endl;
	std::cout << "Events with >= " << 4 << " jets "<< _cutflow->GetBinContent(10) << std::endl;
	std::cout << "Events with >= " << 1 <<     " bjets "<< _cutflow->GetBinContent(11) << std::endl;
	std::cout << "Events with >= " << 2 << " bjets       " << _cutflow->GetBinContent(12) << std::endl;
	std::cout << "Events passing MET cut       " << _cutflow->GetBinContent(14) << std::endl;
	std::cout << "Events with >= 1 photon      " << _cutflow->GetBinContent(15) << std::endl;
	std::cout << std::endl;
}

void EventPick::set_cutflow_labels_mu(TH1D* hist){
	hist->GetXaxis()->SetBinLabel(1,"Input");
	hist->GetXaxis()->SetBinLabel(2,"Trigger");
	hist->GetXaxis()->SetBinLabel(3,"Good Vtx");
	hist->GetXaxis()->SetBinLabel(4,"1 Muons");
	hist->GetXaxis()->SetBinLabel(5,"No Loose Muons");
 	hist->GetXaxis()->SetBinLabel(6,"Veto Electrons");
	hist->GetXaxis()->SetBinLabel(7,">=1 jet");
	hist->GetXaxis()->SetBinLabel(8,">=2 jets");
	hist->GetXaxis()->SetBinLabel(9,">=3 jets");
	hist->GetXaxis()->SetBinLabel(10,">=4 jets");
	hist->GetXaxis()->SetBinLabel(11,">=1 b-tags");
	hist->GetXaxis()->SetBinLabel(12,">=2 b-tags");
	hist->GetXaxis()->SetBinLabel(13,"MET Cut");
	hist->GetXaxis()->SetBinLabel(14,"Photon");
}

void EventPick::set_cutflow_labels_ele(TH1D* hist){
	hist->GetXaxis()->SetBinLabel(1,"Input");
	hist->GetXaxis()->SetBinLabel(2,"Trigger");
	hist->GetXaxis()->SetBinLabel(3,"Good Vtx");
	hist->GetXaxis()->SetBinLabel(4,"1 Electrons");
	hist->GetXaxis()->SetBinLabel(5,"No Loose Electrons");
 	hist->GetXaxis()->SetBinLabel(6,"Veto Muons");
	hist->GetXaxis()->SetBinLabel(7,">=1 jet");
	hist->GetXaxis()->SetBinLabel(8,">=2 jets");
	hist->GetXaxis()->SetBinLabel(9,">=3 jets");
	hist->GetXaxis()->SetBinLabel(10,">=4 jets");
	hist->GetXaxis()->SetBinLabel(11,">=1 b-tags");
	hist->GetXaxis()->SetBinLabel(12,">=2 b-tags");
	hist->GetXaxis()->SetBinLabel(13,"MET Cut");
	hist->GetXaxis()->SetBinLabel(14,"Photon");
}

// void EventPick::clear_vectors(){
// 	Electrons.clear();
// 	ElectronsLoose.clear();
// 	ElectronsMedium.clear();
// 	Muons.clear();
// 	MuonsLoose.clear();
// 	Jets.clear();
// 	bJets.clear();
// 	Photons.clear();
// 	LoosePhotons.clear();
// 	PhotonsPresel.clear();
// 	PhoPassChHadIso.clear();
// 	PhoPassPhoIso.clear();
// 	PhoPassSih.clear();
// }

// double EventPick::dR_jet_ele(int jetInd, int eleInd){
// 	return dR(tree->jetEta_->at(jetInd), tree->jetPhi_->at(jetInd), tree->eleSCEta_->at(eleInd), tree->elePhi_->at(eleInd));
// }
// double EventPick::dR_jet_mu(int jetInd, int muInd){
// 	return dR(tree->jetEta_->at(jetInd), tree->jetPhi_->at(jetInd), tree->muEta_->at(muInd), tree->muPhi_->at(muInd));
// }
// double EventPick::dR_jet_pho(int jetInd, int phoInd){
// 	return dR(tree->jetEta_->at(jetInd), tree->jetPhi_->at(jetInd), tree->phoSCEta_->at(phoInd), tree->phoPhi_->at(phoInd));
// }
// double EventPick::dR_ele_pho(int eleInd, int phoInd){
// 	return dR(tree->eleSCEta_->at(eleInd), tree->elePhi_->at(eleInd), tree->phoSCEta_->at(phoInd), tree->phoPhi_->at(phoInd));
// }
// double EventPick::dR_mu_pho(int muInd, int phoInd){
// 	return dR(tree->muEta_->at(muInd), tree->muPhi_->at(muInd), tree->phoSCEta_->at(phoInd), tree->phoPhi_->at(phoInd));
// }

