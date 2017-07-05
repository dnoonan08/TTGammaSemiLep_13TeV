from ROOT import *

from sampleInformation import *

gROOT.SetBatch(True)

stackList = sampleList[:-1]

stackList.remove("WJets")
stackList.reverse()

_file  = TFile("histograms/mu/testhists.root")

preselhistograms = ["jet1Pt" ,
                    "jet2Pt" ,
                    "jet3Pt" ,
                    "Njet"   ,
                    "M3"     ,
                    "nVtx"    ,
                    ]

phoselhistograms = ["photon1Et"     ,     
                    "photon1Phi"    ,    
                    "photon1Eta"    ,    
                    "dRPhotonLepton",
                    "dRPhotonJet"   ,   
                    "M3"            ,            
                    ]

c1 = TCanvas("c1","c1",1200,800)
c1.cd()
for histName in preselhistograms:
    stack = THStack("presel_%s"%histName,"presel_%s"%histName)
    for sample in stackList:
        hist = _file.Get("%s/preSel_%s_%s"%(sample,histName,sample)).Clone(sample)
        # print hist
        # print hist.Integral()
        stack.Add(hist)
        # print stack.GetStack().Last().Integral()
    dataHist = _file.Get("DataMu/preSel_%s_DataMu"%(histName))

    print dataHist

    stack.SetMaximum(1.05*max(dataHist.GetMaximum(),stack.GetMaximum()))
    stack.Draw("hist,e0")
    dataHist.Draw("e,same")
    
    c1.SaveAs("plots/presel_mu_%s.pdf"%histName)



for histName in phoselhistograms:
    stack = THStack("phosel_%s"%histName,"phosel_%s"%histName)
    for sample in stackList:
        hist = _file.Get("%s/phoSel_%s_%s"%(sample,histName,sample)).Clone(sample)
        # print hist
        # print hist.Integral()
        stack.Add(hist)
        # print stack.GetStack().Last().Integral()
    dataHist = _file.Get("DataMu/phoSel_%s_DataMu"%(histName))

    print dataHist

    stack.SetMaximum(1.05*max(dataHist.GetMaximum(),stack.GetMaximum()))
    stack.Draw("hist,e0")
    dataHist.Draw("e,same")
    
    c1.SaveAs("plots/phosel_mu_%s.pdf"%histName)

