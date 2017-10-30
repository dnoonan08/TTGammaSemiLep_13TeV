from ROOT import *
import os

import sys


padRatio = 0.25
padOverlap = 0.15
padGap = 0.01

_file  = TFile("histograms/mu/qcdhistsCR.root","update")

isTight = False

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
list2 = key.ReadObj().GetListOfKeys()

for l in list2:
    name = l.GetName()
    split = name.split('_')
    nameKey = "%s_%s"%(split[0],split[1])
    hName = "%s_%s_QCD%s"%(split[0],split[1],channel)
    histoList[nameKey] = l.ReadObj().Clone(hName)
    histoList[nameKey].SetNameTitle(hName,hName)
    # histoList[nameKey].Reset()
    # histoList[nameKey].SetMarkerStyle(20)
    # histoList[nameKey].SetLineWidth(1)
    # histoList[nameKey].SetLineColor(kBlack)
    # histoList[nameKey].SetMarkerColor(kBlack)

for key in keylist:

    if "Data" in key.GetName() or "QCD" in key.GetName():
        continue

    list2 = key.ReadObj().GetListOfKeys()

    for l in list2:
        name = l.GetName()
        split = name.split('_')
        nameKey = "%s_%s"%(split[0],split[1])
        tempHist = l.ReadObj()
        histoList[nameKey].Add(tempHist,-1)


_file.mkdir("QCDMu_DD")
_file.cd("QCDMu_DD")
for h in histoList:
    histoList[h].Write()

