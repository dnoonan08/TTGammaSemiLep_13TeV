#include"EventPick.h"
#include <iostream> 
#include <iomanip>


double secondMinDr(int myInd, const EventTree* tree);

EventPick::EventPick(std::string titleIn){
	title = titleIn;

	cutFlow_ele = new TH1D("cut_flow_ele","cut flow e+jets",15,-0.5,14.5);
	cutFlow_ele->SetDirectory(0);
	set_cutflow_labels(cutFlow_ele); // keep the labels close to the cuts definitions (below)
	histVector.push_back(cutFlow_ele);

	cutFlow_mu = new TH1D("cut_flow_mu","cut flow mu+jets",15,-0.5,14.5);
	cutFlow_mu->SetDirectory(0);
	set_cutflow_labels(cutFlow_mu); // keep the labels close to the cuts definitions (below)
	histVector.push_back(cutFlow_mu);
	
	cutFlowWeight_ele = new TH1D("cut_flow_weight_ele","cut flow with PU weight e+jets",15,-0.5,14.5);
	cutFlowWeight_ele->SetDirectory(0);
	set_cutflow_labels(cutFlowWeight_ele);
	histVector.push_back(cutFlowWeight_ele);

	cutFlowWeight_mu = new TH1D("cut_flow_weight_mu","cut flow with PU weight mu+jets",15,-0.5,14.5);
	cutFlowWeight_mu->SetDirectory(0);
	set_cutflow_labels(cutFlowWeight_mu);
	histVector.push_back(cutFlowWeight_mu);

	genPhoRegionWeight = new TH1D("genPhoRegionWeight","GenPhoton passing fiducial cuts: barrel 0 or endcap 1",2,-0.5,1.5);
	genPhoRegionWeight->SetDirectory(0);
	histVector.push_back(genPhoRegionWeight);

	genPhoRegionWeight_1l_2l = new TH1D("genPhoRegionWeight_1l_2l","GenPhoton passing fiducial cuts with 1 or 2 gen leptons: barrel 0 or endcap 1",2,-0.5,1.5);
	genPhoRegionWeight_1l_2l->SetDirectory(0);
	histVector.push_back(genPhoRegionWeight_1l_2l);

	genPhoRegionWeight_1fiducial = new TH1D("genPhoRegionWeight_1lfid","GenPhoton passing fiducial cuts with 1 or 2 gen leptons passing fiducial cuts: barrel 0 or endcap 1",8,-0.5,7.5);
	genPhoRegionWeight_1fiducial->GetXaxis()->SetBinLabel(1,"1 e, barrel pho");
	genPhoRegionWeight_1fiducial->GetXaxis()->SetBinLabel(2,"1 e, endcap pho");
	genPhoRegionWeight_1fiducial->GetXaxis()->SetBinLabel(3,"1 e, topSel, barrel pho");
	genPhoRegionWeight_1fiducial->GetXaxis()->SetBinLabel(4,"1 e, topSel, endcap pho");
	genPhoRegionWeight_1fiducial->GetXaxis()->SetBinLabel(5,"1 #mu, barrel pho");
	genPhoRegionWeight_1fiducial->GetXaxis()->SetBinLabel(6,"1 #mu, endcap pho");
	genPhoRegionWeight_1fiducial->GetXaxis()->SetBinLabel(7,"1 #mu, topSel, barrel pho");
	genPhoRegionWeight_1fiducial->GetXaxis()->SetBinLabel(8,"1 #mu, topSel, endcap pho");

	genPhoRegionWeight_1fiducial->SetDirectory(0);
	histVector.push_back(genPhoRegionWeight_1fiducial);

	genPhoMinDR = new TH1D("genPhoMinDR", "Min DR between gen photon and other gen particles", 100, 0., 1.);
	genPhoMinDR->SetDirectory(0);
	histVector.push_back(genPhoMinDR);



	Nmu_eq = 1;
	Nele_eq = 1;
	NlooseMuVeto_le = 0;
	NlooseEleVeto_le = 0;

	// assign cut values
	veto_jet_dR = 0.1;
	veto_lep_jet_dR = 0.4;
	veto_pho_jet_dR = 0.7;
	veto_pho_lep_dR = 0.7;
	MET_cut = 20.0;
	no_trigger = false;

	Njet_ge = 4;
	SkimNjet_ge = 3;

	NBjet_ge = 2;
	SkimNBjet_ge = 1;
	Nlep_eq = 1;

	Npho_ge = 1;
	NlooseMuVeto_le = 0;
	NlooseEleVeto_le = 0;

}

EventPick::~EventPick(){
}

void EventPick::process_event(const EventTree* inp_tree, const Selector* inp_selector, double weight){
	tree = inp_tree;
	selector = inp_selector;
	clear_vectors();
	passSkim = false;
	passPresel_ele = false;
	passPresel_mu = false;
	passAll_ele = false;
	passAll_mu = false;



	// pre-selection: top ref selection
	// copy jet and electron collections, consiering overlap of jets with electrons, loose electrons:
	// keep jets not close to electrons (veto_jet_dR)
	for(std::vector<int>::const_iterator jetInd = selector->Jets.begin(); jetInd != selector->Jets.end(); jetInd++){
		bool goodJet = true;
		
		for(std::vector<int>::const_iterator eleInd = selector->Electrons.begin(); eleInd != selector->Electrons.end(); eleInd++)
			if(dR_jet_ele(*jetInd, *eleInd) < veto_lep_jet_dR) goodJet = false;
		
		for(std::vector<int>::const_iterator muInd = selector->Muons.begin(); muInd != selector->Muons.end(); muInd++)
			if(dR_jet_mu(*jetInd, *muInd) < veto_lep_jet_dR) goodJet = false;

		if(goodJet) Jets.push_back(*jetInd);

		// take care of bJet collection
		for(std::vector<int>::const_iterator bjetInd = selector->bJets.begin(); bjetInd != selector->bJets.end(); bjetInd++)
			if(*bjetInd == *jetInd && goodJet) bJets.push_back(*bjetInd);
	}
	
	// keep electrons that are not close to jets (veto_lep_jet_dR)
	for(std::vector<int>::const_iterator eleInd = selector->Electrons.begin(); eleInd != selector->Electrons.end(); eleInd++){
		bool goodEle = true;
		if(goodEle) Electrons.push_back(*eleInd);
	}
	
	//loose electrons
	for(std::vector<int>::const_iterator eleInd = selector->ElectronsLoose.begin(); eleInd != selector->ElectronsLoose.end(); eleInd++){
		bool goodEle = true;
		if(goodEle) ElectronsLoose.push_back(*eleInd);
	}

	 //do cleaning of muons that are close to jets
	for(std::vector<int>::const_iterator muInd = selector->Muons.begin(); muInd != selector->Muons.end(); muInd++){
		bool goodMu = true;
		if(goodMu) Muons.push_back(*muInd);
	}
	
	 //photon cleaning:
	for(int phoVi = 0; phoVi < selector->PhotonsPresel.size(); phoVi++){
		bool goodPhoton = true;

		 //remove photons close to jets
	//	for(int jetInd = 0; jetInd < tree->nJet_; jetInd++){
	//		double drjp = dR_jet_pho(jetInd, selector->PhotonsPresel.at(phoVi));
	//		if(tree->jetPt_->at(jetInd) > 20 && veto_jet_dR <= drjp && drjp < veto_pho_jet_dR) goodPhoton = false;
	//	}
		// and electrons
	//	for(std::vector<int>::iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++)
	//		if(dR_ele_pho(*eleInd, selector->PhotonsPresel.at(phoVi)) < veto_pho_lep_dR) goodPhoton = false;
		// and muons too; 0.3 is dR cut between photon and anything in MadGraph 2 to 7 ttgamma  
	//	for(std::vector<int>::iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++)
	//		if(dR_mu_pho(*muInd, selector->PhotonsPresel.at(phoVi)) < 0.3) goodPhoton = false;

		if(goodPhoton){
	//		PhotonsPresel.push_back(selector->PhotonsPresel.at(phoVi));
	//		PhoPassChHadIso.push_back(selector->PhoPassChHadIso.at(phoVi));
	//		PhoPassPhoIso.push_back(selector->PhoPassPhoIso.at(phoVi));
	//		PhoPassSih.push_back(selector->PhoPassSih.at(phoVi));
	//		if(PhoPassChHadIso.back() && PhoPassPhoIso.back() && PhoPassSih.back()) 
			Photons.push_back(selector->PhotonsPresel.at(phoVi));
		}
	}

	bool Pass_trigger_mu  = ( tree->HLTEleMuX >> 19 & 1 || tree->HLTEleMuX >> 20 & 1) || no_trigger;
	bool Pass_trigger_ele = ( tree->HLTEleMuX >> 3 & 1) || no_trigger;

	cutFlow_ele->Fill(0.0); // Input events
	cutFlow_mu->Fill(0.0); // Input events
	cutFlowWeight_ele->Fill(0.0,weight);
	cutFlowWeight_mu->Fill(0.0,weight);

	passPresel_mu  = true;
	passPresel_ele = true;
	
	// Cut events that fail ele trigger
	if( passPresel_mu &&  Pass_trigger_mu) { cutFlow_mu->Fill(1); cutFlowWeight_mu->Fill(1,weight);}
	else { passPresel_mu = false;}
	if( passPresel_mu && tree->isPVGood_) {cutFlow_mu->Fill(2); cutFlowWeight_mu->Fill(2,weight);}
	else { passPresel_mu = false; }

	// Cut on events with ==1 muon, no loose muons, no loose or tight electrons
	if( passPresel_mu && Muons.size() == Nmu_eq) {cutFlow_mu->Fill(3); cutFlowWeight_mu->Fill(3,weight);}
	else { passPresel_mu = false;}
	if( passPresel_mu && selector->MuonsLoose.size() <=  NlooseMuVeto_le ) {cutFlow_mu->Fill(4); cutFlowWeight_mu->Fill(4,weight);}
	else { passPresel_mu = false;}
	if( passPresel_mu && (selector->ElectronsLoose.size() + selector->Electrons.size() ) <=  NlooseEleVeto_le ) {cutFlow_mu->Fill(5); cutFlowWeight_mu->Fill(5,weight);}
	else { passPresel_mu = false;}

	// Cut events that fail ele trigger
	if( passPresel_ele &&  Pass_trigger_ele) { cutFlow_ele->Fill(1); cutFlowWeight_ele->Fill(1,weight);}
	else { passPresel_ele = false;}
	if( passPresel_ele && tree->isPVGood_) {cutFlow_ele->Fill(2); cutFlowWeight_ele->Fill(2,weight);}
	else { passPresel_ele = false; }

	// Cut on events with ==1 muon, no loose muons, no loose or tight electrons
	if( passPresel_ele && Electrons.size() == Nele_eq) {cutFlow_ele->Fill(3); cutFlowWeight_ele->Fill(3,weight);}
	else { passPresel_ele = false;}
	if( passPresel_ele && selector->ElectronsLoose.size() <=  NlooseEleVeto_le ) {cutFlow_ele->Fill(4); cutFlowWeight_ele->Fill(4,weight);}
	else { passPresel_ele = false;}
	if( passPresel_ele && (selector->MuonsLoose.size() + selector->Muons.size() ) <=  NlooseMuVeto_le ) {cutFlow_ele->Fill(5); cutFlowWeight_ele->Fill(5,weight);}
	else { passPresel_ele = false;}


	if ( (passPresel_ele || passPresel_mu) && Jets.size() >= SkimNjet_ge && bJets.size() >= SkimNBjet_ge ){ passSkim = true; }


	// NJet cuts for electrons
	if(passPresel_ele && Jets.size() >= 1 ) {cutFlow_ele->Fill(6); cutFlowWeight_ele->Fill(6,weight);}
	else passPresel_ele = false;
	if(passPresel_ele && Jets.size() >= 2 ) {cutFlow_ele->Fill(7); cutFlowWeight_ele->Fill(7,weight);}
        else passPresel_ele = false;
	if(passPresel_ele && Jets.size() >= 3 ) {cutFlow_ele->Fill(8); cutFlowWeight_ele->Fill(8,weight);}
        else passPresel_ele = false;
	if(passPresel_ele && Jets.size() >= 4) {cutFlow_ele->Fill(9); cutFlowWeight_ele->Fill(9,weight);}
	else passPresel_ele = false;	

	// Nbtag cuts for electrons
        if ( passPresel_ele && bJets.size() >= 1) {cutFlow_ele->Fill(10); cutFlowWeight_ele->Fill(10,weight);}
        else passPresel_ele = false;
	if( passPresel_ele && bJets.size() >= 2) {cutFlow_ele->Fill(11); cutFlowWeight_ele->Fill(11,weight);}
	else passPresel_ele = false;

	// MET cut for electrons
	if(passPresel_ele && tree->pfMET_ >= MET_cut) {cutFlow_ele->Fill(13); cutFlowWeight_ele->Fill(13,weight);}
	else passPresel_ele = false;

	// Photon cut for electrons
	if(passPresel_ele && Photons.size() >= 1) { cutFlow_ele->Fill(14); cutFlowWeight_ele->Fill(14,weight); passAll_ele = true;}
	else passAll_ele = false ; 


	// NJet cuts for muons
	if(passPresel_mu && Jets.size() >= 1 ) {cutFlow_mu->Fill(6); cutFlowWeight_mu->Fill(6,weight);}
	else passPresel_mu = false;
	if(passPresel_mu && Jets.size() >= 2 ) {cutFlow_mu->Fill(7); cutFlowWeight_mu->Fill(7,weight);}
        else passPresel_mu = false;
	if(passPresel_mu && Jets.size() >= 3 ) {cutFlow_mu->Fill(8); cutFlowWeight_mu->Fill(8,weight);}
        else passPresel_mu = false;
	if(passPresel_mu && Jets.size() >= 4) {cutFlow_mu->Fill(9); cutFlowWeight_mu->Fill(9,weight);}
	else passPresel_mu = false;	

	// Nbtag cuts for muons
        if ( passPresel_mu && bJets.size() >= 1) {cutFlow_mu->Fill(10); cutFlowWeight_mu->Fill(10,weight);}
        else passPresel_mu = false;
	if( passPresel_mu && bJets.size() >= 2) {cutFlow_mu->Fill(11); cutFlowWeight_mu->Fill(11,weight);}
	else passPresel_mu = false;

	// MET cut for muons
	if(passPresel_mu && tree->pfMET_ >= MET_cut) {cutFlow_mu->Fill(13); cutFlowWeight_mu->Fill(13,weight);}
	else passPresel_mu = false;

	// Photon cut for muons
	if(passPresel_mu && Photons.size() >= 1) { cutFlow_mu->Fill(14); cutFlowWeight_mu->Fill(14,weight); passAll_mu = true;}
	else passAll_mu = false ; 
	



	// // saving information about Gen Level photons, if any
	// // Save it only if PreSelection passed
	// // Separate count for barrel and endcap (will be used separately anyway)
	
	// bool foundGenPhotonBarrel = false;
	// bool foundGenPhotonEndcap = false;
	// if(passPreSel && !(tree->isData_)){
	// 	for(int mcInd=0; mcInd<tree->nMC_; ++mcInd){
	// 		if(tree->mcPID->at(mcInd) == 22 &&
	// 		 //  (tree->mcParentage->at(mcInd)==2 || tree->mcParentage->at(mcInd)==10 || tree->mcParentage->at(mcInd)==26) &&
	// 		   tree->mcPt->at(mcInd) > selector->pho_Et_cut){		
	// 			if(secondMinDr(mcInd, tree) > 0.2){
	// 				double fabsEta = TMath::Abs(tree->mcEta->at(mcInd));
	// 				if(fabsEta < 1.4442) foundGenPhotonBarrel = true;
	// 				if( 1.566 < fabsEta && fabsEta < 2.5) foundGenPhotonEndcap = true;
	// 			}
	// 		}
	// 	}
	// }
	// if(foundGenPhotonBarrel) genPhoRegionWeight->Fill(0.0, weight);
	// if(foundGenPhotonEndcap) genPhoRegionWeight->Fill(1.0, weight);

	// int EleP = 0;
	// int EleM = 0;
	// int MuP = 0;
	// int MuM = 0;
	// int TauP = 0;
	// int TauM = 0;

	// for( int mcI = 0; mcI < tree->nMC_; ++mcI){
	//   if(abs(tree->mcMomPID->at(mcI))==24 && tree->mcParentage->at(mcI)==10){
	//     if( tree->mcPID->at(mcI) == 11 ) EleP = 1;
	//     if( tree->mcPID->at(mcI) == -11 ) EleM = 1;
	//     if( tree->mcPID->at(mcI) == 13 ) MuP = 1;
	//     if( tree->mcPID->at(mcI) == -13 ) MuM = 1;
	//     if( tree->mcPID->at(mcI) == 15) TauP = 1;
	//     if( tree->mcPID->at(mcI) == -15) TauM = 1;
	//   }
	// }
	// int nEle = EleP + EleM;
	// int nMu = MuP + MuM;
	// int nTau = TauP + TauM;
	// int nLep = nEle + nMu + nTau;

	// if (nLep == 1 || nLep == 2){
	//   if(foundGenPhotonBarrel) genPhoRegionWeight_1l_2l->Fill(0.0, weight);
	//   if(foundGenPhotonEndcap) genPhoRegionWeight_1l_2l->Fill(1.0, weight);
	// }	  

	
	// int ElePfid = 0;
	// int EleMfid = 0;
	// int MuPfid = 0;
	// int MuMfid = 0;
	// int nNufid = 0;
	// for( int mcI = 0; mcI < tree->nMC_; ++mcI){
	//   if((abs(tree->mcMomPID->at(mcI))==24 && tree->mcParentage->at(mcI)==10) || (abs(tree->mcMomPID->at(mcI))==15 && tree->mcParentage->at(mcI)==26)){		  
	//     if( tree->mcPID->at(mcI) == 11 ) {
	//       if (tree->mcPt->at(mcI) > 35 && (fabs(tree->mcEta->at(mcI)) < 2.5 && !(fabs(tree->mcEta->at(mcI)) > 1.4442 && fabs(tree->mcEta->at(mcI))<1.566))) ElePfid += 1;
	//     }
	//     if( tree->mcPID->at(mcI) == -11 ) {
	//       if (tree->mcPt->at(mcI) > 35 && (fabs(tree->mcEta->at(mcI)) < 2.5 && !(fabs(tree->mcEta->at(mcI)) > 1.4442 && fabs(tree->mcEta->at(mcI))<1.566))) EleMfid += 1;
	//     }
	//     if( tree->mcPID->at(mcI) == 13 ) {
	//       if (tree->mcPt->at(mcI) > 26 && fabs(tree->mcEta->at(mcI)) < 2.1) MuPfid += 1;
	//     }
	//     if( tree->mcPID->at(mcI) == -13 ) {
	//       if (tree->mcPt->at(mcI) > 26 && fabs(tree->mcEta->at(mcI)) < 2.1) MuMfid += 1;
	//     }
	//   }
	//   if( fabs(tree->mcPID->at(mcI)) == 12 || fabs(tree->mcPID->at(mcI)) == 14 || fabs(tree->mcPID->at(mcI)) == 16 ) {
	//     if (tree->mcPt->at(mcI) > 20) nNufid += 1;
	//   }
	// }
	// int nElefid = ElePfid + EleMfid;
	// int nMufid = MuPfid + MuMfid;
	// int nJetsfid = 0;
	// if ((nElefid + nMufid)==1 && nNufid == 1){
	//   for ( int jetI = 0; jetI < tree->nJet_; jetI++){
	//     if (tree->jetGenPt_->at(jetI) >= 30) {
	//       if ( fabs(tree->jetGenEta_->at(jetI)) < 2.4) nJetsfid += 1;
	//     }
	//   }
	// }
	

	// if (nElefid==1 && nMufid==0){
	//   if(foundGenPhotonBarrel) genPhoRegionWeight_1fiducial->Fill(0.0, weight);
	//   if(foundGenPhotonEndcap) genPhoRegionWeight_1fiducial->Fill(1.0, weight);
	//   if(nJetsfid >=3 && nNufid == 1){
	//     if (foundGenPhotonBarrel) genPhoRegionWeight_1fiducial->Fill(2.0, weight);
	//     if (foundGenPhotonEndcap) genPhoRegionWeight_1fiducial->Fill(3.0, weight);
	//   }
	// }	  
	// if (nElefid==0 && nMufid==1){
	//   if(foundGenPhotonBarrel) genPhoRegionWeight_1fiducial->Fill(4.0, weight);
	//   if(foundGenPhotonEndcap) genPhoRegionWeight_1fiducial->Fill(5.0, weight);
	//   if(nJetsfid >=3 && nNufid == 1){
	//     if (foundGenPhotonBarrel) genPhoRegionWeight_1fiducial->Fill(6.0, weight);
	//     if (foundGenPhotonEndcap) genPhoRegionWeight_1fiducial->Fill(7.0, weight);
	//   }
	// }	  

	// if(passPreSel && !(tree->isData_)){
	//   double minDR = 999.;
	//   for(int mcInd=0; mcInd<tree->nMC_; ++mcInd){
	//     if(tree->mcPID->at(mcInd) == 22){// &&
	//    //    (tree->mcParentage->at(mcInd)==2 || tree->mcParentage->at(mcInd)==10 || tree->mcParentage->at(mcInd)==26)){
	//       double dr = secondMinDr(mcInd, tree);
	//       if (dr < minDR) minDR = dr;
	//     }
	//   }
	//   genPhoMinDR->Fill(minDR, weight);
	// }

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

void EventPick::set_cutflow_labels(TH1D* hist){
	hist->GetXaxis()->SetBinLabel(1,"Input");
	hist->GetXaxis()->SetBinLabel(2,"Trigger");
	hist->GetXaxis()->SetBinLabel(3,"Good Vtx");
	hist->GetXaxis()->SetBinLabel(4,">1Mu");
	hist->GetXaxis()->SetBinLabel(5,"Loose Mu");
 	hist->GetXaxis()->SetBinLabel(6,"Veto El");
	hist->GetXaxis()->SetBinLabel(7,"1jet");
	hist->GetXaxis()->SetBinLabel(8,"2jets");
	hist->GetXaxis()->SetBinLabel(9,"3jets");
	hist->GetXaxis()->SetBinLabel(10,"4jets");
	hist->GetXaxis()->SetBinLabel(11,">2 b-tags");
        hist->GetXaxis()->SetBinLabel(12,"=2 b-tags");
        hist->GetXaxis()->SetBinLabel(13,"1Muon");
	hist->GetXaxis()->SetBinLabel(14,"MET");
	hist->GetXaxis()->SetBinLabel(15,"Photon");
	hist->GetXaxis()->SetBinLabel(1,"");
}

void EventPick::clear_vectors(){
	Electrons.clear();
	ElectronsLoose.clear();
	ElectronsMedium.clear();
	Muons.clear();
	MuonsLoose.clear();
	Jets.clear();
	bJets.clear();
	Photons.clear();
	PhotonsPresel.clear();
	PhoPassChHadIso.clear();
	PhoPassPhoIso.clear();
	PhoPassSih.clear();
}

double EventPick::dR_jet_ele(int jetInd, int eleInd){
	return dR(tree->jetEta_->at(jetInd), tree->jetPhi_->at(jetInd), tree->eleSCEta_->at(eleInd), tree->elePhi_->at(eleInd));
}
double EventPick::dR_jet_mu(int jetInd, int muInd){
	return dR(tree->jetEta_->at(jetInd), tree->jetPhi_->at(jetInd), tree->muEta_->at(muInd), tree->muPhi_->at(muInd));
}
double EventPick::dR_jet_pho(int jetInd, int phoInd){
	return dR(tree->jetEta_->at(jetInd), tree->jetPhi_->at(jetInd), tree->phoEta_->at(phoInd), tree->phoPhi_->at(phoInd));
}
double EventPick::dR_ele_pho(int eleInd, int phoInd){
	return dR(tree->eleSCEta_->at(eleInd), tree->elePhi_->at(eleInd), tree->phoEta_->at(phoInd), tree->phoPhi_->at(phoInd));
}
double EventPick::dR_mu_pho(int muInd, int phoInd){
	return dR(tree->muEta_->at(muInd), tree->muPhi_->at(muInd), tree->phoEta_->at(phoInd), tree->phoPhi_->at(phoInd));
}

