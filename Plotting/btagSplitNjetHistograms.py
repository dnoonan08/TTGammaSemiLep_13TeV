from ROOT import *
import sys
from sampleInformation import *
import os

gROOT.SetBatch(True)

finalState = "Mu"

#nBJets = 1

# btagWeight = ["1","(1-btagWeight[0])","(btagWeight[2])"]



# extraCutsTight       = "(passPresel_Mu && nJet>=4 && nBJet>=2)*"
# extraPhotonCutsTight = "(passPresel_Mu && nJet>=4 && nBJet>=2 && %s)*"

# extraCuts       = "(passPresel_Mu)*"
# extraPhotonCuts = "(passPresel_Mu && %s)*"

if finalState=="Mu":
    sampleList[-1] = "DataMu"
    sampleList[-2] = "QCDMu"
    analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/troy2012/13TeV_AnalysisNtuples/muons/"
    outputhistName = "histograms/mu/testBtaghists.root"
if finalState=="Ele":
    sampleList[-1] = "DataEle"
    sampleList[-2] = "QCDEle"
    analysisNtupleLocation = "/uscms_data/d2/dnoonan/13TeV_TTGamma/Ntuples/electrons/"
    outputhistName = "histograms/ele/testBtaghists.root"


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

hist_njets0Tag = TH1F("njets0Tag_%s"%sample,"njets0Tag_%s"%sample,10,0,10)
hist_njets1Tag = TH1F("njets1Tag_%s"%sample,"njets1Tag_%s"%sample,10,0,10)
hist_njets2Tag = TH1F("njets2Tag_%s"%sample,"njets2Tag_%s"%sample,10,0,10)
hist_phoselnjets0Tag = TH1F("phoselnjets0Tag_%s"%sample,"phoselnjets0Tag_%s"%sample,10,0,10)
hist_phoselnjets1Tag = TH1F("phoselnjets1Tag_%s"%sample,"phoselnjets1Tag_%s"%sample,10,0,10)
hist_phoselnjets2Tag = TH1F("phoselnjets2Tag_%s"%sample,"phoselnjets2Tag_%s"%sample,10,0,10)

if not "Data" in sample:

    tree.Draw("nJet>>njets0Tag_%s"%sample,      "(passPresel_Mu)*evtWeight*PUweight*muEffWeight*eleEffWeight*btagWeight[0]")
    tree.Draw("nJet>>njets1Tag_%s"%sample,      "(passPresel_Mu)*evtWeight*PUweight*muEffWeight*eleEffWeight*btagWeight[1]")
    tree.Draw("nJet>>njets2Tag_%s"%sample,      "(passPresel_Mu)*evtWeight*PUweight*muEffWeight*eleEffWeight*btagWeight[2]")
    tree.Draw("nJet>>phoselnjets0Tag_%s"%sample,"(phoMediumID && passPresel_Mu)*evtWeight*PUweight*muEffWeight*eleEffWeight*btagWeight[0]")
    tree.Draw("nJet>>phoselnjets1Tag_%s"%sample,"(phoMediumID && passPresel_Mu)*evtWeight*PUweight*muEffWeight*eleEffWeight*btagWeight[1]")
    tree.Draw("nJet>>phoselnjets2Tag_%s"%sample,"(phoMediumID && passPresel_Mu)*evtWeight*PUweight*muEffWeight*eleEffWeight*btagWeight[2]")
else:
    tree.Draw("nJet>>njets0Tag_%s"%sample,      "(passPresel_Mu && nBJet>=0)")
    tree.Draw("nJet>>njets1Tag_%s"%sample,      "(passPresel_Mu && nBJet==1)")
    tree.Draw("nJet>>njets2Tag_%s"%sample,      "(passPresel_Mu && nBJet>=2)")
    tree.Draw("nJet>>phoselnjets0Tag_%s"%sample,"(phoMediumID && passPresel_Mu && nBJet>=0)")
    tree.Draw("nJet>>phoselnjets1Tag_%s"%sample,"(phoMediumID && passPresel_Mu && nBJet==1)")
    tree.Draw("nJet>>phoselnjets2Tag_%s"%sample,"(phoMediumID && passPresel_Mu && nBJet>=2)")
    


# histograms = []
# for h_Info in histogramInfo:
#     print "filling", h_Info[1], sample
#     evtWeight = ""
#     histograms.append(TH1F("%s_%s"%(h_Info[1],sample),"%s_%s"%(h_Info[1],sample),h_Info[2][0],h_Info[2][1],h_Info[2][2]))
#     if h_Info[-1]=="":
#         evtWeight = "%s%s"%(h_Info[3],weights)
#     else:
#         evtWeight = h_Info[-1]
        
#     if "Data" in sample:
#         evtWeight = h_Info[3]

#     if evtWeight[-1]=="*":
#         evtWeight= evtWeight[:-1]
#     tree.Draw("%s>>%s_%s"%(h_Info[0],h_Info[1],sample),evtWeight)


outputFile = TFile(outputhistName,"update")
outputFile.rmdir(sample)
outputFile.mkdir(sample)
outputFile.cd(sample)
hist_njets0Tag.Write()
hist_njets1Tag.Write()
hist_njets2Tag.Write()
hist_phoselnjets0Tag.Write()
hist_phoselnjets1Tag.Write()
hist_phoselnjets2Tag.Write()

outputFile.Close()
