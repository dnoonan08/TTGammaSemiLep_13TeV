####
# make pdf figures of the Njet/Nbjet bins
# uses output files created with btagSplitNjetHistograms.py
####

from ROOT import *
import os
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
H = 600;
W = 800;

canvas = TCanvas('c1','c1',W,H)
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

mcList = {'TTGamma': [kOrange],
          'TTbar': [kRed+1],
          'TTV': [kRed-7],
          'SingleTop': [kOrange-3],
          'WGamma': [kBlue-4],
          'ZGamma': [kBlue-2],
          'WJets': [kCyan-3],
          'ZJets': [kCyan-5],
          #'QCDMu': [kGreen+3],
          }

_file = TFile("histograms/mu/testBtaghists.root","read")

samples = ['TTGamma',	  
           'TTbar',	  
           'WGamma',	  
           'ZGamma',	  
           'ZJets',	  
           'WJets',
           'SingleTop', 
           'TTV',	  
           #'QCDMu',	  
           'DataMu',	  
           ]


histograms = []

for s in samples:    
    histograms.append(TH1F("jbMult_%s"%s,"jbMult_%s"%s,10,0,10))

    h1 = _file.Get("%s/njets1Tag_%s"%(s,s))
    h2 = _file.Get("%s/njets2Tag_%s"%(s,s))
    for i in range(4):
        histograms[-1].SetBinContent(i+1,h1.GetBinContent(3+i))
        histograms[-1].SetBinContent(i+6,h2.GetBinContent(3+i))

        histograms[-1].SetBinContent(5 ,h1.Integral(7,-1))
        histograms[-1].SetBinContent(10,h1.Integral(7,-1))

    if not "DataMu" in s:
        histograms[-1].SetFillColor(mcList[s][0])
        histograms[-1].SetLineColor(mcList[s][0])
    else:
        histograms[-1].SetFillColor(h1.GetFillColor())
        histograms[-1].SetLineColor(h1.GetLineColor())
        histograms[-1].SetMarkerSize(h1.GetMarkerSize())
        histograms[-1].SetMarkerStyle(20)
        histograms[-1].SetMarkerColor(kBlack)

    histograms[-1].GetXaxis().SetBinLabel(1,"=2j=1b")
    histograms[-1].GetXaxis().SetBinLabel(2,"=3j=1b")
    histograms[-1].GetXaxis().SetBinLabel(3,"=4j=1b")
    histograms[-1].GetXaxis().SetBinLabel(4,"=5j=1b")
    histograms[-1].GetXaxis().SetBinLabel(5,"#geq6j=1b")
    histograms[-1].GetXaxis().SetBinLabel(6,"=2j#geq2b")
    histograms[-1].GetXaxis().SetBinLabel(7,"=3j#geq2b")
    histograms[-1].GetXaxis().SetBinLabel(8,"=4j#geq2b")
    histograms[-1].GetXaxis().SetBinLabel(9,"=5j#geq2b")
    histograms[-1].GetXaxis().SetBinLabel(10,"#geq6j#geq2b")
    histograms[-1].GetXaxis().SetLabelSize(0.04)

legendHeightPer = 0.04

legend = TLegend(0.71, 1-T/H-0.01 - legendHeightPer*(len(samples)), 1-R/W-0.01, 1-(T/H)-0.01)

legend.SetBorderSize(0)
legend.SetFillColor(0)













legend.AddEntry(histograms[-1],"data","pe")
legend.AddEntry(histograms[0],'t#bar{t}+#gamma','f')
legend.AddEntry(histograms[1],'t#bar{t}+jets'  ,'f')
legend.AddEntry(histograms[2],'W+#gamma'       ,'f')
legend.AddEntry(histograms[3],'Z+#gamma'       ,'f')
legend.AddEntry(histograms[4],'Z+jets'         ,'f')
legend.AddEntry(histograms[5],'W+jets'         ,'f')
legend.AddEntry(histograms[6],'Single t'       ,'f')
legend.AddEntry(histograms[7],'t#bar{t}+V'     ,'f')
#legend.AddEntry(histograms[8],'Multijet'       ,'f')


stack = THStack()

#stack.Add(histograms[8])
stack.Add(histograms[7])
stack.Add(histograms[6])
stack.Add(histograms[5])
stack.Add(histograms[4])
stack.Add(histograms[3])
stack.Add(histograms[2])
stack.Add(histograms[1])
stack.Add(histograms[0])

stack.Draw()
stack.SetMaximum(1.35*max(histograms[-1].GetMaximum(),stack.GetMaximum()))

histograms[-1].Draw("e,x0,same")

_channelText = "#mu+jets"

CMS_lumi.channelText = _channelText
CMS_lumi.writeChannelText = True
CMS_lumi.writeExtraText = True
CMS_lumi.CMS_lumi(canvas, 4, 11)
legend.Draw()

canvas.SaveAs("JetBjetMult_Presel.pdf")
canvas.SaveAs("JetBjetMult_Presel.png")
