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
parser.add_option("--LooseCR2e0","--looseCR2e0", dest="isLooseCR2e0Selection",default=False,action="store_true",
		  help="Use 2j exactly 0t control region selection" )
parser.add_option("--LooseCR2g0","--looseCR2g0", dest="isLooseCR2g0Selection",default=False,action="store_true",
		  help="Use 2j at least 0t control region selection" )
parser.add_option("--LooseCR2g1","--looseCR2g1", dest="isLooseCR2g1Selection",default=False,action="store_true",
                  help="Use 2j at least 1t control region selection")
parser.add_option("--LooseCR3e0","--looseCR3e0", dest="isLooseCR3e0Selection",default=False,action="store_true",
		  help="Use 3j exactly 0t control region selection" )
parser.add_option("--addPlots","--addOnly", dest="onlyAddPlots", default=False,action="store_true",
                     help="Use only if you want to add a couple of plots to the file, does not remove other plots" )
parser.add_option("--output", dest="outputFileName", default="hists",
                     help="Give the name of the root file for histograms to be saved in (default is hists.root)" )
parser.add_option("--plot", dest="plotList",action="append",
                     help="Add plots" )
parser.add_option("--allPlots","--AllPlots", dest="makeAllPlots",action="store_true",default=False,
                     help="Make full list of plots in histogramDict" )
parser.add_option("--morePlots","--MorePlots","--makeMorePlots", dest="makeMorePlots",action="store_true",default=False,
                     help="Make larger list of plots in histogramDict (mostly object kinematics)" )
parser.add_option("--MegammaPlots","--megammaPlots", dest="makeEGammaPlots",action="store_true",default=False,
                     help="Make only plots for e-gamma mass fits" )
parser.add_option("--quiet", "-q", dest="quiet",default=False,action="store_true",
                     help="Quiet outputs" )

(options, args) = parser.parse_args()

level =options.systematic

gROOT.SetBatch(True)

finalState = options.channel
sample = options.sample
isTightSelection = options.isTightSelection
isLooseCR2e0Selection = options.isLooseCR2e0Selection
isLooseCR2g0Selection = options.isLooseCR2g0Selection
isLooseCR2g1Selection = options.isLooseCR2g1Selection
isLooseCR3e0Selection = options.isLooseCR3e0Selection
onlyAddPlots = options.onlyAddPlots
outputFileName = options.outputFileName

makeAllPlots = options.makeAllPlots
makeMorePlots = options.makeMorePlots
makeEGammaPlots = options.makeEGammaPlots

runQuiet = options.quiet

nJets = 3
nBJets = 1

isQCD = False

Q2 = 1.
Pdf = 1.
Pileup ="PUweight"
MuEff = "muEffWeight"
EleEff= "eleEffWeight"
evtWeight ="evtWeight"
btagWeightCategory = ["1","(1-btagWeight[0])","(btagWeight[2])","(btagWeight[1])"]


#atleast 0, atleast 1, atleast 2, exactly 1, btagWeight[0] = exactly 0


if finalState=="Mu":
    sampleList[-1] = "DataMu"
    sampleList[-2] = "QCDMu"

    if sample=="Data":
        sample = "DataMu"
    if sample=="QCD":
        sample = "QCDMu"
    analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/muons/V08_00_26_07/"
    outputhistName = "histograms/mu/%s"%outputFileName
    if 'JECTotal' in sys.argv:
	if  level=="up":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_muons/V08_00_26_07/JECTotal_up_"
            outputhistName = "histograms/mu/histsJECTotal_up"
    	if level=="down":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_muons/V08_00_26_07/JECTotal_down_"
            outputhistName = "histograms/mu/histsJECTotal_down"
    if 'JER' in sys.argv: 
        if  level=="up":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_muons/V08_00_26_07/JER_up_"
            outputhistName = "histograms/mu/histsJER_up"
        if level=="down":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_muons/V08_00_26_07/JER_down_"
            outputhistName = "histograms/mu/histsJER_down"

    if 'phosmear' in sys.argv: 
        if  level=="up":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_muons/V08_00_26_07/phosmear_up_"
            outputhistName = "histograms/mu/histsphosmear_up"
        if level=="down":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_muons/V08_00_26_07/phosmear_down_"
            outputhistName = "histograms/mu/histsphosmear_down"

    if 'phoscale' in sys.argv:
        if  level=="up":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_muons/V08_00_26_07/phoscale_up_"
            outputhistName = "histograms/mu/histsphoscale_up"
        if level=="down":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_muons/V08_00_26_07/phoscale_down_"
            outputhistName = "histograms/mu/histsphoscale_down"


    if 'elesmear' in sys.argv:
        if  level=="up":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_muons/V08_00_26_07/elesmear_up_"
            outputhistName = "histograms/mu/histselesmear_up"
        if level=="down":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_muons/V08_00_26_07/elesmear_down_"
            outputhistName = "histograms/mu/histselesmear_down"

    if 'elescale' in sys.argv:
        if  level=="up":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_muons/V08_00_26_07/elescale_up_"
            outputhistName = "histograms/mu/histselescale_up"
        if level=="down":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_muons/V08_00_26_07/elescale_down_"
            outputhistName = "histograms/mu/histselescale_down"



    extraCuts            = "(passPresel_Mu && nJet>=3 && nBJet>=1)*"
    extraPhotonCuts      = "(passPresel_Mu && nJet>=3 && nBJet>=1 && %s)*"

    extraCutsTight       = "(passPresel_Mu && nJet>=4 && nBJet>=2)*"
    extraPhotonCutsTight = "(passPresel_Mu && nJet>=4 && nBJet>=2 && %s)*"

    extraCutsLooseCR2g0       = "(passPresel_Mu && nJet==2)*"
    extraPhotonCutsLooseCR2g0 = "(passPresel_Mu && nJet==2 && %s)*"

    extraCutsLooseCR2g1       = "(passPresel_Mu && nJet==2 && nBJet>=1)*"
    extraPhotonCutsLooseCR2g1 = "(passPresel_Mu && nJet==2 && nBJet>=1 && %s)*"

    extraCutsLooseCR2e0       = "(passPresel_Mu && nJet>=2)*"
    extraPhotonCutsLooseCR2e0 = "(passPresel_Mu && nJet>=2 && %s)*"

    extraCutsLooseCR3e0       = "(passPresel_Mu && nJet>=3)*"
    extraPhotonCutsLooseCR3e0 = "(passPresel_Mu && nJet>=3 && %s)*"

elif finalState=="Ele":
    sampleList[-1] = "DataEle"
    sampleList[-2] = "QCDEle"
    if sample=="Data":
        sample = "DataEle"
    if sample=="QCD":
        sample = "QCDEle"
    analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/electrons/V08_00_26_07/"
    outputhistName = "histograms/ele/%s"%outputFileName
    if 'JECTotal' in sys.argv:
        if level=="up":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_electrons/V08_00_26_07/JECTotal_up_"
            outputhistName = "histograms/ele/histsJECTotal_up"
        if level=="down":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_electrons/V08_00_26_07/JECTotal_down_"
            outputhistName = "histograms/ele/histsJECTotal_down"
    if 'JER' in sys.argv:
        if level=="up":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_electrons/V08_00_26_07/JER_up_"
            outputhistName = "histograms/ele/histsJER_up"
        if level=="down":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_electrons/V08_00_26_07/JER_down_"
            outputhistName = "histograms/ele/histsJER_down"

    if 'phosmear' in sys.argv:
        if level=="up":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_electrons/V08_00_26_07/phosmear_up_"
            outputhistName = "histograms/ele/histsphosmear_up"
        if level=="down":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_electrons/V08_00_26_07/phosmear_down_"
            outputhistName = "histograms/ele/histsphosmear_down"

    if 'phoscale' in sys.argv:
        if level=="up":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_electrons/V08_00_26_07/phoscale_up_"
            outputhistName = "histograms/ele/histsphoscale_up"
        if level=="down":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_electrons/V08_00_26_07/phoscale_down_"
            outputhistName = "histograms/ele/histsphoscale_down"

    if 'elesmear' in sys.argv:
        if level=="up":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_electrons/V08_00_26_07/elesmear_up_"
            outputhistName = "histograms/ele/histselesmear_up"
        if level=="down":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_electrons/V08_00_26_07/elesmear_down_"
            outputhistName = "histograms/ele/histselesmear_down"

    if 'elescale' in sys.argv:
        if level=="up":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_electrons/V08_00_26_07/elescale_up_"
            outputhistName = "histograms/ele/histselescale_up"
        if level=="down":
            analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/systematics_electrons/V08_00_26_07/elescale_down_"
            outputhistName = "histograms/ele/histselescale_down"

    extraCuts            = "(passPresel_Ele && nJet>=3 && nBJet>=1)*"
    extraPhotonCuts      = "(passPresel_Ele && nJet>=3 && nBJet>=1 && %s)*"

    extraCutsTight       = "(passPresel_Ele && nJet>=4 && nBJet>=2)*"
    extraPhotonCutsTight = "(passPresel_Ele && nJet>=4 && nBJet>=2 && %s)*"

    extraCutsLooseCR2g0       = "(passPresel_Ele && nJet==2)*"
    extraPhotonCutsLooseCR2g0 = "(passPresel_Ele && nJet==2 && %s)*"

    extraCutsLooseCR2g1       = "(passPresel_Ele && nJet==2 && nBJet>=1)*"
    extraPhotonCutsLooseCR2g1 = "(passPresel_Ele && nJet==2 && nBJet>=1 && %s)*"

    extraCutsLooseCR2e0       = "(passPresel_Ele && nJet>=2)*"
    extraPhotonCutsLooseCR2e0 = "(passPresel_Ele && nJet>=2 && %s)*"

    extraCutsLooseCR3e0       = "(passPresel_Ele && nJet>=3)*"
    extraPhotonCutsLooseCR3e0 = "(passPresel_Ele && nJet>=3 && %s)*"

elif finalState=="DiMu":
    sampleList[-1] = "DataMu"
    sampleList[-2] = "QCDMu"

    if sample=="Data":
        sample = "DataMu"
    if sample=="QCD":
        sample = "QCDMu"
    analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/dimuons/V08_00_26_07/Dilep_"
    outputhistName = "histograms/mu/dilep%s"%outputFileName

    extraCuts            = "(passPresel_Mu && nJet>=3 && nBJet>=1)*"
    extraPhotonCuts      = "(passPresel_Mu && nJet>=3 && nBJet>=1 && %s)*"

    extraCutsTight       = "(passPresel_Mu && nJet>=4 && nBJet>=2)*"
    extraPhotonCutsTight = "(passPresel_Mu && nJet>=4 && nBJet>=2 && %s)*"

    extraCutsLooseCR2e0       = "(passPresel_Mu && nJet==2)*"
    extraPhotonCutsLooseCR2e0 = "(passPresel_Mu && nJet==2 && %s)*"

    extraCutsLooseCR2g0       = "(passPresel_Mu && nJet>=2)*"
    extraPhotonCutsLooseCR2g0 = "(passPresel_Mu && nJet>=2 && %s)*"

    extraCutsLooseCR3g0       = "(passPresel_Mu && nJet>=3 && nBJet>=0)*"
    extraPhotonCutsLooseCR3g0 = "(passPresel_Mu && nJet>=3 && nBJet>=0 && %s)*"

elif finalState=="DiEle":
    sampleList[-1] = "DataEle"
    sampleList[-2] = "QCDEle"
    if sample=="Data":
        sample = "DataEle"
    if sample=="QCD":
        sample = "QCDEle"
    analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/dielectrons/V08_00_26_07/Dilep_"
    outputhistName = "histograms/ele/dilep%s"%outputFileName

    extraCuts            = "(passPresel_Ele && nJet>=3 && nBJet>=1)*"
    extraPhotonCuts      = "(passPresel_Ele && nJet>=3 && nBJet>=1 && %s)*"

    extraCutsTight       = "(passPresel_Ele && nJet>=4 && nBJet>=2)*"
    extraPhotonCutsTight = "(passPresel_Ele && nJet>=4 && nBJet>=2 && %s)*"

    extraCutsLooseCR2e0       = "(passPresel_Ele && nJet==2)*"
    extraPhotonCutsLooseCR2e0 = "(passPresel_Ele && nJet==2 && %s)*"

    extraCutsLooseCR2g0       = "(passPresel_Ele && nJet>=2)*"
    extraPhotonCutsLooseCR2g0 = "(passPresel_Ele && nJet>=2 && %s)*"

    extraCutsLooseCR3g0       = "(passPresel_Ele && nJet>=3)*"
    extraPhotonCutsLooseCR3g0 = "(passPresel_Ele && nJet>=3 && %s)*"

elif finalState=="QCDMu":
    sampleList[-1] = "DataMu"
    sampleList[-2] = "QCDMu"
    if sample=="Data":
        sample = "DataMu"
    if sample=="QCD":
        sample = "QCDMu"

    isQCD = True

    analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/qcdmuons/V08_00_26_07/QCDcr_"
    outputhistName = "histograms/mu/qcdhistsCR"

    nBJets = 0

    extraCuts            = "(passPresel_Mu && muPFRelIso<0.3 && nJet>=3 && nBJet==0)*"
    extraPhotonCuts      = "(passPresel_Mu && muPFRelIso<0.3 && nJet>=3 && nBJet==0 && %s)*"

    extraCutsTight            = "(passPresel_Mu && muPFRelIso<0.3 && nJet>=4 && nBJet==0)*"
    extraPhotonCutsTight      = "(passPresel_Mu && muPFRelIso<0.3 && nJet>=4 && nBJet==0 && %s)*"

    extraCutsLooseCR2e0       = "(passPresel_Mu && muPFRelIso<0.3 && nJet>=2 && nBJet==0)*"
    extraPhotonCutsLooseCR2e0 = "(passPresel_Mu && muPFRelIso<0.3 && nJet>=2 && nBJet==0 && %s)*"

    extraCutsLooseCR2g0       = "(passPresel_Mu && muPFRelIso<0.3 && nJet>=2 && nBJet==0)*"
    extraPhotonCutsLooseCR2g0 = "(passPresel_Mu && muPFRelIso<0.3 && nJet>=2 && nBJet==0 && %s)*"

    extraCutsLooseCR2g1       = "(passPresel_Mu && muPFRelIso<0.3 && nJet>=2 && nBJet==0)*"
    extraPhotonCutsLooseCR2g1 = "(passPresel_Mu && muPFRelIso<0.3 && nJet>=2 && nBJet==0 && %s)*"

    extraCutsLooseCR3e0       = "(passPresel_Mu && muPFRelIso<0.3 && nJet>=2 && nBJet==0)*"
    extraPhotonCutsLooseCR3e0 = "(passPresel_Mu && muPFRelIso<0.3 && nJet>=2 && nBJet==0 && %s)*"


elif finalState=="QCDMu2":
    sampleList[-1] = "DataMu"
    sampleList[-2] = "QCDMu"
    if sample=="Data":
        sample = "DataMu"
    if sample=="QCD":
        sample = "QCDMu"

    isQCD = True

    analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/qcdmuons/V08_00_26_07/QCDcr_"
    outputhistName = "histograms/mu/qcdhistsCR2"

    nBJets = 0

    extraCuts            = "(passPresel_Mu && muPFRelIso>0.3 && nJet>=3 && nBJet==0)*"
    extraPhotonCuts      = "(passPresel_Mu && muPFRelIso>0.3 && nJet>=3 && nBJet==0 && %s)*"

    extraCutsTight            = "(passPresel_Mu && muPFRelIso>0.3 && nJet>=4 && nBJet==0)*"
    extraPhotonCutsTight      = "(passPresel_Mu && muPFRelIso>0.3 && nJet>=4 && nBJet==0 && %s)*"

    extraCutsLoose            = "(passPresel_Mu && muPFRelIso>0.3 && nJet>=2 && nBJet==0)*"
    extraPhotonCutsLoose      = "(passPresel_Mu && muPFRelIso>0.3 && nJet>=2 && nBJet==0 && %s)*"

    extraCutsLooseCR          = "(passPresel_Mu && muPFRelIso>0.3 && nJet>=2 && nBJet==0)*"
    extraPhotonCutsLooseCR    = "(passPresel_Mu && muPFRelIso>0.3 && nJet>=2 && nBJet==0 && %s)*"

elif finalState=="QCDEle":
    sampleList[-1] = "DataEle"
    sampleList[-2] = "QCDEle"
    if sample=="Data":
        sample = "DataEle"
    if sample=="QCD":
        sample = "QCDEle"
    analysisNtupleLocation = "root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/qcdelectrons/V08_00_26_07/QCDcr_"
    outputhistName = "histograms/ele/qcdhistsCR"

    isQCD = True

    nBJets = 0

    extraCuts            = "(passPresel_Ele && nJet>=3 && nBJet==0)*"
    extraPhotonCuts      = "(passPresel_Ele && nJet>=3 && nBJet==0 && %s)*"

    extraCutsTight            = "(passPresel_Ele && nJet>=4 && nBJet==0)*"
    extraPhotonCutsTight      = "(passPresel_Ele && nJet>=4 && nBJet==0 && %s)*"

    extraCutsLoose            = "(passPresel_Ele && nJet>=2 && nBJet==0)*"
    extraPhotonCutsLoose      = "(passPresel_Ele && nJet>=2 && nBJet==0 && %s)*"

    extraCutsLooseCR          = "(passPresel_Ele && nJet>=2 && nBJet==0)*"
    extraPhotonCutsLooseCR    = "(passPresel_Ele && nJet>=2 && nBJet==0 && %s)*"

else:
    print "Unknown final state, options are Mu and Ele"
    sys.exit()



if 'PU' in sys.argv:
    if level=="up":
	
    	Pileup = "PUweight_Up"
    else:
	Pileup = "PUweight_Do"
    sys.argv.remove("PU")
    
    outputhistName = "histograms/%s/%sPileup_%s"%(finalState,outputFileName,level)


if 'Q2' in sys.argv:
	if level=="up":
		Q2="q2weight_Up"
	else:
		Q2="q2weight_Do"
	sys.argv.remove("Q2")
	outputhistName = "histograms/%s/%sQ2_%s"%(finalState,outputFileName,level)


if 'Pdf' in sys.argv:
        if level=="up":
                Pdf="pdfweight_Up"
        else:
                Pdf="pdfweight_Do"

        sys.argv.remove("Pdf")
        outputhistName = "histograms/%s/%sPdf_%s"%(finalState,outputFileName,level)


if 'MuEff' in sys.argv:
    if level=="up":
    	MuEff = "muEffWeight_Up"
    else:
	MuEff = "muEffWeight_Do"

    sys.argv.remove("MuEff")
    outputhistName = "histograms/%s/%sMuEff_%s"%(finalState,outputFileName,level)

if 'EleEff' in sys.argv:
    if level=="up":
    	EleEff = "eleEffWeight_Up"
    else:
	EleEff = "eleEffWeight_Do"

    sys.argv.remove("EleEff")
    outputhistName = "histograms/%s/%sEleEff_%s"%(finalState,outputFileName,level)


if 'BTagSF' in sys.argv:
    if level=="up":
    	btagWeightCategory = ["1","(1-btagWeight_Up[0])","(btagWeight_Up[2])","(btagWeight_Up[1])"]
    else:
	btagWeightCategory = ["1","(1-btagWeight_Do[0])","(btagWeight_Do[2])","(btagWeight_Do[1])"]


    sys.argv.remove("BTagSF")
    outputhistName = "histograms/%s/%sBTagSF_%s"%(finalState,outputFileName,level)

weights = "%s*%s*%s*%s*%s*%s*%s"%(evtWeight,Pileup,MuEff,EleEff,Q2,Pdf,btagWeightCategory[nBJets])

if isTightSelection:
    if not runQuiet: print "Tight Select"
    nJets = 4
    nBJets = 2
    weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*btagWeight[2]"
    extraCuts = extraCutsTight 
    extraPhotonCuts = extraPhotonCutsTight 
    outputhistName = outputhistName + "_tight"

if isLooseCR2g0Selection:
    if not runQuiet: print "Loose Select"
    nJets = 2
    nBJets = 0
    weights = "evtWeight*PUweight*muEffWeight*eleEffWeight"
    extraCuts = extraCutsLooseCR2g0
    extraPhotonCuts = extraPhotonCutsLooseCR2g0
    outputhistName = outputhistName  +"_looseCR2g0"

if isLooseCR2e0Selection:
    if not runQuiet: print "Loose Control Region Select"
    nJets = 2
    nBJets = 0
    weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*btagWeight[0]"
    extraCuts = extraCutsLooseCR2e0
    extraPhotonCuts = extraPhotonCutsLooseCR2e0
    outputhistName = outputhistName + "_looseCR2e0"

if isLooseCR2g1Selection:
    if not runQuiet: print "Loose Control Region1 Select"
    nJets = 2
    nBJets = 1
    weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*(1-btagWeight[0])"
    if 'QCD' in finalState:
        weights = "evtWeight*PUweight*muEffWeight*eleEffWeight"
    extraCuts = extraCutsLooseCR2g1
    extraPhotonCuts = extraPhotonCutsLooseCR2g1    
    outputhistName = outputhistName + "_looseCR2g1"


if isLooseCR3e0Selection:
    if not runQuiet: print "Loose Control Region Select"
    nJets = 3
    nBJets = 0
    weights = "evtWeight*PUweight*muEffWeight*eleEffWeight*(btagWeight[0])"
    extraCuts = extraCutsLooseCR3e0
    extraPhotonCuts = extraPhotonCutsLooseCR3e0
    outputhistName = outputhistName + "_looseCR3e0"

print " the output folder is:", outputhistName


from HistogramListDict import *
histogramInfo = GetHistogramInfo(extraCuts,extraPhotonCuts,nBJets)
#histogramInfo = GetHistforfits(extraCuts,extraPhotonCuts,nBJets)


plotList = options.plotList
if plotList is None:
    if makeAllPlots:
        plotList = histogramInfo.keys()
        if not runQuiet: print "Making full list of plots"
    elif makeMorePlots:
        plotList = ["presel_Njet","presel_Nbjet","phosel_Njet","phosel_Nbjet","presel_jet1Pt","presel_jet2Pt","presel_jet3Pt","phosel_LeadingPhotonEt","phosel_LeadingPhotonEta","phosel_dRLeadingPhotonJet","phosel_dRLeadingPhotonLepton","presel_WtransMass","phosel_WtransMass","presel_MET","phosel_MET"]
        if not runQuiet: print "Making subset of kinematic plots"
    elif makeEGammaPlots:
        plotList = ["phosel_MassEGamma","phosel_MassEGammaMisIDEle","phosel_MassEGammaOthers"]
        if not runQuiet: print "Making only plots for e-gamma fits"
    else:
        plotList = ["presel_M3_control","phosel_noCut_ChIso","phosel_noCut_ChIso_GenuinePhoton","phosel_noCut_ChIso_MisIDEle","phosel_noCut_ChIso_HadronicPhoton","phosel_noCut_ChIso_HadronicFake","phosel_M3","phosel_M3_GenuinePhoton","phosel_M3_MisIDEle","phosel_M3_HadronicPhoton","phosel_M3_HadronicFake","phosel_AntiSIEIE_ChIso","phosel_AntiSIEIE_ChIso_barrel","phosel_AntiSIEIE_ChIso_endcap"]
        if not runQuiet: print "Making only plots for simultaneous fits"

plotList.sort()
if not runQuiet: print '-----'
if not runQuiet: print "Making the following plots:"
if not runQuiet: 
    for p in plotList: print "%s,"%p,
if not runQuiet: print
if not runQuiet: print '-----'

histogramsToMake = plotList

allHistsDefined = True
for hist in histogramsToMake:
    if not hist in histogramInfo:
        print "Histogram %s is not defined in HistogramListDict.py"%hist
        allHistsDefined = False
if not allHistsDefined:
    sys.exit()

# ###This part will make a list of the histograms that need to be produced
# plotList = options.plotList
# if not plotList is None:
#     #gets list of histograms from input options if any given
#     histogramsToMake = plotList
#     ### in this case, we need to check that the histograms are in histogramInfo
#     allHistsDefined = True
#     for hist in histogramsToMake:
#         if not hist in histogramInfo:
#             print "Histogram %s is not defined in HistogramListDict.py"%hist
#             allHistsDefined = False
#     if not allHistsDefined:
#         sys.exit()
# else:
#     ## make all histograms defined in HistogramListDict
#     histogramsToMake = histogramInfo.keys()
#     histogramsToMake.sort()

#     # ## make only a subset of histograms
#     # histogramsToMake = ["phosel_PhotonCategory", "presel_nJet"]
#     # ### in this case, we need to check that the histograms are in histogramInfo
#     # allHistsDefined = True
#     # for hist in histogramsToMake:
#     #     if not hist in histogramInfo:
#     #         print "Histogram %s is not defined in HistogramListDict.py"
#     #         allHistsDefined = False
#     # if not allHistsDefined:
#     #     sys.exit()



histograms=[]
canvas = TCanvas()

#sample = sys.argv[-1]

if sample =="QCD_DD":
    if finalState=="mu":
        if isTightSelection:
            qcd_File    = TFile("histograms/mu/qcdhistsCR_tight/QCD_DD.root","read")
        elif isLooseCR2g1Selection:
            qcd_File    = TFile("histograms/mu/qcdhistsCR_LooseCR2g1/QCD_DD.root","read")
        elif isLooseCR2g0Selection:
            qcd_File    = TFile("histograms/mu/qcdhistsCR_LooseCR2g0/QCD_DD.root","read")
        elif isLooseCR2e0Selection:
            qcd_File    = TFile("histograms/mu/qcdhistsCR_LooseCR2e1/QCD_DD.root","read")
        elif isLooseCR3e0Selection:
            qcd_File    = TFile("histograms/mu/qcdhistsCR_LooseCR3e1/QCD_DD.root","read")
        else:
            qcd_File    = TFile("histograms/mu/qcdhistsCR/QCD_DD.root","read")
        qcd_TF_File = TFile("histograms/mu/qcdTransferFactors.root","read")
        dirName = "QCDMu"
    if finalState=="Ele":
        if isTightSelection:
            qcd_File    = TFile("histograms/ele/qcdhistsCR_tight/QCD_DD.root","read")
        elif isLooseCR2g1Selection:
            qcd_File    = TFile("histograms/ele/qcdhistsCR_LooseCR2g1/QCD_DD.root","read")
        elif isLooseCR2g0Selection:
            qcd_File    = TFile("histograms/ele/qcdhistsCR_LooseCR2g0/QCD_DD.root","read")
        elif isLooseCR2e0Selection:
            qcd_File    = TFile("histograms/ele/qcdhistsCR_LooseCR2e1/QCD_DD.root","read")
        elif isLooseCR3e0Selection:
            qcd_File    = TFile("histograms/ele/qcdhistsCR_LooseCR3e1/QCD_DD.root","read")
        else:
            qcd_File    = TFile("histograms/ele/qcdhistsCR/QCD_DD.root","read")

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
    #print transferFactor

    for hist in histogramsToMake:
        h_Info = histogramInfo[hist]
        if not h_Info[5]: continue
        if not runQuiet: print "filling", h_Info[1], sample

        histograms.append(qcd_File.Get("%s_QCD_DD"%(h_Info[1])))
        histograms[-1].Scale(transferFactor)

if not "QCD_DD" in sample:
    if not sample in samples:
        print "Sample isn't in list"
        print samples.keys()
        sys.exit()

    tree = TChain("AnalysisTree")
    fileList = samples[sample][0]
    for fileName in fileList:
        tree.Add("%s%s"%(analysisNtupleLocation,fileName))

    #print sample

    #print "Number of events:", tree.GetEntries()
    
    for hist in histogramsToMake:
        h_Info = histogramInfo[hist]

        # skip some histograms which rely on MC truth and can't be done in data or QCD data driven templates
        if ('Data' in sample or isQCD) and not h_Info[5]: continue

        if not runQuiet: print "filling", h_Info[1], sample
        evtWeight = ""
        histograms.append(TH1F("%s_%s"%(h_Info[1],sample),"%s_%s"%(h_Info[1],sample),h_Info[2][0],h_Info[2][1],h_Info[2][2]))
        if h_Info[4]=="":
            evtWeight = "%s%s"%(h_Info[3],weights)
        else:
            evtWeight = h_Info[4]

        if "Data" in sample:
            evtWeight = "%s%s"%(h_Info[3],weights)

        if evtWeight[-1]=="*":
            evtWeight= evtWeight[:-1]
        tree.Draw("%s>>%s_%s"%(h_Info[0],h_Info[1],sample),evtWeight)

if not os.path.exists(outputhistName):
    os.makedirs(outputhistName)

outputFile = TFile("%s/%s.root"%(outputhistName,sample),"update")

# if not onlyAddPlots:
#     outputFile.rmdir(sample)
#     outputFile.mkdir(sample)
# outputFile.cd(sample)
for h in histograms:
    outputFile.Delete("%s;*"%h.GetName())
    if onlyAddPlots:
        gDirectory.Delete("%s;*"%(h.GetName()))
    h.Write()

outputFile.Close()

