from ROOT import *
import os
import sys
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-c", "--channel", dest="channel", default="Mu",type='str',
                     help="Specify which channel Mu or Ele? default is Mu" )
parser.add_option("--Tight","--tight", dest="isTightSelection", default=False,action="store_true",
                     help="Use 4j2t selection" )
parser.add_option("--Loose","--loose", dest="isLooseSelection", default=False,action="store_true",
                     help="Use 2j0t selection" )
parser.add_option("-f","--file",dest="fileDir",default="histograms/mu/qcdhistsCR",
                     help="histogram file direcotry")

(options, args) = parser.parse_args()

finalState = options.channel
isTightSelection = options.isTightSelection
isLooseSelection = options.isLooseSelection

_fileDir = options.fileDir


# if finalState=="Mu":
#     if isTightSelection:
#         _file  = TFile("histograms/mu/qcdhistsCR_Tight.root","update")
#     elif isTightSelection:
#         _file  = TFile("histograms/mu/qcdhistsCR_Loose.root","update")
#     else:
#         _file  = TFile("histograms/mu/qcdhistsCR.root","update")

# if finalState=="Ele":
#     if isTightSelection:
#         _file  = TFile("histograms/ele/qcdhistsCR_Tight.root","update")
#     elif isTightSelection:
#         _file  = TFile("histograms/ele/qcdhistsCR_Loose.root","update")
#     else:
#         _file  = TFile("histograms/ele/qcdhistsCR.root","update")



# if 'CR2' in sys.argv:
#     _file  = TFile("histograms/mu/qcdhistsCR2.root","update")


from sampleInformation import *

stackList = sampleList[:-3]

_file = {}
for sample in stackList:
	print sample, "%s/%s.root"%(_fileDir,sample)
	_file[sample] = TFile("%s/%s.root"%(_fileDir,sample),"read")

if finalState=='Ele':
	sample = "DataEle"
	_file[sample] = TFile("%s/%s.root"%(_fileDir,sample),"read")
if finalState=='Mu':
	sample = "DataMu"
	_file[sample] = TFile("%s/%s.root"%(_fileDir,sample),"read")


gROOT.SetBatch(True)
#_file["Data%s"%finalState].cd("Data%s"%finalState)

#keylist = gDirectory.GetListOfKeys()
keylist = _file["Data%s"%finalState].GetListOfKeys()	
print keylist

histoList = {}
#print stackList
for key in keylist:
     
    name = key.GetName()
    print name
    split = name.split('_')
    nameKey = split[0]
#    print split, nameKey, split[1:-1]

    for n in split[1:-1]: nameKey += "_%s"%n

    hName = "%s_QCD_DD"%(nameKey)
    print hName
   # histoList[nameKey] = key.ReadObj().Clone(hName)
    histoList[nameKey]= _file["Data%s"%finalState].Get("%s_%s"%(nameKey,"Data%s"%finalState))
    histoList[nameKey].SetNameTitle(hName,hName)

    for sample in stackList:
	print "%s_%s"%(nameKey,sample)
        tempHist = _file[sample].Get("%s_%s"%(nameKey,sample))
        histoList[nameKey].Add(tempHist,-1)

outputFile = TFile("%s/QCD_DD.root"%_fileDir,"recreate")

for h in histoList:
    histoList[h].Write()

outputFile.Close()

