from ROOT import *
import sys
from sampleInformation import *
import os

gROOT.SetBatch(True)

finalState = "Mu"


extraCutsTight       = "(passPresel_Mu && nJet>=4 && nBJet>=2)*"
extraPhotonCutsTight = "(passPresel_Mu && nJet>=4 && nBJet>=2 && phoMediumID)*"

extraCuts       = "(passPresel_Mu)*"
extraPhotonCuts = "(passPresel_Mu && phoMediumID)*"

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


if "Tight" in sys.argv:
    print "Tight Select"
    extraCuts = extraCutsTight
    extraPhotonCuts = extraPhotonCutsTight
    sys.argv.remove("Tight")
    outputhistName = outputhistName.replace("hists.root","hists_tight.root")


sample = sys.argv[-1]

if not sample in sampleList:
    print "Sample isn't in list"
    print sampleList
    sys.exit()

# preselhistogramInformation = {"jet1Pt" :[980,20,1000],
#                               "jet2Pt" :[280,20,600],
#                               "jet3Pt" :[280,20,300],
#                               "Njet"   :[8,2,10],
#                               "Nbjet"   :[8,1,10],
#                               "M3"     :[300,0,600],
#                               "nVtx"   :[40,0,40],
#                               }

# photonhistogramInformation = {"photon1Et"      :[40,0,200],
#                               "photon1Phi"     :[100,-3.15,3.15],
#                               "photon1Eta"     :[100,-2.5,2.5],
#                               "photon1Iso"     :[100,0.,10.],
#                               "dRPhotonLepton" :[100,0.,5.],
#                               "dRPhotonJet"    :[100,0.,5.],
#                               "M3"             :[100,0,400],
#                               }


tree = TChain("AnalysisTree")
fileList = samples[sample][0]
for fileName in fileList:
    tree.Add("%s/%s"%(analysisNtupleLocation,fileName))

print sample

print "Number of events:", tree.GetEntries()

# presel_jet1Pt = TH1F("presel_jet1Pt_%s"%(sample),"presel_jet1Pt_%s"%(sample),1000,0,1000)
# presel_jet2Pt = TH1F("presel_jet2Pt_%s"%(sample),"presel_jet2Pt_%s"%(sample),1000,0,1000)
# presel_jet3Pt = TH1F("presel_jet3Pt_%s"%(sample),"presel_jet3Pt_%s"%(sample),1000,0,1000)
# presel_Njet   = TH1F("presel_Njet_%s"%(sample),"presel_Njet_%s"%(sample),15,0,15)
# presel_Nbjet  = TH1F("presel_Nbjet_%s"%(sample),"presel_Nbjet_%s"%(sample),10,0,10)
# presel_M3     = TH1F("presel_M3_%s"%(sample),"presel_M3_%s"%(sample),300,0,600)
# presel_nVtx   = TH1F("presel_nVtx_%s"%(sample),"presel_nVtx_%s"%(sample),50,0,50)
# presel_nVtxup = TH1F("presel_nVtxup_%s"%(sample),"presel_nVtxup_%s"%(sample),50,0,50)
# presel_nVtxdo = 



# 
histogramInfo = [ ["jetPt[0]" , "presel_jet1Pt"   ,    [1000,0,1000],  extraCuts      , ""],
                  ["jetPt[1]" , "presel_jet2Pt"   ,    [1000,0,1000],  extraCuts      , ""],
                  ["jetPt[2]" , "presel_jet3Pt"   ,    [1000,0,1000],  extraCuts      , ""],
                  ["nJet"     , "presel_Njet"     ,        [15,0,15],  extraCuts      , ""],
                  ["nBJet"    , "presel_Nbjet"    ,        [10,0,10],  extraCuts      , ""],
                  ["M3"       , "presel_M3"       ,      [300,0,600],  extraCuts      , ""],
                  ["nVtx"     , "presel_nVtx"     ,        [50,0,50],  extraCuts      , ""],
                  ["nVtx"     , "presel_nVtxup"   ,        [50,0,50],  extraCuts      , "%sevtWeight*PUweight_Up*muEffWeight*eleEffWeight*btagWeight"%extraCuts],
                  ["nVtx"     , "presel_nVtxdo"   ,        [50,0,50],  extraCuts      , "%sevtWeight*PUweight_Do*muEffWeight*eleEffWeight*btagWeight"%extraCuts],
                  ["phoEt"    , "phosel_photonEt" ,      [300,0,300],  extraPhotonCuts, ""],
                  ["phoEta"   , "phosel_photonEta",   [100,-2.5,2.5],  extraPhotonCuts, ""],
                  ["phoPhi"   , "phosel_photonPhi", [100,-3.15,3.15],  extraPhotonCuts, ""],
                  ["M3"        , "phosel_M3"      , [100,-3.15,3.15],  extraPhotonCuts, ""],
                  ]


histograms = []
for h_Info in histogramInfo:
    print "filling", h_Info[1], sample
    evtWeight = ""
    histograms.append(TH1F("%s_%s"%(h_Info[1],sample),"%s_%s"%(h_Info[1],sample),h_Info[2][0],h_Info[2][1],h_Info[2][2]))
    if h_Info[-1]=="":
        evtWeight = "%sevtWeight*PUweight*muEffWeight*eleEffWeight*btagWeight"%h_Info[3]
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
