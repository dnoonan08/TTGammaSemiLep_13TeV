####
# make pdf figures of the Njet/Nbjet bins
# uses output files created with btagSplitNjetHistograms.py
####

from ROOT import *
import os
import CMS_lumi
from optparse import OptionParser

padRatio = 0.25
padOverlap = 0.15
padGap = 0.01
parser = OptionParser()
parser.add_option("-c", "--channel", dest="channel", default="Mu",type='str',
                     help="Specify which channel Mu or Ele? default is Mu" )
parser.add_option("-s","--systematic", dest="systematic", default="nominal",type='str',
                     help="Specify up, down or nominal, default is nominal")
(options, args) = parser.parse_args()

finalState = options.channel



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
canvasRatio = TCanvas('c1Ratio','c1Ratio',W,H)
T = 0.08*H
B = 0.12*H
L = 0.12*W
R = 0.04*W
canvasRatio.SetFillColor(0)
canvasRatio.SetBorderMode(0)
canvasRatio.SetFrameFillStyle(0)
canvasRatio.SetFrameBorderMode(0)
canvasRatio.SetLeftMargin( L/W )
canvasRatio.SetRightMargin( R/W )
canvasRatio.SetTopMargin( T/H )
canvasRatio.SetBottomMargin( B/H )
canvasRatio.SetTickx(0)
canvasRatio.SetTicky(0)

pad1 = TPad("p1","p1",0,padRatio-padOverlap,1,1)
pad2 = TPad("p2","p2",0,0,1,padRatio+padOverlap)
pad1.SetLeftMargin( L/W )
pad1.SetRightMargin( R/W )
pad1.SetTopMargin( T/H/(1-padRatio+padOverlap) )
pad1.SetBottomMargin( (padOverlap+padGap)/(1-padRatio+padOverlap) )
pad2.SetLeftMargin( L/W )
pad2.SetRightMargin( R/W )
pad2.SetTopMargin( (padOverlap)/(padRatio+padOverlap) )
pad2.SetBottomMargin( B/H/(padRatio+padOverlap) )

pad1.SetFillColor(0)
pad1.SetBorderMode(0)
pad1.SetFrameFillStyle(0)
pad1.SetFrameBorderMode(0)
pad1.SetTickx(0)
pad1.SetTicky(0)

pad2.SetFillColor(0)
pad2.SetFillStyle(4000)
pad2.SetBorderMode(0)
pad2.SetFrameFillStyle(0)
pad2.SetFrameBorderMode(0)
pad2.SetTickx(0)
pad2.SetTicky(0)

SetOwnership(canvas, False)
SetOwnership(canvasRatio, False)
SetOwnership(pad1, False)
SetOwnership(pad2, False)

#canvasRatio.cd()
#canvasRatio.SetLogy()
pad1.Draw()
pad2.Draw()


canvas.cd()
mcList = {'TTGamma': [kOrange],
          'TTbar': [kRed+1],
          'TGJets':[kGray],
          'TTV': [kRed-7],
          'SingleTop': [kOrange-3],
          'WGamma': [kBlue-4],
          'ZGamma': [kBlue-2],
          'WJets': [kCyan-3],
          'ZJets': [kCyan-5],
          'QCDMu': [kGreen+3],
          }
if finalState=="Mu":
	_file = TFile("histograms/mu/testBtaghists.root","read")
	samples = ['TTGamma',
           'TTbar',
           'TGJets',
           'WGamma',
           'ZGamma',
           'ZJets',
           'WJets',
           'SingleTop',
           'TTV',
         #  'QCDMu',
           'DataMu',
           ]


if finalState=="Ele":
	_file = TFile("histograms/ele/testBtaghists.root","read")
	samples = ['TTGamma',	  
           'TTbar',
           'TGJets',	  
           'WGamma',	  
           'ZGamma',	  
           'ZJets',	  
           'WJets',
           'SingleTop', 
           'TTV',	  	  
           'DataEle',	  
           ]


histograms = []

for s in samples:    
    histograms.append(TH1F("jbMult_%s"%s,"jbMult_%s"%s,15,0,15))
    h0 = _file.Get("%s/phoselnjets0Tag_%s"%(s,s))
    h1 = _file.Get("%s/phoselnjets1Tag_%s"%(s,s))
    h2 = _file.Get("%s/phoselnjets2Tag_%s"%(s,s))
    print s, h0.GetBinContent(3)
    for i in range(4):
	histograms[-1].SetBinContent(i+1,h0.GetBinContent(3+i))
        histograms[-1].SetBinContent(i+6,h1.GetBinContent(3+i))
        histograms[-1].SetBinContent(i+11,h2.GetBinContent(3+i))

    histograms[-1].SetBinContent(5 ,h0.Integral(7,-1))
    histograms[-1].SetBinContent(10,h2.Integral(7,-1))
    histograms[-1].SetBinContent(15,h2.Integral(7,-1))
    if not "DataEle" in s:
        histograms[-1].SetFillColor(mcList[s][0])
        histograms[-1].SetLineColor(mcList[s][0])
    else:
        histograms[-1].SetFillColor(h1.GetFillColor())
        histograms[-1].SetLineColor(h1.GetLineColor())
        histograms[-1].SetMarkerSize(h1.GetMarkerSize())
        histograms[-1].SetMarkerStyle(20)
        histograms[-1].SetMarkerColor(kBlack)
    histograms[-1].GetXaxis().SetBinLabel(1,"=2j=0b")
    histograms[-1].GetXaxis().SetBinLabel(2,"=3j=0b")
    histograms[-1].GetXaxis().SetBinLabel(3,"=4j=0b")
    histograms[-1].GetXaxis().SetBinLabel(4,"=5j=0b")
    histograms[-1].GetXaxis().SetBinLabel(5,"#geq6j=0b")
    histograms[-1].GetXaxis().SetBinLabel(6,"=2j=1b")
    histograms[-1].GetXaxis().SetBinLabel(7,"=3j=1b")
    histograms[-1].GetXaxis().SetBinLabel(8,"=4j=1b")
    histograms[-1].GetXaxis().SetBinLabel(9,"=5j=1b")
    histograms[-1].GetXaxis().SetBinLabel(10,"#geq6j=1b")
    histograms[-1].GetXaxis().SetBinLabel(11,"=2j#geq2b")
    histograms[-1].GetXaxis().SetBinLabel(12,"=3j#geq2b")
    histograms[-1].GetXaxis().SetBinLabel(13,"=4j#geq2b")
    histograms[-1].GetXaxis().SetBinLabel(14,"=5j#geq2b")
    histograms[-1].GetXaxis().SetBinLabel(15,"#geq6j#geq2b")
    histograms[-1].GetXaxis().SetLabelSize(0.04)
legendHeightPer = 0.04

legend = TLegend(0.71, 1-T/H-0.01 - legendHeightPer*(len(samples)), 1-R/W-0.01, 1-(T/H)-0.01)

legend.SetBorderSize(0)
legend.SetFillColor(0)

#legendR = TLegend(0.71, 0.99 - (T/H)/(1.-padRatio+padOverlap) - legendHeightPer/(1.-padRatio+padOverlap)*(len(mcList)+1), 0.99-(R/W), 0.99-(T/H)/(1.-padRatio+padOverlap))
legendR = TLegend(0.31,0.74,0.94,0.91)
legendR.SetNColumns(4);
legendR.SetBorderSize(0)
gStyle.SetLegendTextSize(0.02)
legendR.SetFillColor(0)

legend.AddEntry(histograms[-1],"Data","pe")
legendR.AddEntry(histograms[-1], "Data", 'pe')
legendR.AddEntry(histograms[0],'t#bar{t}+#gamma','f')
legendR.AddEntry(histograms[1],'t#bar{t}+jets'  ,'f')
legendR.AddEntry(histograms[2],'t+#gamma'  ,'f')
legendR.AddEntry(histograms[3],'W+#gamma'       ,'f')
legendR.AddEntry(histograms[4],'Z+#gamma'       ,'f')
legendR.AddEntry(histograms[5],'Z+jets'         ,'f')
legendR.AddEntry(histograms[6],'W+jets'         ,'f')
legendR.AddEntry(histograms[7],'SingleTop'       ,'f')
legendR.AddEntry(histograms[8],'t#bar{t}+V'     ,'f')
#legend.AddEntry(histograms[8],'Multijet'       ,'f')


legend.AddEntry(histograms[0],'t#bar{t}+#gamma','f')
legend.AddEntry(histograms[1],'t#bar{t}+jets'  ,'f')
legend.AddEntry(histograms[2],'t+#gamma'  ,'f')
legend.AddEntry(histograms[3],'W+#gamma'       ,'f')
legend.AddEntry(histograms[4],'Z+#gamma'       ,'f')
legend.AddEntry(histograms[5],'Z+jets'         ,'f')
legend.AddEntry(histograms[6],'W+jets'         ,'f')
legend.AddEntry(histograms[7],'SingleTop'       ,'f')
legend.AddEntry(histograms[8],'t#bar{t}+V'     ,'f')
stack = THStack()

stack.Add(histograms[8])
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
if finalState=="Ele":
	_channelText = "e+jets"
if finalState=="Mu":
	_channelText ="#mu+jets"

CMS_lumi.channelText = _channelText
CMS_lumi.writeChannelText = True
CMS_lumi.writeExtraText = True
CMS_lumi.CMS_lumi(canvas, 4, 11)
legend.Draw()
canvas.SetLogy()
canvas.SaveAs("JetBjetMult_Phosel_log.pdf")
canvas.SaveAs("JetBjetMult_Phosel_log.png")

ratio =histograms[-1].Clone("temp")
temp_stack = stack.GetStack().Last()
for q in range(temp_stack.GetNbinsX()):
       temp_stack.SetBinError(q,0)
ratio.Divide(temp_stack)


pad1.Clear()
pad2.Clear()

canvasRatio.cd()
#canvasRatio.SetLogy()
#canvasRatio.ResetDrawn()

pad1.Clear()
pad2.Clear()


pad1.cd()
#pad1.SetLogy()
stack.Draw('HIST')
#    pad1.Update()
y2 = pad1.GetY2()
stack.SetMinimum(1)
#    pad1.Update()
stack.GetXaxis().SetTitle('')
stack.GetYaxis().SetTitle(histograms[-1].GetYaxis().GetTitle())

stack.SetTitle('')
stack.GetXaxis().SetLabelSize(0)
stack.GetYaxis().SetLabelSize(gStyle.GetLabelSize()/(1.-padRatio+padOverlap))
stack.GetYaxis().SetTitleSize(gStyle.GetTitleSize()/(1.-padRatio+padOverlap))
stack.GetYaxis().SetTitleOffset(gStyle.GetTitleYOffset()*(1.-padRatio+padOverlap))
#stack.GetYaxis().SetTitle(plotInfo[1])
histograms[-1].Draw('E,X0,SAME')
#legendR.AddEntry(histograms[8],'Multijet'       ,'f')
legendR.Draw()
ratio.SetTitle('')

ratio.GetXaxis().SetLabelSize(gStyle.GetLabelSize()/(padRatio+padOverlap))
ratio.GetYaxis().SetLabelSize(gStyle.GetLabelSize()/(padRatio+padOverlap))
ratio.GetXaxis().SetTitleSize(gStyle.GetTitleSize()/(padRatio+padOverlap))
ratio.GetYaxis().SetTitleSize(gStyle.GetTitleSize()/(padRatio+padOverlap))
ratio.GetYaxis().SetTitleOffset(gStyle.GetTitleYOffset()*(padRatio+padOverlap-padGap))
ratio.GetYaxis().SetRangeUser(0.5,5)
ratio.GetYaxis().SetNdivisions(504)
#ratio.GetXaxis().SetTitle(plotInfo[0])
ratio.GetYaxis().SetTitle("Data/MC")

pad2.cd()
ratio.SetMarkerStyle(histograms[-1].GetMarkerStyle())
ratio.SetMarkerSize(histograms[-1].GetMarkerSize())
ratio.SetLineColor(histograms[-1].GetLineColor())
ratio.SetLineWidth(histograms[-1].GetLineWidth())

oneLine = TF1("oneline","1",-9e9,9e9)
oneLine.SetLineColor(kBlack)
oneLine.SetLineWidth(1)
oneLine.SetLineStyle(2)

ratio.Draw('e,x0')
oneLine.Draw("same")

#    pad2.Update()
CMS_lumi.CMS_lumi(pad1, 4, 11)
#canvasRatio.Update()
#canvasRatio.RedrawAxis()
canvasRatio.SetLogy()
canvasRatio.SaveAs("JetBjetMult_Phosel_ratio.pdf")
canvasRatio.SaveAs("JetBjetMult_Phosel_ratio.png")


