#include"Selector.h"
#include"TRandom3.h"
#include <bitset>

double dR(double eta1, double phi1, double eta2, double phi2){
    double dphi = phi2 - phi1;
    double deta = eta2 - eta1;
    static const double pi = TMath::Pi();
    dphi = TMath::Abs( TMath::Abs(dphi) - pi ) - pi;
    return TMath::Sqrt( dphi*dphi + deta*deta );
}

TRandom* generator = new TRandom3(0);

Selector::Selector(){

    year = "2016";
    // jets
    jet_Pt_cut = 30;
    jet_Eta_cut = 2.4;

    printEvent = -1;

    looseJetID = false;
    veto_lep_jet_dR = 0.4; // remove jets with a lepton closer than this cut level
    veto_pho_jet_dR = 0.1; // remove jets with a photon closer than this cut level

    veto_lep_pho_dR = 0.4; // remove photons with a lepton closer than this cut level
    veto_jet_pho_dR = 0.4; // remove photons with a jet closer than this cut level

    JERsystLevel  = 1;
    JECsystLevel  = 1;
    phosmearLevel = 1;
    elesmearLevel = 1;
    phoscaleLevel = 1;
    elescaleLevel = 1;
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
    ele_EtaLoose_cut = 2.4;

    // muons
    mu_Pt_cut = 30;
    mu_Eta_tight = 2.4;
    mu_RelIso_tight = 0.15;

    mu_PtLoose_cut = 15.0;
    mu_Eta_loose = 2.4;
    mu_RelIso_loose = 0.25;
	
    mu_Iso_invert = false;
    smearJetPt = true;
    smearPho = true;
    smearEle = true;
    scaleEle = true;
    scalePho = true;

    // photons
    pho_Et_cut = 20.0; 
    pho_Eta_cut = 1.4442;
    pho_ID_ind = 0; // 0 - Loose, 1 - Medium, 2 - Tight
    pho_noPixelSeed_cut = false;
    pho_noEleVeto_cut = false;
    pho_applyPhoID = true;
	
}

void Selector::process_objects(EventTree* inp_tree){
    tree = inp_tree;
    clear_vectors();
    //cout << "before selector muons" << endl;
    filter_muons();

    //cout << "before selector electrons" << endl;
    filter_electrons();

    //cout << "before selector photons" << endl;
    filter_photons();

    //cout << "before selector jets" << endl;
    filter_jets();

    //cout << "before photon jet dr" << endl;
    // // add in the DR(photon,jet), removing photons with jet < 0.4 away, needs to be done after the jet selection
    filter_photons_jetsDR();
	
    //cout << "end selector" << endl;

}

void Selector::clear_vectors(){
    Photons.clear();

    PhoPassChHadIso.clear();
    PhoPassPhoIso.clear();
    PhoPassSih.clear();

    LoosePhotons.clear();
	
    Electrons.clear();
    ElectronsLoose.clear();
    ElectronsMedium.clear();
    Muons.clear();
    MuonsLoose.clear();
    Jets.clear();
    FwdJets.clear();
    bJets.clear();
	
    MuRelIso_corr.clear();
    PhoChHadIso_corr.clear();
    PhoNeuHadIso_corr.clear();
    PhoPhoIso_corr.clear();
    PhoRandConeChHadIso_corr.clear();
    
}

void Selector::filter_photons(){
    if (tree->event_==printEvent){
	cout << "Found Event Staring Photons" << endl;
	cout << " nPho=" << tree->nPho_ << endl;
    }
    for(int phoInd = 0; phoInd < tree->nPho_; ++phoInd){
	
        double et = tree->phoEt_[phoInd];
        double eta = tree->phoEta_[phoInd];
        double absEta = TMath::Abs(eta);
        double phi = tree->phoPhi_[phoInd];

	
        bool isEB = tree->phoIsEB_[phoInd];
        bool isEE = tree->phoIsEE_[phoInd];
        
        uint photonID = tree->phoIDcutbased_[phoInd];

        bool passMediumPhotonID = photonID >= 2;

        double phoPFRelIso = tree->phoPFRelIso_[phoInd];
        double phoPFRelChIso = tree->phoPFRelChIso_[phoInd];


        ///////// TODO NEEDS TO BE REIMPLEMENTED WITH NANOAOD

        // double PhoSmear = 1.;

        // if (!tree->isData_ && phosmearLevel==1) {PhoSmear = generator->Gaus(1,(tree->phoResol_rho_up_[phoInd]+tree->phoResol_rho_dn_[phoInd])/2.);}
        // if (!tree->isData_ && phosmearLevel==0) {PhoSmear = generator->Gaus(1,tree->phoResol_rho_dn_[phoInd]);}
        // if (!tree->isData_ && phosmearLevel==2) {PhoSmear = generator->Gaus(1,tree->phoResol_rho_up_[phoInd]);}
        // if (smearPho){
        //   //	std::cout << "stat: "<<PhoSmear <<std::endl;
        //   et = et*PhoSmear;
        // }
        // tree->phoEt_[phoInd] = et;
        // double PhoScale = 1.;
        
        // if (tree->isData_ && phoscaleLevel==1) {PhoScale = ((tree->phoScale_stat_up_[phoInd]+tree->phoScale_stat_dn_[phoInd])/2.);}
        // if (!tree->isData_ && phoscaleLevel==2){PhoScale =1.+sqrt(pow((1-tree->phoScale_syst_up_[phoInd]),2)+pow((1-tree->phoScale_stat_up_[phoInd]),2)+pow((1-tree->phoScale_gain_up_[phoInd]),2));}
        // if (!tree->isData_ && phoscaleLevel==0) {PhoScale=1.-sqrt(pow((1-tree->phoScale_syst_dn_[phoInd]),2)+pow((1-tree->phoScale_stat_dn_[phoInd]),2)+pow((1-tree->phoScale_gain_dn_[phoInd]),2));}
        
        // if (scalePho){
        //   et = et*PhoScale;
        // }
        // tree->phoEt_[phoInd] = et;
        
        bool passDR_lep_pho = true;
        
        //loop over selected electrons
        for(std::vector<int>::const_iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++) {
	    if (dR(eta, phi, tree->eleEta_[*eleInd], tree->elePhi_[*eleInd]) < veto_lep_pho_dR) passDR_lep_pho = false;
        }
        
        //loop over selected muons
        for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) {
	    if (dR(eta, phi, tree->muEta_[*muInd], tree->muPhi_[*muInd]) < veto_lep_pho_dR) passDR_lep_pho = false;
        }
        
        
        bool hasPixelSeed = tree->phoPixelSeed_[phoInd];

        bool passPhoEleVeto = tree->phoEleVeto_[phoInd];
        bool phoPresel = (et > pho_Et_cut &&                          
                          absEta < pho_Eta_cut &&
                          (isEE || isEB) &&
                          passDR_lep_pho && 
                          !hasPixelSeed
                          && passPhoEleVeto     //we have to add this in eventTree
			  );

	bool indet = (isEE || isEB);
	bool  pho_et_pass = et > pho_Et_cut ;
	bool pho_eta_pass = absEta < pho_Eta_cut ;
	bool finalsel = phoPresel && passMediumPhotonID ;
	
	if (tree->event_==printEvent){
	    cout << "-- " << phoInd << " pt="<<et<< " eta="<<eta<< " phi="<<phi<< " pho_et_pass "<< pho_et_pass<<" pho_Eta_pass="<< pho_eta_pass <<" (isEE || isEB) ="<<indet<<" hasPixelSeed= "<<hasPixelSeed<<" presel="<< phoPresel<< " drlepgamma="<<passDR_lep_pho<< " medID="<<passMediumPhotonID<<" final selection"<<finalsel<<endl;
	} 
	
        if(phoPresel && passMediumPhotonID){
            Photons.push_back(phoInd);
        }
        if(phoPresel){
            LoosePhotons.push_back(phoInd);
        }
    }
}


void Selector::filter_photons_jetsDR(){
    if (veto_jet_pho_dR < 0) return;
  
    for( int i = Photons.size()-1; i >= 0; i--){
        int phoInd = Photons.at(i);
        double eta = tree->phoEta_[phoInd];
        double et = tree->phoEt_[phoInd];
        double phi = tree->phoPhi_[phoInd];
        
        bool passDR_jet_pho = true;
        double _dr;
    
        for(std::vector<int>::const_iterator jetInd = Jets.begin(); jetInd != Jets.end(); jetInd++) {
            _dr = dR(eta, phi, tree->jetEta_[*jetInd], tree->jetPhi_[*jetInd]);
            if (_dr < veto_jet_pho_dR) passDR_jet_pho = false;
        }
        if (!passDR_jet_pho){
          Photons.erase(Photons.begin()+i);
        }
    }
    


    for(int i = LoosePhotons.size()-1; i >= 0; i--){
        int phoInd = LoosePhotons.at(i);
        double eta = tree->phoEta_[phoInd];
        double et = tree->phoEt_[phoInd];
        double phi = tree->phoPhi_[phoInd];
        
        bool passDR_jet_pho = true;
        double _dr;
        
        for(std::vector<int>::const_iterator jetInd = Jets.begin(); jetInd != Jets.end(); jetInd++) {
          _dr = dR(eta, phi, tree->jetEta_[*jetInd], tree->jetPhi_[*jetInd]);
          if (_dr < veto_jet_pho_dR) passDR_jet_pho = false;
        }
        if (!passDR_jet_pho){
          LoosePhotons.erase(LoosePhotons.begin()+i);
        }
        
    }
}

void Selector::filter_electrons(){
    if (tree->event_==printEvent){
	cout << "Found Event, Starting Electrons" << endl;
	cout << " nEle=" << tree->nEle_ << endl;
    }

    for(int eleInd = 0; eleInd < tree->nEle_; ++eleInd){

        double eta = tree->eleEta_[eleInd];
        double absEta = TMath::Abs(eta);
        double SCeta = eta + tree->eleDeltaEtaSC_[eleInd];
        double absSCEta = TMath::Abs(SCeta);

        double pt = tree->elePt_[eleInd];
        
        // // EA subtraction
        double PFrelIso_corr = tree->elePFRelIso_[eleInd];
        
        uint eleID = tree->eleIDcutbased_[eleInd];
        bool passVetoID   = eleID >= 1;
        bool passLooseID  = eleID >= 2;
        bool passMediumID = eleID >= 3;
        bool passTightID  = eleID >= 4;
        
        // make sure it doesn't fall within the gap
        bool passEtaEBEEGap = (absSCEta < 1.4442) || (absSCEta > 1.566);
        

        // D0 and Dz cuts are different for barrel and endcap
        bool passD0 = ((absEta < 1.479 && abs(tree->eleD0_[eleInd]) < 0.05) ||
                       (absEta > 1.479 && abs(tree->eleD0_[eleInd]) < 0.1));
        bool passDz = ((absEta < 1.479 && abs(tree->eleDz_[eleInd]) < 0.1) ||
                       (absEta > 1.479 && abs(tree->eleDz_[eleInd]) < 0.2));
        
        

        double EleSmear = 1.;

        /////////NEEDS TO BE REIMPLEMENTED

        // if (!tree->isData_ && elesmearLevel==1) {EleSmear = generator->Gaus(1,(tree->eleResol_rho_up_[eleInd]+tree->eleResol_rho_dn_[eleInd])/2.);}
        // if (!tree->isData_ && elesmearLevel==0) {EleSmear = generator->Gaus(1,tree->eleResol_rho_dn_[eleInd]);}
        // if (!tree->isData_ && elesmearLevel==2) {EleSmear = generator->Gaus(1,tree->eleResol_rho_up_[eleInd]);}
        // if (pt<10.){
        //   smearEle= false;
        // }
        // if (smearEle){
        //   pt = pt*EleSmear;
        //   en = EleSmear*en;
        // }
        // tree->elePt_[eleInd] = pt;
        // tree->eleEn_[eleInd]= en;   
        // double EleScale = 1.;
        // double nom_scale =  (float(tree->eleScale_stat_up_[eleInd]+tree->eleScale_stat_dn_[eleInd])/2.);
        // if (tree->isData_ && elescaleLevel==1) {EleScale = ((tree->eleScale_stat_up_[eleInd]+tree->eleScale_stat_dn_[eleInd])/2.);}
        // if (!tree->isData_ && elescaleLevel==2){EleScale = 1.+sqrt(pow((1-tree->eleScale_syst_up_[eleInd]),2)+pow((1-tree->eleScale_stat_up_[eleInd]),2)+pow((1-tree->eleScale_gain_up_[eleInd]),2));}
        // if (!tree->isData_ && elescaleLevel==0){EleScale = 1.-(sqrt(pow((1-tree->eleScale_syst_dn_[eleInd]),2)+pow(1-(tree->eleScale_stat_dn_[eleInd]),2)+pow((1-tree->eleScale_gain_dn_[eleInd]),2)));}
        // if (scaleEle){
        //   //	std::cout<<tree->eleScale_syst_dn_[eleInd]<<   tree->eleScale_stat_dn_[eleInd]<<   tree->eleScale_syst_dn_[eleInd]<<std::endl;
        //   //		std::cout<<"nominal is:"<< nom_scale<<std::endl;
        //   //	std::cout << "stat: "<<EleScale <<std::endl;
        //   pt = pt*EleScale;
        //   en = EleScale*en;
        // }       
        // tree->elePt_[eleInd] = pt;
        // tree->eleEn_[eleInd]= en;
        
	
        if (QCDselect){
            passTightID = false;
            passTightID = passEleTightID(eleInd,false) && 
		PFrelIso_corr > (absSCEta < 1.47 ? 0.0588 : 0.0571) && 
		(tree->eleEcalSumEtDr03_[eleInd] / tree->elePt_[eleInd] ) < (absSCEta < 1.47 ? 0.032 : 0.040) && 
		(tree->eleHcalSumEtDr03_[eleInd] / tree->elePt_[eleInd] ) < (absSCEta < 1.47 ? 0.055 : 0.05) && 
		(tree->eleTrkSumPtDr03_[eleInd]   / tree->elePt_[eleInd] ) < (absSCEta < 1.47 ? 0.06 : 0.05);
        }
        
        bool eleSel = (passEtaEBEEGap && 
                       absEta < ele_Eta_cut &&
                       pt > ele_Pt_cut &&
                       passTightID &&
                       passD0 &&
                       passDz);
	
        bool looseSel = ( passEtaEBEEGap && 
			  absEta < ele_EtaLoose_cut &&
			  pt > ele_PtLoose_cut &&
			  passVetoID &&
			  passD0 &&
			  passDz);
        
        
	if (tree->event_==printEvent){
	    cout << "-- " << eleInd << " eleSel=" <<  eleSel << " looseSel=" <<  looseSel << " pt="<<pt<< " eta="<<eta<< " phi="<<tree->elePhi_[eleInd]<< " eleID="<<eleID << " passD0="<<passD0<< "("<<tree->eleD0_[eleInd]<<") passDz="<<passDz<< "("<<tree->eleDz_[eleInd]<<")"<< endl;
	    cout << "            ";
	    cout << "sieie="<<tree->eleSIEIE_[eleInd];
	    cout << endl;
	    std::cout << std::setbase(8);
	    cout << "            idBits="<<tree->eleVidWPBitmap_[eleInd] << endl;
	    std::cout << std::setbase(10);
	    
	} 
        
	
        if( eleSel ){
            Electrons.push_back(eleInd);
        }
        else if( looseSel ){ 
            ElectronsLoose.push_back(eleInd);
        }
    }

    if (tree->event_==printEvent){
	if (year=="2016"){
	    cout << "            idBits :   MinPtCut, GsfEleSCEtaMultiRangeCut, GsfEleDEtaInSeedCut, GsfEleDPhiInCut, GsfEleFull5x5SigmaIEtaIEtaCut, GsfEleHadronicOverEMCut, GsfEleEInverseMinusPInverseCut, GsfEleEffAreaPFIsoCut, GsfEleConversionVetoCut, GsfEleMissingHitsCut" << endl;
	} else {
	    cout << "            idBits :   MinPtCut, GsfEleSCEtaMultiRangeCut, GsfEleDEtaInSeedCut, GsfEleDPhiInCut, GsfEleFull5x5SigmaIEtaIEtaCut, GsfEleHadronicOverEMEnergyScaledCut, GsfEleEInverseMinusPInverseCut, GsfEleRelPFIsoScaledCut, GsfEleConversionVetoCut, GsfEleMissingHitsCut" << endl;
	}
    }
    
}

void Selector::filter_muons(){
    if (tree->event_==printEvent){
	cout << "Found Event, Starting Muons" << endl;
	cout << " nMu=" << tree->nMuon_ << endl;
    }
    for(int muInd = 0; muInd < tree->nMuon_; ++muInd){

	double eta = tree->muEta_[muInd];
	double pt = tree->muPt_[muInd];

	double PFrelIso_corr = tree->muPFRelIso_[muInd];

	bool looseMuonID = tree->muIsPFMuon_[muInd] && (tree->muIsTracker_[muInd] || tree->muIsGlobal_[muInd]);
	bool mediumMuonID = tree->muMediumId_[muInd];
	bool tightMuonID = tree->muTightId_[muInd];

	bool passTight = (pt > mu_Pt_cut &&
			  TMath::Abs(eta) < mu_Eta_tight &&
			  tightMuonID &&
			  (!QCDselect ? (PFrelIso_corr < mu_RelIso_tight): PFrelIso_corr > mu_RelIso_tight)
			  );

	bool passLoose = (pt > mu_PtLoose_cut &&
			  TMath::Abs(eta) < mu_Eta_loose &&
			  looseMuonID &&
			  (!QCDselect ? (PFrelIso_corr < mu_RelIso_loose): PFrelIso_corr > mu_RelIso_loose)
			  );

	if (tree->event_==printEvent){
	    cout << "-- " << muInd << " passTight="<<passTight<< " passLoose="<<passLoose << " pt="<<pt<< " eta="<<eta<< " phi="<<tree->muPhi_[muInd]<< " tightID="<<tightMuonID<< " looseID="<<looseMuonID << " pfRelIso="<<PFrelIso_corr << endl;
	} 
	
	if(passTight){
	  Muons.push_back(muInd);
	}
	else if (passLoose){
	  MuonsLoose.push_back(muInd);
	}
    }
}



void Selector::filter_jets(){
  //    TLorentzVector tMET;
    if (tree->event_==printEvent){
    	cout << "Found Event Staring Jets" << endl;
    }

    for(int jetInd = 0; jetInd < tree->nJet_; ++jetInd){
        double pt = tree->jetPt_[jetInd];
        double eta = tree->jetEta_[jetInd];
        double phi = tree->jetPhi_[jetInd];

	//tight ID for 2016 (bit 0), tightLeptVeto for 2017 (bit 1)
	int jetID_cutBit = 1;
	if (year=="2016"){ jetID_cutBit = 0; }
	
        bool jetID_pass = (tree->jetID_[jetInd]>>0 & 1 && looseJetID) || (tree->jetID_[jetInd]>>jetID_cutBit & 1);
        

// 		double jetSmear = 1.;
// 		if (!tree->isData_ && JERsystLevel==1) {jetSmear = tree->jetP4Smear_->at(jetInd);}
// 		if (!tree->isData_ && JERsystLevel==0) {jetSmear = tree->jetP4SmearDo_->at(jetInd);}
// 		if (!tree->isData_ && JERsystLevel==2) {jetSmear = tree->jetP4SmearUp_->at(jetInd);}
// 		if (smearJetPt){
// 			pt = pt*jetSmear;
// 			jetEn = jetSmear*jetEn;
// 		}
// 		tree->jetPt_->at(jetInd) = pt;
// 		tree->jetEn_->at(jetInd) = jetEn;


        bool passDR_lep_jet = true;

        //loop over selected electrons
        for(std::vector<int>::const_iterator eleInd = Electrons.begin(); eleInd != Electrons.end(); eleInd++) {
	    if (dR(eta, phi, tree->eleEta_[*eleInd], tree->elePhi_[*eleInd]) < veto_lep_jet_dR) passDR_lep_jet = false;
        }

        //loop over selected muons
        for(std::vector<int>::const_iterator muInd = Muons.begin(); muInd != Muons.end(); muInd++) {
          if (dR(eta, phi, tree->muEta_[*muInd], tree->muPhi_[*muInd]) < veto_lep_jet_dR) passDR_lep_jet = false;
        }

        bool passDR_pho_jet = true;
        //loop over selected photons
        for(std::vector<int>::const_iterator phoInd = Photons.begin(); phoInd != Photons.end(); phoInd++) {
	    if (tree->event_==printEvent){
		cout << "       phoInd=" << *phoInd << "   dR=" << dR(eta, phi, tree->phoEta_[*phoInd], tree->phoPhi_[*phoInd]) << "  phoEta=" << tree->phoEta_[*phoInd] << "  phoPhi=" << tree->phoPhi_[*phoInd] << endl;
	    }
	    if (dR(eta, phi, tree->phoEta_[*phoInd], tree->phoPhi_[*phoInd]) < veto_pho_jet_dR) passDR_pho_jet = false;
	}

        bool jetPresel = (pt > jet_Pt_cut &&
                          TMath::Abs(eta) < jet_Eta_cut &&
                          jetID_pass &&
                          passDR_lep_jet &&
                          passDR_pho_jet
                          );

	if (tree->event_==printEvent){
	    cout << "   pt=" << pt << "  eta=" << eta << " phi=" << phi << "  jetID=" << jetID_pass << endl;
	    cout << "         presel=" << jetPresel << endl;
	    cout << "              pt=" << (pt > jet_Pt_cut) <<endl;
	    cout << "              eta=" << (TMath::Abs(eta) < jet_Eta_cut) <<endl;
	    cout << "              jetID=" << jetID_pass <<endl;
	    cout << "              dRLep=" << passDR_lep_jet <<endl;
	    cout << "              dRPho=" << passDR_pho_jet << endl;
	    cout << "              btag="<<(tree->jetBtagDeepB_[jetInd] > btag_cut_DeepCSV) << endl; 

	}

        
        bool fwdjetPresel = (pt> jet_Pt_cut && jetID_pass && TMath::Abs(eta)<3.0 && TMath::Abs(eta)>2.5 &&
                             passDR_lep_jet &&
                             passDR_pho_jet
                             );
        
        if(fwdjetPresel){
            FwdJets.push_back(jetInd);
        }
        
        
        if( jetPresel){
            Jets.push_back(jetInd);
            if (!useDeepCSVbTag){
                if( tree->jetBtagCSVV2_[jetInd] > btag_cut) bJets.push_back(jetInd);
            } else {
                if( tree->jetBtagDeepB_[jetInd] > btag_cut_DeepCSV) bJets.push_back(jetInd);
            }				
        }
    }
    
    // // Update the MET for JEC changes
    // if (JECsystLevel==0 || JECsystLevel==2){
    // 	tree->pfMET_ = float(tMET.Pt());
    // 	tree->pfMETPhi_ = float(tMET.Phi());
    // }
}


bool Selector::passEleTightID(int eleInd, bool doRelisoCut){

    Int_t WPcutBits = tree->eleVidWPBitmap_[eleInd];

    int nBits = 2;

    bool MinPtCut                            = WPcutBits>>(9*nBits+1) & 3;
    bool GsfEleSCEtaMultiRangeCut            = WPcutBits>>(8*nBits+1) & 3;
    bool GsfEleDEtaInSeedCut                 = WPcutBits>>(7*nBits+1) & 3;
    bool GsfEleDPhiInCut                     = WPcutBits>>(6*nBits+1) & 3;
    bool GsfEleFull5x5SigmaIEtaIEtaCut       = WPcutBits>>(5*nBits+1) & 3;
    bool GsfEleHadronicOverEMEnergyScaledCut = WPcutBits>>(4*nBits+1) & 3;
    bool GsfEleEInverseMinusPInverseCut      = WPcutBits>>(3*nBits+1) & 3;
    bool GsfEleEffAreaPFIsoCut               = WPcutBits>>(2*nBits+1) & 3;
    bool GsfEleConversionVetoCut             = WPcutBits>>(1*nBits+1) & 3;
    bool GsfEleMissingHitsCut                = WPcutBits>>(0*nBits+1) & 3;

    bool passTight = (MinPtCut
                      && GsfEleSCEtaMultiRangeCut
                      && GsfEleDEtaInSeedCut
                      && GsfEleDPhiInCut
                      && GsfEleFull5x5SigmaIEtaIEtaCut
                      && GsfEleHadronicOverEMEnergyScaledCut
                      && GsfEleEInverseMinusPInverseCut
                      && (GsfEleEffAreaPFIsoCut || !doRelisoCut)
                      && GsfEleConversionVetoCut
                      && GsfEleMissingHitsCut);

    return passTight;

}


    // double pt = tree->elePt_->at(eleInd);
    // double eta = TMath::Abs(tree->eleSCEta_->at(eleInd));

    // double PFrelIso_corr = tree->elePFRelIso_->at(eleInd);

    // bool SIEIECut      = (eta < 1.47) ? (tree->eleSIEIE_->at(eleInd) < 0.00998) : (tree->eleSIEIE_->at(eleInd) < 0.0292);
    // bool dEtaCut       = (eta < 1.47) ? (tree->eledEtaseedAtVtx_->at(eleInd)		< 0.00308) : (tree->eledEtaseedAtVtx_->at(eleInd)		 < 0.00605);
// 	bool dPhiCut       = (eta < 1.47) ? (tree->eledPhiAtVtx_->at(eleInd)			< 0.0816 ) : (tree->eledPhiAtVtx_->at(eleInd)			 < 0.0394 );
// 	bool HoverECut     = (eta < 1.47) ? (tree->eleHoverE_->at(eleInd)			    < 0.0414 ) : (tree->eleHoverE_->at(eleInd)			     < 0.0641 );
// 	bool RelIsoCut     = (eta < 1.47) ? (PFrelIso_corr							    < 0.0588 ) : (PFrelIso_corr							     < 0.0571 );
// 	bool overEoverPCut = (eta < 1.47) ? (TMath::Abs(tree->eleEoverPInv_->at(eleInd))< 0.0129 ) : (TMath::Abs(tree->eleEoverPInv_->at(eleInd))< 0.0129 );
// 	bool MissHitsCut   = (eta < 1.47) ? (tree->eleMissHits_->at(eleInd)             <= 1     ) : (tree->eleMissHits_->at(eleInd)             <= 1     );
// 	bool ConvVetoCut   = tree->eleConvVeto_->at(eleInd);
		
//     bool passTightID = SIEIECut && dEtaCut && dPhiCut && HoverECut && (doRelisoCut ? RelIsoCut : true) && overEoverPCut && MissHitsCut && ConvVetoCut;
	
// 	return true;

// }

// bool Selector::passEleVetoID(int eleInd, bool doRelisoCut){

// 	double pt = tree->elePt_->at(eleInd);
//     double eta = TMath::Abs(tree->eleSCEta_->at(eleInd));

// 	double rho = tree->rho_;
// 	double ea = electronEA[egammaRegion(eta)];


// 	// EA subtraction
// 	double PFrelIso_corr = ( tree->elePFChIso_->at(eleInd) + 
// 							 max(0.0, tree->elePFNeuIso_->at(eleInd) + 
// 								 tree->elePFPhoIso_->at(eleInd) -
// 								 rho*ea
// 								 )
// 							 ) / pt;

// 	bool SIEIECut      = (eta < 1.47) ? (tree->eleSigmaIEtaIEtaFull5x5_->at(eleInd) < 0.0115 ) : (tree->eleSigmaIEtaIEtaFull5x5_->at(eleInd) < 0.037);
// 	bool dEtaCut       = (eta < 1.47) ? (tree->eledEtaseedAtVtx_->at(eleInd)		< 0.00749) : (tree->eledEtaseedAtVtx_->at(eleInd)		 < 0.00895);
// 	bool dPhiCut       = (eta < 1.47) ? (tree->eledPhiAtVtx_->at(eleInd)			< 0.228  ) : (tree->eledPhiAtVtx_->at(eleInd)			 < 0.213);
// 	bool HoverECut     = (eta < 1.47) ? (tree->eleHoverE_->at(eleInd)			    < 0.356  ) : (tree->eleHoverE_->at(eleInd)			     < 0.211 );
// 	bool RelIsoCut     = (eta < 1.47) ? (PFrelIso_corr							    < 0.175  ) : (PFrelIso_corr							     < 0.159 );
// 	bool overEoverPCut = (eta < 1.47) ? (TMath::Abs(tree->eleEoverPInv_->at(eleInd))< 0.299  ) : (TMath::Abs(tree->eleEoverPInv_->at(eleInd))< 0.15  );
// 	bool MissHitsCut   = (eta < 1.47) ? (tree->eleMissHits_->at(eleInd)             <= 2     ) : (tree->eleMissHits_->at(eleInd)             <= 3     );
// 	bool ConvVetoCut   = tree->eleConvVeto_->at(eleInd);
		
//     bool passTightID = SIEIECut && dEtaCut && dPhiCut && HoverECut && (doRelisoCut ? RelIsoCut : true) && overEoverPCut && MissHitsCut && ConvVetoCut;
	
// 	return true;

// }

// bool Selector::passPhoMediumID(int phoInd, bool cutHoverE, bool cutSIEIE, bool cutIso){

// 	double pt = tree->phoEt_->at(phoInd);
//     double eta = TMath::Abs(tree->phoSCEta_->at(phoInd));
//     bool passMediumID = false;

// 	double rhoCorrPFChIso  = max(0.0, tree->phoPFChIso_->at(phoInd)  - phoEffArea03ChHad(eta) *tree->rho_);
// 	double rhoCorrPFNeuIso = max(0.0, tree->phoPFNeuIso_->at(phoInd) - phoEffArea03NeuHad(eta)*tree->rho_);
// 	double rhoCorrPFPhoIso = max(0.0, tree->phoPFPhoIso_->at(phoInd) - phoEffArea03Pho(eta)   *tree->rho_);
	
//     if (eta < 1.47){
// 		if ((!cutHoverE || tree->phoHoverE_->at(phoInd)                < 0.0396  ) &&
// 			(!cutSIEIE  || tree->phoSigmaIEtaIEtaFull5x5_->at(phoInd)  < 0.01022 ) &&
// 			(!cutIso    || (rhoCorrPFChIso                              < 0.441 &&
// 							rhoCorrPFNeuIso                             < 2.725+0.0148*pt+0.000017*pt*pt &&
// 							rhoCorrPFPhoIso                             < 2.571+0.0047*pt))){
// 			passMediumID = true;
// 		}
//     } else {
// 		if ((!cutHoverE || tree->phoHoverE_->at(phoInd)                < 0.0219  ) &&
// 			(!cutSIEIE  || tree->phoSigmaIEtaIEtaFull5x5_->at(phoInd)  < 0.03001 ) &&
// 			(!cutIso    || (rhoCorrPFChIso                              < 0.442 &&
// 							rhoCorrPFNeuIso                             < 1.715+0.0163*pt+0.000014*pt*pt &&
// 							rhoCorrPFPhoIso                             < 3.863+0.0034*pt))){
// 			passMediumID = true;
// 		}
//     }
//     return passMediumID;
// }



Selector::~Selector(){
}
