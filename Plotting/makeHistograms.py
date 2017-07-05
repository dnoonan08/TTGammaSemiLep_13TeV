from ROOT import *
import sys
from sampleInformation import *
import os


finalState = "Mu"

if finalState=="Mu":
    sampleList[-1] = "DataMu"
    analysisNtupleLocation = "/uscms_data/d2/dnoonan/13TeV_TTGamma/Ntuples/muons/"
    outputhistName = "histograms/mu/testhists.root"
if finalState=="Ele":
    sampleList[-1] = "DataEle"
    analysisNtupleLocation = "/uscms_data/d2/dnoonan/13TeV_TTGamma/Ntuples/electrons/"
    outputhistName = "histograms/ele/testhists.root"


sample = sys.argv[-1]

if not sample in sampleList:
    print "Sample isn't in list"
    print sampleList
    sys.exit()

preselhistogramInformation = {"jet1Pt" :[280,20,300],
                              "jet2Pt" :[280,20,300],
                              "jet3Pt" :[280,20,300],
                              "Njet"   :[8,2,10],
                              "M3"     :[100,0,400],
                              "nVtx"   :[40,0,40],
                              }

photonhistogramInformation = {"photon1Et"      :[40,0,200],
                              "photon1Phi"     :[100,-3.15,3.15],
                              "photon1Eta"     :[100,-2.5,2.5],
                              "photon1Iso"     :[100,0.,10.],
                              "dRPhotonLepton" :[100,0.,5.],
                              "dRPhotonJet"    :[100,0.,5.],
                              "M3"             :[100,0,400],
                              }


preselhistogramList = {}

for histo in preselhistogramInformation:
    histInfo = preselhistogramInformation[histo]
    preselhistogramList[histo] = {}
    preselhistogramList[histo][sample] = TH1F("preSel_%s_%s"%(histo,sample),"preSel_%s_%s"%(histo,sample),histInfo[0],histInfo[1],histInfo[2])
    preselhistogramList[histo][sample].SetFillColor(samples[sample][1])

    if samples[sample][-1]==isData:
        preselhistogramList[histo][sample].SetMarkerStyle(20)
        preselhistogramList[histo][sample].SetLineWidth(0)

phoselhistogramList = {}

for histo in photonhistogramInformation:
    histInfo = photonhistogramInformation[histo]
    phoselhistogramList[histo] = {}
    phoselhistogramList[histo][sample] = TH1F("phoSel_%s_%s"%(histo,sample),"phoSel_%s_%s"%(histo,sample),histInfo[0],histInfo[1],histInfo[2])
    phoselhistogramList[histo][sample].SetFillColor(samples[sample][1])

    if samples[sample][-1]==isData:
        phoselhistogramList[histo][sample].SetMarkerStyle(20)
        phoselhistogramList[histo][sample].SetLineWidth(0)
        


def fillPreselHistograms(preselhistogramList,sample,event,fillWeight):
    preselhistogramList['M3'][sample].Fill(event.M3,fillWeight)
    preselhistogramList['jet1Pt'][sample].Fill(event.jetPt[0],fillWeight)
    preselhistogramList['jet2Pt'][sample].Fill(event.jetPt[1],fillWeight)
    preselhistogramList['jet3Pt'][sample].Fill(event.jetPt[2],fillWeight)
    preselhistogramList['Njet'][sample].Fill(event.nJet,fillWeight)
    preselhistogramList['nVtx'][sample].Fill(event.nVtx,fillWeight)


def fillPhoselHistograms(phoselhistogramList,sample,event,fillWeight):
    for i in range(len(event.phoEt)):
        if event.phoMediumID[i]:
            phoselhistogramList['M3'][sample].Fill(event.M3,fillWeight)
            phoselhistogramList['photon1Et'][sample].Fill(event.phoEt[i],fillWeight)
            phoselhistogramList['photon1Eta'][sample].Fill(event.phoEta[i],fillWeight)
            phoselhistogramList['photon1Phi'][sample].Fill(event.phoPhi[i],fillWeight)
            phoselhistogramList['photon1Iso'][sample].Fill(event.phoPFChIso[i]+event.phoPFNeuIso[i]+event.phoPFPhoIso[i],fillWeight)
            for dR in event.dRPhotonLepton:
                phoselhistogramList['dRPhotonLepton'][sample].Fill(dR,fillWeight)
            for dR in event.dRPhotonJet:
                phoselhistogramList['dRPhotonJet'][sample].Fill(dR,fillWeight)
            break



if sample in sampleList:
    tree = TChain("AnalysisTree")
    fileList = samples[sample][0]
    for fileName in fileList:
        tree.Add("%s/%s"%(analysisNtupleLocation,fileName))

    print sample

    print "Number of events:", tree.GetEntries()

    i = 0.    
    N = tree.GetEntries()
    k = 50
    
    for event in tree:
        if i%(int(N/k))==0:            
            j = int(i/(int(N/k)))

            sys.stdout.write("[%s%s] %3i%%" % ("="*j," " * (k-j),int(i*100/N)))
            sys.stdout.flush()
            sys.stdout.write("\b"*(k+8))
        i += 1.
        if not event.passPresel_Mu:# or event.nJet < 4 or event.nBJet<2:
            continue

        fillWeight = 1.        

        if samples[sample][-1]==isMC:
            fillWeight *= event.evtWeight
            fillWeight *= event.PUweight
            fillWeight *= event.btagWeight
            fillWeight *= event.muEffWeight
            fillWeight *= event.eleEffWeight

        fillPreselHistograms(preselhistogramList,sample,event,fillWeight)
        
        if event.passAll_Mu:
            fillPhoselHistograms(phoselhistogramList,sample,event,fillWeight)

    sys.stdout.write("[%s] 100%%" % ("="*50))
    print
    tree.Clear()

outputFile = TFile(outputhistName,"update")
outputFile.rmdir(sample)
outputFile.mkdir(sample)
outputFile.cd(sample)
for hist in preselhistogramList:
    preselhistogramList[hist][sample].Write()
for hist in phoselhistogramList:
    phoselhistogramList[hist][sample].Write()
outputFile.Close()
