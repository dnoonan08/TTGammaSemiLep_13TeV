from ROOT import *
import sys
from sampleInformation import *
import os

gROOT.SetBatch(True)

finalState = "Mu"

nBJets = 1

btagWeightCategory = ["1","(1-btagWeight[0])","(btagWeight[2])","(btagWeight[1])"]



extraCutsTight       = "(passPresel_Mu && nJet>=4 && nBJet>=2)*"
extraPhotonCutsTight = "(passPresel_Mu && nJet>=4 && nBJet>=2 && %s)*"

extraCutsLoose       = "(passPresel_Mu && nJet>=2 && nBJet>=1)*"
extraPhotonCutsLoose = "(passPresel_Mu && nJet>=2 && nBJet>=1 && %s)*"

extraCutsLooseCR       = "(passPresel_Mu && nJet==2 && nBJet>=1)*"
extraPhotonCutsLooseCR = "(passPresel_Mu && nJet==2 && nBJet>=1 && %s)*"

extraCuts            = "(passPresel_Mu && nJet>=3 && nBJet>=1)*"
extraPhotonCuts      = "(passPresel_Mu && nJet>=3 && nBJet>=1 && %s)*"

# extraCutsTight       = "(passPresel_Mu && nJet>=3 && nBJet>=2)*"
# extraPhotonCutsTight = "(passPresel_Mu && nJet>=3 && nBJet>=2 && %s)*"

if finalState=="Mu":
    sampleList[-1] = "DataMu"
    sampleList[-2] = "QCDMu"
    analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/dnoonan/13TeV_AnalysisNtuples/muons/"
    outputhistName = "histograms/mu/hists.root"
if finalState=="Ele":
    sampleList[-1] = "DataEle"
    sampleList[-2] = "QCDEle"
    analysisNtupleLocation = "/uscms_data/d2/dnoonan/13TeV_TTGamma/Ntuples/electrons/"
    outputhistName = "histograms/ele/hists.root"




weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*%s"%btagWeightCategory[nBJets]

if "Tight" in sys.argv:
    print "Tight Select"
    nBJets = 2
    weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*btagWeight[2]"
    extraCuts = extraCutsTight
    extraPhotonCuts = extraPhotonCutsTight
    sys.argv.remove("Tight")
    outputhistName = outputhistName.replace("hists.root","hists_tight.root")

if "Loose" in sys.argv:
    print "Loose Select"
    nBJets = 1
    weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*(btagWeight[1]+btagWeight[2])"
    extraCuts = extraCutsLoose
    extraPhotonCuts = extraPhotonCutsLoose
    sys.argv.remove("Loose")
    outputhistName = outputhistName.replace("hists.root","hists_loose.root")

if "LooseCR" in sys.argv:
    print "Loose Control Region Select"
    nBJets = 1
    weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*(btagWeight[1]+btagWeight[2])"
    extraCuts = extraCutsLooseCR
    extraPhotonCuts = extraPhotonCutsLooseCR
    sys.argv.remove("LooseCR")
    outputhistName = outputhistName.replace("hists.root","hists_2jControlRegion.root")





sample = sys.argv[-1]

if not sample in sampleList:
    print "Sample isn't in list"
    print sampleList
    sys.exit()



tree = TChain("AnalysisTree")
fileList = samples[sample][0]
for fileName in fileList:
    tree.Add("%s/%s"%(analysisNtupleLocation,fileName))

print sample

print "Number of events:", tree.GetEntries()

# 
histogramInfo = [ ["jetPt[0]" , "presel_jet1Pt"   ,    [1000,0,1000], extraCuts      , ""],
                  ["jetPt[1]" , "presel_jet2Pt"   ,      [600,0,600], extraCuts      , ""],
                  ["jetPt[2]" , "presel_jet3Pt"   ,      [600,0,600], extraCuts      , ""],
                  ["nJet"     , "presel_Njet"     ,        [15,0,15], extraCuts      , ""],
                  ["nBJet"    , "presel_Nbjet"    ,        [10,0,10], extraCuts      , ""],
                  ["muPt[0]"  , "presel_muPt"     ,      [600,0,600], extraCuts      , ""],
                  ["muEta[0]" , "presel_muEta"    ,   [100,-2.4,2.4], extraCuts      , ""],
                  ["muPhi[0]" , "presel_muPhi"    , [100,-3.15,3.15], extraCuts      , ""],
                  ["M3"       , "presel_M3"       ,      [300,0,600], extraCuts      , ""],
                  ["pfMET"    , "presel_MET"      ,      [300,0,600], extraCuts      , ""],
                  ["pfMETPhi" , "presel_METPhi"   , [100,-3.15,3.15], extraCuts      , ""],
                  # ["nVtx"     , "presel_nVtx"     ,        [50,0,50], extraCuts      , ""],
                  # ["nVtx"     , "presel_nVtxup"   ,        [50,0,50], extraCuts      , "%sevtWeight*PUweight_Up*muEffWeight*eleEffWeight*%s"%(extraCuts,btagWeightCategory[nBJets])],
                  # ["nVtx"     , "presel_nVtxdo"   ,        [50,0,50], extraCuts      , "%sevtWeight*PUweight_Do*muEffWeight*eleEffWeight*%s"%(extraCuts,btagWeightCategory[nBJets])],
                  # ["nVtx"     , "presel_nVtxNoPU" ,        [50,0,50], extraCuts      , "%sevtWeight*muEffWeight*eleEffWeight*%s"%(extraCuts,btagWeightCategory[nBJets])],
                  ["phoEt"      , "phosel_photonEt" ,      [300,0,300], extraPhotonCuts%("phoMediumID"), ""],
                  ["phoEta"     , "phosel_photonEta",   [100,-2.5,2.5], extraPhotonCuts%("phoMediumID"), ""],
                  ["dRPhotonJet"   , "phosel_dRPhotonJet"    , [200,0,5], extraPhotonCuts%("phoMediumID"), ""],
                  ["dRPhotonLepton", "phosel_dRPhotonLepton",  [200,0,10], extraPhotonCuts%("phoMediumID"), ""],
                  ["phoPhi"     , "phosel_photonPhi", [100,-3.15,3.15], extraPhotonCuts%("phoMediumID"), ""],
                  ["M3"         , "phosel_M3"       ,      [120,0,600], extraPhotonCuts%("phoMediumID"), ""],
                  ["pfMET"      , "phosel_MET"      ,      [300,0,600], extraPhotonCuts%("phoMediumID"), ""],
                  ["nJet"       , "phosel_Njet"     ,        [15,0,15], extraPhotonCuts%("phoMediumID"), ""],
                  ["nBJet"      , "phosel_Nbjet"    ,        [10,0,10], extraPhotonCuts%("phoMediumID"), ""],
                  ["phoHoverE"  , "phosel_HoverE"   ,     [100,0.,.04], extraPhotonCuts%("phoMediumID"), ""],
                  ["phoSIEIE"   , "phosel_SIEIE"    ,     [100,0.,.03], extraPhotonCuts%("phoMediumID"), ""],
                  ["phoPFChIso" , "phosel_ChIso"    ,       [100,0,.5], extraPhotonCuts%("phoMediumID"), ""],
                  ["phoPFNeuIso", "phosel_NeuIso"   ,       [100,0,5.], extraPhotonCuts%("phoMediumID"), ""],
                  ["phoPFPhoIso", "phosel_PhoIso"   ,       [100,0,10], extraPhotonCuts%("phoMediumID"), ""],
                  ["phoHoverE"  , "phosel_noCut_HoverE"   ,      [100,0.,.2], extraPhotonCuts%("phoMediumIDPassSIEIE && phoMediumIDPassChIso && phoMediumIDPassNeuIso && phoMediumIDPassPhoIso"), ""],
                  ["phoSIEIE"   , "phosel_noCut_SIEIE"    ,     [100,0.,.08], extraPhotonCuts%("phoMediumIDPassHoverE && phoMediumIDPassChIso && phoMediumIDPassNeuIso && phoMediumIDPassPhoIso"), ""],
                  ["phoPFChIso" , "phosel_noCut_ChIso"    ,      [200,0,100], extraPhotonCuts%("phoMediumIDPassHoverE && phoMediumIDPassSIEIE && phoMediumIDPassNeuIso && phoMediumIDPassPhoIso"), ""],
                  ["phoPFNeuIso", "phosel_noCut_NeuIso"   ,      [200,0,100], extraPhotonCuts%("phoMediumIDPassHoverE && phoMediumIDPassSIEIE && phoMediumIDPassChIso && phoMediumIDPassPhoIso"), ""],
                  ["phoPFPhoIso", "phosel_noCut_PhoIso"   ,      [200,0,100], extraPhotonCuts%("phoMediumIDPassHoverE && phoMediumIDPassSIEIE && phoMediumIDPassChIso && phoMediumIDPassNeuIso"), ""],
                  ["phoPFChIso" , "phosel_AntiSIEIE_ChIso",      [200,0,100], extraPhotonCuts%("phoMediumIDPassHoverE && !phoMediumIDPassSIEIE && phoMediumIDPassNeuIso && phoMediumIDPassPhoIso"), ""],
                  ]


histograms = []
for h_Info in histogramInfo:
    print "filling", h_Info[1], sample
    evtWeight = ""
    histograms.append(TH1F("%s_%s"%(h_Info[1],sample),"%s_%s"%(h_Info[1],sample),h_Info[2][0],h_Info[2][1],h_Info[2][2]))
    if h_Info[-1]=="":
        evtWeight = "%s%s"%(h_Info[3],weights)
    else:
        evtWeight = h_Info[-1]
        
    if "Data" in sample:
        evtWeight = h_Info[3]

    if evtWeight[-1]=="*":
        evtWeight= evtWeight[:-1]
    tree.Draw("%s>>%s_%s"%(h_Info[0],h_Info[1],sample),evtWeight)


outputFile = TFile(outputhistName,"update")
outputFile.rmdir(sample)
outputFile.mkdir(sample)
outputFile.cd(sample)
for h in histograms:
    h.Write()

outputFile.Close()
