#include<iostream>
#include"EventTree.h"

EventTree::EventTree(int nFiles, bool xRootDAccess, string year, char** fileNames){
	chain = new TChain("Events");

	//std::cout << chain->GetCacheSize() << std::endl;
	chain->SetCacheSize(50*1024*1024);
	if (xRootDAccess){
	    string dir = "root://cms-xrd-global.cern.ch/";
	    for(int fileI=0; fileI<nFiles; fileI++){
		string fName = (string) fileNames[fileI];
		chain->Add( (dir + fileNames[fileI]).c_str() );
	    }
	}
	else{
	    for(int fileI=0; fileI<nFiles; fileI++){
		chain->Add(fileNames[fileI]);
	    }
	}
	chain->SetBranchStatus("*",0);
	
	// keep some important branches
// //	chain->SetBranchStatus("nHLT",1);
// //	chain->SetBranchAddress("nHLT", &nHLT_);
// //	chain->SetBranchStatus("HLT",1);
// //	chain->SetBranchAddress("HLT", &HLT_);
// 	chain->SetBranchStatus("HLTEleMuX",1);
// 	chain->SetBranchAddress("HLTEleMuX", &HLTEleMuX);
// //	chain->SetBranchStatus("nGoodVtx",1);
// //	chain->SetBranchAddress("nGoodVtx", &nGoodVtx_);
// 	chain->SetBranchStatus("nGoodVtx",1);
// 	chain->SetBranchAddress("nGoodVtx", &nGoodVtx);


 	chain->SetBranchStatus("PV_ndof",1);
 	chain->SetBranchAddress("PV_ndof", &pvNDOF_);

 	chain->SetBranchStatus("PV_x",1);
 	chain->SetBranchAddress("PV_x", &pvX_);

 	chain->SetBranchStatus("PV_y",1);
 	chain->SetBranchAddress("PV_y", &pvY_);

 	chain->SetBranchStatus("PV_z",1);
 	chain->SetBranchAddress("PV_z", &pvZ_);

 	chain->SetBranchStatus("PV_chi2",1);
 	chain->SetBranchAddress("PV_chi2", &pvChi2_);


 	chain->SetBranchStatus("Pileup_nPU",1);
 	chain->SetBranchAddress("Pileup_nPU", &nPU_);

 	chain->SetBranchStatus("Pileup_nTrueInt",1);
 	chain->SetBranchAddress("Pileup_nTrueInt", &nPUTrue_);


// 	chain->SetBranchStatus("nPUInfo",1);
// 	chain->SetBranchAddress("nPUInfo", &nPUInfo_);
// 	nPU_ = new vector<int>;
// 	chain->SetBranchStatus("nPU",1);
// 	chain->SetBranchAddress("nPU", &nPU_);
// 	puBX_ = new vector<int>;
// 	chain->SetBranchStatus("puBX",1);
// 	chain->SetBranchAddress("puBX", &puBX_);
// 	puTrue_ = new vector<float>;
// 	chain->SetBranchStatus("puTrue",1);
// 	chain->SetBranchAddress("puTrue", &puTrue_);
// 	chain->SetBranchStatus("pdf",1);
// 	chain->SetBranchAddress("pdf", &pdf_);
        
        
//         chain->SetBranchStatus("pdfWeight",1);
//         chain->SetBranchAddress("pdfWeight", &pdfWeight_);
        
// 	pdfSystWeight_ = new vector<float>;
// 	chain->SetBranchStatus("pdfSystWeight",1);
// 	chain->SetBranchAddress("pdfSystWeight", &pdfSystWeight_);
	

	//chain->SetBranchStatus("",1);
	
	// event
	
	chain->SetBranchStatus("run",1);
	chain->SetBranchAddress("run", &run_);

	chain->SetBranchStatus("event",1);
	chain->SetBranchAddress("event", &event_);
	
	chain->SetBranchStatus("luminosityBlock",1);
	chain->SetBranchAddress("luminosityBlock", &lumis_);

	// chain->SetBranchStatus("isData",1);
	// chain->SetBranchAddress("isData", &isData_);

	chain->SetBranchStatus("Generator_weight",1);
	chain->SetBranchAddress("Generator_weight", &genWeight_);

 	chain->SetBranchStatus("PV_npvs",1);
 	chain->SetBranchAddress("PV_npvs", &nVtx_);

 	chain->SetBranchStatus("PV_npvsGood",1);
 	chain->SetBranchAddress("PV_npvsGood", &nGoodVtx_);


	chain->SetBranchStatus("nLHEScaleWeight",1);
 	chain->SetBranchAddress("nLHEScaleWeight", &nLHEScaleWeight_);

	chain->SetBranchStatus("LHEScaleWeight",1);
 	chain->SetBranchAddress("LHEScaleWeight", &LHEScaleWeight_);

	chain->SetBranchStatus("nLHEPdfWeight",1);
 	chain->SetBranchAddress("nLHEPdfWeight", &nLHEPdfWeight_);

	chain->SetBranchStatus("LHEPdfWeight",1);
 	chain->SetBranchAddress("LHEPdfWeight", &LHEPdfWeight_);


	// MET
 	chain->SetBranchStatus("MET_pt",1);
 	chain->SetBranchAddress("MET_pt", &MET_pt_);

 	chain->SetBranchStatus("MET_phi",1);
 	chain->SetBranchAddress("MET_phi", &MET_phi_);

 	chain->SetBranchStatus("GenMET_pt",1);
 	chain->SetBranchAddress("GenMET_pt", &GenMET_pt_);

 	chain->SetBranchStatus("GenMET_phi",1);
 	chain->SetBranchAddress("GenMET_phi", &GenMET_phi_);


	
	// electrons	
	
	chain->SetBranchStatus("nElectron",1);
	chain->SetBranchAddress("nElectron", &nEle_);


        chain->SetBranchStatus("Electron_charge",1);
        chain->SetBranchAddress("Electron_charge", &eleCharge_);	

 	chain->SetBranchStatus("Electron_pt",1);
 	chain->SetBranchAddress("Electron_pt", &elePt_);

 	chain->SetBranchStatus("Electron_deltaEtaSC",1);
 	chain->SetBranchAddress("Electron_deltaEtaSC", &eleDeltaEtaSC_);

 	chain->SetBranchStatus("Electron_eta",1);
 	chain->SetBranchAddress("Electron_eta", &eleEta_);

 	chain->SetBranchStatus("Electron_phi",1);
 	chain->SetBranchAddress("Electron_phi", &elePhi_);

 	chain->SetBranchStatus("Electron_mass",1);
 	chain->SetBranchAddress("Electron_mass", &eleMass_);

 	chain->SetBranchStatus("Electron_pfRelIso03_chg",1);
 	chain->SetBranchAddress("Electron_pfRelIso03_chg", &elePFRelChIso_);

 	chain->SetBranchStatus("Electron_pfRelIso03_all",1);
 	chain->SetBranchAddress("Electron_pfRelIso03_all", &elePFRelIso_);

	chain->SetBranchStatus("Electron_sieie",1);
 	chain->SetBranchAddress("Electron_sieie", &eleSIEIE_);
	
	// chain->SetBranchStatus("Electron_cutBased",1);
	// chain->SetBranchAddress("Electron_cutBased", &eleIDcutbased_);
	
	if (year=="2016"){
	    chain->SetBranchStatus("Electron_cutBased_Sum16",1);
	    chain->SetBranchAddress("Electron_cutBased_Sum16", &eleIDcutbased_);

	    chain->SetBranchStatus("Electron_vidNestedWPBitmapSum16",1);
	    chain->SetBranchAddress("Electron_vidNestedWPBitmapSum16", &eleVidWPBitmap_);

	}
	if (year=="2017" || year=="2018"){

	    chain->SetBranchStatus("Electron_cutBased",1);
	    chain->SetBranchAddress("Electron_cutBased", &eleIDcutbased_);

	    chain->SetBranchStatus("Electron_vidNestedWPBitmap",1);
	    chain->SetBranchAddress("Electron_vidNestedWPBitmap", &eleVidWPBitmap_);
	
	}

 	chain->SetBranchStatus("Electron_dxy",1);
 	chain->SetBranchAddress("Electron_dxy", &eleD0_);

 	chain->SetBranchStatus("Electron_dz",1);
 	chain->SetBranchAddress("Electron_dz", &eleDz_);


 	chain->SetBranchStatus("Electron_dr03EcalRecHitSumEt",1);
 	chain->SetBranchAddress("Electron_dr03EcalRecHitSumEt", &eleEcalSumEtDr03_);

 	chain->SetBranchStatus("Electron_dr03HcalDepth1TowerSumEt",1);
 	chain->SetBranchAddress("Electron_dr03HcalDepth1TowerSumEt", &eleHcalSumEtDr03_);

 	chain->SetBranchStatus("Electron_dr03TkSumPt",1);
 	chain->SetBranchAddress("Electron_dr03TkSumPt", &eleTrkSumPtDr03_);



// 	eleMissHits_ = new vector<int>;
// 	chain->SetBranchStatus("eleMissHits",1);
// 	chain->SetBranchAddress("eleMissHits", &eleMissHits_);

// 	eleConvVeto_ = new vector<int>;
// 	chain->SetBranchStatus("eleConvVeto",1);
// 	chain->SetBranchAddress("eleConvVeto", &eleConvVeto_);

// 	eleEoverP_ = new vector<float>;
// 	chain->SetBranchStatus("eleEoverP",1);
// 	chain->SetBranchAddress("eleEoverP", &eleEoverP_);

// 	eleEoverPInv_ = new vector<float>;
// 	chain->SetBranchStatus("eleEoverPInv",1);
// 	chain->SetBranchAddress("eleEoverPInv", &eleEoverPInv_);

// 	// keep this branch in the skim
// 	//chain->SetBranchStatus("elePin",1);

// 	eleSigmaIPhiIPhiFull5x5_ = new vector<float>;
// 	chain->SetBranchStatus("eleSigmaIEtaIEtaFull5x5",1);
// 	chain->SetBranchAddress("eleSigmaIEtaIEtaFull5x5", &eleSigmaIEtaIEtaFull5x5_);

// 	eledEtaseedAtVtx_ = new vector<float>;
// 	chain->SetBranchStatus("eledEtaseedAtVtx",1);
// 	chain->SetBranchAddress("eledEtaseedAtVtx", &eledEtaseedAtVtx_);

// 	eledEtaAtVtx_ = new vector<float>;
// 	chain->SetBranchStatus("eledEtaAtVtx",1);
// 	chain->SetBranchAddress("eledEtaAtVtx", &eledEtaAtVtx_);

// 	eledPhiAtVtx_ = new vector<float>;
// 	chain->SetBranchStatus("eledPhiAtVtx",1);
// 	chain->SetBranchAddress("eledPhiAtVtx", &eledPhiAtVtx_);

// 	//eleEcalEn_ = new vector<float>;
// 	//chain->SetBranchStatus("eleEcalEn",1);
// 	//chain->SetBranchAddress("eleEcalEn", &eleEcalEn_);

// 	eleHoverE_ = new vector<float>;
// 	chain->SetBranchStatus("eleHoverE",1);
// 	chain->SetBranchAddress("eleHoverE", &eleHoverE_);

// 	elePFClusEcalIso_ = new vector<float>;
// 	chain->SetBranchStatus("elePFClusEcalIso",1);
// 	chain->SetBranchAddress("elePFClusEcalIso", &elePFClusEcalIso_);

// 	elePFClusHcalIso_ = new vector<float>;
// 	chain->SetBranchStatus("elePFClusHcalIso",1);
// 	chain->SetBranchAddress("elePFClusHcalIso", &elePFClusHcalIso_);

// 	eleDr03TkSumPt_ = new vector<float>;
// 	chain->SetBranchStatus("eleDr03TkSumPt",1);
// 	chain->SetBranchAddress("eleDr03TkSumPt", &eleDr03TkSumPt_);


//         eleScale_stat_up_ = new vector<float>;
//         chain->SetBranchStatus("eleScale_stat_up",1);
//         chain->SetBranchAddress("eleScale_stat_up", &eleScale_stat_up_);

//         eleScale_stat_dn_ = new vector<float>;
//         chain->SetBranchStatus("eleScale_stat_dn",1);
//         chain->SetBranchAddress("eleScale_stat_dn", &eleScale_stat_dn_);
// //
//         eleScale_syst_up_ = new vector<float>;
//         chain->SetBranchStatus("eleScale_syst_up",1);
//         chain->SetBranchAddress("eleScale_syst_up", &eleScale_syst_up_);

//         eleScale_syst_dn_ = new vector<float>;
//         chain->SetBranchStatus("eleScale_syst_dn",1);
//         chain->SetBranchAddress("eleScale_syst_dn", &eleScale_syst_dn_);


//         eleScale_gain_up_ = new vector<float>;
//         chain->SetBranchStatus("eleScale_gain_up",1);
//         chain->SetBranchAddress("eleScale_gain_up", &eleScale_gain_up_);

//         eleScale_gain_dn_ = new vector<float>;
//         chain->SetBranchStatus("eleScale_gain_dn",1);
//         chain->SetBranchAddress("eleScale_gain_dn", &eleScale_gain_dn_);


//         eleResol_rho_up_ = new vector<float>;
//         chain->SetBranchStatus("eleResol_rho_up",1);
//         chain->SetBranchAddress("eleResol_rho_up", &eleResol_rho_up_);

//         eleResol_rho_dn_ = new vector<float>;
//         chain->SetBranchStatus("eleResol_rho_dn",1);
//         chain->SetBranchAddress("eleResol_rho_dn", &eleResol_rho_dn_);

//         eleResol_phi_up_ = new vector<float>;
//         chain->SetBranchStatus("eleResol_phi_up",1);
//         chain->SetBranchAddress("eleResol_phi_up", &eleResol_phi_up_);

//         eleResol_phi_dn_ = new vector<float>;
//         chain->SetBranchStatus("eleResol_phi_dn",1);
//         chain->SetBranchAddress("eleResol_phi_dn", &eleResol_phi_dn_);

        

	// muons
	// keep some branches in the skim
	
	chain->SetBranchStatus("nMuon",1);
	chain->SetBranchAddress("nMuon", &nMuon_);

        chain->SetBranchStatus("Muon_charge",1);
        chain->SetBranchAddress("Muon_charge", &muCharge_);
	
	//	muPt_ = new vector<Float_t>;
	chain->SetBranchStatus("Muon_pt",1);
	chain->SetBranchAddress("Muon_pt", &muPt_);

	//	muEta_ = new vector<Float_t>;
	chain->SetBranchStatus("Muon_eta",1);
	chain->SetBranchAddress("Muon_eta", &muEta_);

	chain->SetBranchStatus("Muon_phi",1);
	chain->SetBranchAddress("Muon_phi", &muPhi_);

	chain->SetBranchStatus("Muon_mass",1);
	chain->SetBranchAddress("Muon_mass", &muMass_);

	chain->SetBranchStatus("Muon_pfRelIso04_all",1);
	chain->SetBranchAddress("Muon_pfRelIso04_all", &muPFRelIso_);

        chain->SetBranchStatus("Muon_tightId",1);
        chain->SetBranchAddress("Muon_tightId", &muTightId_);

        chain->SetBranchStatus("Muon_mediumId",1);
        chain->SetBranchAddress("Muon_mediumId", &muMediumId_);

        chain->SetBranchStatus("Muon_isPFcand",1);
        chain->SetBranchAddress("Muon_isPFcand", &muIsPFMuon_);

        chain->SetBranchStatus("Muon_isGlobal",1);
        chain->SetBranchAddress("Muon_isGlobal", &muIsGlobal_);

        chain->SetBranchStatus("Muon_isTracker",1);
        chain->SetBranchAddress("Muon_isTracker", &muIsTracker_);


	// jets
	
	chain->SetBranchStatus("nJet",1);
	chain->SetBranchAddress("nJet", &nJet_);
 
	chain->SetBranchStatus("Jet_pt",1);
	chain->SetBranchAddress("Jet_pt", &jetPt_);

	chain->SetBranchStatus("Jet_rawFactor",1);
        chain->SetBranchAddress("Jet_rawFactor", &jetRawFactor_);
	
	chain->SetBranchStatus("Jet_eta",1);
	chain->SetBranchAddress("Jet_eta", &jetEta_);
	
	chain->SetBranchStatus("Jet_phi",1);
	chain->SetBranchAddress("Jet_phi", &jetPhi_);

	chain->SetBranchStatus("Jet_mass",1);
	chain->SetBranchAddress("Jet_mass", &jetMass_);

	chain->SetBranchStatus("Jet_jetId",1);
	chain->SetBranchAddress("Jet_jetId", &jetID_);

	chain->SetBranchStatus("Jet_area",1);
	chain->SetBranchAddress("Jet_area", &jetArea_);

	chain->SetBranchStatus("Jet_btagCMVA",1);
	chain->SetBranchAddress("Jet_btagCMVA", &jetBtagCMVA_);

	chain->SetBranchStatus("Jet_btagCSVV2",1);
	chain->SetBranchAddress("Jet_btagCSVV2", &jetBtagCSVV2_);

	chain->SetBranchStatus("Jet_btagDeepB",1);
	chain->SetBranchAddress("Jet_btagDeepB", &jetBtagDeepB_);

	chain->SetBranchStatus("Jet_btagDeepC",1);
	chain->SetBranchAddress("Jet_btagDeepC", &jetBtagDeepC_);

	chain->SetBranchStatus("Jet_btagDeepFlavB",1);
	chain->SetBranchAddress("Jet_btagDeepFlavB", &jetBtagDeepFlavB_);


	chain->SetBranchStatus("Jet_hadronFlavour",1);
	chain->SetBranchAddress("Jet_hadronFlavour", &jetHadFlvr_);

	chain->SetBranchStatus("Jet_genJetIdx",1);
	chain->SetBranchAddress("Jet_genJetIdx", &jetGenJetIdx_);


	// jetP4Smear_ = new vector<float>;
	// chain->SetBranchStatus("jetP4Smear",1);
	// chain->SetBranchAddress("jetP4Smear", &jetP4Smear_);

	// jetP4SmearUp_ = new vector<float>;
	// chain->SetBranchStatus("jetP4SmearUp",1);
	// chain->SetBranchAddress("jetP4SmearUp", &jetP4SmearUp_);

	// jetP4SmearDo_ = new vector<float>;
	// chain->SetBranchStatus("jetP4SmearDo",1);
	// chain->SetBranchAddress("jetP4SmearDo", &jetP4SmearDo_);

	// jetJECUnc_ = new vector<float>;
	// chain->SetBranchStatus("jetJECUnc",1);
	// chain->SetBranchAddress("jetJECUnc", &jetJECUnc_);

	// jetCHF_ = new vector<float>;
	// chain->SetBranchStatus("jetCHF",1);
	// chain->SetBranchAddress("jetCHF", &jetCHF_);

	// jetNHF_ = new vector<float>;
	// chain->SetBranchStatus("jetNHF",1);
	// chain->SetBranchAddress("jetNHF", &jetNHF_);

	// jetCEF_ = new vector<float>;
	// chain->SetBranchStatus("jetCEF",1);
	// chain->SetBranchAddress("jetCEF", &jetCEF_);

	// jetNEF_ = new vector<float>;
	// chain->SetBranchStatus("jetNEF",1);
	// chain->SetBranchAddress("jetNEF", &jetNEF_);

	// jetNCH_ = new vector<int>;
	// chain->SetBranchStatus("jetNCH",1);
	// chain->SetBranchAddress("jetNCH", &jetNCH_);

	// jetNNP_ = new vector<int>;
	// chain->SetBranchStatus("jetNNP",1);
	// chain->SetBranchAddress("jetNNP", &jetNNP_);

	// jetMUF_ = new vector<float>;
	// chain->SetBranchStatus("jetMUF",1);
	// chain->SetBranchAddress("jetMUF", &jetMUF_);

	// jetpfCombinedMVAV2BJetTags_ = new vector<float>;
	// chain->SetBranchStatus("jetpfCombinedMVAV2BJetTags",1);
	// chain->SetBranchAddress("jetpfCombinedMVAV2BJetTags", &jetpfCombinedMVAV2BJetTags_);
	
	// jetCSV2BJetTags_ = new vector<float>;
	// chain->SetBranchStatus("jetCSV2BJetTags",1);
	// chain->SetBranchAddress("jetCSV2BJetTags", &jetCSV2BJetTags_);

	// jetDeepCSVTags_b_ = new vector<float>;
	// chain->SetBranchStatus("jetDeepCSVTags_b",1);
	// chain->SetBranchAddress("jetDeepCSVTags_b", &jetDeepCSVTags_b_);

	// jetDeepCSVTags_bb_ = new vector<float>;
	// chain->SetBranchStatus("jetDeepCSVTags_bb",1);
	// chain->SetBranchAddress("jetDeepCSVTags_bb", &jetDeepCSVTags_bb_);

	// jetDeepCSVTags_c_ = new vector<float>;
	// chain->SetBranchStatus("jetDeepCSVTags_c",1);
	// chain->SetBranchAddress("jetDeepCSVTags_c", &jetDeepCSVTags_c_);

	// jetDeepCSVTags_cc_ = new vector<float>;
	// chain->SetBranchStatus("jetDeepCSVTags_cc",1);
	// chain->SetBranchAddress("jetDeepCSVTags_cc", &jetDeepCSVTags_cc_);

	// jetDeepCSVTags_udsg_ = new vector<float>;
	// chain->SetBranchStatus("jetDeepCSVTags_udsg",1);
	// chain->SetBranchAddress("jetDeepCSVTags_udsg", &jetDeepCSVTags_udsg_);

	// // jetCombinedSecondaryVtxMVABJetTags_ = new vector<float>;
	// // chain->SetBranchStatus("jetCombinedSecondaryVtxMVABJetTags",1);
	// // chain->SetBranchAddress("jetCombinedSecondaryVtxMVABJetTags", &jetCombinedSecondaryVtxMVABJetTags_);

	// jetHadFlvr_ = new vector<int>;
	// chain->SetBranchStatus("jetHadFlvr",1);
	// chain->SetBranchAddress("jetHadFlvr", &jetHadFlvr_);

	// jetPartonID_ = new vector<int>;
	// chain->SetBranchStatus("jetPartonID",1);
	// chain->SetBranchAddress("jetPartonID", &jetPartonID_);
	
	// jetGenPartonID_ = new vector<int>;
	// chain->SetBranchStatus("jetGenPartonID",1);
	// chain->SetBranchAddress("jetGenPartonID", &jetGenPartonID_);
	
	// //jetGenJetIndex_ = new vector<int>;
	// //chain->SetBranchStatus("jetGenJetIndex",1);
	// //chain->SetBranchAddress("jetGenJetIndex", &jetGenJetIndex_);

	// jetGenJetPt_ = new vector<float>;
	// chain->SetBranchStatus("jetGenJetPt",1);
	// chain->SetBranchAddress("jetGenJetPt", &jetGenJetPt_);

	// jetGenJetEta_ = new vector<float>;
        // chain->SetBranchStatus("jetGenJetEta",1);
        // chain->SetBranchAddress("jetGenJetEta", &jetGenJetEta_);

	// jetGenJetPhi_ = new vector<float>;
        // chain->SetBranchStatus("jetGenJetPhi",1);
        // chain->SetBranchAddress("jetGenJetPhi", &jetGenJetPhi_);

	// jetGenPt_ = new vector<float>;
	// chain->SetBranchStatus("jetGenPt",1);
	// chain->SetBranchAddress("jetGenPt", &jetGenPt_);
	
	// jetGenEta_ = new vector<float>;
	// chain->SetBranchStatus("jetGenEta",1);
	// chain->SetBranchAddress("jetGenEta", &jetGenEta_);
	
	// jetGenPhi_ = new vector<float>;
	// chain->SetBranchStatus("jetGenPhi",1);
	// chain->SetBranchAddress("jetGenPhi", &jetGenPhi_);

	// // photons
	
	chain->SetBranchStatus("nPhoton",1);
	chain->SetBranchAddress("nPhoton", &nPho_);

	chain->SetBranchStatus("Photon_pt",1);
        chain->SetBranchAddress("Photon_pt", &phoEt_);
	
	chain->SetBranchStatus("Photon_eta",1);
	chain->SetBranchAddress("Photon_eta", &phoEta_);

	chain->SetBranchStatus("Photon_phi",1);
	chain->SetBranchAddress("Photon_phi", &phoPhi_);
	
	chain->SetBranchStatus("Photon_isScEtaEB",1);
	chain->SetBranchAddress("Photon_isScEtaEB", &phoIsEB_);

	chain->SetBranchStatus("Photon_isScEtaEE",1);
	chain->SetBranchAddress("Photon_isScEtaEE", &phoIsEE_);

	if (year=="2016"){
	    chain->SetBranchStatus("Photon_cutBased",1);
	    chain->SetBranchAddress("Photon_cutBased", &phoIDcutbased_);
	}
	if (year=="2017" || year=="2018"){
	    chain->SetBranchStatus("Photon_cutBasedBitmap",1);
	    chain->SetBranchAddress("Photon_cutBasedBitmap", &phoIDcutbased_);
	}
	

	chain->SetBranchStatus("Photon_pfRelIso03_all",1);
	chain->SetBranchAddress("Photon_pfRelIso03_all", &phoPFRelIso_);

	chain->SetBranchStatus("Photon_pfRelIso03_chg",1);
	chain->SetBranchAddress("Photon_pfRelIso03_chg", &phoPFRelChIso_);

	chain->SetBranchStatus("Photon_vidNestedWPBitmap",1);
	chain->SetBranchAddress("Photon_vidNestedWPBitmap", &phoVidWPBitmap_);

	chain->SetBranchStatus("Photon_pixelSeed",1);
	chain->SetBranchAddress("Photon_pixelSeed", &phoPixelSeed_);

	chain->SetBranchStatus("Photon_r9",1);
	chain->SetBranchAddress("Photon_r9", &phoR9_);

	chain->SetBranchStatus("Photon_sieie",1);
	chain->SetBranchAddress("Photon_sieie", &phoSIEIE_);

	chain->SetBranchStatus("Photon_hoe",1);
	chain->SetBranchAddress("Photon_hoe", &phoHoverE_);

	chain->SetBranchStatus("Photon_genPartIdx",1);
	chain->SetBranchAddress("Photon_genPartIdx", &phoGenPartIdx_);

	// phoCalibE_ = new vector<float>;	
	// chain->SetBranchStatus("phoCalibE",1);
	// chain->SetBranchAddress("phoCalibE", &phoCalibE_);
	
	// phoCalibEt_ = new vector<float>;	
	// chain->SetBranchStatus("phoCalibEt",1);
	// chain->SetBranchAddress("phoCalibEt", &phoCalibEt_);
	
	// //phoSeedBCE_ = new vector<int>;
	// //chain->SetBranchStatus("phoSeedBCE",1);
	// //chain->SetBranchAddress("phoSeedBCE", &phoSeedBCE_);
	
	// phohasPixelSeed_ = new vector<int>;
	// chain->SetBranchStatus("phohasPixelSeed",1);
	// chain->SetBranchAddress("phohasPixelSeed", &phohasPixelSeed_);

	// phoEleVeto_ = new vector<int>;
	// chain->SetBranchStatus("phoEleVeto",1);
	// chain->SetBranchAddress("phoEleVeto", &phoEleVeto_);
	
	// phoIDbit_ = new vector<unsigned short>;
	// chain->SetBranchStatus("phoIDbit",1);
	// chain->SetBranchAddress("phoIDbit", &phoIDbit_);

	// phoHoverE_ = new vector<float>;
	// chain->SetBranchStatus("phoHoverE",1);
	// chain->SetBranchAddress("phoHoverE", &phoHoverE_);

	// phoSigmaIEtaIEtaFull5x5_ = new vector<float>;
	// chain->SetBranchStatus("phoSigmaIEtaIEtaFull5x5",1);
	// chain->SetBranchAddress("phoSigmaIEtaIEtaFull5x5", &phoSigmaIEtaIEtaFull5x5_);
	
	// phoPFChIso_ = new vector<float>;
	// chain->SetBranchStatus("phoPFChIso",1);
	// chain->SetBranchAddress("phoPFChIso", &phoPFChIso_);
	
	// phoPFNeuIso_ = new vector<float>;
	// chain->SetBranchStatus("phoPFNeuIso",1);
	// chain->SetBranchAddress("phoPFNeuIso", &phoPFNeuIso_);

	// phoPFPhoIso_ = new vector<float>;
	// chain->SetBranchStatus("phoPFPhoIso",1);
	// chain->SetBranchAddress("phoPFPhoIso", &phoPFPhoIso_);

	// phoR9_ = new vector<float>;
	// chain->SetBranchStatus("phoR9",1);
	// chain->SetBranchAddress("phoR9", &phoR9_);

	// phoPFRandConeChIso_ = new vector<vector<float>>;
	// chain->SetBranchStatus("phoPFRandConeChIso",1);
	// chain->SetBranchAddress("phoPFRandConeChIso", &phoPFRandConeChIso_);

	// phoPFRandConePhi_ = new vector<vector<float>>;
	// chain->SetBranchStatus("phoPFRandConePhi",1);
	// chain->SetBranchAddress("phoPFRandConePhi", &phoPFRandConePhi_);

        // phoScale_stat_up_ = new vector<float>;
        // chain->SetBranchStatus("phoScale_stat_up",1);
        // chain->SetBranchAddress("phoScale_stat_up", &phoScale_stat_up_); 

        // phoScale_stat_dn_ = new vector<float>;
        // chain->SetBranchStatus("phoScale_stat_dn",1);
        // chain->SetBranchAddress("phoScale_stat_dn", &phoScale_stat_dn_);

        // phoScale_syst_up_ = new vector<float>;
        // chain->SetBranchStatus("phoScale_syst_up",1);
        // chain->SetBranchAddress("phoScale_syst_up", &phoScale_syst_up_);

        // phoScale_syst_dn_ = new vector<float>;
        // chain->SetBranchStatus("phoScale_syst_dn",1);
        // chain->SetBranchAddress("phoScale_syst_dn", &phoScale_syst_dn_);


        // phoScale_gain_up_ = new vector<float>;
        // chain->SetBranchStatus("phoScale_gain_up",1);
        // chain->SetBranchAddress("phoScale_gain_up", &phoScale_gain_up_);

        // phoScale_gain_dn_ = new vector<float>;
        // chain->SetBranchStatus("phoScale_gain_dn",1);
        // chain->SetBranchAddress("phoScale_gain_dn", &phoScale_gain_dn_);

       
        // phoResol_rho_up_ = new vector<float>;
        // chain->SetBranchStatus("phoResol_rho_up",1);
        // chain->SetBranchAddress("phoResol_rho_up", &phoResol_rho_up_);
        
        // phoResol_rho_dn_ = new vector<float>;
        // chain->SetBranchStatus("phoResol_rho_dn",1);
        // chain->SetBranchAddress("phoResol_rho_dn", &phoResol_rho_dn_);

        // phoResol_phi_up_ = new vector<float>;
        // chain->SetBranchStatus("phoResol_phi_up",1);
        // chain->SetBranchAddress("phoResol_phi_up", &phoResol_phi_up_);

        // phoResol_phi_dn_ = new vector<float>;
        // chain->SetBranchStatus("phoResol_phi_dn",1);
        // chain->SetBranchAddress("phoResol_phi_dn", &phoResol_phi_dn_);

	// //phoPFPhoIso_ = new vector<float>;
	// //chain->SetBranchStatus("phoPFPhoIso",1);
	// //chain->SetBranchAddress("phoPFPhoIso", &phoPFPhoIsoFrix7_);

	// //phoPFChIsoFrix7_ = new vector<float>;
	// //chain->SetBranchStatus("phoPFChIsoFrix7",1);
	// //chain->SetBranchAddress("phoPFChIsoFrix7", &phoPFChIsoFrix7_);
	
	// //phoPFPhoIsoFrix6_ = new vector<float>;
	// //chain->SetBranchStatus("phoPFPhoIsoFrix6",1);
	// //chain->SetBranchAddress("phoPFPhoIsoFrix6", &phoPFPhoIsoFrix6_);
	
	// //phoPFChIsoFrix6_ = new vector<float>;
	// //chain->SetBranchStatus("phoPFChIsoFrix6",1);
	// //chain->SetBranchAddress("phoPFChIsoFrix6", &phoPFChIsoFrix6_);

	// //phoGenIndex_ = new vector<int>;
	// //chain->SetBranchStatus("phoGenIndex",1);
	// //chain->SetBranchAddress("phoGenIndex", &phoGenIndex_);
	
	// //phoGenGMomPID_ = new vector<int>;
	// //chain->SetBranchStatus("phoGenGMomPID",1);
	// //chain->SetBranchAddress("phoGenGMomPID", &phoGenGMomPID_);
	
	// //phoGenMomPID_ = new vector<int>;
	// //chain->SetBranchStatus("phoGenMomPID",1);
	// //chain->SetBranchAddress("phoGenMomPID", &phoGenMomPID_);
	

        // Gen Partons

        chain->SetBranchStatus("nGenPart",1);
        chain->SetBranchAddress("nGenPart", &nGenPart_);

        chain->SetBranchStatus("GenPart_pt",1);
        chain->SetBranchAddress("GenPart_pt", &GenPart_pt_);

        chain->SetBranchStatus("GenPart_eta",1);
        chain->SetBranchAddress("GenPart_eta", &GenPart_eta_);

        chain->SetBranchStatus("GenPart_phi",1);
        chain->SetBranchAddress("GenPart_phi", &GenPart_phi_);

        chain->SetBranchStatus("GenPart_mass",1);
        chain->SetBranchAddress("GenPart_mass", &GenPart_mass_);

        chain->SetBranchStatus("GenPart_genPartIdxMother",1);
        chain->SetBranchAddress("GenPart_genPartIdxMother", &GenPart_genPartIdxMother_);

        chain->SetBranchStatus("GenPart_pdgId",1);
        chain->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId_);

        chain->SetBranchStatus("GenPart_status",1);
        chain->SetBranchAddress("GenPart_status", &GenPart_status_);

        chain->SetBranchStatus("GenPart_statusFlags",1);
        chain->SetBranchAddress("GenPart_statusFlags", &GenPart_statusFlags_);


        chain->SetBranchStatus("nGenJet",1);
        chain->SetBranchAddress("nGenJet", &nGenJet_);

        chain->SetBranchStatus("GenJet_pt",1);
        chain->SetBranchAddress("GenJet_pt", &GenJet_pt_);

        chain->SetBranchStatus("GenJet_eta",1);
        chain->SetBranchAddress("GenJet_eta", &GenJet_eta_);

        chain->SetBranchStatus("GenJet_phi",1);
        chain->SetBranchAddress("GenJet_phi", &GenJet_phi_);

        chain->SetBranchStatus("GenJet_mass",1);
        chain->SetBranchAddress("GenJet_mass", &GenJet_mass_);



	// // MC gen particles
	
	// chain->SetBranchStatus("nMC",1);
	// chain->SetBranchAddress("nMC", &nMC_);
	
	// mcPt = new vector<float>;
	// chain->SetBranchStatus("mcPt",1);
	// chain->SetBranchAddress("mcPt", &mcPt);

	// genScaleSystWeights_ = new vector<float>;
        // chain->SetBranchStatus("genScaleSystWeights",1);
        // chain->SetBranchAddress("genScaleSystWeights", &genScaleSystWeights_);

	// mcEta = new vector<float>;
	// chain->SetBranchStatus("mcEta",1);
	// chain->SetBranchAddress("mcEta", &mcEta);
	
	// mcPhi = new vector<float>;
	// chain->SetBranchStatus("mcPhi",1);
	// chain->SetBranchAddress("mcPhi", &mcPhi);
	
	// mcMass = new vector<float>;
	// chain->SetBranchStatus("mcMass",1);
	// chain->SetBranchAddress("mcMass", &mcMass);
	
	// mcPID = new vector<int>;
	// chain->SetBranchStatus("mcPID",1);
	// chain->SetBranchAddress("mcPID", &mcPID);
	
	// mcMomPID = new vector<int>;
	// chain->SetBranchStatus("mcMomPID",1);
	// chain->SetBranchAddress("mcMomPID", &mcMomPID);
	
	// mcGMomPID = new vector<int>;
	// chain->SetBranchStatus("mcGMomPID",1);
	// chain->SetBranchAddress("mcGMomPID", &mcGMomPID);

	// mcMomPt = new vector<float>;
	// chain->SetBranchStatus("mcMomPt",1);
	// chain->SetBranchAddress("mcMomPt", &mcMomPt);
	
	// //mcDecayType = new vector<int>;
	// //chain->SetBranchStatus("mcDecayType",1);
	// //chain->SetBranchAddress("mcDecayType", &mcDecayType);
	
	// //mcIndex = new vector<int>;
	// //chain->SetBranchStatus("mcIndex",1);
	// //chain->SetBranchAddress("mcIndex", &mcIndex);

	// mcStatus = new vector<int>;
	// chain->SetBranchStatus("mcStatus",1);
	// chain->SetBranchAddress("mcStatus", &mcStatus);
	
        // mcStatusFlag = new vector<UShort_t>;
        // chain->SetBranchStatus("mcStatusFlag",1);
        // chain->SetBranchAddress("mcStatusFlag", &mcStatusFlag);	
	// // // mcMomPt = new vector<float>;
	// // // chain->SetBranchStatus("mcMomPt",1);
	// // // chain->SetBranchAddress("mcMomPt", &mcMomPt);
	
	// mcMomEta = new vector<float>;
	// chain->SetBranchStatus("mcMomEta",1);
	// chain->SetBranchAddress("mcMomEta", &mcMomEta);
	
	// mcMomPhi = new vector<float>;
	// chain->SetBranchStatus("mcMomPhi",1);
	// chain->SetBranchAddress("mcMomPhi", &mcMomPhi);
	
	// mcMomMass = new vector<float>;
	// chain->SetBranchStatus("mcMomMass",1);
	// chain->SetBranchAddress("mcMomMass", &mcMomMass);
	
	// mcParentage = new vector<int>;
	// chain->SetBranchStatus("mcParentage",1);
	// chain->SetBranchAddress("mcParentage", &mcParentage);
	
	// //chain->SetBranchStatus("",1);
	//chain->SetBranchAddress("", _);


        //TRIGGERS

	if (year=="2016"){
	    chain->SetBranchStatus("HLT_Ele32_eta2p1_WPTight_Gsf",1);
	    chain->SetBranchAddress("HLT_Ele32_eta2p1_WPTight_Gsf",&HLT_Ele32_eta2p1_WPTight_Gsf_);

	    chain->SetBranchStatus("HLT_IsoMu24",1);
	    chain->SetBranchAddress("HLT_IsoMu24",&HLT_IsoMu24_);

	    chain->SetBranchStatus("HLT_IsoTkMu24",1);
	    chain->SetBranchAddress("HLT_IsoTkMu24",&HLT_IsoTkMu24_);

	}
	
	if (year=="2017"){
	    chain->SetBranchStatus("HLT_Ele32_WPTight_Gsf_L1DoubleEG",1);
	    chain->SetBranchAddress("HLT_Ele32_WPTight_Gsf_L1DoubleEG",&HLT_Ele32_WPTight_Gsf_L1DoubleEG_);

	    chain->SetBranchStatus("HLT_Ele35_WPTight_Gsf",1);
	    chain->SetBranchAddress("HLT_Ele35_WPTight_Gsf",&HLT_Ele35_WPTight_Gsf_);

	    chain->SetBranchStatus("HLT_IsoMu24",1);
	    chain->SetBranchAddress("HLT_IsoMu24",&HLT_IsoMu24_);

	    chain->SetBranchStatus("HLT_IsoTkMu24",1);
	    chain->SetBranchAddress("HLT_IsoTkMu24",&HLT_IsoTkMu24_);

	    chain->SetBranchStatus("HLT_IsoMu24_eta2p1",1);
	    chain->SetBranchAddress("HLT_IsoMu24_eta2p1",&HLT_IsoMu24_eta2p1_);

	    chain->SetBranchStatus("HLT_IsoMu27",1);
	    chain->SetBranchAddress("HLT_IsoMu27",&HLT_IsoMu27_);

	}

	if (year=="2018"){
            chain->SetBranchStatus("HLT_Ele32_WPTight_Gsf",1);
            chain->SetBranchAddress("HLT_Ele32_WPTight_Gsf",&HLT_Ele32_WPTight_Gsf_);

            chain->SetBranchStatus("HLT_Ele35_WPTight_Gsf",1);
            chain->SetBranchAddress("HLT_Ele35_WPTight_Gsf",&HLT_Ele35_WPTight_Gsf_);

            chain->SetBranchStatus("HLT_Ele38_WPTight_Gsf",1);
            chain->SetBranchAddress("HLT_Ele38_WPTight_Gsf",&HLT_Ele38_WPTight_Gsf_);

	    chain->SetBranchStatus("HLT_IsoMu24",1);
	    chain->SetBranchAddress("HLT_IsoMu24",&HLT_IsoMu24_);

	}	

        chain->SetBranchStatus("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",1);
        chain->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL",&HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_);

        chain->SetBranchStatus("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",1);
        chain->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",&HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_);

        chain->SetBranchStatus("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",1);
        chain->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",&HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_);

        chain->SetBranchStatus("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",1);
        chain->SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",&HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_);

        chain->SetBranchStatus("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",1);
        chain->SetBranchAddress("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL",&HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_);

        chain->SetBranchStatus("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",1);
        chain->SetBranchAddress("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ",&HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_);



}

EventTree::~EventTree(){
	delete chain;
	// will be some memory leak due to created vectors
}

Long64_t EventTree::GetEntries(){
	return chain->GetEntries();
}

Int_t EventTree::GetEntry(Long64_t entry){
	chain->GetEntry(entry);
	return chain->GetEntries();
}
