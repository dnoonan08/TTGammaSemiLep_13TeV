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

(options, args) = parser.parse_args()

finalState = options.channel
isTightSelection = options.isTightSelection
isLooseSelection = options.isLooseSelection

if finalState=="Mu":
    if isTightSelection:
        _file  = TFile("histograms/mu/qcdhistsCR_Tight.root","update")
    elif isTightSelection:
        _file  = TFile("histograms/mu/qcdhistsCR_Loose.root","update")
    else:
        _file  = TFile("histograms/mu/qcdhistsCR.root","update")

if finalState=="Ele":
    if isTightSelection:
        _file  = TFile("histograms/ele/qcdhistsCR_Tight.root","update")
    elif isTightSelection:
        _file  = TFile("histograms/ele/qcdhistsCR_Loose.root","update")
    else:
        _file  = TFile("histograms/ele/qcdhistsCR.root","update")



if 'CR2' in sys.argv:
    _file  = TFile("histograms/mu/qcdhistsCR2.root","update")


from sampleInformation import *

gROOT.SetBatch(True)
channel = "Mu"
_file.rmdir("QCDMu_DD")


sampleList.pop(-2)
stackList = sampleList[:-1]

# stackList.remove("WJets")
stackList.reverse()

keylist = _file.GetListOfKeys()

histoList = {}

key = _file.FindKey("DataMu")
print key
list2 = key.ReadObj().GetListOfKeys()

for l in list2:
    name = l.GetName()
    split = name.split('_')
    nameKey = split[0]

    for n in split[1:-1]: nameKey += "_%s"%n
#    nameKey = "%s_%s"%(split[0],split[1])
    hName = "%s_QCD_DD"%(nameKey)
    histoList[nameKey] = l.ReadObj().Clone(hName)
    histoList[nameKey].SetNameTitle(hName,hName)

for key in keylist:
    print key
    if "Data" in key.GetName() or "QCD" in key.GetName():
        continue

    list2 = key.ReadObj().GetListOfKeys()

    for l in list2:
        name = l.GetName()
        split = name.split('_')
#        nameKey = "%s_%s"%(split[0],split[1])
        nameKey = split[0]
#        print split[1:-1]
        for n in split[1:-1]: nameKey += "_%s"%n
        tempHist = l.ReadObj()
        histoList[nameKey].Add(tempHist,-1)


_file.rmdir("QCD_DD")
_file.mkdir("QCD_DD")
_file.cd("QCD_DD")
for h in histoList:
    histoList[h].Write()



