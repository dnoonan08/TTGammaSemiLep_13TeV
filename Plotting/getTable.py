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



list_ = ['TTGamma', 'TTbar', 'TGJets','SingleTop', 'WGamma','ZGamma','WJets', 'ZJets', 'TTV']
#list_=["ZGamma"]
gROOT.SetBatch(True)

yield_ ={'TTGamma':[],
                 'TTbar':[],
                 'SingleTop': [],
                 'WGamma':  [],
                 'ZGamma': [],
                 'WJets' : [],
                 'ZJets' : [],
                 'TTV': [],
                 'TGJets': [],
			}


err_={'TTGamma':[],
                 'TTbar':[],
                 'SingleTop': [],
                 'WGamma':  [],
                 'ZGamma': [],
                 'WJets' : [],
                 'ZJets' : [],
                 'TTV': [],
                 'TGJets': [],
                        }

sum_s= {'TTGamma':[],
                 'TTbar':[],
                 'SingleTop': [],
                 'WGamma':  [],
                 'ZGamma': [],
                 'WJets' : [],
                 'ZJets' : [],
                 'TTV': [],
                 'TGJets': [],
                        }
err_s= {'TTGamma':[],
                 'TTbar':[],
                 'SingleTop': [],
                 'WGamma':  [],
                 'ZGamma': [],
                 'WJets' : [],
                 'ZJets' : [],
                 'TTV': [],
                 'TGJets': [],
}
hist_= ["phosel_NGenuinePho", "phosel_NMisIDEle","phosel_NHadronicPho","phosel_NHadronicFake"]
for sample in list_:
#	print sample
        for h in hist_:
 #               print _file, ("%s/%s_%s"%(sample,h,sample))
                hist=_file.Get("%s/%s_%s"%(sample,h,sample))
  #              print hist.Integral(-1,-1)
                err = Double(0.0)
                err_[sample].append(err)            
        	yield_[sample].append(float(hist.IntegralAndError(-1,-1,err)))
                
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
table +=  '\\begin{tabular}{c c c c c c c} \n'
table +=  '\\hline\n'
table +=  'Sample & GenuinePhoton & MisIDEle & HadronicPho & HadronicFake & Total\\\\ \n'
table +=  '\\hline\n'
for sample in list_:
	table += '%s & $%.1f \pm %.1f$  & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$   \\\\ \n' % (sample, yield_[sample][0], err_[sample][0], yield_[sample][1], err_[sample][1], yield_[sample][2], err_[sample][2], yield_[sample][3], err_[sample][3], sum_s[sample][0], err_s[sample][0])

#	total += yield_[sample][0]+yield_[sample][1]+yield_[sample][2]+yield_[sample][3]
#	totalErr += (err_[sample][0]+err_[sample][1]+err_[sample][2]+err_[sample][3])**0.5
table += '\\hline \n'
table += "Totals & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$\\\\ \n" %(genuine_,genuine_error,misID_,misID_error,HadPho_,HadPho_error,HadFake_,HadFake_error, total_, error)
table += '\\hline \n'
table += "Percentage & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$ & $%.1f \\pm %.1f$ \\\\ \n" % (percentage[0], percentage_err[0],percentage[1], percentage_err[1], percentage[2], percentage_err[2],percentage[3], percentage_err[3])
table += '\\end{tabular} \n'


print table

sys.exit()
print " The Number of Photons from different Category and from the different MC"
print " Samples    GenuinePhoton    MisIDEle    HadronicPho    HadronicFake     Total"

print " TTGamma   ", yield_['TTGamma'][0],   yield_['TTGamma'][1],     yield_['TTGamma'][2],    yield_['TTGamma'][3],    sum_[5]

print " TTbar     ", yield_['TTbar'][0],     yield_['TTbar'][1],       yield_['TTbar'][2],      yield_['TTbar'][3],      sum_[1]

print " SingleTop ", yield_['SingleTop'][0], yield_['SingleTop'][1],   yield_['SingleTop'][2],  yield_['SingleTop'][3],  sum_[0]

print " WGamma    ", yield_['WGamma'][0],    yield_['WGamma'][1],      yield_['WGamma'][2],     yield_['WGamma'][3],     sum_[7]

print " ZGamma    ", yield_['ZGamma'][0],    yield_['ZGamma'][1],      yield_['ZGamma'][2],     yield_['ZGamma'][3],     sum_[6]

print " WJets     ", yield_['WJets'][0],     yield_['WJets'][1],       yield_['WJets'][2],      yield_['WJets'][3],      sum_[3]

print " ZJets     ", yield_['ZJets'][0],     yield_['ZJets'][1],       yield_['ZJets'][2],      yield_['ZJets'][3],      sum_[4]

print " TG        ", yield_['TG'][0],        yield_['TG'][1],          yield_['TG'][2],         yield_['TG'][3],         sum_[8]

print " TTV       ", yield_['TTV'][0],       yield_['TTV'][1],         yield_['TTV'][2],        yield_['TTV'][3],        sum_[2]

print " Total     ", sum2_[0],               sum2_[1],                 sum2_[2],                sum2_[3],                total_
