#MCType='RunIISummer16NanoAODv5-PUMoriond17_Nano1June2019_102X_mcRun2_asymptotic_v7-v1'
MCType='RunIISummer16NanoAODv6-PUMoriond17_Nano25Oct2019_102X_mcRun2_asymptotic_v7-v1'
MCType_ext1=MCType.replace('-v1','_ext1-v1')
MCType_ext2=MCType.replace('-v1','_ext2-v1')
MCType_ext3=MCType.replace('-v1','_ext3-v1')
MCType_noPULabel = MCType.replace('PUMoriond17_','')

MCType_v2 = MCType.replace('-v1','-v2')

DataType='Nano1June2019-v1'
DataType_ver2='_ver2-Nano1June2019_ver2-v1'

sampleList_2016 = {
'TTGamma_Dilepton'     : '/TTGamma_Dilept_TuneCP5_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_Hadronic'   : '/TTGamma_Hadronic_TuneCP5_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_SingleLept' : '/TTGamma_SingleLept_TuneCP5_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',

'TTGamma_Dilepton_Pt100'  : '/TTGamma_Dilept_ptGamma100-200_TuneCP5_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_Dilepton_Pt200' : '/TTGamma_Dilept_ptGamma200inf_TuneCP5_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',

'TTGamma_SingleLept_Pt100' : '/TTGamma_SingleLept_ptGamma100-200_TuneCP5_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_SingleLept_Pt200' : '/TTGamma_SingleLept_ptGamma200inf_TuneCP5_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',

'TTGamma_Hadronic_Pt100' : '/TTGamma_Hadronic_ptGamma100-200_TuneCP5_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_Hadronic_Pt200' : '/TTGamma_Hadronic_ptGamma200inf_TuneCP5_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',

# 'TTGamma_Dilept_small'   : '/store/user/lpctop/TTGamma/NanoAOD/2016/Dilept',
# 'TTGamma_Hadronic_small' : '/store/user/lpctop/TTGamma/NanoAOD/2016/Had',
# 'TTGamma_SemiLept_small' : '/store/user/lpctop/TTGamma/NanoAOD/2016/SemiLept',

'TTGamma_Dilepton_TuneDown' : '/TTGamma_Dilept_TuneCP5Down_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_Dilepton_TuneUp'   : '/TTGamma_Dilept_TuneCP5Up_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_Dilepton_erdOn'    : '/TTGamma_Dilept_TuneCP5_erdON_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_Dilepton_CR2'      : '/TTGamma_Dilept_TuneCP5CR1_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_Dilepton_CR1'      : '/TTGamma_Dilept_TuneCP5CR2_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',


'TTGamma_SingleLept_TuneDown' : '/TTGamma_SingleLept_TuneCP5Down_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_SingleLept_TuneUp'   : '/TTGamma_SingleLept_TuneCP5Up_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_SingleLept_erdOn'    : '/TTGamma_SingleLept_TuneCP5_erdON_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_SingleLept_CR1'      : '/TTGamma_SingleLept_TuneCP5CR1_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_SingleLept_CR2'      : '/TTGamma_SingleLept_TuneCP5CR2_PSweights_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',


'Data_SingleMu_b' : '/SingleMuon/Run2016B'+DataType_ver2+'/NANOAOD',
'Data_SingleMu_c' : '/SingleMuon/Run2016C-'+DataType+'/NANOAOD',
'Data_SingleMu_d' : '/SingleMuon/Run2016D-'+DataType+'/NANOAOD',
'Data_SingleMu_e' : '/SingleMuon/Run2016E-'+DataType+'/NANOAOD',
'Data_SingleMu_f' : '/SingleMuon/Run2016F-'+DataType+'/NANOAOD',
'Data_SingleMu_g' : '/SingleMuon/Run2016G-'+DataType+'/NANOAOD',
'Data_SingleMu_h' : '/SingleMuon/Run2016H-'+DataType+'/NANOAOD',

'Data_SingleEle_b' : '/SingleElectron/Run2016B'+DataType_ver2+'/NANOAOD',
'Data_SingleEle_c' : '/SingleElectron/Run2016C-'+DataType+'/NANOAOD',
'Data_SingleEle_d' : '/SingleElectron/Run2016D-'+DataType+'/NANOAOD',
'Data_SingleEle_e' : '/SingleElectron/Run2016E-'+DataType+'/NANOAOD',
'Data_SingleEle_f' : '/SingleElectron/Run2016F-'+DataType+'/NANOAOD',
'Data_SingleEle_g' : '/SingleElectron/Run2016G-'+DataType+'/NANOAOD',
'Data_SingleEle_h' : '/SingleElectron/Run2016H-'+DataType+'/NANOAOD',


'TTbarPowheg_Dilepton' : '/TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8/'+MCType+'/NANOAODSIM',
'TTbarPowheg_Hadronic' : '/TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8/'+MCType+'/NANOAODSIM',
'TTbarPowheg_Semilept' : '/TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8/'+MCType+'/NANOAODSIM',


'W1jets'      : '/W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'W2jets'      : '/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'W2jets_ext1' : '/W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType_ext1+'/NANOAODSIM',
'W3jets'      : '/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'W3jets_ext1' : '/W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType_ext1+'/NANOAODSIM',
'W4jets'      : '/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'W4jets_ext1' : '/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType_ext1+'/NANOAODSIM',
'W4jets_ext2' : '/W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType_ext2+'/NANOAODSIM',

'WJetsToQQ'   : '/WJetsToQQ_HT180_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',



'DYjetsM10to50' : '/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'DYjetsM50_ext1' : '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType_ext1+'/NANOAODSIM',
'DYjetsM50_ext2' : '/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType_ext2+'/NANOAODSIM',


'ST_s_channel' : '/ST_s-channel_4f_leptonDecays_TuneCP5_PSweights_13TeV-amcatnlo-pythia8/'+MCType+'/NANOAODSIM',
'ST_t_channel' : '/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/'+MCType+'/NANOAODSIM',
'ST_tbar_channel' : '/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/'+MCType+'/NANOAODSIM',
'ST_tW_channel' : '/ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/'+MCType+'/NANOAODSIM',
'ST_tbarW_channel' : '/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8/'+MCType+'/NANOAODSIM',


'TTWtoQQ' : '/TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/'+MCType+'/NANOAODSIM',
'TTWtoLNu_ext1' : '/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/'+MCType_ext1+'/NANOAODSIM',
'TTWtoLNu_ext2' : '/TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/'+MCType_ext2+'/NANOAODSIM',
'TTZtoLL_ext1' : '/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/'+MCType_ext1+'/NANOAODSIM',
'TTZtoLL_ext2' : '/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/'+MCType_ext2+'/NANOAODSIM',
'TTZtoLL_ext3' : '/TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8/'+MCType_ext3+'/NANOAODSIM',
'TTZtoLL_M1to10' : '/TTZToLL_M-1to10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType_noPULabel+'/NANOAODSIM',
'TTZtoQQ'        : '/TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8/'+MCType+'/NANOAODSIM',

'WW'      : '/WW_TuneCUETP8M1_13TeV-pythia8/'+MCType+'/NANOAODSIM',
'WW_ext1' : '/WW_TuneCUETP8M1_13TeV-pythia8/'+MCType_ext1+'/NANOAODSIM',
'WZ'      : '/WZ_TuneCUETP8M1_13TeV-pythia8/'+MCType+'/NANOAODSIM',
'WZ_ext1' : '/WZ_TuneCUETP8M1_13TeV-pythia8/'+MCType_ext1+'/NANOAODSIM',
'ZZ'      : '/ZZ_TuneCUETP8M1_13TeV-pythia8/'+MCType+'/NANOAODSIM',
'ZZ_ext1' : '/ZZ_TuneCUETP8M1_13TeV-pythia8/'+MCType_ext1+'/NANOAODSIM',

'WWTo1L1Nu2Q_amcatnlo' : '/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/'+MCType+'/NANOAODSIM',
'WWToLNuQQ_powheg' : '/WWToLNuQQ_13TeV-powheg/'+MCType+'/NANOAODSIM',
'WWToLNuQQ_powheg_ext1' : '/WWToLNuQQ_13TeV-powheg/'+MCType_ext1+'/NANOAODSIM',
'WWTo2L2Nu_powheg' : '/WWTo2L2Nu_13TeV-powheg/'+MCType+'/NANOAODSIM',
'WWTo4Q_powheg' : '/WWTo4Q_13TeV-powheg/'+MCType+'/NANOAODSIM',

'WZTo1L3Nu_amcatnlo' : '/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/'+MCType+'/NANOAODSIM',
'WZTo1L1Nu2Q_amcatnlo' : '/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/'+MCType+'/NANOAODSIM',
'WZTo2L2Q_amcatnlo' : '/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/'+MCType+'/NANOAODSIM',
'WZTo3LNu_powheg' : '/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/'+MCType+'/NANOAODSIM',
'WZTo3LNu_powheg_ext1' : '/WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8/'+MCType_ext1+'/NANOAODSIM',

'ZZTo2L2Q_powheg' : '/ZZTo2L2Q_13TeV_powheg_pythia8/'+MCType+'/NANOAODSIM',
'ZZTo2L2Nu_powheg' : '/ZZTo2L2Nu_13TeV_powheg_pythia8/'+MCType+'/NANOAODSIM',
'ZZTo2L2Nu_powheg_ext1' : '/ZZTo2L2Nu_13TeV_powheg_pythia8_ext1/'+MCType+'/NANOAODSIM',
'ZZTo2Q2Nu_amcatnlo' : '/ZZTo2Q2Nu_13TeV_amcatnloFXFX_madspin_pythia8/'+MCType+'/NANOAODSIM',
'ZZTo2Q2Nu_powheg' : '/ZZTo2Q2Nu_13TeV_powheg_pythia8/'+MCType+'/NANOAODSIM',
'ZZTo4L_powheg' : '/ZZTo4L_13TeV_powheg_pythia8/'+MCType+'/NANOAODSIM',

'VVTo2L2Nu_amcatnlo' : '/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/'+MCType+'/NANOAODSIM',
'VVTo2L2Nu_amcatnlo_ext1' : '/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/'+MCType_ext1+'/NANOAODSIM',


'WGamma' : '/WGToLNuG_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'ZGamma_01J_5f_lowMass' : '/ZGToLLG_01J_5f_lowMLL_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/'+MCType+'/NANOAODSIM',

'ZGamma_01J_LoosePt' : '/ZGToLLG_01J_LoosePtlPtg_5f_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/'+MCType+'/NANOAODSIM',

'ZGamma_01J_lowMLL_lowGPt': '/ZGToLLG_01J_5f_lowMLL_lowGPt_TuneCP5_13TeV-amcatnloFXFX-pythia8/'+MCType+'/NANOAODSIM',

'TGJets' : '/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/'+MCType+'/NANOAODSIM',
'TGJets_ext1' : '/TGJets_TuneCUETP8M1_13TeV_amcatnlo_madspin_pythia8/'+MCType_ext1+'/NANOAODSIM',


'GJets_HT40To100'      : '/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'GJets_HT40To100_ext1' : '/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType_ext1+'/NANOAODSIM',
'GJets_HT100To200'      : '/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'GJets_HT100To200_ext1' : '/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType_ext1+'/NANOAODSIM',
'GJets_HT200To400'      : '/GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'GJets_HT200To400_ext1' : '/GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType_ext1+'/NANOAODSIM',
'GJets_HT400To600'     : '/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'GJets_HT400To600_ext1' : '/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType_ext1+'/NANOAODSIM',
'GJets_HT600ToInf'      : '/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'GJets_HT600ToInf_ext1' : '/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/'+MCType_ext1+'/NANOAODSIM',


'QCD_Pt15to20_Mu'         : '/QCD_Pt-15to20_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt20to30_Mu'         : '/QCD_Pt-20to30_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt30to50_Mu'         : '/QCD_Pt-30to50_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt50to80_Mu'         : '/QCD_Pt-50to80_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt80to120_Mu'        : '/QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt80to120_Mu_ext1'   : '/QCD_Pt-80to120_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType_ext1+'/NANOAODSIM',
'QCD_Pt120to170_Mu'       : '/QCD_Pt-120to170_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt170to300_Mu'       : '/QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt170to300_Mu_ext1'  : '/QCD_Pt-170to300_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType_ext1+'/NANOAODSIM',
'QCD_Pt300to470_Mu'       : '/QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt300to470_Mu_ext1'  : '/QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType_ext1+'/NANOAODSIM',
'QCD_Pt300to470_Mu_ext2'  : '/QCD_Pt-300to470_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType_ext2+'/NANOAODSIM',
'QCD_Pt470to600_Mu'       : '/QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt470to600_Mu_ext1'  : '/QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType_ext1+'/NANOAODSIM',
'QCD_Pt470to600_Mu_ext2'  : '/QCD_Pt-470to600_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType_ext2+'/NANOAODSIM',
'QCD_Pt600to800_Mu'       : '/QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt600to800_Mu_ext1'  : '/QCD_Pt-600to800_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType_ext1+'/NANOAODSIM',
'QCD_Pt800to1000_Mu'      : '/QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt800to1000_Mu_ext1' : '/QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType_ext1+'/NANOAODSIM',
'QCD_Pt800to1000_Mu_ext2' : '/QCD_Pt-800to1000_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType_ext2+'/NANOAODSIM',
'QCD_Pt1000toInf_Mu'      : '/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt1000toInf_Mu_ext1' : '/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCUETP8M1_13TeV_pythia8/'+MCType_ext1+'/NANOAODSIM',


'QCD_Pt20to30_Ele'        : '/QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt30to50_Ele'        : '/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt30to50_Ele_ext1'   : '/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8/'+MCType_ext1+'/NANOAODSIM',
'QCD_Pt50to80_Ele'        : '/QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt50to80_Ele_ext1'   : '/QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8/'+MCType_ext1+'/NANOAODSIM',
'QCD_Pt80to120_Ele'       : '/QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt80to120_Ele_ext1'  : '/QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8/'+MCType_ext1+'/NANOAODSIM',
'QCD_Pt120to170_Ele'      : '/QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt120to170_Ele_ext1' : '/QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8/'+MCType_ext1+'/NANOAODSIM',
'QCD_Pt170to300_Ele'      : '/QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt300toInf_Ele'      : '/QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8/'+MCType+'/NANOAODSIM',


}
