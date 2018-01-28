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
parser.add_option("--LooseCR2e0","--looseCR2e0", dest="isLooseCR2e0Selection", default=False,action="store_true",
		  help="Use 2j exactly 0t control region selection" )
parser.add_option("--LooseCR3e0","--looseCR3e0", dest="isLooseCR3e0Selection", default=False,action="store_true",
		  help="Use 3j exactly 0t control region selection" )
parser.add_option("--LooseCR2g0","--looseCR2g0", dest="isLooseCR2g0Selection", default=False,action="store_true",
		  help="Use 2j at least 0t control region selection" )
parser.add_option("--LooseCR2g1","--looseCR2g1", dest="isLooseCR2g1Selection", default=False,action="store_true",
		  help="Use 2j at least 1t control region selection" )
parser.add_option("--plot", dest="plotList",action="append",
		  help="Add plots" )
parser.add_option("--file",dest="inputFile",default=None,
		  help="Specify specific input file")

(options, args) = parser.parse_args()

isTightSelection = options.isTightSelection
isLooseCR2e0Selection = options.isLooseCR2e0Selection
isLooseCR2g0Selection = options.isLooseCR2g0Selection
isLooseCR2g1Selection = options.isLooseCR2g1Selection
isLooseCR3e0Selection = options.isLooseCR3e0Selection
plotList = options.plotList

inputFile = options.inputFile




finalState = options.channel
print "Running on the %s channel"%(finalState)
if finalState=='Mu':
	_fileDir = "histograms/mu/hists"
#	_file  = TFile("histograms/mu/hists.root")
	plotDirectory = "plots_mu/"
	regionText = ", N_{j}#geq3, N_{b}#geq1"
	channel = 'mu'
if finalState=="Ele":
	_fileDir = "histograms/ele/hists"
#	_file  = TFile("histograms/ele/hists.root")
        plotDirectory = "plots_ele/"
        regionText = ", N_{j}#geq3, N_{b}#geq1"
	channel = 'ele'



if isTightSelection:
	plotDirectory = "tightplots_%s/"%channel
	_fileDir = "histograms/%s/hists_tight/"%channel
#	_file  = TFile("histograms/%s/hists_tight.root"%channel)
	regionText = ", N_{j}#geq4, N_{b}#geq2"
if isLooseCR2g0Selection:
	plotDirectory = "looseplots_%s_CR2g0/"%channel
	_fileDir = "histograms/%s/hists_looseCR2g0/"%channel
#	_file  = TFile("histograms/%s/hists_looseCR2g0.root"%channel)
	regionText = ", N_{j}=2, N_{b}#geq0"
if isLooseCR2g1Selection:
	plotDirectory = "looseplots_%s_CR2g1/"%channel
	_fileDir = "histograms/%s/hists_looseCR2g1/"%channel
#	_file  = TFile("histograms/%s/hists_looseCR2g1.root"%channel)
	regionText = ", N_{j}=2, N_{b}#geq1"
if isLooseCR2e0Selection:
	plotDirectory = "looseplots_%s_CR2e0/"%channel
	_fileDir = "histograms/%s/hists_looseCR2e0"%channel
#	_file  = TFile("histograms/%s/hists_looseCR2e0.root"%channel)
	regionText = ", N_{j}#geq2, N_{b}=0"
if isLooseCR3e0Selection:
	plotDirectory = "looseCRplots_%s_CR3e0/"%channel
	_fileDir = "histograms/%s/hists_looseCR3e0"%channel
#	_file  = TFile("histograms/%s/hists_looseCR3e0.root"%channel)
	regionText = ", N_{j}#geq3, N_{b}=0"


if not inputFile is None:
	_fileDir = "histograms/%s/%s"%(channel,inputFile)
#	_file  = TFile("histograms/%s/%s"%(channel,inputFile))
	if not _file.IsOpen():
		print "Unable to open file"
		sys.exit()

if not os.path.exists(plotDirectory):
	os.mkdir(plotDirectory)


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
	      "phosel_M3_GenuinePhoton"           : ["M_{3} (GeV)"                , "Events/2", 5, [-1,-1], regionText,  NoLog, "Genuine Photon"],   
	      "phosel_M3_MisIDEle"             : ["M_{3} (GeV)"                , "Events/2", 5, [-1,-1], regionText,  NoLog, "MisIDEle"],
	      "phosel_M3_HadronicPhoton"          : ["M_{3} (GeV)"                , "Events/2", 5, [-1,-1], regionText,  NoLog, "Hadronic Photon"],
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


if plotList is None:
	plotList = histograms.keys()
	plotList.sort()
if not plotList is None:
	allHistsDefined = True
	for hist in plotList:
		if not hist in histograms:
			print "Histogram %s plotting information not defined" % hist
			allHistsDefined = False
	if not allHistsDefined:
		sys.exit()




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

#sampleList[-2] = "QCD_DD"
sampleList[-2] = "QCDMu"
stackList = sampleList[:-1]

#stackList.remove("QCD_DD")
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

# legList = {'TTGamma': [kAzure+3, 't#bar{t}+#gamma'],
#           'TTJets': [kRed+1, 't#bar{t}+jets'],
#           'TTV': [kRed+1, 't#bar{t}+V'],
#           'Vgamma': [kGray, 'W/Z+#gamma'],
#           'SingleTop': [kMagenta, 'Single t'],
#           'WJets': [kGreen -3, 'W+jets'],
#           'ZJets': [kGreen -3, 'Z+jets'],
# 	  'Diboson':[kCyan-7, 'WW/WZ/ZZ'],
#           'TGJets'   :[kGray, 't+#gamma'],
#           'QCD_DD': [kYellow, 'Multijet'],
#           }

# mcList = {'TTGamma': [kOrange],
#           'TTbar': [kRed+1],
#           'TTV': [kRed-7],
#           'SingleTop': [kOrange-3],
#           'WGamma': [kBlue-4],
#           'ZGamma': [kBlue-2],
#           'WJets': [kCyan-3],
#           'ZJets': [kCyan-5],
# 	  'Diboson':[kCyan-7],
#           'TGJets': [kGray],
#           'QCD_DD': [kGreen+3],
#           'QCDMu': [kGreen+3],
#           'GJets': [kGreen+1],
#           }


legendHeightPer = 0.04
legList = stackList[:]
legList.reverse()

legend = TLegend(0.71, 1-T/H-0.01 - legendHeightPer*(len(legList)+1), 1-R/W-0.01, 1-(T/H)-0.01)

legendR = TLegend(0.71, 0.99 - (T/H)/(1.-padRatio+padOverlap) - legendHeightPer/(1.-padRatio+padOverlap)*(len(legList)+1), 0.99-(R/W), 0.99-(T/H)/(1.-padRatio+padOverlap))
legendR.SetBorderSize(0)
legendR.SetFillColor(0)



legend.SetBorderSize(0)
legend.SetFillColor(0)

_file = {}
for sample in stackList:
	_file[sample] = TFile("%s/%s.root"%(_fileDir,sample),"read")

if finalState=='Ele':
	sample = "DataEle"
	_file[sample] = TFile("%s/%s.root"%(_fileDir,sample),"read")
if finalState=='Mu':
	sample = "DataMu"
	_file[sample] = TFile("%s/%s.root"%(_fileDir,sample),"read")

histName = plotList[0]
#print legList
for sample in legList:
    print sample, _file[sample]
    # print "%s/%s_%s"%(sample,histName,sample)
    hist = _file[sample].Get("%s_%s"%(histName,sample))
    print hist, "%s_%s"%(histName,sample)
    hist.SetFillColor(samples[sample][1])
    hist.SetLineColor(samples[sample][1])
    legend.AddEntry(hist,samples[sample][2],'f')
    legendR.AddEntry(hist,samples[sample][2],'f')
if finalState=='Ele':
    dataHist = _file["DataEle"].Get("presel_%s_DataEle"%(histName))
elif finalState=='Mu':
    dataHist = _file["DataMu"].Get("presel_%s_DataMu"%(histName))
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
        hist = _file[sample].Get("%s_%s"%(histName,sample))
#        hist = _file[sample].Get("%s/%s_%s"%(sample,histName,sample))
	if type(hist)==type(TObject()): continue
	hist = hist.Clone(sample)	
        hist.SetFillColor(samples[sample][1])
        hist.SetLineColor(samples[sample][1])

        hist.Rebin(plotInfo[2])

        stack.Add(hist)
    if finalState=='Ele':
   	dataHist = _file["DataEle"].Get("%s_DataEle"%(histName))
#	dataHist.Draw()
    elif finalState=='Mu':
	dataHist = _file["DataMu"].Get("%s_DataMu"%(histName))
    noData = False
    if type(dataHist)==type(TObject()): noData = True
    if not noData:
	    dataHist.Rebin(plotInfo[2])

    oneLine = TF1("oneline","1",-9e9,9e9)
    oneLine.SetLineColor(kBlack)
    oneLine.SetLineWidth(1)
    oneLine.SetLineStyle(2)
	
    _text = TPaveText(0.47,.75,0.55,0.85,"NDC")
    _text.SetTextColor(kBlack)
    _text.SetFillColor(0)
    _text.SetTextSize(0.05)
    _text.SetTextFont(42)
    _text.AddText(plotInfo[6])

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

	# maxRatio = ratio.GetMaximum()
	# if maxRatio > 1.8:
	# 	ratio.GetYaxis().SetRangeUser(0,round(0.5+maxRatio))
	# elif maxRatio < 1:
	# 	ratio.GetYaxis().SetRangeUser(0,1.2)
	# else:
	# 	ratio.GetYaxis().SetRangeUser(2-1.1*maxRatio,1.1*maxRatio)

	ratio.GetYaxis().SetNdivisions(504)
	ratio.GetXaxis().SetTitle(plotInfo[0])
	ratio.GetYaxis().SetTitle("Data/MC")
	CMS_lumi.CMS_lumi(pad1, 4, 11)

	pad2.cd()

	ratio.SetMarkerStyle(dataHist.GetMarkerStyle())
	ratio.SetMarkerSize(dataHist.GetMarkerSize())
	ratio.SetLineColor(dataHist.GetLineColor())
	ratio.SetLineWidth(dataHist.GetLineWidth())
	ratio.Draw('e,x0')

	oneLine.Draw("same")
	#    pad2.Update()
	canvasRatio.Update()
	canvasRatio.RedrawAxis()
	canvasRatio.SaveAs("%s/%s_ratio.pdf"%(plotDirectory,histName))
	canvasRatio.SaveAs("%s/%s_ratio.png"%(plotDirectory,histName))
	canvasRatio.SetLogy(0)


print pad1, pad2

for histName in plotList:
	drawHist(histName,histograms[histName],plotDirectory,_file)

# for histName in phoselhistograms:
#         drawHist("phosel_%s"%histName,phoselhistograms[histName],plotDirectory,_file)

