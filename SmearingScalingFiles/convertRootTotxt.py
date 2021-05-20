import ROOT
import itertools
import numpy


myfile=ROOT.TFile("electron_2016_Res.root","read")
h_up=myfile.Get("pt_eta_ResUp")
h_do=myfile.Get("pt_eta_ResDown")
mymatrix=numpy.ones((5,10), dtype=numpy.int32)
# print(mymatrix)
for ipt,ieta in itertools.product(range(10),range(5)): #ipt=x, ieta=y, 
	# print(ipt,ieta)
	print(h_up.GetBinContent(ipt+1,ieta+1))
	mymatrix[ieta][ipt]=h_up.GetBinContent(ipt+1,ieta+1)
	# print(mymatrix[ieta][ipt])
	# print(h_up.GetBinContent(ipt,ieta))


# print(mymatrix)


# [[0 0 0 0 0 0 0 0 0 0]
#  [0 1 0 1 1 0 1 0 1 1]
#  [0 1 0 1 1 0 1 1 1 1]
#  [0 1 0 0 1 1 1 1 1 1]
#  [0 1 1 0 1 1 1 1 1 0]]
