
# samples = []

# for year in [2016, 2017, 2018]:
#     with open('sampleList_%i.sh'%year,'r') as _file:
#         for line in _file:
#             if len(line)<10: continue
#             sample = line.split('_%i='%year)[0]

#             if not sample in samples:
#                 samples.append(sample)
    # for x in unUsed:
    #     if len(x)>1:
    #         sample = x.split('/')[-1]
    #         sType = sample.split('_%i_skim'%year)[0]
    #         if 'ext' in sample:
    #             sType = sample.split('_ext')[0]
    #         if not sType in newSamples:
    #             newSamples.append(sType)

# print(samples)

samples = ['DYjetsM10to50', 'DYjetsM50', 'Data_SingleEle_b', 'Data_SingleEle_c', 'Data_SingleEle_d', 'Data_SingleEle_e', 'Data_SingleEle_f', 'Data_SingleEle_g', 'Data_SingleEle_h', 'Data_SingleMu_b', 'Data_SingleMu_c', 'Data_SingleMu_d', 'Data_SingleMu_e', 'Data_SingleMu_f', 'Data_SingleMu_g', 'Data_SingleMu_h', 'GJets_HT40To100', 'GJets_HT100To200', 'GJets_HT200To400', 'GJets_HT400To600', 'GJets_HT600ToInf', 'QCD_Pt20to30_Ele', 'QCD_Pt30to50_Ele', 'QCD_Pt50to80_Ele', 'QCD_Pt80to120_Ele', 'QCD_Pt120to170_Ele', 'QCD_Pt170to300_Ele', 'QCD_Pt300toInf_Ele', 'QCD_Pt20to30_Mu', 'QCD_Pt30to50_Mu', 'QCD_Pt50to80_Mu', 'QCD_Pt80to120_Mu', 'QCD_Pt120to170_Mu', 'QCD_Pt170to300_Mu', 'QCD_Pt300to470_Mu', 'QCD_Pt470to600_Mu', 'QCD_Pt600to800_Mu', 'QCD_Pt800to1000_Mu', 'QCD_Pt1000toInf_Mu', 'ST_s_channel', 'ST_tW_channel', 'ST_tbarW_channel', 'ST_tbar_channel', 'ST_t_channel', 'TGJets', 'TTGamma_Dilepton', 'TTGamma_Dilepton_Pt100', 'TTGamma_Dilepton_Pt200', 'TTGamma_Dilepton_small', 'TTGamma_Hadronic', 'TTGamma_Hadronic_Pt100', 'TTGamma_Hadronic_Pt200', 'TTGamma_Hadronic_small', 'TTGamma_SingleLept', 'TTGamma_SingleLept_Pt100', 'TTGamma_SingleLept_Pt200', 'TTGamma_SingleLept_small', 'TTWtoLNu', 'TTWtoQQ', 'TTZtoLL', 'TTZtoLL_M1to10', 'TTZtoQQ', 'TTbarPowheg_Dilepton', 'TTbarPowheg_Hadronic', 'TTbarPowheg_Semilept', 'W1jets', 'W2jets', 'W3jets', 'W4jets', 'WGamma_01J_5f', 'ZGamma_01J_5f_lowMass', 'ZGamma_01J_5f_LoosePt', 'WW', 'WZ', 'ZZ', 'WWToLNuQQ', 'WWTo4Q', 'WZTo1L3Nu', 'WZTo1L1Nu2Q', 'WZTo2L2Q', 'WZTo3L1Nu', 'ZZTo2L2Q', 'ZZTo2Q2Nu', 'ZZTo4L', 'VVTo2L2Nu', 'Data_SingleEle_a', 'Data_SingleMu_a']

samples += ['TTGamma_Dilepton_TuneDown', 'TTGamma_Dilepton_TuneUp', 'TTGamma_Dilepton_erdOn', 'TTGamma_SingleLept_TuneDown', 'TTGamma_SingleLept_TuneUp', 'TTGamma_SingleLept_erdOn', 'VVTo2L2Nu_amcatnlo', 'WGamma', 'WWTo1L1Nu2Q_amcatnlo', 'WWTo2L2Nu_powheg', 'WWTo4Q_powheg', 'WWToLNuQQ_powheg', 'WZTo1L1Nu2Q_amcatnlo', 'WZTo1L3Nu_amcatnlo', 'WZTo2L2Q_amcatnlo', 'WZTo3LNu_powheg', 'ZGamma_01J_LoosePt', 'ZGamma_01J_lowMLL_lowGPt', 'ZZTo2L2Nu_powheg', 'ZZTo2L2Q_powheg', 'ZZTo2Q2Nu_amcatnlo', 'ZZTo2Q2Nu_powheg', 'ZZTo4L_powheg', 'ZZTo2L2Q_amcatnlo', 'ZZTo4L_amcatnlo', 'WZTo3LNu_amcatnlo']

samples.sort()

newSamples = []

import subprocess
import sys

yearVal = 2016
if len(sys.argv)==2:
    arg = sys.argv[1]
    if arg.isdigit():
        yearVal = int(arg)

directory = '/store/user/lpctop/TTGamma_FullRun2/Skims_v6/'

for year in [yearVal]:
    fileList = subprocess.Popen('xrdfs root://cmseos.fnal.gov/ ls %s%i'%(directory, year),shell=True,stdout=subprocess.PIPE).communicate()[0].split('\n')
    newSamples = []
    for x in fileList:
        if len(x)>1:
            sample = x.split('/')[-1]
            sType = sample.split('_%i_skim'%year)[0]
            if 'ext' in sample:
                sType = sample.split('_ext')[0]
            if not sType in newSamples:
                newSamples.append(sType)

    newSamples.sort()
    samples = newSamples[:]
    unUsed = fileList[:]
    
    #print(unUsed)
    for s in samples:
        line = '%s_%i="'%(s, year)
        hasAny=False
        sType = '%s%i/%s_%i'%(directory, year, s,year)
        sType_ext = '%s%i/%s_ext'%(directory, year, s)
        for f in fileList:
            if f.startswith(sType) or f.startswith(sType_ext):
                #print(s,f)
                # if '%s_Pt'%s in f: continue
                # if '%s_Tune'%s in f: continue
                # if '%s_erd'%s in f: continue
                hasAny=True
                unUsed.remove(f)
                line += 'root://cmseos.fnal.gov/%s '%(f)
        line = line[:-1] + '"\n'
        if hasAny:
            print(line)
    
    # for x in unUsed:
    #     if len(x)>1:
    #         sample = x.split('/')[-1]
    #         sType = sample.split('_%i_skim'%year)[0]
    #         if 'ext' in sample:
    #             sType = sample.split('_ext')[0]
    #         if not sType in newSamples:
    #             newSamples.append(sType)
    
    
    # print(newSamples)


