#include"Selector.h"


double dR(double eta1, double phi1, double eta2, double phi2){
	double dphi = phi2 - phi1;
	double deta = eta2 - eta1;
	static const double pi = TMath::Pi();
	dphi = TMath::Abs( TMath::Abs(dphi) - pi ) - pi;
	return TMath::Sqrt( dphi*dphi + deta*deta );
}

Selector::Selector(){
	// jets
	jet_Pt_cut = 30;
	jet_Eta_cut = 2.4;

	looseJetID = true;
	veto_lep_jet_dR = 0.4; // remove jets with a lepton closer than this cut level
	veto_pho_jet_dR = 0.1; // remove jets with a photon closer than this cut level

	veto_lep_pho_dR = 0.4; // remove photons with a lepton closer than this cut level
	veto_jet_pho_dR = 0.4; // remove photons with a jet closer than this cut level

	JERsystLevel = 1;
	JECsystLevel = 1;

	useDeepCSVbTag = false;
	//https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
	// CSVv2M
	btag_cut = 0.8484;  
	// DeepCSV
	btag_cut_DeepCSV = 0.6324;  


	// whether to invert lepton requirements for 
	QCDselect = false;

	// electrons
	ele_Pt_cut = 35.0;
	ele_Eta_cut = 2.1;
	ele_PtLoose_cut = 15.0;
	ele_EtaLoose_cut = 2.5;

	// muons
	mu_Pt_cut = 30;
	mu_Eta_tight = 2.4;
	mu_RelIso_tight = 0.15;
	mu_QCDRelIso_tight = 0.25;

	mu_PtLoose_cut = 15.0;
	mu_Eta_loose = 2.4;
	mu_RelIso_loose = 0.25;
	mu_QCDRelIso_loose = 0.25;
	
	mu_Iso_invert = false;
	smearJetPt = true;
	// photons
	pho_Et_cut = 15.0; 
	pho_Eta_cut = 2.5; 
	pho_ID_ind = 0; // 0 - Loose, 1 - Medium, 2 - Tight
	pho_noPixelSeed_cut = false;
	pho_noEleVeto_cut = false;
	pho_applyPhoID = true;
	
}

void Selector::process_objects(EventTree* inp_tree){
	tree = inp_tree;

	clear_vectors();
	//	cout << "before selector muons" << endl;
	filter_muons();

	//	cout << "before selector electrons" << endl;
 	filter_electrons();
	
	//	cout << "before selector photons" << endl;
	filter_photons();

	//	cout << "before selector jets" << endl;
	filter_jets();

	//	cout << "before photon jet dr" << endl;
	// add in the DR(photon,jet), removing photons with jet < 0.4 away, needs to be done after the jet selection
	filter_photons_jetsDR();

	//	cout << "end selector" << endl;

}

void Selector::clear_vectors(){
	PhotonsPresel.clear();
	PhoPassChHadIso.clear();
	PhoPassPhoIso.clear();
	PhoPassSih.clear();
	
	Electrons.clear();
	ElectronsLoose.clear();
	ElectronsMedium.clear();
	Muons.clear();
	MuonsLoose.clear();
	Jets.clear();
	bJets.clear();
	
	EleRelIso_corr.clear();
	MuRelIso_corr.clear();
	PhoChHadIso_corr.clear();
	PhoNeuHadIso_corr.clear();
	PhoPhoIso_corr.clear();
	PhoRandConeChHadIso_corr.clear();
	// Pho03ChHadSCRIso.clear();
	// Pho03PhoSCRIso.clear();
	// Pho03RandPhoIso.clear();
	// Pho03RandChHadIso.clear();
}

void Selector::filter_photons(){
	for(int phoInd = 0; phoInd < tree->nPho_; ++phoInd){
		double SCeta = tree->phoSCEta_->at(phoInd);
		double absSCEta = TMath::Abs(SCeta);

		double eta = tree->phoEta_->at(phoInd);
		double absEta = TMath::Abs(eta);
		double et = tree->phoEt_->at(phoInd);
		double phi = tree->phoPhi_->at(phoInd);

		uint photonIDbit = tree->phoIDbit_->at(phoInd);
		// bool passLoosePhotonID  = photonIDbit >> 0 & 1;
		bool passMediumPhotonID = photonIDbit >> 1 & 1;
		// bool passTightPhotonID  = photonIDbit >> 2 & 1;

		double rhoCorrPFChIso  = max(0.0, tree->phoPFChIso_->at(phoInd) - phoEffArea03ChHad(SCeta)*tree->rho_);
		double rhoCorrPFNeuIso = max(0.0, tree->phoPFNeuIso_->at(phoInd) - phoEffArea03NeuHad(SCeta)*tree->rho_);
		double rhoCorrPFPhoIso = max(0.0, tree->phoPFPhoIso_->at(phoInd) - phoEffArea03Pho(SCeta)*tree->rho_);
		double rhoCorrPFRandConeChIso  = max(0.0, tree->phoPFRandConeChIso_->at(phoInd) - phoEffArea03ChHad(SCeta)*tree->rho_);

		PhoChHadIso_corr.push_back(rhoCorrPFChIso);
		PhoNeuHadIso_corr.push_back(rhoCorrPFNeuIso);
		PhoPhoIso_corr.push_back(rhoCorrPFPhoIso);
		PhoRandConeChHadIso_corr.push_back(rhoCorrPFRandConeChIso);

		bool passDR_lep_pho = true;

		//loop over selected electrons
		for(std::vector<int>::const_iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++) {
			if (dR(eta, phi, tree->eleEta_->at(*eleInd), tree->elePhi_->at(*eleInd)) < veto_lep_pho_dR) passDR_lep_pho = false;
		}

		//loop over selected muons
		for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) {
			if (dR(eta, phi, tree->muEta_->at(*muInd), tree->muPhi_->at(*muInd)) < veto_lep_pho_dR) passDR_lep_pho = false;
		}


		bool hasPixelSeed = tree->phohasPixelSeed_->at(phoInd);

		// make sure it doesn't fall within the gap
		bool passEtaOverlap = (absSCEta < 1.4442) || (absSCEta > 1.566);

		bool isEndCap = (absEta > 1.479);

		bool phoPresel = (et > pho_Et_cut &&
						  abs(eta) < pho_Eta_cut &&
						  passEtaOverlap &&
						  passDR_lep_pho && 
						  (!pho_applyPhoID || passMediumPhotonID) &&
						  !hasPixelSeed);

		if(phoPresel){
			PhotonsPresel.push_back(phoInd);
		}
	}
}


void Selector::filter_photons_jetsDR(){
	if (veto_jet_pho_dR < 0) return;
	//	cout << tree->event_ << endl;
	//	cout << "muon Pt/Eta/Phi " << tree->muPt_->at(muInd) << "  " << tree->muEta_->at(muInd) << "  " << tree->muPhi_->at(muInd) << endl;
	for(int i = PhotonsPresel.size()-1; i >= 0; i--){
	// for(std::vector<int>::const_iterator phoInd = PhotonsPresel.begin(); phoInd != PhotonsPresel.end(); phoInd++) {
		int phoInd = PhotonsPresel.at(i);
		double eta = tree->phoEta_->at(phoInd);
		double et = tree->phoEt_->at(phoInd);
		double phi = tree->phoPhi_->at(phoInd);

		bool passDR_jet_pho = true;
		double _dr;
		//loop over selected muons
		//		cout << "Photon Et/Eta/Phi " << et << "  " << eta << "  " << phi << endl; 
		for(std::vector<int>::const_iterator jetInd = Jets.begin(); jetInd != Jets.end(); jetInd++) {

			_dr = dR(eta, phi, tree->jetEta_->at(*jetInd), tree->jetPhi_->at(*jetInd));
			//			cout <<"     jet Pt/Eta/Phi/DR " << tree->jetPt_->at(*jetInd) << "  " << tree->jetEta_->at(*jetInd) << "  " << tree->jetPhi_->at(*jetInd) << "  "<<_dr << endl;
			if (_dr < veto_jet_pho_dR) passDR_jet_pho = false;
		}
		if (!passDR_jet_pho){
			//			cout << "removing Photon" << endl;			
			PhotonsPresel.erase(PhotonsPresel.begin()+i);
		}

	}



}
void Selector::filter_electrons(){
	for(int eleInd = 0; eleInd < tree->nEle_; ++eleInd){
		double eta = tree->eleEta_->at(eleInd);
		double absEta = TMath::Abs(eta);
		double SCeta = tree->eleSCEta_->at(eleInd);
		double absSCEta = TMath::Abs(SCeta);
		double pt = tree->elePt_->at(eleInd);

		// Not actually needed at the moment, the relIso cuts are incorporated into the electron ID requirements
		double rho = tree->rho_;
		double ea = electronEA[egammaRegion(absSCEta)];


		// EA subtraction
		double PFrelIso_corr = ( tree->elePFChIso_->at(eleInd) + 
								 max(0.0, tree->elePFNeuIso_->at(eleInd) + 
									 tree->elePFPhoIso_->at(eleInd) -
									 rho*ea
									 )
								 ) / pt;
		
		EleRelIso_corr.push_back(PFrelIso_corr);


		uint eleID = tree->eleIDbit_->at(eleInd);
		bool passEleVetoID = (eleID >> 0) & 1;
		bool passEleLooseID = (eleID >> 1) & 1;
		bool passEleMediumID = (eleID >> 2) & 1;
		bool passEleTightID = (eleID >> 3) & 1;

		// make sure it doesn't fall within the gap
		bool passEtaEBEEGap = (absSCEta < 1.4442) || (absSCEta > 1.566);


		// D0 and Dz cuts are different for barrel and endcap
		bool passD0 = ((absEta < 1.479 && tree->eleD0_->at(eleInd) < 0.05) ||
			       (absEta > 1.479 && tree->eleD0_->at(eleInd) < 0.1));
		bool passDz = ((absEta < 1.479 && tree->eleDz_->at(eleInd) < 0.1) ||
			       (absEta > 1.479 && tree->eleDz_->at(eleInd) < 0.2));
		


		bool eleSel = (passEtaEBEEGap &&
			       absEta < ele_Eta_cut &&
			       pt > ele_Pt_cut &&
			       passEleTightID &&
			       passD0 &&
			       passDz);

	
		bool looseSel = (passEtaEBEEGap &&
				 absEta < ele_EtaLoose_cut &&
				 pt > ele_PtLoose_cut &&
				 passEleVetoID &&
				 passD0 &&
				 passDz);


		if( eleSel ){
			Electrons.push_back(eleInd);
		}
		else if( looseSel ){ 
			ElectronsLoose.push_back(eleInd);
		}
	}
}




void Selector::filter_muons(){
	for(int muInd = 0; muInd < tree->nMu_; ++muInd){

		double eta = tree->muEta_->at(muInd);
		double pt = tree->muPt_->at(muInd);

		// Applying the beta corrections
		double PFrelIso_corr = ( tree->muPFChIso_->at(muInd) + 
								 max(0.0, tree->muPFNeuIso_->at(muInd) + 
									 tree->muPFPhoIso_->at(muInd) -
									 0.5*tree->muPFPUIso_->at(muInd)
									 ) 
								 ) / pt;

		MuRelIso_corr.push_back(PFrelIso_corr);

		//MuonID, cuts outlined here:
		//https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Muon_Identification

		uint muIDbit = tree->muIDbit_->at(muInd);
		bool looseMuonID = muIDbit >> 0 & 1;
		bool mediumMuonID = muIDbit >> 1 & 1;
		bool tightMuonID = muIDbit >> 2 & 1;


		bool passTight = (pt > mu_Pt_cut &&
						  TMath::Abs(eta) < mu_Eta_tight &&
						  tightMuonID &&
						  ((!QCDselect && PFrelIso_corr < mu_RelIso_tight) ||
						   (QCDselect && PFrelIso_corr > mu_QCDRelIso_tight))
						  );
		bool passLoose = (pt > mu_PtLoose_cut &&
						  TMath::Abs(eta) < mu_Eta_loose &&
						  looseMuonID &&
						  PFrelIso_corr < mu_RelIso_loose);
		
		if(passTight){
		 	Muons.push_back(muInd);
		}
		else if (passLoose){
		 	MuonsLoose.push_back(muInd);
		}
	}
}


void Selector::filter_jets(){
	TLorentzVector tMET;

	if (JECsystLevel==0 || JECsystLevel==2){
		tMET.SetPtEtaPhiM(tree->pfMET_,0.0,tree->pfMETPhi_,0.0);
	}

	for(int jetInd = 0; jetInd < tree->nJet_; ++jetInd){

		if (JECsystLevel==0 || JECsystLevel==2){
			TLorentzVector tJet;
			tJet.SetPtEtaPhiE(tree->jetPt_->at(jetInd),tree->jetEta_->at(jetInd),tree->jetPhi_->at(jetInd),tree->jetEn_->at(jetInd));
			tMET += tJet;
			double JECUnc = tree->jetJECUnc_->at(jetInd);
			if (JECsystLevel==0){
				tree->jetPt_->at(jetInd) = tree->jetPt_->at(jetInd)*(1-JECUnc);
				tree->jetEn_->at(jetInd) = tree->jetEn_->at(jetInd)*(1-JECUnc);
			}
			if (JECsystLevel==2){
				tree->jetPt_->at(jetInd) = tree->jetPt_->at(jetInd)*(1+JECUnc);
				tree->jetEn_->at(jetInd) = tree->jetEn_->at(jetInd)*(1+JECUnc);
			}
			tJet.SetPtEtaPhiE(tree->jetPt_->at(jetInd),tree->jetEta_->at(jetInd),tree->jetPhi_->at(jetInd),tree->jetEn_->at(jetInd));
			tMET -= tJet;
		}

		double jetSmear = 1.;
		double pt = tree->jetPt_->at(jetInd);
		bool jetID_pass = (tree->jetPFLooseID_->at(jetInd) && looseJetID) || (tree->jetID_->at(jetInd)>>2&1);
		double jetEn = tree->jetEn_->at(jetInd);

		if (!tree->isData_ && JERsystLevel==1) {jetSmear = tree->jetP4Smear_->at(jetInd);}
		if (!tree->isData_ && JERsystLevel==0) {jetSmear = tree->jetP4SmearDo_->at(jetInd);}
		if (!tree->isData_ && JERsystLevel==2) {jetSmear = tree->jetP4SmearUp_->at(jetInd);}

		if (smearJetPt){
			pt = pt*jetSmear;
			jetEn = jetSmear*jetEn;
		}
		tree->jetPt_->at(jetInd) = pt;
		tree->jetEn_->at(jetInd) = jetEn;
		double eta = tree->jetEta_->at(jetInd);


		//		cout << "starting DR cuts" << endl;

		bool passDR_lep_jet = true;

		//loop over selected electrons
		for(std::vector<int>::const_iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++) {
			if (dR(tree->jetEta_->at(jetInd), tree->jetPhi_->at(jetInd), tree->eleEta_->at(*eleInd), tree->elePhi_->at(*eleInd)) < veto_lep_jet_dR) passDR_lep_jet = false;
		}

		//loop over selected muons
		for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) {
			if (dR(tree->jetEta_->at(jetInd), tree->jetPhi_->at(jetInd), tree->muEta_->at(*muInd), tree->muPhi_->at(*muInd)) < veto_lep_jet_dR) passDR_lep_jet = false;
		}

		bool passDR_pho_jet = true;
		//		cout << "photon dR" << endl;
		//loop over selected photons

		for(std::vector<int>::const_iterator phoInd = PhotonsPresel.begin(); phoInd != PhotonsPresel.end(); phoInd++) {
			// Only look at photons which pass the medium ID (this is left out of the selector in makeAnalysisNtuple so that different cuts can be invereted)
			if (tree->phoIDbit_->at(*phoInd) >> 1 & 1){
				if (dR(tree->jetEta_->at(jetInd), tree->jetPhi_->at(jetInd), tree->phoEta_->at(*phoInd), tree->phoPhi_->at(*phoInd)) < veto_pho_jet_dR) passDR_pho_jet = false;
			}
		}

		//		cout << "finished DR cuts" << endl;

		bool jetPresel = (pt > jet_Pt_cut &&
						  TMath::Abs(eta) < jet_Eta_cut &&
						  jetID_pass &&
						  passDR_lep_jet &&
						  passDR_pho_jet
						  );



		if( jetPresel){
			Jets.push_back(jetInd);
			if (!useDeepCSVbTag){
				if(tree->jetCSV2BJetTags_->at(jetInd) > btag_cut) bJets.push_back(jetInd);
			} else {
				if( (tree->jetDeepCSVTags_b_->at(jetInd) + tree->jetDeepCSVTags_bb_->at(jetInd) ) > btag_cut_DeepCSV) bJets.push_back(jetInd);
			}				
		}
	}

	// Update the MET for JEC changes
	if (JECsystLevel==0 || JECsystLevel==2){
		tree->pfMET_ = float(tMET.Pt());
		tree->pfMETPhi_ = float(tMET.Phi());
	}
}


// https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedPhotonID2012#Effective_Areas_for_rho_correcti
int Selector::egammaRegion(double absEta){
	int region = 0;
	if( absEta >= 1.0  ) region++;
	if( absEta >= 1.479) region++;
	if( absEta >= 2.0  ) region++;
	if( absEta >= 2.2  ) region++;
	if( absEta >= 2.3  ) region++;
	if( absEta >= 2.4  ) region++;
	return region;
}

// Currently, these are the listed values for the SPRING16 MC samples, need to verify that they are what should be used from SUMMER16 as well


double Selector::phoEffArea03ChHad(double phoSCEta){
	double eta = TMath::Abs(phoSCEta);
	return photonEA[egammaRegion(eta)][0];
}

double Selector::phoEffArea03NeuHad(double phoSCEta){
	double eta = TMath::Abs(phoSCEta);
	return photonEA[egammaRegion(eta)][1];
}

double Selector::phoEffArea03Pho(double phoSCEta){
	double eta = TMath::Abs(phoSCEta);
	return photonEA[egammaRegion(eta)][2];
}

bool Selector::passEleTightID(int eleInd){
  return true;
}

bool Selector::passEleLooseID(int eleInd){
  return true;
}

bool Selector::passPhoMediumID(int phoInd, bool cutHoverE, bool cutSIEIE, bool cutIso){

	double pt = tree->phoEt_->at(phoInd);
    double eta = TMath::Abs(tree->phoSCEta_->at(phoInd));
    bool passMediumID = false;

	double rhoCorrPFChIso  = max(0.0, tree->phoPFChIso_->at(phoInd)  - phoEffArea03ChHad(eta) *tree->rho_);
	double rhoCorrPFNeuIso = max(0.0, tree->phoPFNeuIso_->at(phoInd) - phoEffArea03NeuHad(eta)*tree->rho_);
	double rhoCorrPFPhoIso = max(0.0, tree->phoPFPhoIso_->at(phoInd) - phoEffArea03Pho(eta)   *tree->rho_);
	
    if (eta < 1.47){
		if ((!cutHoverE || tree->phoHoverE_->at(phoInd)                < 0.0396  ) &&
			(!cutSIEIE  || tree->phoSigmaIEtaIEtaFull5x5_->at(phoInd)  < 0.01022 ) &&
			(!cutIso    || (rhoCorrPFChIso                              < 0.441 &&
							rhoCorrPFNeuIso                             < 2.725+0.0148*pt+0.000017*pt*pt &&
							rhoCorrPFPhoIso                             < 2.571+0.0047*pt))){
			passMediumID = true;
		}
    } else {
		if ((!cutHoverE || tree->phoHoverE_->at(phoInd)                < 0.0219  ) &&
			(!cutSIEIE  || tree->phoSigmaIEtaIEtaFull5x5_->at(phoInd)  < 0.03001 ) &&
			(!cutIso    || (rhoCorrPFChIso                              < 0.442 &&
							rhoCorrPFNeuIso                             < 1.715+0.0163*pt+0.000014*pt*pt &&
							rhoCorrPFPhoIso                             < 3.863+0.0034*pt))){
			passMediumID = true;
		}
    }
    return passMediumID;
}



Selector::~Selector(){
}
