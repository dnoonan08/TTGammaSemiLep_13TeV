#ifndef EVENTTREE_H
#define EVENTTREE_H

#include<TFile.h>
#include<TTree.h>
#include<TChain.h>

#include<vector>

using namespace std;
const Int_t maxP = 600;

class EventTree{
 public:
    EventTree(int nFiles, bool xRootDAccess, string year, char** fileNames);
    ~EventTree();
    Long64_t GetEntries();
    Int_t GetEntry(Long64_t entry);
    
    TChain* chain;
    
    // include all variables just in case
    Int_t    run_;
    Long64_t event_;
    Int_t    lumis_;
    
    Float_t  genWeight_;

    UInt_t nLHEScaleWeight_;
    Float_t LHEScaleWeight_[200];
    
    UInt_t nLHEPdfWeight_;
    Float_t LHEPdfWeight_[200];
    
    bool isData_;

    Int_t    nVtx_;
    Int_t    nGoodVtx_;
    

    Float_t    pvNDOF_;
    Float_t    pvX_;
    Float_t    pvY_;
    Float_t    pvZ_;
    Float_t    pvChi2_;
    

    // genParticle
    
    Int_t    nGenPart_;
    
    Float_t   GenPart_pt_[200];
    Float_t   GenPart_eta_[200];
    Float_t   GenPart_phi_[200];
    Float_t   GenPart_mass_[200];
    Int_t     GenPart_genPartIdxMother_[200];
    Int_t     GenPart_pdgId_[200];
    Int_t     GenPart_status_[200];
    Int_t     GenPart_statusFlags_[200];
    
    
    Int_t    nGenJet_;
    
    Float_t   GenJet_pt_[200];
    Float_t   GenJet_eta_[200];
    Float_t   GenJet_phi_[200];
    Float_t   GenJet_mass_[200];
    
    // PU
    Int_t    nPU_;  
    Float_t  nPUTrue_;  
    
    Float_t  MET_pt_;
    Float_t  MET_phi_;
    
    Float_t  GenMET_pt_;
    Float_t  GenMET_phi_;

    // Electron

    UInt_t          nEle_;
    Float_t         elePhi_[10];
    Float_t         elePt_[10];
    Float_t         eleEta_[10];
    Float_t         eleDeltaEtaSC_[10];
    Int_t           eleCharge_[10];
    Float_t         eleMass_[10];
    Float_t         elePFRelIso_[10];
    Float_t         elePFRelChIso_[10];
    Int_t           eleIDcutbased_[10];
    Float_t         eleD0_[10];
    Float_t         eleDz_[10];
    Float_t         eleSIEIE_[10];

    Int_t           eleVidWPBitmap_[10];
    Float_t         eleEcalSumEtDr03_[10];
    Float_t         eleHcalSumEtDr03_[10];
    Float_t         eleTrkSumPtDr03_[10];


    // Photon
    
    UInt_t          nPho_;
    Float_t         phoEt_[10];
    Float_t         phoEta_[10];
    Float_t         phoPhi_[10];
    Bool_t          phoIsEB_[10];
    Bool_t          phoIsEE_[10];
    Float_t         phoPFRelIso_[10];
    Float_t         phoPFRelChIso_[10];
    Int_t          phoIDcutbased_[10];
    Int_t           phoVidWPBitmap_[10];
    Bool_t           phoPixelSeed_[10];
    Bool_t           phoEleVeto_[10];

    Float_t         phoR9_[10];
    Float_t         phoSIEIE_[10];
    Float_t         phoHoverE_[10];
    
    Int_t           phoGenPartIdx_[10];
    

    // I don't know why, but these two lines are needed to avoid possible memory issue with nMuon (segfault when it thinks there are 2**32-1 muons in an event
    // These vectors are not used
    vector<float>*  PFClustdEta_;
    vector<float>*  PFClustdPhi_;



    // Muon
    UInt_t          nMuon_;
    Float_t         muPhi_[10];
    Float_t         muPt_[10];
    Float_t         muEta_[10];
    Int_t           muCharge_[10];
    Float_t         muMass_[10];
    Float_t         muPFRelIso_[10];
    Bool_t          muMediumId_[10];
    Bool_t          muTightId_[10];
    Bool_t          muIsPFMuon_[10];
    Bool_t          muIsGlobal_[10];
    Bool_t          muIsTracker_[10];



    // Jet

    UInt_t          nJet_;
    Float_t         jetPt_[40];
    Float_t         jetEta_[40];
    Float_t         jetPhi_[40];
    Float_t         jetMass_[40];
    Float_t         jetRawFactor_[40];
    Int_t           jetID_[40];
    Float_t         jetArea_[40];
    Float_t         jetBtagCMVA_[40];
    Float_t         jetBtagCSVV2_[40];
    Float_t         jetBtagDeepB_[40];
    Float_t         jetBtagDeepC_[40];
    Float_t         jetBtagDeepFlavB_[40];
    Int_t           jetHadFlvr_[40];
    Int_t           jetGenJetIdx_[40];

    Float_t  rho_;


    Bool_t   HLT_Ele32_eta2p1_WPTight_Gsf_;
    Bool_t   HLT_IsoMu24_;
    Bool_t   HLT_IsoTkMu24_;
    Bool_t   HLT_Ele32_WPTight_Gsf_L1DoubleEG_;
    Bool_t   HLT_IsoMu24_eta2p1_;
    Bool_t   HLT_IsoMu27_;
    
    Bool_t   HLT_Ele27_WPTight_Gsf_;
    Bool_t   HLT_Ele32_WPTight_Gsf_;
    Bool_t   HLT_Ele35_WPTight_Gsf_;
    Bool_t   HLT_Ele38_WPTight_Gsf_;
    
    Bool_t   HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_;
    Bool_t   HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
    Bool_t   HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_;
    Bool_t   HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_;
    Bool_t   HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_;
    Bool_t   HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_;
    
    Bool_t   Flag_goodVertices_ ;
    Bool_t   Flag_globalSuperTightHalo2016Filter_ ;
    Bool_t   Flag_HBHENoiseFilter_ ;
    Bool_t   Flag_HBHENoiseIsoFilter_ ;
    Bool_t   Flag_EcalDeadCellTriggerPrimitiveFilter_ ;
    Bool_t   Flag_BadPFMuonFilter_ ;
    Bool_t   Flag_ecalBadCalibFilterV2_ ;
    

};
#endif
