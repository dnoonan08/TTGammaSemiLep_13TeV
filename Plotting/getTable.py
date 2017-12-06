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
(options, args) = parser.parse_args()
finalState = options.channel
print "Running on the %s channel"%(finalState)
if finalState=='Mu':
#        _file  = TFile("histograms/mu/testhist.root")
        _file  = TFile("histograms/mu/hists.root")
        plotDirectory = "plots_mu/"
        regionText = ", N_{j}#geq3, N_{b}#geq1"
        if 'Tight' in sys.argv:
                plotDirectory = "tightplots_mu/"
                _file  = TFile("histograms/mu/hists_tight.root")
                regionText = ", N_{j}#geq4, N_{b}#geq2"
        if 'Loose' in sys.argv:
                plotDirectory = "looseplots_mu/"
                _file  = TFile("histograms/mu_Nov/hists_loose.root")
                regionText = ", N_{j}=2, N_{b}=0"
        if 'LooseCR' in sys.argv:
                plotDirectory = "looseCRplots_mu/"
                _file  = TFile("histograms/mu_Nov/hists_looseCR.root")
                regionText = ", N_{j}#geq2, N_{b}#geq0"

if finalState=="Ele":
	#   _file  = TFile("histograms/ele/hists1.root")
        _file  = TFile("histograms/ele/hists.root")
        plotDirectory = "plots_ele/"
        regionText = ", N_{j}#geq3, N_{b}#geq1"

        if 'Tight' in sys.argv:
                plotDirectory = "tightplots_ele/"
                #_file  = TFile("histograms/ele/hists1_tight.root")
                _file  = TFile("histograms/ele/hists_tight.root")
                regionText = ", N_{j}#geq4, N_{b}#geq2"
        if 'Loose' in sys.argv:
                plotDirectory = "looseplots_ele/"
                _file  = TFile("histograms/ele/hists_loose.root")
                regionText = ", N_{j}=2, N_{b}=0"
        if 'LooseCR' in sys.argv:
                plotDirectory = "looseCRplots_ele/"
                _file  = TFile("histograms/ele/hists_looseCR.root")
                regionText = ", N_{j}#geq2, N_{b}#geq0"



list_ = ['TTGamma', 'TTbar', 'TGJets','ST-tW','ST-tch','ST-sch', 'WGamma','ZGamma','WJets', 'ZJets', 'TTV']
#list_=["ZGamma"]
gROOT.SetBatch(True)

yield_ = {}
err_ = {}
sum_s = {}
err_s = {}

for l in list_:
	yield_[l] = []
	err_[l] = []
	sum_s[l] = []
	err_s[l] = []
# yield_ ={'TTGamma':[],
# 	 'TTbar':[],
# 	 'ST_tW': [],
# 	 'ST_tch': [],
# 	 'ST_sch': [],
# 	 'WGamma':  [],
# 	 'ZGamma': [],
# 	 'WJets' : [],
# 	 'ZJets' : [],
# 	 'TTV': [],
# 	 'TGJets': [],
# 	 }


# err_={'TTGamma':[],
#       'TTbar':[],
#       'SingleTop': [],
#       'WGamma':  [],
#       'ZGamma': [],
#       'WJets' : [],
#       'ZJets' : [],
#       'TTV': [],
#       'TGJets': [],
#       }

# sum_s= {'TTGamma':[],
# 	'TTbar':[],
# 	'SingleTop': [],
# 	'WGamma':  [],
# 	'ZGamma': [],
# 	'WJets' : [],
# 	'ZJets' : [],
# 	'TTV': [],
# 	'TGJets': [],
# 	}

# err_s= {'TTGamma':[],
# 	'TTbar':[],
# 	'SingleTop': [],
# 	'WGamma':  [],
# 	'ZGamma': [],
# 	'WJets' : [],
# 	'ZJets' : [],
# 	'TTV': [],
# 	'TGJets': [],
# 	}

hist_= ["phosel_NGenuinePho", "phosel_NMisIDEle","phosel_NHadronicPho","phosel_NHadronicFake"]
for sample in list_:
	hist=_file.Get("%s/phosel_PhotonCategory_%s"%(sample,sample))	
	for i in range(1,5):
                err = Double(0.0)
                err_[sample].append(err)            
        	yield_[sample].append(float(hist.IntegralAndError(i,i,err)))

sum_=[]
total_=0
totalerr=0.0
for sample in list_:
	
	sum_s[sample].append(yield_[sample][0]+yield_[sample][1]+yield_[sample][2]+yield_[sample][3])
	err_s[sample].append(((err_[sample][0])**2+(err_[sample][1])**2+(err_[sample][2])**2+(err_[sample][3])**2)**0.5)
for sample in list_:
	total_+=sum_s[sample][0]
	totalerr+= err_s[sample][0]**2

error=0.
error= (totalerr)**.5
#for i in range(9):
#	total_+=sum_[i]

genuine_=0
genuineerr=0.
misID_=0
misIDerr=0.
HadPho_=0
HadPhoerr=0.
HadFake_=0
HadFakeerr=0.
for sample in list_:
	genuine_+=yield_[sample][0]
        misID_+=yield_[sample][1]
        HadPho_+=yield_[sample][2]
        HadFake_+=yield_[sample][3]
        genuineerr+=(err_[sample][0])**2
        misIDerr+=(err_[sample][1])**2
        HadPhoerr+=(err_[sample][2])**2
        HadFakeerr+=(err_[sample][3])**2

genuine_error=genuineerr**0.5
misID_error=misIDerr**0.5
HadPho_error=HadPhoerr**0.5
HadFake_error=HadFakeerr**0.5
percentage=[]
percentage.append((genuine_/total_)*100)
percentage.append((misID_/total_)*100)
percentage.append((HadPho_/total_)*100)
percentage.append((HadFake_/total_)*100)

percentage_err=[]
percentage_err.append((genuine_error/total_)*100)
percentage_err.append((misID_error/total_)*100)
percentage_err.append((HadPho_error/total_)*100)
percentage_err.append((HadFake_error/total_)*100)

table=''
table +=  '\\begin{tabular}{l | c c c c | c r} \n'
table +=  '\\hline\n'
table +=  'Sample & GenuinePhoton & MisIDEle & HadronicPho & HadronicFake & Total & Percent \\\\ \n'
table +=  '\\hline\n'
for sample in list_:
	table += '%s & $%.1f \pm %.1f$  & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$ & $%.1f\%%$   \\\\ \n' % (sample, yield_[sample][0], err_[sample][0], yield_[sample][1], err_[sample][1], yield_[sample][2], err_[sample][2], yield_[sample][3], err_[sample][3], sum_s[sample][0], err_s[sample][0],100.*sum_s[sample][0]/total_)

#	total += yield_[sample][0]+yield_[sample][1]+yield_[sample][2]+yield_[sample][3]
#	totalErr += (err_[sample][0]+err_[sample][1]+err_[sample][2]+err_[sample][3])**0.5
table += '\\hline \n'
table += "Totals & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$ &\\\\ \n" %(genuine_,genuine_error,misID_,misID_error,HadPho_,HadPho_error,HadFake_,HadFake_error, total_, error)
table += '\\hline \n'
table += "Percentage & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$ \\\\ \n" % (percentage[0], percentage_err[0],percentage[1], percentage_err[1], percentage[2], percentage_err[2],percentage[3], percentage_err[3])
table += '\\end{tabular} \n'

table = table.replace("$0.0 \pm 0.0$","---")

print table

