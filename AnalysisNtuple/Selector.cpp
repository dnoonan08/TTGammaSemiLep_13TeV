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

	JERsystLevel = 1;
	JECsystLevel = 1;

	// CSVv2M
	//https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation80XReReco
	btag_cut = 0.8484;  

	// electrons
	ele_Pt_cut = 35.0;
	ele_Eta_cut = 2.1;
	ele_PtLoose_cut = 15.0;

	// muons
	mu_Pt_cut = 25;
	mu_Eta_tight = 2.4;
	mu_RelIso_tight = 0.15;

	mu_PtLoose_cut = 10.0;
	mu_Eta_loose = 2.4;
	mu_RelIso_loose = 0.25;
	
	mu_Iso_invert = false;

	// photons
	pho_Et_cut = 25.0; 
	pho_Eta_cut = 2.1; 
	pho_ID_ind = 0; // 0 - Loose, 1 - Medium, 2 - Tight
	pho_noPixelSeed_cut = false;
	pho_noEleVeto_cut = false;
	
}

void Selector::process_objects(EventTree* inp_tree){
	tree = inp_tree;

	clear_vectors();
	//	cout << "before selector photons" << endl;
	filter_photons();

	//	cout << "before selector muons" << endl;
	filter_muons();

	//	cout << "before selector electrons" << endl;
 	filter_electrons();
	
	//	cout << "before selector jets" << endl;
	filter_jets();
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
	// Pho03ChHadSCRIso.clear();
	// Pho03PhoSCRIso.clear();
	// Pho03RandPhoIso.clear();
	// Pho03RandChHadIso.clear();
}

void Selector::filter_photons(){
	for(int phoInd = 0; phoInd < tree->nPho_; ++phoInd){
		double eta = tree->phoEta_->at(phoInd);
		double absEta = TMath::Abs(eta);
		double et = tree->phoEt_->at(phoInd);

		// uint photonIDbit = tree->phoIDbit_->at(phoInd);
		// bool passLoosePhotonID  = photonIDbit >> 0 & 1;
		// bool passMediumPhotonID = photonIDbit >> 1 & 1;
		// bool passTightPhotonID  = photonIDbit >> 2 & 1;


		double rhoCorrPFChIso = tree->phoPFChIso_->at(phoInd) - phoEffArea03ChHad(eta)*tree->rho_;
		double rhoCorrPFNeuIso = tree->phoPFNeuIso_->at(phoInd) - phoEffArea03NeuHad(eta)*tree->rho_;
		double rhoCorrPFPhoIso = tree->phoPFPhoIso_->at(phoInd) - phoEffArea03Pho(eta)*tree->rho_;

		PhoChHadIso_corr.push_back(rhoCorrPFChIso);
		PhoNeuHadIso_corr.push_back(rhoCorrPFNeuIso);
		PhoPhoIso_corr.push_back(rhoCorrPFPhoIso);


		bool passMediumPhotonID = passPhoMediumID(phoInd);


		bool hasPixelSeed = tree->phohasPixelSeed_->at(phoInd);

		// make sure it doesn't fall within the gap
		bool passEtaOverlap = (absEta < 1.4442) || (absEta > 1.566);

		bool isEndCap = (absEta > 1.479);

		
		// Pho03ChHadIso.push_back( max(0., tree->phoPFChIso_->at(phoInd)   - tree->rho_ * phoEffArea03ChHad(eta) ));
		// Pho03ChHadSCRIso.push_back( max(0., tree->phoPFChIso_->at(phoInd)  - tree->rho_ * phoEffArea03ChHad(eta) ));
		// Pho03RandChHadIso.push_back( max(0., tree->phoPFChIso_->at(phoInd) - tree->rho_ * phoEffArea03ChHad(eta) ));
		
		// Pho03NeuHadIso.push_back( max(0., tree->phoPFNeuIso_->at(phoInd) - tree->rho_ * phoEffArea03NeuHad(eta) ));
		
		// Pho03PhoIso.push_back( max(0., tree->phoPFPhoIso_->at(phoInd)  - tree->rho_ * phoEffArea03Pho(eta) ));
		// Pho03PhoSCRIso.push_back(   max(0., tree->phoPFPhoIso_->at(phoInd) - tree->rho_ * phoEffArea03Pho(eta) ));
		// Pho03RandPhoIso.push_back(  max(0., tree->phoPFPhoIso_->at(phoInd) - tree->rho_ * phoEffArea03Pho(eta) ));
		
		// manual spike cleaning (was necessary before)
		//if (dR(tree->phoEta_->at(phoInd), tree->phoPhi_->at(phoInd), -1.76, 1.37) < 0.05) continue;
		//if (dR(tree->phoEta_->at(phoInd), tree->phoPhi_->at(phoInd),  2.37, 2.69) < 0.05) continue;		

		bool phoPresel = (et > pho_Et_cut &&
						  eta < pho_Eta_cut &&
						  passEtaOverlap &&
						  passMediumPhotonID &&
						  !hasPixelSeed);

		if(phoPresel){
			PhotonsPresel.push_back(phoInd);
		}
	}
}

void Selector::filter_electrons(){
	for(int eleInd = 0; eleInd < tree->nEle_; ++eleInd){
		double eta = tree->eleSCEta_->at(eleInd);
		double absEta = TMath::Abs(eta);
		double pt = tree->elePt_->at(eleInd);

		// Not actually needed at the moment, the relIso cuts are incorporated into the electron ID requirements
		double rho = tree->rho_;
		double ea = electronEA[egammaRegion(absEta)];


		// EA subtraction
		double PFrelIso_corr = ( tree->elePFChIso_->at(eleInd) + 
								 max(0.0, tree->elePFNeuIso_->at(eleInd) + 
									 tree->elePFPhoIso_->at(eleInd) -
									 rho*ea
									 )
								 ) / pt;
		
		EleRelIso_corr.push_back(PFrelIso_corr);


		uint eleID = tree->eleIDbit_->at(eleInd);
		bool passEleLooseID = (eleID >> 1) & 1;
		bool passEleMediumID = (eleID >> 2) & 1;
		bool passEleTightID = (eleID >> 3) & 1;

		// make sure it doesn't fall within the gap
		bool passEtaOverlap = (absEta < 1.4442) || (absEta > 1.566);


		// D0 and Dz cuts are different for barrel and endcap
		bool passD0 = ((absEta < 1.479 && tree->eleD0_->at(eleInd) < 0.05) ||
			       (absEta > 1.479 && tree->eleD0_->at(eleInd) < 0.1));
		bool passDz = ((absEta < 1.479 && tree->eleDz_->at(eleInd) < 0.1) ||
			       (absEta > 1.479 && tree->eleDz_->at(eleInd) < 0.2));
		


		bool eleSel = (passEtaOverlap &&
			       absEta < ele_Eta_cut &&
			       pt > ele_Pt_cut &&
			       passEleTightID &&
			       passD0 &&
			       passDz);

	
		bool looseSel = (passEtaOverlap &&
				 absEta < ele_Eta_cut &&
				 pt > ele_PtLoose_cut &&
				 passEleLooseID &&
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
				  PFrelIso_corr < mu_RelIso_tight);
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

// jet ID is not likely to be altered, so it is hardcoded
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
		bool jetID_pass = tree->jetPFLooseID_->at(jetInd);

		if (not tree->isData_ and JERsystLevel==1) jetSmear = tree->jetP4Smear_->at(jetInd);
		if (not tree->isData_ and JERsystLevel==0) jetSmear = tree->jetP4SmearDo_->at(jetInd);
		if (not tree->isData_ and JERsystLevel==2) jetSmear = tree->jetP4SmearUp_->at(jetInd);

		tree->jetPt_->at(jetInd) = jetSmear * pt;
		tree->jetEn_->at(jetInd) = jetSmear*tree->jetEn_->at(jetInd);
		double eta = tree->jetEta_->at(jetInd);

		bool jetPresel = (pt > jet_Pt_cut &&
				  TMath::Abs(eta) < jet_Eta_cut &&
				  jetID_pass);

		if( jetPresel){
			Jets.push_back(jetInd);
			if(tree->jetCSV2BJetTags_->at(jetInd) > btag_cut) bJets.push_back(jetInd);
		}
	}

	if (JECsystLevel==0 || JECsystLevel==2){

		tree->pfMET_ = float(tMET.Pt());
		tree->pfMETPhi_ = float(tMET.Phi());
	}
}


bool Selector::fidEtaPass(double Eta){
	double fabsEta = TMath::Abs(Eta);
	if( fabsEta > 2.5) return false;
	if( 1.4442 < fabsEta && fabsEta < 1.566) return false;
	return true;
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


double Selector::phoEffArea03ChHad(double phoEta){
	double eta = TMath::Abs(phoEta);
	return photonEA[egammaRegion(eta)][0];
}

double Selector::phoEffArea03NeuHad(double phoEta){
	double eta = TMath::Abs(phoEta);
	return photonEA[egammaRegion(eta)][1];
}

double Selector::phoEffArea03Pho(double phoEta){
	double eta = TMath::Abs(phoEta);
	return photonEA[egammaRegion(eta)][2];
}

bool Selector::passEleTightID(int eleInd){
  return true;
}

bool Selector::passEleLooseID(int eleInd){
  return true;
}

bool Selector::passPhoMediumID(int phoInd){
	double pt = tree->phoEt_->at(phoInd);
    double eta = TMath::Abs(tree->phoEta_->at(phoInd));
    bool passMediumID = false;

    double rhoCorrPFChIso = tree->phoPFChIso_->at(phoInd) - phoEffArea03ChHad(eta)*tree->rho_;
    double rhoCorrPFNeuIso = tree->phoPFNeuIso_->at(phoInd) - phoEffArea03NeuHad(eta)*tree->rho_;
    double rhoCorrPFPhoIso = tree->phoPFPhoIso_->at(phoInd) - phoEffArea03Pho(eta)*tree->rho_;
	
    if (eta < 1.47){
		if (tree->phoHoverE_->at(phoInd)                < 0.0396  &&
			tree->phoSigmaIEtaIEtaFull5x5_->at(phoInd)  < 0.01022 &&
			rhoCorrPFPhoIso                             < 0.441 &&
			rhoCorrPFNeuIso                             < 2.725+0.0148*pt+0.000017*pt*pt &&
			rhoCorrPFPhoIso                             < 2.571+0.0047*pt){
			passMediumID = true;
		}
    } else {
		if (tree->phoHoverE_->at(phoInd)                < 0.0219  &&
			tree->phoSigmaIEtaIEtaFull5x5_->at(phoInd)  < 0.03001 &&
			rhoCorrPFPhoIso                             < 0.442 &&
			rhoCorrPFNeuIso                             < 1.715+0.0163*pt+0.000014*pt*pt &&
			rhoCorrPFPhoIso                             < 3.863+0.0034*pt){
			passMediumID = true;
		}
    }
    return passMediumID;
}

Selector::~Selector(){
}
