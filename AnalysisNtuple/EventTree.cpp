#include"EventTree.h"

EventTree::EventTree(int nFiles, char** fileNames){
	chain = new TChain("ggNtuplizer/EventTree");
	for(int fileI=0; fileI<nFiles; fileI++){
		chain->Add(fileNames[fileI]);
	}
	chain->SetBranchStatus("*",0);
	
	// keep some important branches
//	chain->SetBranchStatus("nHLT",1);
//	chain->SetBranchAddress("nHLT", &nHLT_);
//	chain->SetBranchStatus("HLT",1);
//	chain->SetBranchAddress("HLT", &HLT_);
	chain->SetBranchStatus("HLTEleMuX",1);
	chain->SetBranchAddress("HLTEleMuX", &HLTEleMuX);
//	chain->SetBranchStatus("nGoodVtx",1);
//	chain->SetBranchAddress("nGoodVtx", &nGoodVtx_);
	chain->SetBranchStatus("nGoodVtx",1);
	chain->SetBranchAddress("nGoodVtx", &nGoodVtx);
//	chain->SetBranchStatus("bspotPos",1);
//	chain->SetBranchAddress("bspotPos", &bspotPos_);
	chain->SetBranchStatus("isPVGood",1);
	chain->SetBranchAddress("isPVGood", &isPVGood_);
	chain->SetBranchStatus("nPUInfo",1);
	chain->SetBranchAddress("nPUInfo", &nPUInfo_);
	nPU_ = new vector<int>;
	chain->SetBranchStatus("nPU",1);
	chain->SetBranchAddress("nPU", &nPU_);
	puBX_ = new vector<int>;
	chain->SetBranchStatus("puBX",1);
	chain->SetBranchAddress("puBX", &puBX_);
	puTrue_ = new vector<float>;
	chain->SetBranchStatus("puTrue",1);
	chain->SetBranchAddress("puTrue", &puTrue_);
	chain->SetBranchStatus("pdf",1);
	chain->SetBranchAddress("pdf", &pdf_);
        
        
        chain->SetBranchStatus("pdfWeight",1);
        chain->SetBranchAddress("pdfWeight", &pdfWeight_);
        
	pdfSystWeight_ = new vector<float>;
	chain->SetBranchStatus("pdfSystWeight",1);
	chain->SetBranchAddress("pdfSystWeight", &pdfSystWeight_);
	

	//chain->SetBranchStatus("",1);
	
	// event
	
	chain->SetBranchStatus("run",1);
	chain->SetBranchAddress("run", &run_);

	chain->SetBranchStatus("event",1);
	chain->SetBranchAddress("event", &event_);
	
	chain->SetBranchStatus("lumis",1);
	chain->SetBranchAddress("lumis", &lumis_);

	chain->SetBranchStatus("isData",1);
	chain->SetBranchAddress("isData", &isData_);

	chain->SetBranchStatus("genWeight",1);
	chain->SetBranchAddress("genWeight", &genWeight_);

	chain->SetBranchStatus("nVtx",1);
	chain->SetBranchAddress("nVtx", &nVtx_);

	chain->SetBranchStatus("pfMET",1);    // FIXME
	chain->SetBranchAddress("pfMET", &pfMET_); // FIXME

	chain->SetBranchStatus("pfMETPhi",1); // FIXME
	chain->SetBranchAddress("pfMETPhi", &pfMETPhi_);  // FIXME

//	chain->SetBranchStatus("pfMET*",1);
//	chain->SetBranchStatus("pfType01MET*",1);

	chain->SetBranchStatus("genMET",1);    // FIXME
	chain->SetBranchAddress("genMET", &genMET_); // FIXME

	
	// electrons	
	
	chain->SetBranchStatus("nEle",1);
	chain->SetBranchAddress("nEle", &nEle_);

	//chain->SetBranchStatus("eleEta",1);
	
 	eleCharge_ = new vector<int>;
	chain->SetBranchStatus("eleCharge",1);
	chain->SetBranchAddress("eleCharge", &eleCharge_);	

	elePt_ = new vector<float>;
	chain->SetBranchStatus("elePt",1);
	chain->SetBranchAddress("elePt", &elePt_);

	eleEn_ = new vector<float>;
	chain->SetBranchStatus("eleEn",1);
	chain->SetBranchAddress("eleEn", &eleEn_);

	eleSCEta_ = new vector<float>;
	chain->SetBranchStatus("eleSCEta",1);
	chain->SetBranchAddress("eleSCEta", &eleSCEta_);

	eleEta_ = new vector<float>;
	chain->SetBranchStatus("eleEta",1);
	chain->SetBranchAddress("eleEta", &eleEta_);

	elePhi_ = new vector<float>;
	chain->SetBranchStatus("elePhi",1);
	chain->SetBranchAddress("elePhi", &elePhi_);

	eleCalibPt_ = new vector<float>;
	chain->SetBranchStatus("eleCalibPt",1);
	chain->SetBranchAddress("eleCalibPt", &eleCalibPt_);

	eleCalibEn_ = new vector<float>;
	chain->SetBranchStatus("eleCalibEn",1);
	chain->SetBranchAddress("eleCalibEn", &eleCalibEn_);

	elePFChIso_ = new vector<float>;
	chain->SetBranchStatus("elePFChIso",1);
	chain->SetBranchAddress("elePFChIso", &elePFChIso_);

	elePFNeuIso_ = new vector<float>;
	chain->SetBranchStatus("elePFNeuIso",1);
	chain->SetBranchAddress("elePFNeuIso", &elePFNeuIso_);

	elePFPhoIso_ = new vector<float>;
	chain->SetBranchStatus("elePFPhoIso",1);
	chain->SetBranchAddress("elePFPhoIso", &elePFPhoIso_);

	chain->SetBranchStatus("rho",1);
	chain->SetBranchAddress("rho", &rho_);

	eleIDMVA_ = new vector<float>;
	chain->SetBranchStatus("eleIDMVA",1);
	chain->SetBranchAddress("eleIDMVA", &eleIDMVA_);
        
	// eleIDMVAHZZ_ = new vector<float>;
    //     chain->SetBranchStatus("eleIDMVAHZZ",1);
    //     chain->SetBranchAddress("eleIDMVAHZZ", &eleIDMVAHZZ_); 
        
	eleIDbit_ = new vector<unsigned short>;
        chain->SetBranchStatus("eleIDbit",1);
        chain->SetBranchAddress("eleIDbit", &eleIDbit_);

	eleD0_ = new vector<float>;
	chain->SetBranchStatus("eleD0",1);
	chain->SetBranchAddress("eleD0", &eleD0_);

	eleMissHits_ = new vector<int>;
	chain->SetBranchStatus("eleMissHits",1);
	chain->SetBranchAddress("eleMissHits", &eleMissHits_);

	eleConvVeto_ = new vector<int>;
	chain->SetBranchStatus("eleConvVeto",1);
	chain->SetBranchAddress("eleConvVeto", &eleConvVeto_);

	eleDz_ = new vector<float>;
	chain->SetBranchStatus("eleDz",1);
	chain->SetBranchAddress("eleDz", &eleDz_);

	eleEoverP_ = new vector<float>;
	chain->SetBranchStatus("eleEoverP",1);
	chain->SetBranchAddress("eleEoverP", &eleEoverP_);

	eleEoverPInv_ = new vector<float>;
	chain->SetBranchStatus("eleEoverPInv",1);
	chain->SetBranchAddress("eleEoverPInv", &eleEoverPInv_);

	// keep this branch in the skim
	//chain->SetBranchStatus("elePin",1);

	eleSigmaIPhiIPhiFull5x5_ = new vector<float>;
	chain->SetBranchStatus("eleSigmaIEtaIEtaFull5x5",1);
	chain->SetBranchAddress("eleSigmaIEtaIEtaFull5x5", &eleSigmaIEtaIEtaFull5x5_);

	eledEtaseedAtVtx_ = new vector<float>;
	chain->SetBranchStatus("eledEtaseedAtVtx",1);
	chain->SetBranchAddress("eledEtaseedAtVtx", &eledEtaseedAtVtx_);

	eledEtaAtVtx_ = new vector<float>;
	chain->SetBranchStatus("eledEtaAtVtx",1);
	chain->SetBranchAddress("eledEtaAtVtx", &eledEtaAtVtx_);

	eledPhiAtVtx_ = new vector<float>;
	chain->SetBranchStatus("eledPhiAtVtx",1);
	chain->SetBranchAddress("eledPhiAtVtx", &eledPhiAtVtx_);

	//eleEcalEn_ = new vector<float>;
	//chain->SetBranchStatus("eleEcalEn",1);
	//chain->SetBranchAddress("eleEcalEn", &eleEcalEn_);

	eleHoverE_ = new vector<float>;
	chain->SetBranchStatus("eleHoverE",1);
	chain->SetBranchAddress("eleHoverE", &eleHoverE_);

	elePFClusEcalIso_ = new vector<float>;
	chain->SetBranchStatus("elePFClusEcalIso",1);
	chain->SetBranchAddress("elePFClusEcalIso", &elePFClusEcalIso_);

	elePFClusHcalIso_ = new vector<float>;
	chain->SetBranchStatus("elePFClusHcalIso",1);
	chain->SetBranchAddress("elePFClusHcalIso", &elePFClusHcalIso_);

	eleDr03TkSumPt_ = new vector<float>;
	chain->SetBranchStatus("eleDr03TkSumPt",1);
	chain->SetBranchAddress("eleDr03TkSumPt", &eleDr03TkSumPt_);


        eleScale_stat_up_ = new vector<float>;
        chain->SetBranchStatus("eleScale_stat_up",1);
        chain->SetBranchAddress("eleScale_stat_up", &eleScale_stat_up_);

        eleScale_stat_dn_ = new vector<float>;
        chain->SetBranchStatus("eleScale_stat_dn",1);
        chain->SetBranchAddress("eleScale_stat_dn", &eleScale_stat_dn_);
//
        eleScale_syst_up_ = new vector<float>;
        chain->SetBranchStatus("eleScale_syst_up",1);
        chain->SetBranchAddress("eleScale_syst_up", &eleScale_syst_up_);

        eleScale_syst_dn_ = new vector<float>;
        chain->SetBranchStatus("eleScale_syst_dn",1);
        chain->SetBranchAddress("eleScale_syst_dn", &eleScale_syst_dn_);


        eleScale_gain_up_ = new vector<float>;
        chain->SetBranchStatus("eleScale_gain_up",1);
        chain->SetBranchAddress("eleScale_gain_up", &eleScale_gain_up_);

        eleScale_gain_dn_ = new vector<float>;
        chain->SetBranchStatus("eleScale_gain_dn",1);
        chain->SetBranchAddress("eleScale_gain_dn", &eleScale_gain_dn_);


        eleResol_rho_up_ = new vector<float>;
        chain->SetBranchStatus("eleResol_rho_up",1);
        chain->SetBranchAddress("eleResol_rho_up", &eleResol_rho_up_);

        eleResol_rho_dn_ = new vector<float>;
        chain->SetBranchStatus("eleResol_rho_dn",1);
        chain->SetBranchAddress("eleResol_rho_dn", &eleResol_rho_dn_);

        eleResol_phi_up_ = new vector<float>;
        chain->SetBranchStatus("eleResol_phi_up",1);
        chain->SetBranchAddress("eleResol_phi_up", &eleResol_phi_up_);

        eleResol_phi_dn_ = new vector<float>;
        chain->SetBranchStatus("eleResol_phi_dn",1);
        chain->SetBranchAddress("eleResol_phi_dn", &eleResol_phi_dn_);

        

	// muons
	// keep some branches in the skim
	
	
	muCharge_ = new vector<int>;
        chain->SetBranchStatus("muCharge",1);
        chain->SetBranchAddress("muCharge", &muCharge_);
	
	
	muChi2NDF_ = new vector<float>;
	chain->SetBranchStatus("muChi2NDF", 1);
	chain->SetBranchAddress("muChi2NDF",&muChi2NDF_);

	muTrkLayers_ = new vector<int>;
	chain->SetBranchStatus("muTrkLayers",1);
	chain->SetBranchAddress("muTrkLayers",&muTrkLayers_);
		
	muMuonHits_ = new vector<int>;
	chain->SetBranchStatus("muMuonHits",1);
	chain->SetBranchAddress("muMuonHits", &muMuonHits_);

	muPixelHits_ = new vector<int>;
	chain->SetBranchStatus("muPixelHits",1);
	chain->SetBranchAddress("muPixelHits",&muPixelHits_);
	
	muDz_ = new vector<float>;
	chain->SetBranchStatus("muDz",1);
	chain->SetBranchAddress("muDz",&muDz_);
	
	muD0_ = new vector<float>;
	chain->SetBranchStatus("muD0",1);
	chain->SetBranchAddress("muD0",&muD0_);

	muStations_ = new vector<int>;
	chain->SetBranchStatus("muStations",1);
	chain->SetBranchAddress("muStations",&muStations_);

	chain->SetBranchStatus("nMu",1);
	chain->SetBranchAddress("nMu", &nMu_);

	muPt_ = new vector<float>;
	chain->SetBranchStatus("muPt",1);
	chain->SetBranchAddress("muPt", &muPt_);

	muEn_ = new vector<float>;
	chain->SetBranchStatus("muEn",1);
	chain->SetBranchAddress("muEn", &muEn_);

	muEta_ = new vector<float>;
	chain->SetBranchStatus("muEta",1);
	chain->SetBranchAddress("muEta", &muEta_);

	muPhi_ = new vector<float>;
	chain->SetBranchStatus("muPhi",1);
	chain->SetBranchAddress("muPhi", &muPhi_);
	
	muPFChIso_ = new vector<float>;
	chain->SetBranchStatus("muPFChIso",1);
	chain->SetBranchAddress("muPFChIso", &muPFChIso_);
	
	muPFNeuIso_ = new vector<float>;
	chain->SetBranchStatus("muPFNeuIso",1);
	chain->SetBranchAddress("muPFNeuIso", &muPFNeuIso_);
	
	muPFPhoIso_ = new vector<float>;
	chain->SetBranchStatus("muPFPhoIso",1);
	chain->SetBranchAddress("muPFPhoIso", &muPFPhoIso_);

	muPFPUIso_ = new vector<float>;
	chain->SetBranchStatus("muPFPUIso",1);
	chain->SetBranchAddress("muPFPUIso", &muPFPUIso_);

	muType_ = new vector<int>;
	chain->SetBranchStatus("muType",1);
	chain->SetBranchAddress("muType",&muType_);
	
	muIDbit_ = new vector<unsigned short>;
        chain->SetBranchStatus("muIDbit",1);
        chain->SetBranchAddress("muIDbit", &muIDbit_);

	// jets
	
	chain->SetBranchStatus("nJet",1);
	chain->SetBranchAddress("nJet", &nJet_);

	jetPt_ = new vector<float>;
	chain->SetBranchStatus("jetPt",1);
	chain->SetBranchAddress("jetPt", &jetPt_);

	jetRawPt_ = new vector<float>;
	chain->SetBranchStatus("jetRawPt",1);
        chain->SetBranchAddress("jetRawPt", &jetRawPt_);
	
	jetEta_ = new vector<float>;
	chain->SetBranchStatus("jetEta",1);
	chain->SetBranchAddress("jetEta", &jetEta_);
	
	jetPhi_ = new vector<float>;
	chain->SetBranchStatus("jetPhi",1);
	chain->SetBranchAddress("jetPhi", &jetPhi_);

	jetEn_ = new vector<float>;
	chain->SetBranchStatus("jetEn",1);
	chain->SetBranchAddress("jetEn", &jetEn_);
	
	jetPFLooseID_ = new vector<bool>;
	chain->SetBranchStatus("jetPFLooseId",1);
	chain->SetBranchAddress("jetPFLooseId", &jetPFLooseID_);

	jetID_ = new vector<int>;
	chain->SetBranchStatus("jetID",1);
	chain->SetBranchAddress("jetID", &jetID_);

	jetArea_ = new vector<float>;
	chain->SetBranchStatus("jetArea",1);
	chain->SetBranchAddress("jetArea", &jetArea_);

	jetP4Smear_ = new vector<float>;
	chain->SetBranchStatus("jetP4Smear",1);
	chain->SetBranchAddress("jetP4Smear", &jetP4Smear_);

	jetP4SmearUp_ = new vector<float>;
	chain->SetBranchStatus("jetP4SmearUp",1);
	chain->SetBranchAddress("jetP4SmearUp", &jetP4SmearUp_);

	jetP4SmearDo_ = new vector<float>;
	chain->SetBranchStatus("jetP4SmearDo",1);
	chain->SetBranchAddress("jetP4SmearDo", &jetP4SmearDo_);

	jetJECUnc_ = new vector<float>;
	chain->SetBranchStatus("jetJECUnc",1);
	chain->SetBranchAddress("jetJECUnc", &jetJECUnc_);

	jetCHF_ = new vector<float>;
	chain->SetBranchStatus("jetCHF",1);
	chain->SetBranchAddress("jetCHF", &jetCHF_);

	jetNHF_ = new vector<float>;
	chain->SetBranchStatus("jetNHF",1);
	chain->SetBranchAddress("jetNHF", &jetNHF_);

	jetCEF_ = new vector<float>;
	chain->SetBranchStatus("jetCEF",1);
	chain->SetBranchAddress("jetCEF", &jetCEF_);

	jetNEF_ = new vector<float>;
	chain->SetBranchStatus("jetNEF",1);
	chain->SetBranchAddress("jetNEF", &jetNEF_);

	jetNCH_ = new vector<int>;
	chain->SetBranchStatus("jetNCH",1);
	chain->SetBranchAddress("jetNCH", &jetNCH_);

	jetNNP_ = new vector<int>;
	chain->SetBranchStatus("jetNNP",1);
	chain->SetBranchAddress("jetNNP", &jetNNP_);

	jetMUF_ = new vector<float>;
	chain->SetBranchStatus("jetMUF",1);
	chain->SetBranchAddress("jetMUF", &jetMUF_);

	// This is only included in "development" versions of the ggNtuples
	// jetHFHAE_ = new vector<float>;
	// chain->SetBranchStatus("jetHFHAE",1);
	// chain->SetBranchAddress("jetHFHAE", &jetHFHAE_);

	// This is only included in "development" versions of the ggNtuples
	// jetHFEME_ = new vector<float>;
	// chain->SetBranchStatus("jetHFEME",1);
	// chain->SetBranchAddress("jetHFEME", &jetHFEME_);

	// This is only included in "development" versions of the ggNtuples
	// jetNConstituents_ = new vector<int>;
	// chain->SetBranchStatus("jetNConstituents",1);
	// chain->SetBranchAddress("jetNConstituents", &jetNConstituents_);



	// AK8Jetnconstituents_ = new vector<int>;
	// chain->SetBranchStatus("AK8Jetnconstituents",1);
	// chain->SetBranchAddress("AK8Jetnconstituents", &AK8Jetnconstituents_);
	
	//jetNCharged_ = new vector<float>;
	//chain->SetBranchStatus("jetNCharged",1);
	//chain->SetBranchAddress("jetNCharged", &jetNCharged_);

	// AK8JetCEF_ = new vector<float>;	
	// chain->SetBranchStatus("AK8JetCEF",1);
	// chain->SetBranchAddress("AK8JetCEF", &AK8JetCEF_);

	// AK8JetNHF_ = new vector<float>;
	// chain->SetBranchStatus("AK8JetNHF",1);
	// chain->SetBranchAddress("AK8JetNHF", &AK8JetNHF_);
	
	// AK8JetNEF_ = new vector<float>;
	// chain->SetBranchStatus("AK8JetNEF",1);
	// chain->SetBranchAddress("AK8JetNEF", &AK8JetNEF_);
	
	// AK8JetCHF_ = new vector<float>;
	// chain->SetBranchStatus("AK8JetCHF",1);
	// chain->SetBranchAddress("AK8JetCHF", &AK8JetCHF_);

	jetpfCombinedMVAV2BJetTags_ = new vector<float>;
	chain->SetBranchStatus("jetpfCombinedMVAV2BJetTags",1);
	chain->SetBranchAddress("jetpfCombinedMVAV2BJetTags", &jetpfCombinedMVAV2BJetTags_);
	
	jetCSV2BJetTags_ = new vector<float>;
	chain->SetBranchStatus("jetCSV2BJetTags",1);
	chain->SetBranchAddress("jetCSV2BJetTags", &jetCSV2BJetTags_);

	jetDeepCSVTags_b_ = new vector<float>;
	chain->SetBranchStatus("jetDeepCSVTags_b",1);
	chain->SetBranchAddress("jetDeepCSVTags_b", &jetDeepCSVTags_b_);

	jetDeepCSVTags_bb_ = new vector<float>;
	chain->SetBranchStatus("jetDeepCSVTags_bb",1);
	chain->SetBranchAddress("jetDeepCSVTags_bb", &jetDeepCSVTags_bb_);

	jetDeepCSVTags_c_ = new vector<float>;
	chain->SetBranchStatus("jetDeepCSVTags_c",1);
	chain->SetBranchAddress("jetDeepCSVTags_c", &jetDeepCSVTags_c_);

	jetDeepCSVTags_cc_ = new vector<float>;
	chain->SetBranchStatus("jetDeepCSVTags_cc",1);
	chain->SetBranchAddress("jetDeepCSVTags_cc", &jetDeepCSVTags_cc_);

	jetDeepCSVTags_udsg_ = new vector<float>;
	chain->SetBranchStatus("jetDeepCSVTags_udsg",1);
	chain->SetBranchAddress("jetDeepCSVTags_udsg", &jetDeepCSVTags_udsg_);

	// jetCombinedSecondaryVtxMVABJetTags_ = new vector<float>;
	// chain->SetBranchStatus("jetCombinedSecondaryVtxMVABJetTags",1);
	// chain->SetBranchAddress("jetCombinedSecondaryVtxMVABJetTags", &jetCombinedSecondaryVtxMVABJetTags_);

	jetHadFlvr_ = new vector<int>;
	chain->SetBranchStatus("jetHadFlvr",1);
	chain->SetBranchAddress("jetHadFlvr", &jetHadFlvr_);

	jetPartonID_ = new vector<int>;
	chain->SetBranchStatus("jetPartonID",1);
	chain->SetBranchAddress("jetPartonID", &jetPartonID_);
	
	jetGenPartonID_ = new vector<int>;
	chain->SetBranchStatus("jetGenPartonID",1);
	chain->SetBranchAddress("jetGenPartonID", &jetGenPartonID_);
	
	//jetGenJetIndex_ = new vector<int>;
	//chain->SetBranchStatus("jetGenJetIndex",1);
	//chain->SetBranchAddress("jetGenJetIndex", &jetGenJetIndex_);

	jetGenJetPt_ = new vector<float>;
	chain->SetBranchStatus("jetGenJetPt",1);
	chain->SetBranchAddress("jetGenJetPt", &jetGenJetPt_);

	jetGenPt_ = new vector<float>;
	chain->SetBranchStatus("jetGenPt",1);
	chain->SetBranchAddress("jetGenPt", &jetGenPt_);
	
	jetGenEta_ = new vector<float>;
	chain->SetBranchStatus("jetGenEta",1);
	chain->SetBranchAddress("jetGenEta", &jetGenEta_);
	
	jetGenPhi_ = new vector<float>;
	chain->SetBranchStatus("jetGenPhi",1);
	chain->SetBranchAddress("jetGenPhi", &jetGenPhi_);

	// photons
	
	chain->SetBranchStatus("nPho",1);
	chain->SetBranchAddress("nPho", &nPho_);

	phoE_ = new vector<float>;	
	chain->SetBranchStatus("phoE",1);
	chain->SetBranchAddress("phoE", &phoE_);
	
	phoEt_ = new vector<float>;	
	chain->SetBranchStatus("phoEt",1);
	chain->SetBranchAddress("phoEt", &phoEt_);
	
	phoEta_ = new vector<float>;
	chain->SetBranchStatus("phoEta",1);
	chain->SetBranchAddress("phoEta", &phoEta_);

	phoPhi_ = new vector<float>;
	chain->SetBranchStatus("phoPhi",1);
	chain->SetBranchAddress("phoPhi", &phoPhi_);
	
	phoSCEta_ = new vector<float>;
	chain->SetBranchStatus("phoSCEta",1);
	chain->SetBranchAddress("phoSCEta", &phoSCEta_);

	phoSCPhi_ = new vector<float>;
	chain->SetBranchStatus("phoSCPhi",1);
	chain->SetBranchAddress("phoSCPhi", &phoSCPhi_);

	phoSCE_ = new vector<float>;
	chain->SetBranchStatus("phoSCE",1);
	chain->SetBranchAddress("phoSCE", &phoSCE_);

	phoCalibE_ = new vector<float>;	
	chain->SetBranchStatus("phoCalibE",1);
	chain->SetBranchAddress("phoCalibE", &phoCalibE_);
	
	phoCalibEt_ = new vector<float>;	
	chain->SetBranchStatus("phoCalibEt",1);
	chain->SetBranchAddress("phoCalibEt", &phoCalibEt_);
	
	//phoSeedBCE_ = new vector<int>;
	//chain->SetBranchStatus("phoSeedBCE",1);
	//chain->SetBranchAddress("phoSeedBCE", &phoSeedBCE_);
	
	phohasPixelSeed_ = new vector<int>;
	chain->SetBranchStatus("phohasPixelSeed",1);
	chain->SetBranchAddress("phohasPixelSeed", &phohasPixelSeed_);

	phoEleVeto_ = new vector<int>;
	chain->SetBranchStatus("phoEleVeto",1);
	chain->SetBranchAddress("phoEleVeto", &phoEleVeto_);
	
	phoIDbit_ = new vector<unsigned short>;
	chain->SetBranchStatus("phoIDbit",1);
	chain->SetBranchAddress("phoIDbit", &phoIDbit_);

	phoHoverE_ = new vector<float>;
	chain->SetBranchStatus("phoHoverE",1);
	chain->SetBranchAddress("phoHoverE", &phoHoverE_);

	phoSigmaIEtaIEtaFull5x5_ = new vector<float>;
	chain->SetBranchStatus("phoSigmaIEtaIEtaFull5x5",1);
	chain->SetBranchAddress("phoSigmaIEtaIEtaFull5x5", &phoSigmaIEtaIEtaFull5x5_);
	
	phoPFChIso_ = new vector<float>;
	chain->SetBranchStatus("phoPFChIso",1);
	chain->SetBranchAddress("phoPFChIso", &phoPFChIso_);
	
	phoPFNeuIso_ = new vector<float>;
	chain->SetBranchStatus("phoPFNeuIso",1);
	chain->SetBranchAddress("phoPFNeuIso", &phoPFNeuIso_);

	phoPFPhoIso_ = new vector<float>;
	chain->SetBranchStatus("phoPFPhoIso",1);
	chain->SetBranchAddress("phoPFPhoIso", &phoPFPhoIso_);

	phoR9_ = new vector<float>;
	chain->SetBranchStatus("phoR9",1);
	chain->SetBranchAddress("phoR9", &phoR9_);

	phoPFRandConeChIso_ = new vector<vector<float>>;
	chain->SetBranchStatus("phoPFRandConeChIso",1);
	chain->SetBranchAddress("phoPFRandConeChIso", &phoPFRandConeChIso_);

	phoPFRandConePhi_ = new vector<vector<float>>;
	chain->SetBranchStatus("phoPFRandConePhi",1);
	chain->SetBranchAddress("phoPFRandConePhi", &phoPFRandConePhi_);

        phoScale_stat_up_ = new vector<float>;
        chain->SetBranchStatus("phoScale_stat_up",1);
        chain->SetBranchAddress("phoScale_stat_up", &phoScale_stat_up_); 

        phoScale_stat_dn_ = new vector<float>;
        chain->SetBranchStatus("phoScale_stat_dn",1);
        chain->SetBranchAddress("phoScale_stat_dn", &phoScale_stat_dn_);

        phoScale_syst_up_ = new vector<float>;
        chain->SetBranchStatus("phoScale_syst_up",1);
        chain->SetBranchAddress("phoScale_syst_up", &phoScale_syst_up_);

        phoScale_syst_dn_ = new vector<float>;
        chain->SetBranchStatus("phoScale_syst_dn",1);
        chain->SetBranchAddress("phoScale_syst_dn", &phoScale_syst_dn_);


        phoScale_gain_up_ = new vector<float>;
        chain->SetBranchStatus("phoScale_gain_up",1);
        chain->SetBranchAddress("phoScale_gain_up", &phoScale_gain_up_);

        phoScale_gain_dn_ = new vector<float>;
        chain->SetBranchStatus("phoScale_gain_dn",1);
        chain->SetBranchAddress("phoScale_gain_dn", &phoScale_gain_dn_);

       
        phoResol_rho_up_ = new vector<float>;
        chain->SetBranchStatus("phoResol_rho_up",1);
        chain->SetBranchAddress("phoResol_rho_up", &phoResol_rho_up_);
        
        phoResol_rho_dn_ = new vector<float>;
        chain->SetBranchStatus("phoResol_rho_dn",1);
        chain->SetBranchAddress("phoResol_rho_dn", &phoResol_rho_dn_);

        phoResol_phi_up_ = new vector<float>;
        chain->SetBranchStatus("phoResol_phi_up",1);
        chain->SetBranchAddress("phoResol_phi_up", &phoResol_phi_up_);

        phoResol_phi_dn_ = new vector<float>;
        chain->SetBranchStatus("phoResol_phi_dn",1);
        chain->SetBranchAddress("phoResol_phi_dn", &phoResol_phi_dn_);

	//phoPFPhoIso_ = new vector<float>;
	//chain->SetBranchStatus("phoPFPhoIso",1);
	//chain->SetBranchAddress("phoPFPhoIso", &phoPFPhoIsoFrix7_);

	//phoPFChIsoFrix7_ = new vector<float>;
	//chain->SetBranchStatus("phoPFChIsoFrix7",1);
	//chain->SetBranchAddress("phoPFChIsoFrix7", &phoPFChIsoFrix7_);
	
	//phoPFPhoIsoFrix6_ = new vector<float>;
	//chain->SetBranchStatus("phoPFPhoIsoFrix6",1);
	//chain->SetBranchAddress("phoPFPhoIsoFrix6", &phoPFPhoIsoFrix6_);
	
	//phoPFChIsoFrix6_ = new vector<float>;
	//chain->SetBranchStatus("phoPFChIsoFrix6",1);
	//chain->SetBranchAddress("phoPFChIsoFrix6", &phoPFChIsoFrix6_);

	//phoGenIndex_ = new vector<int>;
	//chain->SetBranchStatus("phoGenIndex",1);
	//chain->SetBranchAddress("phoGenIndex", &phoGenIndex_);
	
	//phoGenGMomPID_ = new vector<int>;
	//chain->SetBranchStatus("phoGenGMomPID",1);
	//chain->SetBranchAddress("phoGenGMomPID", &phoGenGMomPID_);
	
	//phoGenMomPID_ = new vector<int>;
	//chain->SetBranchStatus("phoGenMomPID",1);
	//chain->SetBranchAddress("phoGenMomPID", &phoGenMomPID_);
	
	// MC gen particles
	
	chain->SetBranchStatus("nMC",1);
	chain->SetBranchAddress("nMC", &nMC_);
	
	mcPt = new vector<float>;
	chain->SetBranchStatus("mcPt",1);
	chain->SetBranchAddress("mcPt", &mcPt);

	genScaleSystWeights_ = new vector<float>;
        chain->SetBranchStatus("genScaleSystWeights",1);
        chain->SetBranchAddress("genScaleSystWeights", &genScaleSystWeights_);

	mcEta = new vector<float>;
	chain->SetBranchStatus("mcEta",1);
	chain->SetBranchAddress("mcEta", &mcEta);
	
	mcPhi = new vector<float>;
	chain->SetBranchStatus("mcPhi",1);
	chain->SetBranchAddress("mcPhi", &mcPhi);
	
	mcMass = new vector<float>;
	chain->SetBranchStatus("mcMass",1);
	chain->SetBranchAddress("mcMass", &mcMass);
	
	mcPID = new vector<int>;
	chain->SetBranchStatus("mcPID",1);
	chain->SetBranchAddress("mcPID", &mcPID);
	
	mcMomPID = new vector<int>;
	chain->SetBranchStatus("mcMomPID",1);
	chain->SetBranchAddress("mcMomPID", &mcMomPID);
	
	mcGMomPID = new vector<int>;
	chain->SetBranchStatus("mcGMomPID",1);
	chain->SetBranchAddress("mcGMomPID", &mcGMomPID);

	mcMomPt = new vector<float>;
	chain->SetBranchStatus("mcMomPt",1);
	chain->SetBranchAddress("mcMomPt", &mcMomPt);
	
	//mcDecayType = new vector<int>;
	//chain->SetBranchStatus("mcDecayType",1);
	//chain->SetBranchAddress("mcDecayType", &mcDecayType);
	
	//mcIndex = new vector<int>;
	//chain->SetBranchStatus("mcIndex",1);
	//chain->SetBranchAddress("mcIndex", &mcIndex);

	mcStatus = new vector<int>;
	chain->SetBranchStatus("mcStatus",1);
	chain->SetBranchAddress("mcStatus", &mcStatus);
	
        mcStatusFlag = new vector<UShort_t>;
        chain->SetBranchStatus("mcStatusFlag",1);
        chain->SetBranchAddress("mcStatusFlag", &mcStatusFlag);	
	// // mcMomPt = new vector<float>;
	// // chain->SetBranchStatus("mcMomPt",1);
	// // chain->SetBranchAddress("mcMomPt", &mcMomPt);
	
	mcMomEta = new vector<float>;
	chain->SetBranchStatus("mcMomEta",1);
	chain->SetBranchAddress("mcMomEta", &mcMomEta);
	
	mcMomPhi = new vector<float>;
	chain->SetBranchStatus("mcMomPhi",1);
	chain->SetBranchAddress("mcMomPhi", &mcMomPhi);
	
	mcMomMass = new vector<float>;
	chain->SetBranchStatus("mcMomMass",1);
	chain->SetBranchAddress("mcMomMass", &mcMomMass);
	
	mcParentage = new vector<int>;
	chain->SetBranchStatus("mcParentage",1);
	chain->SetBranchAddress("mcParentage", &mcParentage);
	
	//chain->SetBranchStatus("",1);
	//chain->SetBranchAddress("", _);
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
