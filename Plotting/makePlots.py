from ROOT import *
import os

from sampleInformation import *

gROOT.SetBatch(True)

import CMS_lumi

from Style import *
thestyle = Style()

HasCMSStyle = False
style = None
if os.path.isfile('tdrstyle.C'):
    ROOT.gROOT.ProcessLine('.L tdrstyle.C')
    ROOT.setTDRStyle()
    print "Found tdrstyle.C file, using this style."
    HasCMSStyle = True
    if os.path.isfile('CMSTopStyle.cc'):
        gROOT.ProcessLine('.L CMSTopStyle.cc+')
        style = CMSTopStyle()
        style.setupICHEPv1()
        print "Found CMSTopStyle.cc file, use TOP style if requested in xml file."
if not HasCMSStyle:
    print "Using default style defined in cuy package."
    thestyle.SetStyle()

ROOT.gROOT.ForceStyle()


stackList = sampleList[:-1]

# stackList.remove("WJets")
stackList.reverse()

_file  = TFile("histograms/mu/testhists.root")

YesLog = True
NoLog=False

preselhistograms = {"jet1Pt" : ["Leading Jet Pt (GeV)",  YesLog],
                    "jet2Pt" : ["Second Jet Pt (GeV)",  YesLog],
                    "jet3Pt" : ["Third Jet Pt (GeV)",  YesLog],
                    "Njet"   : ["N Jets",  NoLog],
                    "Nbjet"  : ["N B-Jets",  NoLog],
                    "M3"     : ["M_{3} (GeV)",  YesLog],
                    "nVtx"   : ["N Vtx",   NoLog],
                    "nVtxup"   : ["N Vtx",   NoLog],
                    "nVtxdo"   : ["N Vtx",   NoLog],
                    }

phoselhistograms = {"photonEt"      : ["Photon Et (GeV)"  , NoLog],     
                    "photonPhi"     : ["Photon Phi (GeV)" , NoLog],    
                    "photonEta"     : ["Photon Eta (GeV)" , NoLog],    
                    # "dRPhotonLepton" : ["dR(Photon,Lepton)", NoLog],
                    # "dRPhotonJet"    : ["dR(Photon,Jet)"   , NoLog],   
                    # "M3"             : ["M_{3} (GeV)"         , NoLog],            
                    }



H = 600;
W = 800;

canvas = TCanvas('c1','c1',W,H)

# references for T, B, L, R                                                                                                             
T = 0.08*H
B = 0.12*H
L = 0.12*W
R = 0.04*W
canvas.SetFillColor(0)
canvas.SetBorderMode(0)
canvas.SetFrameFillStyle(0)
canvas.SetFrameBorderMode(0)
canvas.SetLeftMargin( L/W )
canvas.SetRightMargin( R/W )
canvas.SetTopMargin( T/H )
canvas.SetBottomMargin( B/H )
canvas.SetTickx(0)

canvas.cd()

legList = {'TTGamma': [kAzure+3, 't#bar{t}+#gamma'],
          'TTJets': [kRed+1, 't#bar{t}+jets'],
          'TTV': [kRed+1, 't#bar{t}+V'],
          'Vgamma': [kGray, 'W/Z+#gamma'],
          'SingleTop': [kMagenta, 'Single t'],
          'WJets': [kGreen -3, 'W+jets'],
          'ZJets': [kGreen -3, 'Z+jets'],
          'QCD': [kYellow, 'Multijet'],
          }

mcList = {'TTGamma': [kOrange],
          'TTbar': [kRed+1],
          'TTV': [kRed-7],
          'SingleTop': [kOrange-3],
          'WGamma': [kBlue-4],
          'ZGamma': [kBlue-4],
          'WJets': [kCyan-3],
          'ZJets': [kCyan-3],

          'QCD': [kGreen+3],
          }

legend = TLegend(0.71, 1-T/H-0.01 - 0.06*(len(legList)+1), 1-R/W-0.01, 1-(T/H)-0.01)

legend.SetBorderSize(0)
legend.SetFillColor(0)

histName = preselhistograms.keys()[0]
legList = stackList[:]
legList.reverse()
dataHist = _file.Get("DataMu/presel_%s_DataMu"%(histName))
legend.AddEntry(dataHist, "Data", 'pe')

for sample in legList:
    hist = _file.Get("%s/presel_%s_%s"%(sample,histName,sample))
    hist.SetFillColor(mcList[sample][0])
    hist.SetLineColor(mcList[sample][0])
    legend.AddEntry(hist,sample,'f')

for histName in preselhistograms:
    stack = THStack("presel_%s"%histName,"presel_%s"%histName)

    for sample in stackList:
        hist = _file.Get("%s/presel_%s_%s"%(sample,histName,sample)).Clone(sample)
        
        # print hist
        # print hist.Integral()
        hist.SetFillColor(mcList[sample][0])
        hist.SetLineColor(mcList[sample][0])
        stack.Add(hist)
        # print stack.GetStack().Last().Integral()


    dataHist = _file.Get("DataMu/presel_%s_DataMu"%(histName))
    
    print dataHist
    canvas.SetLogy(preselhistograms[histName][-1])

    stack.SetMaximum(1.05*max(dataHist.GetMaximum(),stack.GetMaximum()))
    stack.Draw("HIST")
    stack.GetHistogram().GetXaxis().SetTitle(preselhistograms[histName][0])
    dataHist.Draw("e,X0,same")
    legend.Draw("same")
    canvas.SaveAs("plots/presel_mu_%s.pdf"%histName)
    canvas.SetLogy(0)



for histName in phoselhistograms:
    stack = THStack("phosel_%s"%histName,"phosel_%s"%histName)
    for sample in stackList:
        hist = _file.Get("%s/phosel_%s_%s"%(sample,histName,sample)).Clone(sample)
        # print hist
        # print hist.Integral()
        hist.SetFillColor(mcList[sample][0])
        hist.SetLineColor(mcList[sample][0])
        stack.Add(hist)
        # print stack.GetStack().Last().Integral()
    dataHist = _file.Get("DataMu/phosel_%s_DataMu"%(histName))

    print dataHist
    canvas.SetLogy(phoselhistograms[histName][-1])

    stack.SetMaximum(1.05*max(dataHist.GetMaximum(),stack.GetMaximum()))
    stack.Draw("hist")
    stack.GetHistogram().GetXaxis().SetTitle(phoselhistograms[histName][0])
    dataHist.Draw("e,X0,same")
    legend.Draw("same")

    canvas.SaveAs("plots/phosel_mu_%s.pdf"%histName)

