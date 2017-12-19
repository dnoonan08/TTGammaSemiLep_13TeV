from ROOT import *
import os

import sys
from optparse import OptionParser

padRatio = 0.25
padOverlap = 0.15
padGap = 0.01
parser = OptionParser()

parser.add_option("-c", "--channel", dest="channel", default="Mu",type='str',
		  help="Specify which channel Mu or Ele? default is Mu" )
parser.add_option("--Tight","--tight", dest="isTightSelection", default=False,action="store_true",
		  help="Use 4j2t selection" )
parser.add_option("--Loose","--loose", dest="isLooseSelection", default=False,action="store_true",
		  help="Use 2j0t selection" )
parser.add_option("--LooseCR","--looseCR", dest="isLooseCRSelection", default=False,action="store_true",
		  help="Use 2j exactly 0t control region selection" )
parser.add_option("--plot", dest="plotList",action="append",
                     help="Add plots" )
(options, args) = parser.parse_args()

isTightSelection = options.isTightSelection
isLooseSelection = options.isLooseSelection
isLooseCRSelection = options.isLooseCRSelection
plotList = options.plotList

finalState = options.channel
print "Running on the %s channel"%(finalState)
if finalState=='Mu':
	_file  = TFile("histograms/mu/hists.root")
	plotDirectory = "plots_mu/"
	regionText = ", N_{j}#geq3, N_{b}#geq1"
	if isTightSelection:
        	plotDirectory = "tightplots_mu/"
        	_file  = TFile("histograms/mu/hists_tight.root")
        	regionText = ", N_{j}#geq4, N_{b}#geq2"
	if isLooseSelection:
        	plotDirectory = "looseplots_mu/"
        	_file  = TFile("histograms/mu/hists_loose.root")
        	regionText = ", N_{j}=2, N_{b}#geq0"
	if isLooseCRSelection:
        	plotDirectory = "looseCRplots_mu/"
        	_file  = TFile("histograms/mu/hists_looseCR.root")
        	regionText = ", N_{j}#geq2, N_{b}=0"

if finalState=="Ele":
	_file  = TFile("histograms/ele/hists.root")
        plotDirectory = "plots_ele/"
        regionText = ", N_{j}#geq3, N_{b}#geq1"

	if isTightSelection:
    		plotDirectory = "tightplots_ele/"
    		_file  = TFile("histograms/ele/hists_tight.root")
    		regionText = ", N_{j}#geq4, N_{b}#geq2"
	if isLooseSelection:
    		plotDirectory = "looseplots_ele/"
    		_file  = TFile("histograms/ele/hists_loose.root")
    		regionText = ", N_{j}=2, N_{b}#geq0"
	if isLooseCRSelection:
    		plotDirectory = "looseCRplots_ele/"
    		_file  = TFile("histograms/ele/hists_looseCR.root")
    		regionText = ", N_{j}#geq2, N_{b}=0"



from sampleInformation import *

gROOT.SetBatch(True)




YesLog = True
NoLog=False




# Histogram Information:
# [X-axis title, 
#  Y-axis title,
#  Rebinning factor,
#  [x-min,x-max], -1 means keep as is
#  Extra text about region
#  log plot]


histograms = {"presel_jet1Pt"   : ["Leading Jet Pt (GeV)", "Events", 5, [-1,-1], regionText, YesLog, " "],
	      "presel_jet2Pt"   : ["Second Jet Pt (GeV)" , "Events", 5, [-1,-1], regionText, YesLog, " "],
	      "presel_jet3Pt"   : ["Third Jet Pt (GeV)"  , "Events", 5, [-1,-1], regionText, YesLog, " "],
	      "presel_muPt"     : ["Muon p_{T} (GeV)"    , "Events", 5, [-1,-1], regionText,  NoLog, " "],
	      "presel_muEta"    : ["Muon #eta"           , "Events/0.05", 5, [-1,-1], regionText,  NoLog, " "],
	      "presel_muPhi"    : ["Muon #phi"           , "Events/0.06", 5, [-1,-1], regionText,  NoLog, " "],
	      "presel_elePt"    : ["Electron p_{T} (GeV)", "Events", 5, [-1,-1], regionText,  NoLog, " "],
	      "presel_eleSCEta" : ["Electron #eta"       , "Events/0.05", 5, [-1,-1], regionText,  NoLog, " "],
	      "presel_elePhi"   : ["Electron #phi"       , "Events/0.06", 5, [-1,-1], regionText,  NoLog, " "],
	      "presel_Njet"     : ["N Jets"              , "Events", 1, [-1,-1], regionText,  NoLog, " "],
	      "presel_Nbjet"    : ["N B-Jets"            , "Events", 1, [-1,-1], regionText,  NoLog, " "],
	      "presel_M3"       : ["M_{3} (GeV)"         , "Events/5 GeV", 5, [-1,-1], regionText,  NoLog, " "],
	      "presel_M3_control": ["M_{3} (GeV)"         , "Events/5 GeV", 5, [-1,-1], regionText,  NoLog, " "],
	      "presel_MET"      : ["MET (GeV)  "         , "Events/2 GeV", 5, [-1,-1], regionText,  NoLog, " "],
	      "presel_WtransMass"     : ["W transverse mass (GeV)  ", "Events/5", 1, [-1,-1], regionText,  NoLog, " "],
	      "presel_HT"       :["H_{T} (GeV)","Events/9", 1, [-1,-1], regionText,  NoLog, " "],
	      "presel_nVtx"     : ["N Vtx nominal"       , "Events", 1, [-1,-1], regionText,  NoLog, " "],
	      "presel_nVtxup"   : ["N Vtx up"               , "Events", 1, [-1,-1], regionText,  NoLog, " "],
	      "presel_nVtxdo"   : ["N Vtx down"               , "Events", 1, [-1,-1], regionText,  NoLog, " "],
	      "presel_nVtxNoPU" : ["N Vtx noPU"               , "Events", 1, [-1,-1], regionText,  NoLog, " "],
	      "phosel_LeadingPhotonEt"                : ["Photon Et (GeV)"          , "Events", 5, [-1,-1], regionText,  NoLog, " "],     
	      "phosel_SecondLeadingPhotonEt"          : ["Photon Phi (GeV)"         , "Events", 1, [-1,-1], regionText,  NoLog, " "],    
	      "phosel_LeadingPhotonEta"               : ["Photon Eta (GeV)"         , "Events/0.1", 1, [-1,-1], regionText,  NoLog, " "],   
	      "phosel_LeadingPhotonSCEta"             : ["Photon SCEta (GeV)"       , "Events/0.1", 1, [-1,-1], regionText,  NoLog, " "], 
	      "phosel_dRLeadingPhotonLepton"          : ["dR(LeadingPhoton,Lepton)" , "Events/0.025", 2, [-1,-1], regionText,  NoLog, " "],
	      "phosel_dRLeadingPromptPhotonLepton"    : ["dR(LeadingPhoton,Lepton)" , "Events/0.025", 2, [-1,-1], regionText,  NoLog, "Prompt Photon"],
	      "phosel_dRLeadingNonPromptPhotonLepton" : ["dR(LeadingPhoton,Lepton)" , "Events/0.025", 2, [-1,-1], regionText,  NoLog, "NonPrompt Photon"],
	      "phosel_dRLeadingPhotonJet"             : ["dR(LeadingPhoton,Jet)"    , "Events/0.025", 2, [-1,-1], regionText,  NoLog, " "],  
	      "phosel_dRLeadingPromptPhotonJet"       : ["dR(LeadingPhoton,Jet)"    , "Events/0.025", 2, [-1,-1], regionText,  NoLog, "Prompt Photon"],
	      "phosel_dRLeadingNonPromptPhotonJet"    : ["dR(LeadingPhoton,Jet)"    , "Events/0.025", 2, [-1,-1], regionText,  NoLog, "NonPrompt Photon"],
	      "phosel_dRLeadingGenuinePhotonLepton"   : ["dR(LeadingPhoton,Jet)"    , "Events/0.025", 2, [-1,-1], regionText,  NoLog, "Genuine"],
	      "phosel_dRLeadingMisIDEleLepton"        : ["dR(LeadingPhoton,Jet)"    , "Events/0.025", 2, [-1,-1], regionText,  NoLog, "MisIDEle"],
	      "phosel_dRLeadingHadPhoLepton"          : ["dR(LeadingPhoton,Jet)"    , "Events/0.025", 2, [-1,-1], regionText,  NoLog, "Hadronic Photon"],
	      "phosel_dRLeadingHadFakeLepton"         : ["dR(LeadingPhoton,Jet)"    , "Events/0.025", 2, [-1,-1], regionText,  NoLog, "Hadronic Fake"],
	      "phosel_WtransMass"              : ["W transverse mass GeV "        , "Events/5", 1, [-1,-1], regionText,  NoLog, " "],
	      "phosel_Nphotons"                : ["Number of Photons "            , "Events", 1, [-1,-1], regionText,  YesLog, " "],
	      "phosel_HT"                      : ["H_{T} (GeV)"                ,"Events/9",  1, [-1,-1], regionText,  NoLog, " "],
	      "phosel_MET"                     : ["MET (GeV)  "                , "Events/2", 5, [-1,-1], regionText,  NoLog, " "],
	      "phosel_M3"                      : ["M_{3} (GeV)"                , "Events/2", 5, [-1,-1], regionText,  NoLog, " "],   
	      "phosel_M3_GenuinePho"           : ["M_{3} (GeV)"                , "Events/2", 5, [-1,-1], regionText,  NoLog, "Genuine Photon"],   
	      "phosel_M3_MisIDEle"             : ["M_{3} (GeV)"                , "Events/2", 5, [-1,-1], regionText,  NoLog, "MisIDEle"],
	      "phosel_M3_HadronicPho"          : ["M_{3} (GeV)"                , "Events/2", 5, [-1,-1], regionText,  NoLog, "Hadronic Photon"],
	      "phosel_M3_HadronicFake"         : ["M_{3} (GeV)"                , "Events/2", 5, [-1,-1], regionText,  NoLog, "Hadronic Fake"],
	      "phosel_muEta"                   : ["Muon #eta"                  , "Events/0.05", 5, [-1,-1], regionText,  NoLog, " "],
	      "phosel_muPt"    		       : ["Muon p_{T} (GeV) "          , "Events", 5, [-1,-1], regionText,  NoLog, " "],
	      "phosel_elePt"                   : ["Electron p_{T} (GeV)", "Events", 5, [-1,-1], regionText,  NoLog, " "],
	      "phosel_eleSCEta"                : ["Electron SC#eta"       , "Events/0.05", 5, [-1,-1], regionText,  NoLog, " "],
	      "phosel_Njet"                    : ["N Jets"                     , "Events", 1, [-1,-1], regionText,  NoLog, " "],
	      "phosel_Nbjet"                   : ["N B-Jets"                   , "Events", 1, [-1,-1], regionText,  NoLog, " "],
	      "phosel_HoverE"                  : ["H over E"                   , "Events/0.0004", 1, [-1,-1], regionText, YesLog, " "],
	      "phosel_SIEIE"                   : ["Sigma Ieta Ieta"            , "Events/0.0003", 1, [-1,-1], regionText, YesLog, " "],
	      "phosel_ChIso"                   : ["Charged Hadron Iso (GeV)"   , "Events/0.005", 1, [-1,-1], regionText, YesLog, " "],
	      "phosel_NeuIso"                  : ["Neutral Hadron Iso (GeV)"   , "Events/0.05", 1, [-1,-1], regionText, YesLog, " "],
	      "phosel_nVtx"     : ["N Vtx nominal"               , "Events", 1, [-1,-1], regionText,  NoLog, " "],
	      "phosel_nVtxup"   : ["N Vtx up"               , "Events", 1, [-1,-1], regionText,  NoLog, " "],
	      "phosel_nVtxdo"   : ["N Vtx down"               , "Events", 1, [-1,-1], regionText,  NoLog, " "],
	      "phosel_nVtxNoPU" : ["N Vtx noPU"               , "Events", 1, [-1,-1], regionText,  NoLog, " "],
	      "phosel_PhoIso"                  : ["Photon Iso (GeV)"           , "Events/0.1", 1, [-1,-1], regionText, YesLog, " "],
	      "phosel_noCut_HoverE"            : ["H over E"                   , "Events/0.002", 1, [-1,-1], regionText, YesLog, " "],
	      "phosel_noCut_SIEIE"             : ["Sigma Ieta Ieta"            , "Events/0.0007", 1, [-1,-1], regionText, YesLog, " "],
	      "phosel_noCut_SIEIE_GenuinePho"  :["Sigma Ieta Ieta"            , "Events/0.0007", 1, [-1,-1], regionText, YesLog, "Genuine Photon"],
	      "phosel_noCut_SIEIE_MisIDEle"  :["Sigma Ieta Ieta"            , "Events/0.0007", 1, [-1,-1], regionText, YesLog,"MisIDEle"],
	      "phosel_noCut_SIEIE_HadPho"    :["Sigma Ieta Ieta"            , "Events/0.0007", 1, [-1,-1], regionText, YesLog, "Hadronic Photon"],
	      "phosel_noCut_SIEIE_HadFake"    :["Sigma Ieta Ieta"            , "Events/0.0007", 1, [-1,-1], regionText, YesLog, "Hadronic Fake"],
	      "phosel_noCut_ChIso"             : ["Charged Hadron Iso (GeV)"   , "Events/0.25", 1, [-1,-1], regionText, NoLog, " "],
	      "phosel_noCut_ChIso_GenuinePhoton": ["Charged Hadron Iso (GeV)"   , "Events/0.25", 1, [-1,-1], regionText, YesLog, "Genuine Photon"],
	      "phosel_noCut_ChIso_MisIDEle"    : ["Charged Hadron Iso (GeV)"   , "Events/0.25", 1, [-1,-1], regionText, YesLog, "MisIDEle"],
	      "phosel_noCut_ChIso_HadronicPhoton": ["Charged Hadron Iso (GeV)"   , "Events/0.25", 1, [-1,-1], regionText, YesLog, "Hadronic Photon"],
	      "phosel_noCut_ChIso_HadronicFake": ["Charged Hadron Iso (GeV)"   , "Events/0.25", 1, [-1,-1], regionText, YesLog, "Hadronic Fake"],
	      "phosel_noCut_ChIso_PromptPhoton": ["Charged Hadron Iso (GeV)"   , "Events/0.25", 1, [-1,-1], regionText, YesLog, "Prompt Photon"],
	      "phosel_noCut_ChIso_NonPromptPhoton": ["Charged Hadron Iso (GeV)"   , "Events/0.25", 1, [-1,-1], regionText, YesLog, "NonPrompt Photon"],
	      "phosel_noCut_NeuIso"            : ["Neutral Hadron Iso (GeV)"   , "Events/0.5", 1, [-1,-1], regionText, YesLog, " "],
	      "phosel_noCut_PhoIso"            : ["Photon Iso (GeV)"           , "Events/0.5", 1, [-1,-1], regionText, YesLog, " "],
	      "phosel_AntiSIEIE_ChIso"         : ["Charged Hadron Iso (GeV)"   , "Events/0.5", 1, [0,15], regionText,  NoLog, " "],
	      "phosel_AntiSIEIE_ChIso_GenuinePho": ["Charged Hadron Iso (GeV)"   , "Events/0.5", 1, [0,15], regionText,  NoLog, "Genuine Photon"],
	      "phosel_AntiSIEIE_ChIso_MisIDEle": ["Charged Hadron Iso (GeV)"   , "Events/0.5", 1, [0,15], regionText,  NoLog, "MisIDEle"],    
	      "phosel_AntiSIEIE_ChIso_HadPho": ["Charged Hadron Iso (GeV)"   , "Events/0.5", 1, [0,15], regionText,  NoLog,"Hadronic Photon"],       
	      "phosel_AntiSIEIE_ChIso_HadFake": ["Charged Hadron Iso HadFake (GeV)"   , "Events/0.5", 1, [0,15], regionText,  NoLog, "Hadronic Fake"], 
	      "phosel_noCut_SIEIE_endcap"      : ["Sigma Ieta Ieta"            , "Events/0.0006", 1, [-1,1], regionText,  NoLog, "Endcap"],
	      "phosel_noCut_SIEIE_barrel"      : ["Sigma Ieta Ieta"            , "Events/0.0002", 1, [-1,-1], regionText,  NoLog, "Barrel"],
	      "phosel_mcMomPIDGenuinePho" :["ParentPID of GenuinePho", "Events", 1, [-25,25], regionText,  YesLog, "GenuinePhoton"],
	      "phosel_mcMomPIDMisIDEle"  :["ParentPID of MisIDEle", "Events", 1, [-1,-1], regionText,  YesLog, "MisIDEle"],
	      "phosel_mcMomPIDHadPho":    ["ParentPID of HadronicPho", "Events", 1, [-1000,600], regionText, YesLog, "Hadronic Photon"],
	      "phosel_mcMomPIDHadFake":    ["ParentPID of HadronicFake", "Events", 1, [-1,-1], regionText,  YesLog, "Hadronic Fake"],
	      "phosel_RandomCone"     :    ["RandomConeIsolation GeV", "Events", 1, [-1,-1], regionText,  NoLog, " "],
	      "phosel_MassEGamma"     :    ["m_{e,#gamma} GeV", "Events", 1, [-1,-1], regionText,  NoLog, " "],
	      }


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

sampleList[-2] = "QCD_DD"
stackList = sampleList[:-1]

# stackList.remove("QCDMu")
stackList.reverse()

if finalState=="Mu":
	_channelText = "#mu+jets"
elif finalState=="Ele":
        _channelText = "e+jets"

CMS_lumi.channelText = _channelText
CMS_lumi.writeChannelText = True
CMS_lumi.writeExtraText = True


H = 600;
W = 800;

canvas = TCanvas('c1','c1',W,H)

# references for T, B, L, R                                                                                                             
T = 0.08*H
B = 0.12*H
L = 0.12*W
R = 0.1*W
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
# references for T, B, L, R                                                                                                             
T = 0.08*H
B = 0.12*H
L = 0.12*W
R = 0.1*W
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

canvasRatio.cd()
pad1.Draw()
pad2.Draw()


canvas.cd()

legList = {'TTGamma': [kAzure+3, 't#bar{t}+#gamma'],
          'TTJets': [kRed+1, 't#bar{t}+jets'],
          'TTV': [kRed+1, 't#bar{t}+V'],
          'Vgamma': [kGray, 'W/Z+#gamma'],
          'SingleTop': [kMagenta, 'Single t'],
          'WJets': [kGreen -3, 'W+jets'],
          'ZJets': [kGreen -3, 'Z+jets'],
	  'Diboson':[kCyan-7, 'WW/WZ/ZZ'],
          'TGJets'   :[kGray, 't+#gamma'],
          'QCD_DD': [kYellow, 'Multijet'],
          }

mcList = {'TTGamma': [kOrange],
          'TTbar': [kRed+1],
          'TTV': [kRed-7],
          'SingleTop': [kOrange-3],
          'WGamma': [kBlue-4],
          'ZGamma': [kBlue-2],
          'WJets': [kCyan-3],
          'ZJets': [kCyan-5],
	  'Diboson':[kCyan-7],
          'TGJets': [kGray],
          'QCD_DD': [kGreen+3],
          }


legendHeightPer = 0.04

legend = TLegend(0.71, 1-T/H-0.01 - legendHeightPer*(len(legList)+1), 1-R/W-0.01, 1-(T/H)-0.01)

legendR = TLegend(0.71, 0.99 - (T/H)/(1.-padRatio+padOverlap) - legendHeightPer/(1.-padRatio+padOverlap)*(len(legList)+1), 0.99-(R/W), 0.99-(T/H)/(1.-padRatio+padOverlap))
legendR.SetBorderSize(0)
legendR.SetFillColor(0)



legend.SetBorderSize(0)
legend.SetFillColor(0)

histName = "jet1Pt"#preselhistograms.keys()[0]
legList = stackList[:]
legList.reverse()
#legList.remove('TGJets')
#print histName
print legList
for sample in legList:
    # print sample, _file
    # print "%s/%s_%s"%(sample,histName,sample)
    hist = _file.Get("%s/presel_%s_%s"%(sample,histName,sample))
#    hist.Draw()
    hist.SetFillColor(mcList[sample][0])
    hist.SetLineColor(mcList[sample][0])
    legend.AddEntry(hist,sample,'f')
    legendR.AddEntry(hist,sample,'f')
if finalState=='Ele':
    dataHist = _file.Get("DataEle/presel_%s_DataEle"%(histName))
elif finalState=='Mu':
    dataHist = _file.Get("DataMu/presel_%s_DataMu"%(histName))
legend.AddEntry(dataHist, "Data", 'pe')
legendR.AddEntry(dataHist, "Data", 'pe')




TGaxis.SetMaxDigits(3)
#stackList.remove('TGJets')
def drawHist(histName,plotInfo, plotDirectory, _file):
    print "start drawing"
    
    canvas.cd()
    canvas.ResetDrawn()
    stack = THStack(histName,histName)
    for sample in stackList:
#        print sample, histName
        hist = _file.Get("%s/%s_%s"%(sample,histName,sample))
	if type(hist)==type(TObject()): continue
	hist = hist.Clone(sample)	
        hist.SetFillColor(mcList[sample][0])
        hist.SetLineColor(mcList[sample][0])

        hist.Rebin(plotInfo[2])
        stack.Add(hist)
    if finalState=='Ele':
   	dataHist = _file.Get("DataEle/%s_DataEle"%(histName))
#	dataHist.Draw()
    elif finalState=='Mu':
	dataHist = _file.Get("DataMu/%s_DataMu"%(histName))
    noData = False
    if type(dataHist)==type(TObject()): noData = True
    if not noData:
	    dataHist.Rebin(plotInfo[2])
    
    #sys.exit()
    _text = TPaveText(0.47,.75,0.55,0.85,"NDC")
    _text.AddText(plotInfo[6])
    _text.SetTextColor(kBlack)
    _text.SetFillColor(0)
    _text.SetTextSize(0.05)
    _text.SetTextFont(42)
    #histograms list has flag whether it's log or not
    canvas.SetLogy(plotInfo[5])
    #canvas.SetLogy()
    if not noData:
        stack.SetMaximum(1.35*max(dataHist.GetMaximum(),stack.GetMaximum()))
    else:
	stack.SetMaximum(1.35*stack.GetMaximum())
    stack.Draw('hist')
    _text.Draw("same")
    #histograms list has x-axis title
    stack.GetHistogram().GetXaxis().SetTitle(plotInfo[0])
    stack.GetHistogram().GetYaxis().SetTitle(plotInfo[1])
    if not -1 in plotInfo[3]:
        stack.GetHistogram().GetXaxis().SetRangeUser(plotInfo[3][0],plotInfo[3][1])
	if not noData:
            dataHist.GetXaxis().SetRangeUser(plotInfo[3][0],plotInfo[3][1])

    if not noData:
	dataHist.Draw("e,X0,same")
    legend.Draw("same")
  
    
    #_text.Draw()
    CMS_lumi.channelText = _channelText+plotInfo[4]
    CMS_lumi.CMS_lumi(canvas, 4, 11)

    canvas.Print("%s/%s.pdf"%(plotDirectory,histName))
    canvas.Print("%s/%s.png"%(plotDirectory,histName))

    if not noData:
        ratio = dataHist.Clone("temp")
	ratio.Divide(stack.GetStack().Last())
    
    
	pad1.Clear()
	pad2.Clear()

	canvasRatio.cd()
	canvasRatio.ResetDrawn()

	pad1.Clear()
	pad2.Clear()


	pad1.cd()

	pad1.SetLogy(plotInfo[5])
	stack.Draw('HIST')
	#    pad1.Update()
	y2 = pad1.GetY2()
	
	stack.SetMinimum(1)
	#    pad1.Update()
	stack.GetXaxis().SetTitle('')
	stack.GetYaxis().SetTitle(dataHist.GetYaxis().GetTitle())
	
	stack.SetTitle('')
	stack.GetXaxis().SetLabelSize(0)
	stack.GetYaxis().SetLabelSize(gStyle.GetLabelSize()/(1.-padRatio+padOverlap))
	stack.GetYaxis().SetTitleSize(gStyle.GetTitleSize()/(1.-padRatio+padOverlap))
	stack.GetYaxis().SetTitleOffset(gStyle.GetTitleYOffset()*(1.-padRatio+padOverlap))
	stack.GetYaxis().SetTitle(plotInfo[1])
	dataHist.Draw('E,X0,SAME')
	legendR.Draw()
	_text = TPaveText(0.47,.75,0.55,0.85,"NDC")
	_text.AddText(plotInfo[6])
	_text.SetTextColor(kBlack)
	_text.SetFillColor(0)
	_text.SetTextSize(0.05)
	_text.SetTextFont(42)
	_text.Draw("same")
	ratio.SetTitle('')
	
	ratio.GetXaxis().SetLabelSize(gStyle.GetLabelSize()/(padRatio+padOverlap))
	ratio.GetYaxis().SetLabelSize(gStyle.GetLabelSize()/(padRatio+padOverlap))
	ratio.GetXaxis().SetTitleSize(gStyle.GetTitleSize()/(padRatio+padOverlap))
	ratio.GetYaxis().SetTitleSize(gStyle.GetTitleSize()/(padRatio+padOverlap))
	ratio.GetYaxis().SetTitleOffset(gStyle.GetTitleYOffset()*(padRatio+padOverlap-padGap))
	ratio.GetYaxis().SetRangeUser(0.5,1.5)
	ratio.GetYaxis().SetNdivisions(504)
	ratio.GetXaxis().SetTitle(plotInfo[0])
	ratio.GetYaxis().SetTitle("Data/MC")
	
	pad2.cd()
	ratio.SetMarkerStyle(dataHist.GetMarkerStyle())
	ratio.SetMarkerSize(dataHist.GetMarkerSize())
	ratio.SetLineColor(dataHist.GetLineColor())
	ratio.SetLineWidth(dataHist.GetLineWidth())
	
	oneLine = TF1("oneline","1",-9e9,9e9)
	oneLine.SetLineColor(kBlack)
	oneLine.SetLineWidth(1)
	oneLine.SetLineStyle(2)
	
	ratio.Draw('e,x0')
	oneLine.Draw("same")

	#    pad2.Update()
	CMS_lumi.CMS_lumi(pad1, 4, 11)
	canvasRatio.Update()
	canvasRatio.RedrawAxis()
	canvasRatio.SaveAs("%s/%s_ratio.pdf"%(plotDirectory,histName))
	canvasRatio.SaveAs("%s/%s_ratio.png"%(plotDirectory,histName))
	canvasRatio.SetLogy(0)

histogramList = histograms.keys()
histogramList.sort()

if not plotList is None:
	histogramList = plotList
	allHistsDefined = True
	print plotList
	print histogramList
	for hist in histogramList:
		print hist
		if not hist in histograms:
			print "Histogram %s plotting information not defined" % hist
			allHistsDefined = False
	if not allHistsDefined:
		sys.exit()

for histName in histogramList:
	drawHist(histName,histograms[histName],plotDirectory,_file)

# for histName in phoselhistograms:
#         drawHist("phosel_%s"%histName,phoselhistograms[histName],plotDirectory,_file)

