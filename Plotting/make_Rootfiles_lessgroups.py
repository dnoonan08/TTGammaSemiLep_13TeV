## Make root files for combine with different MC signals and their systematics###
##uncertainties in both electron and muon channel####

from ROOT import *
import math
import os
import sys
from array import array
import CMS_lumi

from Style import *
thestyle = Style()
random=TRandom3(0)

_file = {}
from optparse import OptionParser


parser = OptionParser()

parser.add_option("-c", "--channel", dest="channel", default="mu",type='str',
                  help="Specify which channel mu or ele? default is mu" )
parser.add_option("--Tight","--tight", dest="isTightSelection", default=False,action="store_true",
                     help="Use 4j2t selection" )

(options, args) = parser.parse_args()


finalState = options.channel
TightSelection = options.isTightSelection

samples =["TTGamma","TTbar","TTV","TGJets","SingleTop","WJets","ZJets","WGamma","ZGamma","Diboson"]
if finalState=="mu":
	samples.append("DataMu")
else:
	samples.append("DataEle")

if TightSelection:
	for s in samples:
        	_file[s] = TFile("/uscms_data/d3/troy2012/CMSSW_8_0_26_patch1/src/TTGammaSemiLep_13TeV/Plotting/histograms/%s/hists_tight/%s.root"%(finalState,s))
else:
	for s in samples:
		print s
                _file[s] = TFile("/uscms_data/d3/troy2012/CMSSW_8_0_26_patch1/src/TTGammaSemiLep_13TeV/Plotting/histograms/%s/hists/%s.root"%(finalState,s))

#exit()
misIDEleSF = 1.
HistDict={}
HistDict_up={}
HistDict_do={}
_file_up={}
_file_do={}
if finalState=="mu":
	systematics = ["JER","JECTotal","phosmear","phoscale","BTagSF","Q2","Pdf","PU","MuEff","PhoEff"]
else:
	systematics = ["JER","JECTotal","phosmear","phoscale","elesmear","elescale","BTagSF","Q2","Pdf","PU","EleEff","PhoEff"]

systematics2 = ["isr","fsr"]


for sys in systematics2:
	_file_up[sys]={}
        _file_do[sys]={}


for sys in systematics:
      
       _file_up[sys]={}
       _file_do[sys]={}
       if TightSelection:
		for s in samples:
			if s=="DataMu" or s=="DataEle":continue
			_file_up[sys][s]=TFile("/uscms_data/d3/troy2012/CMSSW_8_0_26_patch1/src/TTGammaSemiLep_13TeV/Plotting/histograms/%s/hists%s_up_tight/%s.root"%(finalState,sys,s))
			_file_do[sys][s]=TFile("/uscms_data/d3/troy2012/CMSSW_8_0_26_patch1/src/TTGammaSemiLep_13TeV/Plotting/histograms/%s/hists%s_down_tight/%s.root"%(finalState,sys,s))
       else:					
       		for s in samples:
			if s=="DataMu" or s=="DataEle":continue
               		_file_up[sys][s]=TFile("/uscms_data/d3/troy2012/CMSSW_8_0_26_patch1/src/TTGammaSemiLep_13TeV/Plotting/histograms/%s/hists%s_up/%s.root"%(finalState,sys,s))
               		_file_do[sys][s]=TFile("/uscms_data/d3/troy2012/CMSSW_8_0_26_patch1/src/TTGammaSemiLep_13TeV/Plotting/histograms/%s/hists%s_down/%s.root"%(finalState,sys,s))
if TightSelection:
	for sys in systematics2:

		_file_up[sys]["TTGamma"]=TFile("/uscms_data/d3/troy2012/CMSSW_8_0_26_patch1/src/TTGammaSemiLep_13TeV/Plotting/histograms/%s/hists%s_up_tight/TTGamma.root"%(finalState,sys))
        	_file_do[sys]["TTGamma"]=TFile("/uscms_data/d3/troy2012/CMSSW_8_0_26_patch1/src/TTGammaSemiLep_13TeV/Plotting/histograms/%s/hists%s_down_tight/TTGamma.root"%(finalState,sys))
else:
	for sys in systematics2:
		_file_up[sys]["TTGamma"]=TFile("/uscms_data/d3/troy2012/CMSSW_8_0_26_patch1/src/TTGammaSemiLep_13TeV/Plotting/histograms/%s/hists%s_up/TTGamma.root"%(finalState,sys))
        	_file_do[sys]["TTGamma"]=TFile("/uscms_data/d3/troy2012/CMSSW_8_0_26_patch1/src/TTGammaSemiLep_13TeV/Plotting/histograms/%s/hists%s_down/TTGamma.root"%(finalState,sys))


#binsM3=[]
#binsM3=[0.,10.,20.,30.,40.,50.,60.,70.,80.,90.,100.,110.,120,130.,140.,150.,160.,170.,180.,190.,200.,210,220.,230.,240.,250.,260.,270.,280.,290.,300.,310.,320.,330.]
#print _file_up["isr"]["TTGamma"]
binsChHad = [0.,0.1,1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.,13.,14.,15.,16.,17.,18.,19.,20.]
#print len(binsChHad)
#for i in range(-10,350,10):
#	binsM3.append(i+10)


#for i in range(350,595,5):
#	binsM3.append(i+5)
#print len(binsM3)

#exit()


#for i in range(46,56):
#	binsM3.append(1)

observables={"M3": ["M3",10],
	     "ChHad":["noCut_ChIso",binsChHad],
             "AntiSIEIE":["AntiSIEIE_ChIso",binsChHad],
	     "M3_control":["M3_control",10]
           }

#print sorted(observables.keys())[:2]


process_signal = {"TTGamma_Prompt":["TTGamma"],
	   "TTGamma_NonPrompt":["TTGamma"],
           "TTbar_Prompt": ["TTbar"],
           "TTbar_NonPrompt": ["TTbar"],
           "VGamma_Prompt":["ZGamma","WGamma"],
           "VGamma_NonPrompt":["ZGamma","WGamma"],
           "VJets_Prompt":["ZJets", "WJets"],
           "VJets_NonPrompt":["ZJets", "WJets"],
           "Other_Prompt":["TTV", "Diboson", "TGJets", "SingleTop"],
           "Other_NonPrompt":["TTV", "Diboson","TGJets", "SingleTop"],
	}



process_control ={"TTGamma":["TTGamma"],
		  "TTbar":  ["TTbar"],
		  "VGamma":["ZGamma", "WGamma"],
		  "VJets":["WJets", "ZJets"],
		  "Other":[ "TTV", "Diboson","TGJets", "SingleTop"],
		}	





##### Make Prompt and NonPrompt MC templates#######
process={}
for obs in observables:
	HistDict[obs]={}
	HistDict_up[obs]={}
	HistDict_do[obs]={}
        if obs=="M3_control":
		for p in process_control:
			s= process_control[p][0]
			HistDict_up[obs][p]={}
			HistDict_do[obs][p]={}
			HistDict[obs][p]   = _file[s].Get("presel_%s_%s"%(observables[obs][0],s)).Clone("%s_%s"%(obs,p))
				
			for sys in systematics:
				#we only need the shape uncertainty for Q2, keeping cross section constant
				if sys=="Q2":
				#	print obs, p, sys
					HistDict_up[obs][p][sys] = _file_up[sys][s].Get("presel_%s_%s"%(observables[obs][0],s)).Clone("%s_%s"%(obs,p))
					total_up= HistDict_up[obs][p][sys].Integral()
					HistDict_up[obs][p][sys].Scale(HistDict[obs][p].Integral()/total_up)
					HistDict_do[obs][p][sys] = _file_do[sys][s].Get("presel_%s_%s"%(observables[obs][0],s)).Clone("%s_%s"%(obs,p))
					total_do= HistDict_do[obs][p][sys].Integral()
					HistDict_do[obs][p][sys].Scale(HistDict[obs][p].Integral()/total_do) 
				else:

					
					HistDict_up[obs][p][sys] = _file_up[sys][s].Get("presel_%s_%s"%(observables[obs][0],s)).Clone("%s_%s"%(obs,p))
					HistDict_do[obs][p][sys] = _file_do[sys][s].Get("presel_%s_%s"%(observables[obs][0],s)).Clone("%s_%s"%(obs,p))
			
					

			for s in process_control[p][1:]:
				HistDict[obs][p].Add(_file[s].Get("presel_%s_%s"%(observables[obs][0],s)))
				for sys	in systematics:
					if sys=="Q2":continue
					HistDict_up[obs][p][sys].Add(_file_up[sys][s].Get("presel_%s_%s"%(observables[obs][0],s)))
					HistDict_do[obs][p][sys].Add(_file_do[sys][s].Get("presel_%s_%s"%(observables[obs][0],s)))
			HistDict[obs][p].Rebin(10)
		
			for sys in systematics:
				HistDict_up[obs][p][sys].Rebin(10)			
				HistDict_do[obs][p][sys].Rebin(10)
		for sys in systematics2:
			HistDict_up[obs]["TTGamma"][sys] = _file_up[sys]["TTGamma"].Get("presel_%s_TTGamma"%(observables[obs][0])).Clone("%s_TTGamma"%(obs))
			HistDict_up[obs]["TTGamma"][sys].Rebin(10)
                        HistDict_do[obs]["TTGamma"][sys] = _file_do[sys]["TTGamma"].Get("presel_%s_TTGamma"%(observables[obs][0])).Clone("%s_TTGamma"%(obs))
			HistDict_do[obs]["TTGamma"][sys].Rebin(10)
	
	else:
		

		for p in process_signal:
			HistDict_up[obs][p]={}
                        HistDict_do[obs][p]={}
			
		 	s = process_signal[p][0]
			if "NonPrompt" in p:
				 print _file[s]
				 print "phosel_%s_HadronicPhoton_barrel_%s"%(observables[obs][0],s)
				 HistDict[obs][p]   = _file[s].Get("phosel_%s_HadronicPhoton_barrel_%s"%(observables[obs][0],s)).Clone("%s_%s"%(obs,p))
				 HistDict[obs][p].Add(_file[s].Get("phosel_%s_HadronicFake_barrel_%s"%(observables[obs][0],s)))
				
				 for sys in systematics:
					 if "AntiSIEIE" in observables[obs][0]:continue
					 if sys=="Q2":
				#		print obs, sys, p
	                                        HistDict_up[obs][p][sys] = _file_up[sys][s].Get("phosel_%s_HadronicPhoton_barrel_%s"%(observables[obs][0],s)).Clone("%s_%s"%(obs,p))
						HistDict_up[obs][p][sys].Add(_file_up[sys][s].Get("phosel_%s_HadronicFake_barrel_%s"%(observables[obs][0],s)))
        	                                total_up= HistDict_up[obs][p][sys].Integral()
                	                        HistDict_up[obs][p][sys].Scale(HistDict[obs][p].Integral()/total_up)
                        	                HistDict_do[obs][p][sys] = _file_do[sys][s].Get("phosel_%s_HadronicPhoton_barrel_%s"%(observables[obs][0],s)).Clone("%s_%s"%(obs,p))
                                                HistDict_do[obs][p][sys].Add(_file_do[sys][s].Get("phosel_%s_HadronicFake_barrel_%s"%(observables[obs][0],s)))
                                	        total_do= HistDict_do[obs][p][sys].Integral()
                                        	HistDict_do[obs][p][sys].Scale(HistDict[obs][p].Integral()/total_do)
					 else:  
				#		print _file_up[sys][s]
					 	HistDict_up[obs][p][sys] = _file_up[sys][s].Get("phosel_%s_HadronicPhoton_barrel_%s"%(observables[obs][0],s)).Clone("%s_%s"%(obs,p))
					 	HistDict_up[obs][p][sys].Add(_file_up[sys][s].Get("phosel_%s_HadronicFake_barrel_%s"%(observables[obs][0],s)))

					 	HistDict_do[obs][p][sys] = _file_do[sys][s].Get("phosel_%s_HadronicPhoton_barrel_%s"%(observables[obs][0],s)).Clone("%s_%s"%(obs,p))
                                         	HistDict_do[obs][p][sys].Add(_file_do[sys][s].Get("phosel_%s_HadronicFake_barrel_%s"%(observables[obs][0],s)))

		 	if "_Prompt" in p:
				print "phosel_%s_GenuinePhoton_barrel_%s"%(observables[obs][0],s)
			 	HistDict[obs][p]   = _file[s].Get("phosel_%s_GenuinePhoton_barrel_%s"%(observables[obs][0],s)).Clone("%s_%s"%(obs,p))
			 	HistDict[obs][p].Add(_file[s].Get("phosel_%s_MisIDEle_barrel_%s"%(observables[obs][0],s)))
				for sys in systematics:
					if (finalState=="mu") and ("VJets" in p):continue	
					if "AntiSIEIE" in observables[obs][0]:continue
					if sys=="Q2":
                                                HistDict_up[obs][p][sys] = _file_up[sys][s].Get("phosel_%s_GenuinePhoton_barrel_%s"%(observables[obs][0],s)).Clone("%s_%s"%(obs,p))
                                                HistDict_up[obs][p][sys].Add(_file_up[sys][s].Get("phosel_%s_MisIDEle_barrel_%s"%(observables[obs][0],s)))
                                                total_up= HistDict_up[obs][p][sys].Integral()
						
                                                HistDict_up[obs][p][sys].Scale(HistDict[obs][p].Integral()/total_up)
                                                HistDict_do[obs][p][sys] = _file_do[sys][s].Get("phosel_%s_GenuinePhoton_barrel_%s"%(observables[obs][0],s)).Clone("%s_%s"%(obs,p))
                                                HistDict_do[obs][p][sys].Add(_file_do[sys][s].Get("phosel_%s_MisIDEle_barrel_%s"%(observables[obs][0],s)))
                                                total_do= HistDict_do[obs][p][sys].Integral()
                                                HistDict_do[obs][p][sys].Scale(HistDict[obs][p].Integral()/total_do)
					else:
						HistDict_up[obs][p][sys] = _file_up[sys][s].Get("phosel_%s_GenuinePhoton_barrel_%s"%(observables[obs][0],s)).Clone("%s_%s"%(obs,p))
						HistDict_up[obs][p][sys].Add(_file_up[sys][s].Get("phosel_%s_MisIDEle_barrel_%s"%(observables[obs][0],s)))

						HistDict_do[obs][p][sys] = _file_do[sys][s].Get("phosel_%s_GenuinePhoton_barrel_%s"%(observables[obs][0],s)).Clone("%s_%s"%(obs,p))
                                        	HistDict_do[obs][p][sys].Add(_file_do[sys][s].Get("phosel_%s_MisIDEle_barrel_%s"%(observables[obs][0],s)))
									
				
			for s in process_signal[p][1:]:
				if "_Prompt" in p:
					if (finalState=="mu") and ("VJets" in p):continue	
					HistDict[obs][p].Add(_file[s].Get("phosel_%s_GenuinePhoton_barrel_%s"%(observables[obs][0],s)))
					HistDict[obs][p].Add(_file[s].Get("phosel_%s_MisIDEle_barrel_%s"%(observables[obs][0],s)))
					for sys in systematics:
						if "AntiSIEIE" in observables[obs][0]:continue
						if sys=="Q2":continue	
						HistDict_up[obs][p][sys].Add(_file_up[sys][s].Get("phosel_%s_GenuinePhoton_barrel_%s"%(observables[obs][0],s)))
						HistDict_up[obs][p][sys].Add(_file_up[sys][s].Get("phosel_%s_MisIDEle_barrel_%s"%(observables[obs][0],s)))

						HistDict_do[obs][p][sys].Add(_file_do[sys][s].Get("phosel_%s_GenuinePhoton_barrel_%s"%(observables[obs][0],s)))
                                                HistDict_do[obs][p][sys].Add(_file_do[sys][s].Get("phosel_%s_MisIDEle_barrel_%s"%(observables[obs][0],s)))
					
				if "_NonPrompt" in p:
					HistDict[obs][p].Add(_file[s].Get("phosel_%s_HadronicPhoton_barrel_%s"%(observables[obs][0],s)))
                                        HistDict[obs][p].Add(_file[s].Get("phosel_%s_HadronicFake_barrel_%s"%(observables[obs][0],s)))

					for sys in systematics:
						if "AntiSIEIE" in observables[obs][0]:continue
						if sys=="Q2":continue
                                                HistDict_up[obs][p][sys].Add(_file_up[sys][s].Get("phosel_%s_HadronicPhoton_barrel_%s"%(observables[obs][0],s)))
						HistDict_up[obs][p][sys].Add(_file_up[sys][s].Get("phosel_%s_HadronicFake_barrel_%s"%(observables[obs][0],s)))


						HistDict_do[obs][p][sys].Add(_file_do[sys][s].Get("phosel_%s_HadronicPhoton_barrel_%s"%(observables[obs][0],s)))
                                                HistDict_do[obs][p][sys].Add(_file_do[sys][s].Get("phosel_%s_HadronicFake_barrel_%s"%(observables[obs][0],s)))
			

			


			if "ChIso" in observables[obs][0]:
				HistDict[obs][p]= HistDict[obs][p].Rebin(21,"",array('d',binsChHad))
				for sys in systematics:
					 if "AntiSIEIE" in observables[obs][0]:continue
					 if (finalState=="mu") and ("VJets_Prompt" in p):continue
					 HistDict_up[obs][p][sys] = HistDict_up[obs][p][sys].Rebin(21,"",array('d',binsChHad))
					 HistDict_do[obs][p][sys] = HistDict_do[obs][p][sys].Rebin(21,"",array('d',binsChHad))
			else:
				HistDict[obs][p].Rebin(10)
				for sys in systematics:
					
					 if (finalState=="mu") and ("VJets_Prompt" in p):continue
					 HistDict_up[obs][p][sys].Rebin(10)
					 HistDict_do[obs][p][sys].Rebin(10)
		for sys in systematics2:
			if "AntiSIEIE" in observables[obs][0]:continue
			print obs, #_file_up[sys]["TTGamma"]
			HistDict_up[obs]["TTGamma_NonPrompt"][sys] = _file_up[sys]["TTGamma"].Get("phosel_%s_HadronicPhoton_barrel_TTGamma"%(observables[obs][0])).Clone("%s_TTGamma_Prompt"%(obs))
			HistDict_up[obs]["TTGamma_NonPrompt"][sys].Add(_file_up[sys]["TTGamma"].Get("phosel_%s_HadronicFake_barrel_TTGamma"%(observables[obs][0])))

			HistDict_do[obs]["TTGamma_NonPrompt"][sys] = _file_do[sys]["TTGamma"].Get("phosel_%s_HadronicPhoton_barrel_TTGamma"%(observables[obs][0])).Clone("%s_TTGamma_Prompt"%(obs))
			HistDict_do[obs]["TTGamma_NonPrompt"][sys].Add(_file_do[sys]["TTGamma"].Get("phosel_%s_HadronicFake_barrel_TTGamma"%(observables[obs][0])))
			
			
			HistDict_up[obs]["TTGamma_Prompt"][sys] = _file_up[sys]["TTGamma"].Get("phosel_%s_GenuinePhoton_barrel_TTGamma"%(observables[obs][0])).Clone("%s_TTGamma_Prompt"%(obs))
			HistDict_up[obs]["TTGamma_Prompt"][sys].Add(_file_up[sys]["TTGamma"].Get("phosel_%s_MisIDEle_barrel_TTGamma"%(observables[obs][0])))

			HistDict_do[obs]["TTGamma_Prompt"][sys] = _file_do[sys]["TTGamma"].Get("phosel_%s_GenuinePhoton_barrel_TTGamma"%(observables[obs][0])).Clone("%s_TTGamma_Prompt"%(obs))
			HistDict_do[obs]["TTGamma_Prompt"][sys].Add(_file_do[sys]["TTGamma"].Get("phosel_%s_MisIDEle_barrel_TTGamma"%(observables[obs][0])))
for sys in systematics2:
	HistDict_up["ChHad"]["TTGamma_NonPrompt"][sys]= HistDict_up["ChHad"]["TTGamma_NonPrompt"][sys].Rebin(21,"",array('d',binsChHad))
	HistDict_up["ChHad"]["TTGamma_Prompt"][sys]= HistDict_up["ChHad"]["TTGamma_Prompt"][sys].Rebin(21,"",array('d',binsChHad))
	HistDict_up["M3"]["TTGamma_NonPrompt"][sys].Rebin(10)
	HistDict_up["M3"]["TTGamma_Prompt"][sys].Rebin(10)
	HistDict_do["ChHad"]["TTGamma_NonPrompt"][sys]= HistDict_do["ChHad"]["TTGamma_NonPrompt"][sys].Rebin(21,"",array('d',binsChHad))
        HistDict_do["ChHad"]["TTGamma_Prompt"][sys]= HistDict_do["ChHad"]["TTGamma_Prompt"][sys].Rebin(21,"",array('d',binsChHad))
        HistDict_do["M3"]["TTGamma_NonPrompt"][sys]= HistDict_do["M3"]["TTGamma_NonPrompt"][sys].Rebin(10)
        HistDict_do["M3"]["TTGamma_Prompt"][sys].Rebin(10)



#print  HistDict_up["M3"]["TTGamma_Prompt"]["Q2"], HistDict_up["M3_control"]["TTGamma"]["Q2"],  HistDict_up["ChHad"]["TTGamma_NonPrompt"]["Q2"] 
#print  HistDict_do["M3"]["TTGamma_Prompt"]["Q2"], HistDict_do["M3_control"]["TTGamma"]["Q2"],  HistDict_do["ChHad"]["TTGamma_NonPrompt"]["Q2"]    
#exit()

###make Data-Driven NonPrompt Templates######
if finalState=="ele":
	h1 = _file["DataEle"].Get("phosel_AntiSIEIE_ChIso_barrel_DataEle").Clone("ChHad_NonPrompt")
else:
	h1 = _file["DataMu"].Get("phosel_AntiSIEIE_ChIso_barrel_DataMu").Clone("ChHad_NonPrompt")
h1 = h1.Rebin(21,"",array('d',binsChHad))

total = h1.Integral()
NormFactor={}



for p in process_signal:
	NormFactor[p]={}
	if "_NonPrompt" in p:
		print p	
		p1=p.strip("NonPrompt")
		p1= p1.strip("_")
#		print p1
		print "%s_DD"%p1
		if finalState=="ele":
			HistDict["ChHad"]["%s_DD"%p1] = _file["DataEle"].Get("phosel_AntiSIEIE_ChIso_barrel_DataEle").Clone("ChHad_NonPrompt")
		else:
			HistDict["ChHad"]["%s_DD"%p1] = _file["DataMu"].Get("phosel_AntiSIEIE_ChIso_barrel_DataMu").Clone("ChHad_NonPrompt")
		HistDict["ChHad"]["%s_DD"%p1]=HistDict["ChHad"]["%s_DD"%p1].Rebin(21,"",array('d',binsChHad))
		NormFactor["%s_DD"%p1]=HistDict["ChHad"][p].Integral()
		print "Scaling to:",NormFactor["%s_DD"%p1]
		print "Original number:",HistDict["ChHad"]["%s_DD"%p1].Integral()
		HistDict["ChHad"]["%s_DD"%p1].Scale(NormFactor["%s_DD"%p1]/total)
		print "Final number:",HistDict["ChHad"]["%s_DD"%p1].Integral()




#print HistDict["ChHad"]["Other_DD"].Integral()
		
		
	
print "done with making Data Driven templates"

process_DDtemplates = {"TTGamma_Prompt":[kOrange,"TTGamma"],
           "TTGamma_DD":[kOrange,"TTGamma"],
           "TTbar_Prompt": [kRed+1,"TTbar"],
           "TTbar_DD": [kRed+1,"TTbar"],
           "VGamma_Prompt":[kBlue-9,"VGamma"],
           "VGamma_DD":[kBlue-9,"VGamma"],
           "VJets_Prompt":[kGreen-6,"VJets"],
           "VJets_DD":[kGreen-6,"VJets"],
           "Other_Prompt":[kBlue,"Other"],
           "Other_DD":[kBlue,"Other"],
        }
#process_= ["Other_Prompt","Other_DD","VGamma_Prompt","VGamma_DD","VJets_Prompt","VJets_DD","TTbar_Prompt","TTbar_DD","TTGamma_Prompt","TTGamma_DD"]


#print HistDict["ChHad"]["VJets_Prompt"]
def makePseudoData(HistDict,processList,variables,processScales = None):
       # print processList
        if processScales==None :processScales = [1.]*len(processList)
        if not len(processList)==len(processScales):
                print "different length of process list and process scales, ignoring scales"
                processScales = [1.]*len(processList)

        for c in variables:
                print c, processList[0]
                HistDict[c]["data_obs"] = HistDict[c][processList[0]].Clone("%s_data_obs"%c)
                HistDict[c]["data_obs"].Scale(processScales[0])
                for p,scale in zip(processList[1:],processScales[1:]):
			print c, p
                        HistDict[c]["data_obs"].Add(HistDict[c][p],scale)
                for b in range(1,HistDict[c]["data_obs"].GetNbinsX()+1):
                        HistDict[c]["data_obs"].SetBinContent(b,int(random.Poisson(HistDict[c]["data_obs"].GetBinContent(b))))
                        HistDict[c]["data_obs"].SetBinError(b,math.sqrt(HistDict[c]["data_obs"].GetBinContent(b)))
        return HistDict








##Making Pseudo data based on MC templates

for c in HistDict:
        if c=="M3_control":
                HistDict = makePseudoData(HistDict,process_control.keys(),["M3_control"])
        if c=="M3":
		HistDict = makePseudoData(HistDict,process_signal.keys(),["M3"])
	if c =="ChHad": 
                HistDict = makePseudoData(HistDict,process_signal.keys(),["ChHad"])

#print "made pseduo data for all MConly  templates"

print "Total pseudo data for MC ChHad: ", HistDict["ChHad"]["data_obs"].Integral()
print "Total MC in ChHad:",HistDict["ChHad"]["TTGamma_Prompt"].Integral()+HistDict["ChHad"]["TTGamma_NonPrompt"].Integral()+HistDict["ChHad"]["TTbar_Prompt"].Integral()+HistDict["ChHad"]["TTbar_NonPrompt"].Integral()+HistDict["ChHad"]["VGamma_Prompt"].Integral()+HistDict["ChHad"]["VGamma_NonPrompt"].Integral()+HistDict["ChHad"]["VJets_NonPrompt"].Integral()+HistDict["ChHad"]["Other_Prompt"].Integral()+HistDict["ChHad"]["Other_NonPrompt"].Integral()



###We need MC NonPrompt templates in fit region for shape uncertainty on DataDriven templates

nbins = HistDict["ChHad"]["TTGamma_NonPrompt"].GetNbinsX()

if nbins != HistDict["AntiSIEIE"]["TTGamma_NonPrompt"].GetNbinsX():
	print "binsChHad not equal in two regions !! abort !!"
	exit()
diff=0.

unc_=[]
for p in process_control:


       if p=="TTbar":continue
       HistDict["AntiSIEIE"]["TTbar_NonPrompt"].Add(HistDict["AntiSIEIE"]["%s_NonPrompt"%p])
       HistDict["ChHad"]["TTbar_NonPrompt"].Add(HistDict["ChHad"]["%s_NonPrompt"%p])

HistDict["AntiSIEIE"]["TTbar_NonPrompt"].Scale(1/HistDict["AntiSIEIE"]["TTbar_NonPrompt"].Integral())
HistDict["ChHad"]["TTbar_NonPrompt"].Scale(1/HistDict["ChHad"]["TTbar_NonPrompt"].Integral())

for bin_ in range(nbins):

        diff=HistDict["ChHad"]["TTbar_NonPrompt"].GetBinContent(bin_+1)-HistDict["AntiSIEIE"]["TTbar_NonPrompt"].GetBinContent(bin_+1)
        unc_.append(diff/HistDict["AntiSIEIE"]["TTbar_NonPrompt"].GetBinContent(bin_+1))



for p in process_control:
	
	HistDict_up["ChHad"]["%s_DD"%p] ={}
	HistDict_do["ChHad"]["%s_DD"%p] ={}
	HistDict_up["ChHad"]["%s_DD"%p]["shapeDD"] = TH1F("%s_shapeDD"%p,"%s_shapeDD"%p,21,0,20)
	HistDict_up["ChHad"]["%s_DD"%p]["shapeDD"] = HistDict_up["ChHad"]["%s_DD"%p]["shapeDD"].Rebin(21,"",array('d',binsChHad))
	
	HistDict_do["ChHad"]["%s_DD"%p]["shapeDD"] = TH1F("%s_shapeDD"%p,"%s_shapeDD"%p,21,0,20)
	HistDict_do["ChHad"]["%s_DD"%p]["shapeDD"] = HistDict_do["ChHad"]["%s_DD"%p]["shapeDD"].Rebin(21,"",array('d',binsChHad))
	for bin_ in range(nbins):
	
		orig_=HistDict["ChHad"]["%s_DD"%p].GetBinContent(bin_+1)
		up = orig_+orig_*unc_[bin_]
		do = orig_-orig_*unc_[bin_]
		HistDict_up["ChHad"]["%s_DD"%p]["shapeDD"].SetBinContent(bin_+1,up)
		HistDict_do["ChHad"]["%s_DD"%p]["shapeDD"].SetBinContent(bin_+1,do)


if TightSelection:
	outputFile = TFile("Combine_withMCTemplate_v2_%s_tight.root"%(finalState),"recreate")

else:
	outputFile = TFile("Combine_withMCTemplate_v2_%s.root"%(finalState),"recreate")

for obs in observables:
	if obs=="AntiSIEIE":continue
        outputFile.mkdir("%s/%s"%(obs,"data_obs"))
        outputFile.cd("%s/%s"%(obs,"data_obs"))
        HistDict[obs]["data_obs"].Write("nominal")
        outputFile.mkdir(obs)
        if obs=="M3_control":
                 for p in process_control.keys():
                         outputFile.mkdir("%s/%s"%(obs,p))
                         outputFile.cd("%s/%s"%(obs,p))
                         HistDict[obs][p].Write("nominal")
                         for sys in systematics:
				if sys=="Q2" and ("TTbar" not in p or "TTGamma" not in p): continue
                                HistDict_up[obs][p][sys].Write("%sUp"%(sys))
                                HistDict_do[obs][p][sys].Write("%sDown"%(sys))
		 outputFile.cd("%s/TTGamma"%(obs))
		 for sys in systematics2:
			HistDict_up[obs]["TTGamma"][sys].Write("%sUp"%(sys))
                        HistDict_do[obs]["TTGamma"][sys].Write("%sDown"%(sys))
	else :
		 for p in process_signal.keys():
                        outputFile.mkdir("%s/%s"%(obs,p))
                        outputFile.cd("%s/%s"%(obs,p))
                        
                        HistDict[obs][p].Write("nominal")
                        for sys in systematics:
				if finalState=="mu" and "VJets_Prompt" in p:continue
				if sys=="Q2" and ("TTbar" not in p or "TTGamma" not in p): continue
                                HistDict_up[obs][p][sys].Write("%sUp"%(sys))
                                HistDict_do[obs][p][sys].Write("%sDown"%(sys))
		 outputFile.cd("%s/TTGamma_Prompt"%(obs))
		 for sys in systematics2:
                        HistDict_up[obs]["TTGamma_Prompt"][sys].Write("%sUp"%(sys))
                        HistDict_do[obs]["TTGamma_Prompt"][sys].Write("%sDown"%(sys))

		 outputFile.cd("%s/TTGamma_NonPrompt"%(obs))
		
		 for sys in systematics2:
			HistDict_up[obs]["TTGamma_NonPrompt"][sys].Write("%sUp"%(sys))
                        HistDict_do[obs]["TTGamma_NonPrompt"][sys].Write("%sDown"%(sys))

outputFile.Close()

for c in HistDict:
        if c =="ChHad":
                HistDict = makePseudoData(HistDict,process_DDtemplates.keys(),["ChHad"])

print "Made pseudo data for DD ChIso"
c1 = TCanvas('c1','c1',1000,1000)
c1.SetFillColor(0)
c1.cd()



print "Total pseudo data for DD ChHad: ", HistDict["ChHad"]["data_obs"].Integral()
print "Total MC+DD in ChHad:",HistDict["ChHad"]["TTGamma_Prompt"].Integral()+HistDict["ChHad"]["TTGamma_DD"].Integral()+HistDict["ChHad"]["TTbar_Prompt"].Integral()+HistDict["ChHad"]["TTbar_DD"].Integral()+HistDict["ChHad"]["VGamma_Prompt"].Integral()+HistDict["ChHad"]["VGamma_DD"].Integral()+HistDict["ChHad"]["VJets_DD"].Integral()+HistDict["ChHad"]["Other_Prompt"].Integral()+HistDict["ChHad"]["Other_DD"].Integral()


if TightSelection:
        outputFile = TFile("Combine_withDDTemplate_v2_%s_tight.root"%(finalState),"recreate")

else:
	outputFile = TFile("Combine_withDDTemplate_v2_%s.root"%(finalState),"recreate")

for obs in observables:
	if obs=="AntiSIEIE":continue
        outputFile.mkdir("%s/%s"%(obs,"data_obs"))
        outputFile.cd("%s/%s"%(obs,"data_obs"))
        HistDict[obs]["data_obs"].Write("nominal")
        outputFile.mkdir(obs)
        if obs=="M3_control":
                 for p in process_control.keys():
                         outputFile.mkdir("%s/%s"%(obs,p))
                         outputFile.cd("%s/%s"%(obs,p))
                         HistDict[obs][p].Write("nominal")
                         for sys in systematics:
				print sys, obs, p
				HistDict_up[obs][p][sys].Write("%sUp"%(sys))
                                HistDict_do[obs][p][sys].Write("%sDown"%(sys))
		

		 outputFile.cd("%s/TTGamma"%(obs))

		 for sys in systematics2:
                        HistDict_up[obs]["TTGamma"][sys].Write("%sUp"%(sys))
                        HistDict_do[obs]["TTGamma"][sys].Write("%sDown"%(sys))

	elif obs=="M3":
		for p in process_signal.keys():	
			 outputFile.mkdir("%s/%s"%(obs,p))
                         outputFile.cd("%s/%s"%(obs,p))
                         HistDict[obs][p].Write("nominal")
                         for sys in systematics:
				print sys, obs, p
				if finalState=="mu" and p=="VJets_Prompt":continue
				# if sys=="Q2" and (("TTGamma" not in p) or ("TTbar" not in p)):continue
				HistDict_up[obs][p][sys].Write("%sUp"%(sys))
				HistDict_do[obs][p][sys].Write("%sDown"%(sys))
		outputFile.cd("%s/TTGamma_Prompt"%(obs))
		for sys in systematics2:
                        HistDict_up[obs]["TTGamma_Prompt"][sys].Write("%sUp"%(sys))
                        HistDict_do[obs]["TTGamma_Prompt"][sys].Write("%sDown"%(sys))
		
		outputFile.cd("%s/TTGamma_NonPrompt"%(obs))
		
		for sys in systematics2:
                        HistDict_up[obs]["TTGamma_NonPrompt"][sys].Write("%sUp"%(sys))
                        HistDict_do[obs]["TTGamma_NonPrompt"][sys].Write("%sDown"%(sys))
        else:

                for p in process_DDtemplates.keys():
                        outputFile.mkdir("%s/%s"%(obs,p))
                        outputFile.cd("%s/%s"%(obs,p))
			
		
                        HistDict[obs][p].Write("nominal")
			if "_DD" in p:
				HistDict_up["ChHad"][p]["shapeDD"].Write("shapeDDUp")
				HistDict_do["ChHad"][p]["shapeDD"].Write("shapeDDDown")
			
		
                        for sys in systematics:
				if "_DD" in p:continue
                                print sys, obs, p
				if finalState=="mu" and p=="VJets_Prompt":continue
				HistDict_up[obs][p][sys].Write("%sUp"%(sys))
				HistDict_do[obs][p][sys].Write("%sDown"%(sys))
		
		outputFile.cd("%s/TTGamma_Prompt"%(obs))
	  	for sys in systematics2:
                        HistDict_up[obs]["TTGamma_Prompt"][sys].Write("%sUp"%(sys))
                        HistDict_do[obs]["TTGamma_Prompt"][sys].Write("%sDown"%(sys))



outputFile.Close()
##make DataDriven templates root file with actual data###
if TightSelection:
        outputFile = TFile("Combine_withDDTemplateData_v2_%s_tight.root"%(finalState),"recreate")

else:
        outputFile = TFile("Combine_withDDTemplateData_v2_%s.root"%(finalState),"recreate")




for obs in observables:
	if obs=="AntiSIEIE":continue
        outputFile.mkdir("%s/%s"%(obs,"data_obs"))
        outputFile.cd("%s/%s"%(obs,"data_obs"))
	if finalState=="mu":
		if obs=="M3_control":
			HistDict[obs]["data"]=_file["DataMu"].Get("presel_%s_DataMu"%(observables[obs][0])).Clone("%s_DataMu"%(obs))
			HistDict[obs]["data"].Rebin(10)
			HistDict[obs]["data"].Write("nominal")
		else:
			HistDict[obs]["data"]=_file["DataMu"].Get("phosel_%s_barrel_DataMu"%(observables[obs][0])).Clone("%s_DataMu"%(obs))
			if obs=="M3":
				HistDict[obs]["data"].Rebin(10)
			else:
				HistDict[obs]["data"]=HistDict[obs]["data"].Rebin(21,"",array('d',binsChHad))
        		HistDict[obs]["data"].Write("nominal")
	else:
		if obs=="M3_control":
                        HistDict[obs]["data"]=_file["DataEle"].Get("presel_%s_DataEle"%(observables[obs][0])).Clone("%s_DataEle"%(obs))
			HistDict[obs]["data"].Rebin(10)
                        HistDict[obs]["data"].Write("nominal")
		else:
			HistDict[obs]["data"]=_file["DataEle"].Get("phosel_%s_barrel_DataEle"%(observables[obs][0])).Clone("%s_DataEle"%(obs))
			if obs=="M3":
                                HistDict[obs]["data"].Rebin(10)
                        else:
                                HistDict[obs]["data"]=HistDict[obs]["data"].Rebin(21,"",array('d',binsChHad))

			HistDict[obs]["data"].Write("nominal")
        outputFile.mkdir(obs)
        if obs=="M3_control":
                 for p in process_control.keys():
                         outputFile.mkdir("%s/%s"%(obs,p))
                         outputFile.cd("%s/%s"%(obs,p))
                         HistDict[obs][p].Write("nominal")
                         for sys in systematics:
                                print sys, obs, p
                                HistDict_up[obs][p][sys].Write("%sUp"%(sys))
                                HistDict_do[obs][p][sys].Write("%sDown"%(sys))


                 outputFile.cd("%s/TTGamma"%(obs))

                 for sys in systematics2:
                        HistDict_up[obs]["TTGamma"][sys].Write("%sUp"%(sys))
                        HistDict_do[obs]["TTGamma"][sys].Write("%sDown"%(sys))

        elif obs=="M3":
                for p in process_signal.keys():
                         outputFile.mkdir("%s/%s"%(obs,p))
                         outputFile.cd("%s/%s"%(obs,p))
                         HistDict[obs][p].Write("nominal")
                         for sys in systematics:
				print sys, obs, p
                                if finalState=="mu" and p=="VJets_Prompt":continue
                                # if sys=="Q2" and (("TTGamma" not in p) or ("TTbar" not in p)):continue
                                HistDict_up[obs][p][sys].Write("%sUp"%(sys))
                                HistDict_do[obs][p][sys].Write("%sDown"%(sys))
                outputFile.cd("%s/TTGamma_Prompt"%(obs))
                for sys in systematics2:
                        HistDict_up[obs]["TTGamma_Prompt"][sys].Write("%sUp"%(sys))
                        HistDict_do[obs]["TTGamma_Prompt"][sys].Write("%sDown"%(sys))

                outputFile.cd("%s/TTGamma_NonPrompt"%(obs))

                for sys in systematics2:
                        HistDict_up[obs]["TTGamma_NonPrompt"][sys].Write("%sUp"%(sys))
                        HistDict_do[obs]["TTGamma_NonPrompt"][sys].Write("%sDown"%(sys))
        else:

                for p in process_DDtemplates.keys():
                        outputFile.mkdir("%s/%s"%(obs,p))
                        outputFile.cd("%s/%s"%(obs,p))


                        HistDict[obs][p].Write("nominal")
                        if "_DD" in p:
                                HistDict_up["ChHad"][p]["shapeDD"].Write("shapeDDUp")
                                HistDict_do["ChHad"][p]["shapeDD"].Write("shapeDDDown")


                        for sys in systematics:
                                if "_DD" in p:continue
                                print sys, obs, p
                                if finalState=="mu" and p=="VJets_Prompt":continue
                                HistDict_up[obs][p][sys].Write("%sUp"%(sys))
                                HistDict_do[obs][p][sys].Write("%sDown"%(sys))

                outputFile.cd("%s/TTGamma_Prompt"%(obs))
                for sys in systematics2:
                        HistDict_up[obs]["TTGamma_Prompt"][sys].Write("%sUp"%(sys))
                        HistDict_do[obs]["TTGamma_Prompt"][sys].Write("%sDown"%(sys))



outputFile.Close()

