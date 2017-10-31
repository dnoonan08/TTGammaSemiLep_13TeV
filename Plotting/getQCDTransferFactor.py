from ROOT import *
import sys
from sampleInformation import *
import os

gROOT.SetBatch(True)

sample = "QCDMu"
finalState = "Mu"

outputFileName = "histograms/mu/qcdTransferFactors.root"
outputFile = TFile(outputFileName,"recreate")

analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/qcdmuons/V08_00_26_07"

tree = TChain("AnalysisTree")
fileList = samples[sample][0]
for fileName in fileList:
    tree.Add("%s/QCDcr_%s"%(analysisNtupleLocation,fileName))

nJets  = 2
nBJets = 0

extraCuts       = "(passPresel_Mu && nJet>=%i && nBJet==%i)*"%(nJets, nBJets)

weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*btagWeight[%i]"%nBJets

histCR = TH1F("histNjet_QCDcr","histNjet_QCDcr",15,0,15)

tree.Draw("nJet>>histNjet_QCDcr",extraCuts+weights)
outputFile.cd()
histCR.Write()


analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/muons/V08_00_26_07"

tree = TChain("AnalysisTree")
fileList = samples[sample][0]
for fileName in fileList:
    tree.Add("%s/%s"%(analysisNtupleLocation,fileName))

nJets  = 2
nBJets = 0
extraCuts       = "(passPresel_Mu && nJet>=%i && nBJet==%i)*"%(nJets, nBJets)

weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*btagWeight[%i]"%nBJets
hist0 = TH1F("histNjet_0b","histNjet_0b",15,0,15)

tree.Draw("nJet>>histNjet_0b",extraCuts+weights)
outputFile.cd()
hist0.Write()

nJets  = 2
nBJets = 1
extraCuts       = "(passPresel_Mu && nJet>=%i && nBJet==%i)*"%(nJets, nBJets)

weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*btagWeight[%i]"%nBJets
hist1 = TH1F("histNjet_1b","histNjet_1b",15,0,15)

tree.Draw("nJet>>histNjet_1b",extraCuts+weights)
outputFile.cd()
hist1.Write()

nJets  = 2
nBJets = 2
extraCuts       = "(passPresel_Mu && nJet>=%i && nBJet>=%i)*"%(nJets, nBJets)

weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*btagWeight[%i]"%nBJets
hist2 = TH1F("histNjet_2b","histNjet_2b",15,0,15)

tree.Draw("nJet>>histNjet_2b",extraCuts+weights)
outputFile.cd()
hist2.Write()


hist0_TF = hist0.Clone("histNjet_0b_TF")
hist0_TF.SetNameTitle("histNjet_0b_TF","histNjet_0b_TF")
hist0_TF.Divide(histCR)

hist1_TF = hist1.Clone("histNjet_1b_TF")
hist1_TF.SetNameTitle("histNjet_1b_TF","histNjet_1b_TF")
hist1_TF.Divide(histCR)

hist2_TF = hist2.Clone("histNjet_2b_TF")
hist2_TF.SetNameTitle("histNjet_2b_TF","histNjet_2b_TF")
hist2_TF.Divide(histCR)

hist0_TF.Write()
hist1_TF.Write()
hist2_TF.Write()


hist_TF = TH1F("TransferFactors","TransferFactors",3,0,3)
hist_TFCR = TH1F("TransferFactorsCR","TransferFactorsCR",3,0,3)

histCR.Rebin(15)
hist0.Rebin(15)
hist1.Rebin(15)
hist2.Rebin(15)

hist_TF.SetBinContent(1,hist0.GetBinContent(1))
hist_TF.SetBinError(1,hist0.GetBinError(1))

hist_TF.SetBinContent(2,hist1.GetBinContent(1))
hist_TF.SetBinError(2,hist1.GetBinError(1))

hist_TF.SetBinContent(3,hist2.GetBinContent(1))
hist_TF.SetBinError(3,hist2.GetBinError(1))

hist_TFCR.SetBinContent(1,histCR.GetBinContent(1))
hist_TFCR.SetBinError(1,histCR.GetBinError(1))

hist_TFCR.SetBinContent(2,histCR.GetBinContent(1))
hist_TFCR.SetBinError(2,histCR.GetBinError(1))

hist_TFCR.SetBinContent(3,histCR.GetBinContent(1))
hist_TFCR.SetBinError(3,histCR.GetBinError(1))

hist_TF.Divide(hist_TFCR)
hist_TF.Write()
