from ROOT import *
import sys
from sampleInformation import *
import os
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-c", "--channel", dest="channel", default="Mu",type='str',
                     help="Specify which channel Mu or Ele? default is Mu" )
parser.add_option("-s","--systematic", dest="systematic", default="nominal",type='str',
		     help="Specify up, down or nominal, default is nominal")
(options, args) = parser.parse_args()

level =options.systematic


gROOT.SetBatch(True)

finalState = options.channel

nBJets = 1


#atleast 0, atleast 1, atleast 2, exactly 1, btagWeight[0] = exactly 0

extraCutsTight       = "(passPresel_Mu && nJet>=4 && nBJet>=2)*"
extraPhotonCutsTight = "(passPresel_Mu && nJet>=4 && nBJet>=2 && %s)*"
extraPhoTight= "(passPresel_Mu && nJet>=4 && nBJet>=2 && loosePhoMediumID)*"

extraCutsLoose       = "(passPresel_Mu && nJet==2 && nBJet==0)*"
extraPhotonCutsLoose = "(passPresel_Mu && nJet==2 && nBJet==0 && %s)*"

extraCutsLooseCR       = "(passPresel_Mu && nJet>=2 && nBJet>=0)*"
extraPhotonCutsLooseCR = "(passPresel_Mu && nJet>=2 && nBJet>=0 && %s)*"

extraCuts            = "(passPresel_Mu && nJet>=3 && nBJet>=1)*"
extraPhotonCuts      = "(passPresel_Mu && nJet>=3 && nBJet>=1 && %s)*"

# extraCutsTight       = "(passPresel_Mu && nJet>=3 && nBJet>=2)*"
# extraPhotonCutsTight = "(passPresel_Mu && nJet>=3 && nBJet>=2 && %s)*"

if finalState=="Mu":
    sampleList[-1] = "DataMu"
    sampleList[-2] = "QCDMu"
    analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/muons/V08_00_26_07"
  #  analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/troy2012/13TeV_AnalysisNtuples/muons/"
    outputhistName = "histograms/mu/hists.root"
    extraCutsTight       = "(passPresel_Mu && nJet>=4 && nBJet>=2)*"
    extraPhotonCutsTight = "(passPresel_Mu && nJet>=4 && nBJet>=2 && %s)*"
    extraPhoTight= "(passPresel_Mu && nJet>=4 && nBJet>=2 && loosePhoMediumID)*"

    extraCutsLoose       = "(passPresel_Mu && nJet==2 && nBJet==0)*"
    extraPhotonCutsLoose = "(passPresel_Mu && nJet==2 && nBJet==0 && %s)*"

    extraCutsLooseCR       = "(passPresel_Mu && nJet>=2 && nBJet>=0)*"
    extraPhotonCutsLooseCR = "(passPresel_Mu && nJet>=2 && nBJet>=0 && %s)*"

    extraCuts            = "(passPresel_Mu && nJet>=3 && nBJet>=1)*"
    extraPhotonCuts      = "(passPresel_Mu && nJet>=3 && nBJet>=1 && %s)*"
    extraPho= "(passPresel_Mu && nJet>=3 && nBJet>=1 && phoMediumID)*"
if finalState=="Ele":
    sampleList[-1] = "DataEle"
    sampleList[-2] = "QCDEle"
    analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/electrons/V08_00_26_07"
    outputhistName = "histograms/ele/hists.root"
    extraCutsTight       = "(passPresel_Ele && nJet>=4 && nBJet>=2)*"
    extraPhotonCutsTight = "(passPresel_Ele && nJet>=4 && nBJet>=2 && %s)*"
    extraPhoTight= "(passPresel_Ele && nJet>=4 && nBJet>=2 && loosePhoMediumID)*"
    
    extraCutsLoose       = "(passPresel_Ele && nJet==2 && nBJet==0)*"
    extraPhotonCutsLoose = "(passPresel_Ele && nJet==2 && nBJet==0 && %s)*"

    extraCutsLooseCR       = "(passPresel_Ele && nJet>=2 && nBJet>=0)*"
    extraPhotonCutsLooseCR = "(passPresel_Ele && nJet>=2 && nBJet>=0 && %s)*"

    extraCuts            = "(passPresel_Ele && nJet>=3 && nBJet>=1)*"
    extraPhotonCuts      = "(passPresel_Ele && nJet>=3 && nBJet>=1 && %s)*"
    extraPho= "(passPresel_Ele && nJet>=3 && nBJet>=1 && phoMediumID)*"



Pileup ="PUweight"
MuEff = "muEffWeight"
btagWeightCategory = ["1","(1-btagWeight[0])","(btagWeight[2])","(btagWeight[1])"]


if 'PU' in sys.argv:
        
        Pileup = "PUweight_%s"%(level)
        sys.argv.remove("PU")
	outputhistName = outputhistName.replace("hists.root","hists_Pileup_%s.root"%(level))
        
if 'MuEff' in sys.argv:
        MuEff = "muEffWeight_%s"%(level)
	
	sys.argv.remove("MuEff")
        outputhistName = outputhistName.replace("hists.root","hists_MuEff_%s.root"%(level))
        

if 'BTagSF' in sys.argv:
        
        btagWeightCategory = ["1","(1-btagWeight_%s[0])"%(level),"(btagWeight_%s[2])"%(level),"(btagWeight_%s[1])"%(level)]
        

	sys.argv.remove("BTagSF")
	outputhistName = outputhistName.replace("hists.root","hists_BTagSF_%s.root"%(level))
        





weights = "evtWeight*%s*muEffWeight*eleEffWeight*%s"%(Pileup,btagWeightCategory[nBJets])
#weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*btagWeight[1]"

if "Tight" in sys.argv:
    print "Tight Select"
    nBJets = 2
    weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*btagWeight[2]"
    extraCuts = extraCutsTight 
    extraPhotonCuts = extraPhotonCutsTight 
    extraPho = extraPhoTight
    sys.argv.remove("Tight")
    outputhistName = outputhistName.replace("hists.root","hists_tight.root")

if "Loose" in sys.argv:
    print "Loose Select"
    nBJets = 0
    weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*(btagWeight[0])"
    extraCuts = extraCutsLoose
    extraPhotonCuts = extraPhotonCutsLoose
    sys.argv.remove("Loose")
    outputhistName = outputhistName.replace("hists.root","hists_loose.root")

if "LooseCR" in sys.argv:
    print "Loose Control Region Select"
    nBJets = 0
    weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*1" #*(btagWeight[2])"
    extraCuts = extraCutsLooseCR
    extraPhotonCuts = extraPhotonCutsLooseCR
    sys.argv.remove("LooseCR")
    outputhistName = outputhistName.replace("hists.root","hists_looseCR.root")





sample = sys.argv[-1]

if not sample in sampleList:
    print "Sample isn't in list"
    print sampleList
    sys.exit()

#Etabarrelcut = 

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
                  ["muPt"  , "presel_muPt"     ,      [600,0,600], extraCuts      , ""],
                  ["muEta" , "presel_muEta"    ,   [100,-2.4,2.4], extraCuts      , ""],
                  ["muPhi" , "presel_muPhi"    , [100,-3.15,3.15], extraCuts      , ""],
		  ["elePt"  , "presel_elePt"     ,      [600,0,600], extraCuts      , ""],
                  ["eleSCEta" , "presel_eleSCEta"    ,   [100,-2.4,2.4], extraCuts      , ""],
                  ["elePhi" , "presel_elePhi"    , [100,-3.15,3.15], extraCuts      , ""],
                  ["M3"       , "presel_M3"       ,      [300,0,600], extraCuts      , ""],
                  ["pfMET"    , "presel_MET"      ,      [300,0,600], extraCuts      , ""],
                  ["pfMETPhi" , "presel_METPhi"   , [100,-3.15,3.15], extraCuts      , ""],
                  ["nVtx"     , "presel_nVtx"     ,        [50,0,50], extraCuts      , ""],
		  ["WtransMass","presel_WtransMass", [80,0,400],extraCuts      , ""],
		  ["HT"        ,"presel_HT", [150,120,1500],extraCuts      , ""],
                  ["nVtx"     , "presel_nVtxup"   ,        [50,0,50], extraCuts      , "%sevtWeight*PUweight_Up*muEffWeight*eleEffWeight*%s"%(extraCuts,btagWeightCategory[nBJets])],
                  ["nVtx"     , "presel_nVtxdo"   ,        [50,0,50], extraCuts      , "%sevtWeight*PUweight_Do*muEffWeight*eleEffWeight*%s"%(extraCuts,btagWeightCategory[nBJets])],
                  ["nVtx"     , "presel_nVtxNoPU" ,        [50,0,50], extraCuts      , "%sevtWeight*muEffWeight*eleEffWeight*%s"%(extraCuts,btagWeightCategory[nBJets])],
                  ["nVtx"     , "phosel_nVtxup"   ,        [50,0,50], extraPhotonCuts%("phoMediumID"), "%sevtWeight*PUweight_Up*muEffWeight*eleEffWeight*%s"%(extraPho,btagWeightCategory[nBJets])],
                  ["nVtx"     , "phosel_nVtxdo"   ,        [50,0,50], extraPhotonCuts%("phoMediumID"), "%sevtWeight*PUweight_Do*muEffWeight*eleEffWeight*%s"%(extraPho,btagWeightCategory[nBJets])],
                  ["nVtx"     , "phosel_nVtxNoPU" ,        [50,0,50], extraPhotonCuts%("phoMediumID"), "%sevtWeight*muEffWeight*eleEffWeight*%s"%(extraPho,btagWeightCategory[nBJets])],
		  ["nVtx"     , "phosel_nVtx"     ,        [50,0,50], extraPhotonCuts%("phoMediumID") , ""],
#		  ["DiphoMass", "phosel_DiphoMass", [80,0,400],extraPhotonCuts%("phoMediumID") , ""],
		  ["nPho",      "phosel_Nphotons", [3,1,4], extraPhotonCuts%("phoMediumID") , ""],
		  ["phoEt[0]"      ,"phosel_LeadingPhotonEt" ,      [300,0,300], extraPhotonCuts%("phoMediumID"), ""],
		  ["phoEt[1]"      ,"phosel_SecondLeadingPhotonEt" ,      [300,0,300], extraPhotonCuts%("phoMediumID"), ""],
                  ["phoEta[0]"     ,"phosel_LeadingPhotonEta",   [50,-2.5,2.5], extraPhotonCuts%("phoMediumID"), ""],
		  ["phoSCEta[0]" ,  "phosel_LeadingPhotonSCEta", [50,-2.5,2.5], extraPhotonCuts%("phoMediumID"), ""],
                  ["dRPhotonJet"   , "phosel_dRLeadingPhotonJet"    , [200,0,5], extraPhotonCuts%("phoMediumID"), ""],
                  ["dRPhotonJet"   , "phosel_dRLeadingPromptPhotonJet"    , [200,0,5], extraPhotonCuts%("phoMediumID && (photonIsGenuine[0]||photonIsMisIDEle[0])"), ""],
                  ["dRPhotonJet"   , "phosel_dRLeadingNonPromptPhotonJet", [200,0,5], extraPhotonCuts%("phoMediumID && (photonIsHadronicPhoton[0]||photonIsHadronicFake[0])"), ""],
		  ["dRPhotonLepton", "phosel_dRLeadingPromptPhotonLepton",  [120,0,6], extraPhotonCuts%("phoMediumID && (photonIsGenuine[0]||photonIsMisIDEle[0])"), ""],
                  ["dRPhotonLepton", "phosel_dRLeadingNonPromptPhotonLepton",  [120,0,6], extraPhotonCuts%("phoMediumID && (photonIsHadronicPhoton[0]||photonIsHadronicFake[0])"), ""],
                  ["dRPhotonLepton", "phosel_dRLeadingGenuinePhotonLepton",  [120,0,6], extraPhotonCuts%("phoMediumID && photonIsGenuine[0]"),""],
                  ["dRPhotonLepton", "phosel_dRLeadingMisIDEleLepton",  [120,0,6], extraPhotonCuts%("phoMediumID && photonIsMisIDEle[0]"),""],
		  ["dRPhotonLepton", "phosel_dRLeadingHadPhoLepton",  [120,0,6], extraPhotonCuts%("phoMediumID && photonIsHadronicPhoton[0]"),""],
                  ["dRPhotonLepton", "phosel_dRLeadingHadFakeLepton",  [120,0,6], extraPhotonCuts%("phoMediumID && photonIsHadronicFake[0]"),""],
                  ["dRPhotonLepton", "phosel_dRLeadingPhotonLepton",  [120,0,6], extraPhotonCuts%("phoMediumID"), ""],
                  ["WtransMass","phosel_WtransMass",           [80,0,400],extraPhotonCuts%("phoMediumID"), ""],		
	          ["HT"         , "phosel_HT"       ,          [150,120,1500],extraPhotonCuts%("phoMediumID"), ""],
                  ["M3"         , "phosel_M3"       ,      [300,0,600], extraPhotonCuts%("phoMediumID"), ""],
                  ["M3"         , "phosel_M3_GenuinePho" , [300,0,600], extraPhotonCuts%("phoMediumID && photonIsGenuine"), ""],
                  ["M3"         , "phosel_M3_MisIDEle" , [300,0,600], extraPhotonCuts%("phoMediumID && photonIsMisIDEle"), ""],
                  ["M3"         , "phosel_M3_HadronicPho" , [300,0,600], extraPhotonCuts%("phoMediumID && photonIsHadronicPhoton"), ""],
                  ["M3"         , "phosel_M3_HadronicFake" , [300,0,600], extraPhotonCuts%("phoMediumID && photonIsHadronicFake"), ""],
                  ["pfMET"      , "phosel_MET"      ,      [300,0,600], extraPhotonCuts%("phoMediumID"), ""],
		  ["elePt"  , "phosel_elePt"     ,      [600,0,600], extraPhotonCuts%("phoMediumID"), ""],
                  ["eleSCEta"  , "phosel_eleSCEta"     , [ 100,-2.4,2.4], extraPhotonCuts%("phoMediumID"), ""],
		  ["muPt"  , "phosel_muPt"     ,      [600,0,600], extraPhotonCuts%("phoMediumID"), ""],
                  ["muEta" , "phosel_muEta"    ,   [100,-2.4,2.4], extraPhotonCuts%("phoMediumID"), ""],
                  ["nJet"       , "phosel_Njet"     ,        [15,0,15], extraPhotonCuts%("phoMediumID"), ""],
                  ["nBJet"      , "phosel_Nbjet"    ,        [10,0,10], extraPhotonCuts%("phoMediumID"), ""],
                  ["phoHoverE"  , "phosel_HoverE"   ,     [100,0.,.04], extraPhotonCuts%("phoMediumID"), ""],
                  ["phoSIEIE"   , "phosel_SIEIE"    ,     [100,0.,.03], extraPhotonCuts%("phoMediumID"), ""],
                  ["phoPFChIso" , "phosel_ChIso"    ,       [100,0,.5], extraPhotonCuts%("phoMediumID"), ""],
                  ["phoPFNeuIso", "phosel_NeuIso"   ,       [100,0,5.], extraPhotonCuts%("phoMediumID"), ""],
                  ["phoPFPhoIso", "phosel_PhoIso"   ,       [50,0,5], extraPhotonCuts%("phoMediumID"), ""],
                  ["loosePhoHoverE"  , "phosel_noCut_HoverE"   ,      [100,0.,.2], extraPhotonCuts%("loosePhoMediumIDPassSIEIE && loosePhoMediumIDPassChIso && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso"), ""],
                  ["loosePhoSIEIE"   , "phosel_noCut_SIEIE_barrel", [100,0.,.015],extraPhotonCuts%("loosePhoMediumIDPassHoverE && loosePhoMediumIDPassChIso && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso && (abs(loosePhoSCEta)<1.47)"),""],
		  ["loosePhoSIEIE"   , "phosel_noCut_SIEIE_endcap"  ,  [100,0.015,.07],extraPhotonCuts%("loosePhoMediumIDPassHoverE && loosePhoMediumIDPassChIso && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso && (abs(loosePhoSCEta)>1.47)"),""],
		  ["loosePhoSIEIE"   , "phosel_noCut_SIEIE", [100,0.,.07], extraPhotonCuts%("loosePhoMediumIDPassHoverE && loosePhoMediumIDPassChIso && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso"), ""],
                  ["loosePhoSIEIE"   , "phosel_noCut_SIEIE_GenuinePho", [100,0.,.07], extraPhotonCuts%("loosePhoMediumIDPassHoverE && loosePhoMediumIDPassChIso && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso && loosePhotonIsGenuine"), ""],
                  ["loosePhoSIEIE"   , "phosel_noCut_SIEIE_MisIDEle", [100,0.,.07], extraPhotonCuts%("loosePhoMediumIDPassHoverE && loosePhoMediumIDPassChIso && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso && loosePhotonIsMisIDEle"), ""],
                  ["loosePhoSIEIE"   , "phosel_noCut_SIEIE_HadPho", [100,0.,.07], extraPhotonCuts%("loosePhoMediumIDPassHoverE && loosePhoMediumIDPassChIso && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso && loosePhotonIsHadronicPhoton"), ""],
                  ["loosePhoSIEIE"   , "phosel_noCut_SIEIE_HadFake", [100,0.,.07], extraPhotonCuts%("loosePhoMediumIDPassHoverE && loosePhoMediumIDPassChIso && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso && loosePhotonIsHadronicFake"), ""],
		  ["loosePhoPFChIso" , "phosel_noCut_ChIso", [80,0,20], extraPhotonCuts%("loosePhoMediumIDPassHoverE && loosePhoMediumIDPassSIEIE && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso"), ""],
		  ["loosePhoPFChIso" , "phosel_noCut_ChIso_GenuinePhoton" ,      [80,0,20], extraPhotonCuts%("loosePhoMediumIDPassHoverE && loosePhoMediumIDPassSIEIE && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso && loosePhotonIsGenuine"), ""],
		  ["loosePhoPFChIso" , "phosel_noCut_ChIso_MisIDEle",      [80,0,20], extraPhotonCuts%("loosePhoMediumIDPassHoverE && loosePhoMediumIDPassSIEIE && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso && loosePhotonIsMisIDEle"), ""],
                  ["loosePhoPFChIso" , "phosel_noCut_ChIso_HadronicPhoton" ,      [80,0,20], extraPhotonCuts%("loosePhoMediumIDPassHoverE && loosePhoMediumIDPassSIEIE && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso && loosePhotonIsHadronicPhoton"), ""],
		  ["loosePhoPFChIso" , "phosel_noCut_ChIso_HadronicFake",      [80,0,20], extraPhotonCuts%("loosePhoMediumIDPassHoverE && loosePhoMediumIDPassSIEIE && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso && loosePhotonIsHadronicFake"), ""],
		  ["loosePhoPFChIso" , "phosel_noCut_ChIso_PromptPhoton" ,      [80,0,20], extraPhotonCuts%("loosePhoMediumIDPassHoverE && loosePhoMediumIDPassSIEIE && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso && (loosePhotonIsGenuine||loosePhotonIsMisIDEle)"), ""],
		  ["loosePhoPFChIso" , "phosel_noCut_ChIso_NonPromptPhoton" ,      [80,0,20], extraPhotonCuts%("loosePhoMediumIDPassHoverE && loosePhoMediumIDPassSIEIE && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso && (loosePhotonIsHadronicPhoton||loosePhotonIsHadronicFake)"), ""],
		  ["loosePhoPFNeuIso", "phosel_noCut_NeuIso",      [80,0,40], extraPhotonCuts%("loosePhoMediumIDPassHoverE && loosePhoMediumIDPassSIEIE && loosePhoMediumIDPassChIso && loosePhoMediumIDPassPhoIso"), ""],
                  ["loosePhoPFLoosePhoIso", "phosel_noCut_PhoIso",      [200,0,100], extraPhotonCuts%("loosePhoMediumIDPassHoverE && loosePhoMediumIDPassSIEIE && loosePhoMediumIDPassChIso && loosePhoMediumIDPassNeuIso"), ""],
                  ["loosePhoPFChIso" , "phosel_AntiSIEIE_ChIso",      [80,0,20], extraPhotonCuts%("loosePhoMediumIDPassHoverE && !loosePhoMediumIDPassSIEIE && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso"), ""],
		  ["loosePhoPFChIso" , "phosel_AntiSIEIE_ChIso_GenuinePho",      [80,0,20], extraPhotonCuts%("loosePhoMediumIDPassHoverE && !loosePhoMediumIDPassSIEIE && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso && loosePhotonIsGenuine"), ""],
                  ["loosePhoPFChIso" , "phosel_AntiSIEIE_ChIso_MisIDEle",      [80,0,20], extraPhotonCuts%("loosePhoMediumIDPassHoverE && !loosePhoMediumIDPassSIEIE && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso && loosePhotonIsMisIDEle"), ""],
		  ["loosePhoPFChIso" , "phosel_AntiSIEIE_ChIso_HadPho",      [80,0,20], extraPhotonCuts%("loosePhoMediumIDPassHoverE && !loosePhoMediumIDPassSIEIE && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso && loosePhotonIsHadronicPhoton"), ""],
		  ["loosePhoPFChIso" , "phosel_AntiSIEIE_ChIso_HadFake",      [200,0,50], extraPhotonCuts%("loosePhoMediumIDPassHoverE && !loosePhoMediumIDPassSIEIE && loosePhoMediumIDPassNeuIso && loosePhoMediumIDPassPhoIso && loosePhotonIsHadronicFake"), ""],
		  ["nPho","phosel_NGenuinePho",[2,0,2], extraPhotonCuts%("photonIsGenuine"), ""],
                  ["nPho","phosel_NMisIDEle",[2,0,2], extraPhotonCuts%("photonIsMisIDEle"), ""],
                  ["nPho","phosel_NHadronicPho",[2,0,2], extraPhotonCuts%("photonIsHadronicPhoton"), ""],
                  ["nPho","phosel_NHadronicFake",[2,0,2], extraPhotonCuts%("photonIsHadronicFake"), ""],
                  ["phoPFRandConeChIsoUnCorr", "phosel_RandomCone",[80,0,20],extraPhotonCuts%("phoMediumID") , ""],
                  ["photonParentPID", "phosel_mcMomPIDGenuinePho",[2000,-1000,1000],extraPhotonCuts%("phoMediumID && photonIsGenuine") , ""],
                  ["photonParentPID", "phosel_mcMomPIDMisIDEle",[2000,-1000,1000],extraPhotonCuts%("phoMediumID && photonIsMisIDEle") , ""],
                  ["photonParentPID", "phosel_mcMomPIDHadPho",[2000,-1000,1000],extraPhotonCuts%("phoMediumID && photonIsHadronicPhoton") , ""],
                  ["photonParentPID", "phosel_mcMomPIDHadFake",[2000,-1000,1000],extraPhotonCuts%("phoMediumID && photonIsHadronicFake") , ""],
                  ]
histograms=[]

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
