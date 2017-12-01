from ROOT import *
import sys
from sampleInformation import *
import os
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-c", "--channel", dest="channel", default="Mu",type='str',
                     help="Specify which channel Mu or Ele? default is Mu" )
parser.add_option("-s", "--sample", dest="sample", default="",type='str',
                     help="Specify which sample to run on" )
parser.add_option("--syst", "--systematic", dest="systematic", default="nominal",type='str',
		     help="Specify up, down or nominal, default is nominal")
parser.add_option("--Tight","--tight", dest="isTightSelection", default=False,action="store_true",
                     help="Use 4j2t selection" )
parser.add_option("--Loose","--loose", dest="isLooseSelection", default=False,action="store_true",
                     help="Use 2j0t selection" )

(options, args) = parser.parse_args()

level =options.systematic

gROOT.SetBatch(True)

finalState = options.channel
sample = options.sample
isTightSelection = options.isTightSelection
isLooseSelection = options.isLooseSelection

print isTightSelection
print isLooseSelection

nJets = 3
nBJets = 1


#atleast 0, atleast 1, atleast 2, exactly 1, btagWeight[0] = exactly 0

# extraCutsTight       = "(passPresel_Mu && nJet>=4 && nBJet>=2)*"
# extraPhotonCutsTight = "(passPresel_Mu && nJet>=4 && nBJet>=2 && %s)*"
# extraPhoTight= "(passPresel_Mu && nJet>=4 && nBJet>=2 && loosePhoMediumID)*"

# extraCutsLoose       = "(passPresel_Mu && nJet==2 && nBJet==0)*"
# extraPhotonCutsLoose = "(passPresel_Mu && nJet==2 && nBJet==0 && %s)*"

# extraCutsLooseCR       = "(passPresel_Mu && nJet>=2 && nBJet>=0)*"
# extraPhotonCutsLooseCR = "(passPresel_Mu && nJet>=2 && nBJet>=0 && %s)*"

# extraCuts            = "(passPresel_Mu && nJet>=3 && nBJet>=1)*"
# extraPhotonCuts      = "(passPresel_Mu && nJet>=3 && nBJet>=1 && %s)*"

if finalState=="Mu":
    sampleList[-1] = "DataMu"
    sampleList[-2] = "QCDMu"
    analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/muons/V08_00_26_07"
    outputhistName = "histograms/mu/hists.root"

    extraCuts            = "(passPresel_Mu && nJet>=3 && nBJet>=1)*"
    extraPhotonCuts      = "(passPresel_Mu && nJet>=3 && nBJet>=1 && %s)*"

    extraCutsTight       = "(passPresel_Mu && nJet>=4 && nBJet>=2)*"
    extraPhotonCutsTight = "(passPresel_Mu && nJet>=4 && nBJet>=2 && %s)*"

    extraCutsLoose       = "(passPresel_Mu && nJet==2 && nBJet==0)*"
    extraPhotonCutsLoose = "(passPresel_Mu && nJet==2 && nBJet==0 && %s)*"

    extraCutsLooseCR       = "(passPresel_Mu && nJet>=2 && nBJet>=0)*"
    extraPhotonCutsLooseCR = "(passPresel_Mu && nJet>=2 && nBJet>=0 && %s)*"

elif finalState=="Ele":
    sampleList[-1] = "DataEle"
    sampleList[-2] = "QCDEle"
    analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/electrons/V08_00_26_07"
    outputhistName = "histograms/ele/hists.root"

    extraCuts            = "(passPresel_Ele && nJet>=3 && nBJet>=1)*"
    extraPhotonCuts      = "(passPresel_Ele && nJet>=3 && nBJet>=1 && %s)*"

    extraCutsTight       = "(passPresel_Ele && nJet>=4 && nBJet>=2)*"
    extraPhotonCutsTight = "(passPresel_Ele && nJet>=4 && nBJet>=2 && %s)*"

    extraCutsLoose       = "(passPresel_Ele && nJet==2 && nBJet==0)*"
    extraPhotonCutsLoose = "(passPresel_Ele && nJet==2 && nBJet==0 && %s)*"

    extraCutsLooseCR       = "(passPresel_Ele && nJet>=2 && nBJet>=0)*"
    extraPhotonCutsLooseCR = "(passPresel_Ele && nJet>=2 && nBJet>=0 && %s)*"
else:
    print "Unknown final state, options are Mu and Ele"
    sys.exit()


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

if isTightSelection:
    print "Tight Select"
    nJets = 4
    nBJets = 2
    weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*btagWeight[2]"
    extraCuts = extraCutsTight 
    extraPhotonCuts = extraPhotonCutsTight 
    outputhistName = outputhistName.replace("hists.root","hists_tight.root")

if "Loose" in sys.argv:
    print "Loose Select"
    nJets = 2
    nBJets = 0
    weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*(btagWeight[0])"
    extraCuts = extraCutsLoose
    extraPhotonCuts = extraPhotonCutsLoose
    outputhistName = outputhistName.replace("hists.root","hists_loose.root")

if "LooseCR" in sys.argv:
    print "Loose Control Region Select"
    nJets = 2
    nBJets = 0
    weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*1" #*(btagWeight[2])"
    extraCuts = extraCutsLooseCR
    extraPhotonCuts = extraPhotonCutsLooseCR
    outputhistName = outputhistName.replace("hists.root","hists_looseCR.root")

from HistogramListInfo import *
histogramInfo = GetHistogramInfo(extraCuts,extraPhotonCuts,nBJets)


histograms=[]

#sample = sys.argv[-1]

if sample =="QCD_DD":
    if finalState=="Mu":
        if isTightSelection:
            qcd_File    = TFile("histograms/mu/qcdhistsCR_Tight.root","read")
        elif isLooseSelection:
            qcd_File    = TFile("histograms/mu/qcdhistsCR_Loose.root","read")
        else:
            qcd_File    = TFile("histograms/mu/qcdhistsCR.root","read")
        qcd_TF_File = TFile("histograms/mu/qcdTransferFactors.root","read")
        dirName = "QCDMu"
    if finalState=="Ele":
        if isTightSelection:
            qcd_File    = TFile("histograms/ele/qcdhistsCR_Tight.root","read")
        elif isLooseSelection:
            qcd_File    = TFile("histograms/ele/qcdhistsCR_Loose.root","read")
        else:
            qcd_File    = TFile("histograms/ele/qcdhistsCR.root","read")
        qcd_TF_File = TFile("histograms/ele/qcdTransferFactors.root","read")
        dirName = "QCDEle"


    #Calculate the transfer Factor for the QCD events from the QCDcr to the signal region being used, based on jet/bjet multiplicities
    transferFactor = 1.
    histNjet_QCDcr = qcd_TF_File.Get("histNjet_QCDcr")
    histNjet_0b = qcd_TF_File.Get("histNjet_0b")
    histNjet_1b = qcd_TF_File.Get("histNjet_1b")
    histNjet_2b = qcd_TF_File.Get("histNjet_2b")
    if nBJets==0:
        histNjet_2b.Add(histNjet_1b)
        histNjet_2b.Add(histNjet_0b)
    if nBJets==1:
        histNjet_2b.Add(histNjet_1b)
#    transferFactor = histNjet_2b.Integral(nJets+1,-1)/histNjet_QCDcr.Integral(-1,-1)
    transferFactor = histNjet_2b.Integral(nJets+1,-1)/histNjet_QCDcr.Integral(nJets+1,-1)
    print transferFactor

    for h_Info in histogramInfo:
        if not h_Info[5]: continue
        print "filling", h_Info[1], sample
        # tempHist = qcd_File.Get("%s_DD/%s_%s"%(dirName,h_Info[1],dirName))
        # print qcd_File
        # print "%s_DD/%s_%s"%(dirName,h_Info[1],dirName)
        # print tempHist
        histograms.append(qcd_File.Get("QCD_DD/%s_QCD_DD"%(h_Info[1])))
        histograms[-1].Scale(transferFactor)

if not "QCD_DD" in sample:
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

    for h_Info in histogramInfo:
        print "filling", h_Info[1], sample
        evtWeight = ""
        histograms.append(TH1F("%s_%s"%(h_Info[1],sample),"%s_%s"%(h_Info[1],sample),h_Info[2][0],h_Info[2][1],h_Info[2][2]))
        if h_Info[4]=="":
            evtWeight = "%s%s"%(h_Info[3],weights)
        else:
            evtWeight = h_Info[4]

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

