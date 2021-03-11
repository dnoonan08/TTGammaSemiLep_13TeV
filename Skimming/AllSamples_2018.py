#MCType='RunIIAutumn18NanoAODv5-Nano1June2019_102X_upgrade2018_realistic_v19-v1'
MCType='RunIIAutumn18NanoAODv7-Nano02Apr2020_102X_upgrade2018_realistic_v21-v1'

MCType_ext1 = MCType.replace('-v1','_ext1-v1')
MCType_ext2 = MCType.replace('-v1','_ext2-v1')
MCType_ext3 = MCType.replace('-v1','_ext3-v1')
MCType_4cores5k = MCType.replace('102X','4cores5k_102X')

MCType_v3 = MCType.replace('-v1','-v3')

DataType='02Apr2020-v1'


sampleList_2018 = {
'TstarTstarToTgammaTgluon_M700'  : '/TstarTstarToTgluonTgamma_M-700_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M800'  : '/TstarTstarToTgluonTgamma_M-800_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M900'  : '/TstarTstarToTgluonTgamma_M-900_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M1000' : '/TstarTstarToTgluonTgamma_M-1000_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
#'TstarTstarToTgammaTgluon_M1100' : '/TstarTstarToTgluonTgamma_M-1100_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M1200' : '/TstarTstarToTgluonTgamma_M-1200_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M1300' : '/TstarTstarToTgluonTgamma_M-1300_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M1400' : '/TstarTstarToTgluonTgamma_M-1400_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M1500' : '/TstarTstarToTgluonTgamma_M-1500_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M1600' : '/TstarTstarToTgluonTgamma_M-1600_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M1700' : '/TstarTstarToTgluonTgamma_M-1700_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M1800' : '/TstarTstarToTgluonTgamma_M-1800_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M1900' : '/TstarTstarToTgluonTgamma_M-1900_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M2000' : '/TstarTstarToTgluonTgamma_M-2000_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',

'TstarTstarToTgluonTgluon_M700'  : '/TstarTstarToTgluonTgluon_M-700_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgluonTgluon_M800'  : '/TstarTstarToTgluonTgluon_M-800_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgluonTgluon_M900'  : '/TstarTstarToTgluonTgluon_M-900_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgluonTgluon_M1000' : '/TstarTstarToTgluonTgluon_M-1000_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
#'TstarTstarToTgluonTgluon_M1100' : '/TstarTstarToTgluonTgluon_M-1100_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgluonTgluon_M1200' : '/TstarTstarToTgluonTgluon_M-1200_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgluonTgluon_M1300' : '/TstarTstarToTgluonTgluon_M-1300_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgluonTgluon_M1400' : '/TstarTstarToTgluonTgluon_M-1400_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgluonTgluon_M1500' : '/TstarTstarToTgluonTgluon_M-1500_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgluonTgluon_M1600' : '/TstarTstarToTgluonTgluon_M-1600_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgluonTgluon_M1700' : '/TstarTstarToTgluonTgluon_M-1700_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgluonTgluon_M1800' : '/TstarTstarToTgluonTgluon_M-1800_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgluonTgluon_M1900' : '/TstarTstarToTgluonTgluon_M-1900_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgluonTgluon_M2000' : '/TstarTstarToTgluonTgluon_M-2000_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',

'TstarTstarToTgammaTgamma_M700'  : '/TstarTstarToTgammaTgamma_M-700_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgamma_M800'  : '/TstarTstarToTgammaTgamma_M-800_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgamma_M900'  : '/TstarTstarToTgammaTgamma_M-900_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgamma_M1000' : '/TstarTstarToTgammaTgamma_M-1000_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
#'TstarTstarToTgammaTgamma_M1100' : '/TstarTstarToTgammaTgamma_M-1100_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgamma_M1200' : '/TstarTstarToTgammaTgamma_M-1200_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgamma_M1300' : '/TstarTstarToTgammaTgamma_M-1300_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgamma_M1400' : '/TstarTstarToTgammaTgamma_M-1400_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgamma_M1500' : '/TstarTstarToTgammaTgamma_M-1500_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgamma_M1600' : '/TstarTstarToTgammaTgamma_M-1600_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgamma_M1700' : '/TstarTstarToTgammaTgamma_M-1700_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgamma_M1800' : '/TstarTstarToTgammaTgamma_M-1800_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgamma_M1900' : '/TstarTstarToTgammaTgamma_M-1900_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgamma_M2000' : '/TstarTstarToTgammaTgamma_M-2000_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',

'TTGamma_Dilepton'     : '/TTGamma_Dilept_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_Hadronic'   : '/TTGamma_Hadronic_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_SingleLept' : '/TTGamma_SingleLept_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',

'TTGamma_Dilepton_Pt100' : '/TTGamma_Dilept_ptGamma100-200_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_Dilepton_Pt200' : '/TTGamma_Dilept_ptGamma200inf_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',

'TTGamma_SingleLept_Pt100' : '/TTGamma_SingleLept_ptGamma100-200_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_SingleLept_Pt200' : '/TTGamma_SingleLept_ptGamma200inf_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',

'TTGamma_Hadronic_Pt100' : '/TTGamma_Hadronic_ptGamma100-200_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_Hadronic_Pt200' : '/TTGamma_Hadronic_ptGamma200inf_TuneCP5_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',

# 'TTGamma_Dilepton_small'   : '/store/user/lpctop/TTGamma/NanoAOD/2018/Dilept',
# 'TTGamma_Hadronic_small' : '/store/user/lpctop/TTGamma/NanoAOD/2018/Had',
# 'TTGamma_SemiLept_small' : '/store/user/lpctop/TTGamma/NanoAOD/2018/SemiLept',

'TTGamma_Dilepton_TuneDown' : '/TTGamma_Dilept_TuneCP5Down_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_Dilepton_TuneUp'   : '/TTGamma_Dilept_TuneCP5Up_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_Dilepton_erdOn'    : '/TTGamma_Dilept_TuneCP5_erdON_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_Dilepton_CR1'      : '/TTGamma_Dilept_TuneCP5CR1_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_Dilepton_CR2'      : '/TTGamma_Dilept_TuneCP5CR2_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',


'TTGamma_SingleLept_TuneDown' : '/TTGamma_SingleLept_TuneCP5Down_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_SingleLept_TuneUp'   : '/TTGamma_SingleLept_TuneCP5Up_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_SingleLept_erdOn'    : '/TTGamma_SingleLept_TuneCP5_erdON_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_SingleLept_CR1'      : '/TTGamma_SingleLept_TuneCP5CR1_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TTGamma_SingleLept_CR2'      : '/TTGamma_SingleLept_TuneCP5CR2_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',


'Data_SingleMu_a' : '/SingleMuon/Run2018A-'+DataType+'/NANOAOD',
'Data_SingleMu_b' : '/SingleMuon/Run2018B-'+DataType+'/NANOAOD',
'Data_SingleMu_c' : '/SingleMuon/Run2018C-'+DataType+'/NANOAOD',
'Data_SingleMu_d' : '/SingleMuon/Run2018D-'+DataType+'/NANOAOD',

'Data_SingleEle_a' : '/EGamma/Run2018A-'+DataType+'/NANOAOD',
'Data_SingleEle_b' : '/EGamma/Run2018B-'+DataType+'/NANOAOD',
'Data_SingleEle_c' : '/EGamma/Run2018C-'+DataType+'/NANOAOD',
'Data_SingleEle_d' : '/EGamma/Run2018D-'+DataType+'/NANOAOD',


'TTbarPowheg_Dilepton' : '/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/'+MCType+'/NANOAODSIM',
'TTbarPowheg_Hadronic' : '/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/'+MCType+'/NANOAODSIM',
'TTbarPowheg_Semilept' : '/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/'+MCType+'/NANOAODSIM',

'TTbarPowheg_Dilepton_ext3' : '/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/'+MCType_ext3+'/NANOAODSIM',
'TTbarPowheg_Hadronic_ext3' : '/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/'+MCType_ext3+'/NANOAODSIM',
'TTbarPowheg_Semilept_ext3' : '/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/'+MCType_ext3+'/NANOAODSIM',


'W1jets'      : '/W1JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'W2jets'      : '/W2JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'W3jets'      : '/W3JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'W4jets'      : '/W4JetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',

'DYjetsM10to50'  : '/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'DYjetsM10to50_ext1'  : '/DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8/'+MCType_ext1+'/NANOAODSIM',
'DYjetsM50'      : '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',


'ST_s_channel'     : '/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-madgraph-pythia8/'+MCType_ext1+'/NANOAODSIM',
'ST_t_channel'     : '/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/'+MCType+'/NANOAODSIM',
'ST_tbar_channel'  : '/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/'+MCType+'/NANOAODSIM',
'ST_tW_channel'    : '/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/'+MCType_ext1+'/NANOAODSIM',
'ST_tbarW_channel' : '/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/'+MCType_ext1+'/NANOAODSIM',


'TTWtoQQ'  : '/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/'+MCType+'/NANOAODSIM',
'TTWtoLNu' : '/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/'+MCType_ext1+'/NANOAODSIM',
'TTZtoLL'  : '/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/'+MCType_ext1+'/NANOAODSIM',
'TTZtoLL_M1to10' : '/TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8/'+MCType+'/NANOAODSIM',
'TTZtoQQ' : '/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8/'+MCType+'/NANOAODSIM',
'TTZtoQQ_ext1' : '/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8/'+MCType_ext1+'/NANOAODSIM',

'WW'      : '/WW_TuneCP5_13TeV-pythia8/'+MCType+'/NANOAODSIM',
'WZ'      : '/WZ_TuneCP5_13TeV-pythia8/'+MCType+'/NANOAODSIM',
'ZZ'      : '/ZZ_TuneCP5_13TeV-pythia8/'+MCType+'/NANOAODSIM',

'WWTo1L1Nu2Q_amcatnlo' : '/WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/'+MCType+'/NANOAODSIM',
'WWToLNuQQ_powheg' : '/WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8/'+MCType+'/NANOAODSIM',
'WWTo2L2Nu_powheg' : '/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/'+MCType+'/NANOAODSIM',
'WWTo4Q_powheg' : '/WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8/'+MCType+'/NANOAODSIM',

'WZTo1L3Nu_amcatnlo' : '/WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8/'+MCType+'/NANOAODSIM',
'WZTo1L1Nu2Q_amcatnlo' : '/WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8/'+MCType+'/NANOAODSIM',
'WZTo2L2Q_amcatnlo' : '/WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/'+MCType+'/NANOAODSIM',
'WZTo3LNu_powheg' : '/WZTo3LNu_TuneCP5_13TeV-powheg-pythia8/'+MCType_ext1+'/NANOAODSIM',
'WZTo3LNu_amcatnlo' : '/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/'+MCType+'/NANOAODSIM',
'WZTo3LNu_amcatnlo_ext1' : '/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/'+MCType_ext1+'/NANOAODSIM',

'ZZTo2L2Q_amcatnlo' : '/ZZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8/'+MCType+'/NANOAODSIM',
'ZZTo2L2Nu_powheg_ext1' : '/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/'+MCType_ext1+'/NANOAODSIM',
'ZZTo2L2Nu_powheg_ext2' : '/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/'+MCType_ext2+'/NANOAODSIM',
'ZZTo2Q2Nu_amcatnlo' : '/ZZTo2Q2Nu_TuneCP5_13TeV_amcatnloFXFX_madspin_pythia8/'+MCType+'/NANOAODSIM',
'ZZTo4L_powheg_ext1' : '/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/'+MCType_ext1+'/NANOAODSIM',
'ZZTo4L_powheg_ext2' : '/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/'+MCType_ext2+'/NANOAODSIM',
'ZZTo4L_amcatnlo' : '/ZZTo4L_TuneCP5_13TeV-amcatnloFXFX-pythia8/'+MCType+'/NANOAODSIM',

'VVTo2L2Nu_amcatnlo' : '/VVTo2L2Nu_13TeV_amcatnloFXFX_madspin_pythia8/'+MCType+'/NANOAODSIM',

'WGamma' : '/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'ZGamma_01J_5f_lowMass' : '/ZGToLLG_01J_5f_lowMLL_TuneCP5_13TeV-amcatnloFXFX-pythia8/'+MCType+'/NANOAODSIM',

'ZGamma_01J_LoosePt' : '/ZGToLLG_01J_LoosePtlPtg_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/'+MCType+'/NANOAODSIM',

'ZGamma_01J_lowMLL_lowGPt': '/ZGToLLG_01J_5f_lowMLL_lowGPt_TuneCP5_13TeV-amcatnloFXFX-pythia8/'+MCType+'/NANOAODSIM',

'TGJets' : '/TGJets_TuneCP5_13TeV_amcatnlo_madspin_pythia8/'+MCType+'/NANOAODSIM',


'GJets_HT40To100'       : '/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'GJets_HT100To200'      : '/GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/'+MCType_4cores5k+'/NANOAODSIM',
'GJets_HT200To400'      : '/GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'GJets_HT400To600'      : '/GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/'+MCType+'/NANOAODSIM',
'GJets_HT600ToInf'      : '/GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/'+MCType_ext1+'/NANOAODSIM',


'QCD_Pt20to30_Mu'         : '/QCD_Pt-20to30_MuEnrichedPt5_TuneCP5_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt30to50_Mu'         : '/QCD_Pt-30to50_MuEnrichedPt5_TuneCP5_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt50to80_Mu'         : '/QCD_Pt-50to80_MuEnrichedPt5_TuneCP5_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt80to120_Mu'        : '/QCD_Pt-80to120_MuEnrichedPt5_TuneCP5_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt80to120_Mu_ext1'   : '/QCD_Pt-80to120_MuEnrichedPt5_TuneCP5_13TeV_pythia8/'+MCType_ext1+'/NANOAODSIM',
'QCD_Pt120to170_Mu'       : '/QCD_Pt-120to170_MuEnrichedPt5_TuneCP5_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt120to170_Mu_ext1'  : '/QCD_Pt-120to170_MuEnrichedPt5_TuneCP5_13TeV_pythia8/'+MCType_ext1+'/NANOAODSIM',
'QCD_Pt170to300_Mu'       : '/QCD_Pt-170to300_MuEnrichedPt5_TuneCP5_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt300to470_Mu'       : '/QCD_Pt-300to470_MuEnrichedPt5_TuneCP5_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt300to470_Mu_ext3'  : '/QCD_Pt-300to470_MuEnrichedPt5_TuneCP5_13TeV_pythia8/'+MCType_ext3+'/NANOAODSIM',
'QCD_Pt470to600_Mu'       : '/QCD_Pt-470to600_MuEnrichedPt5_TuneCP5_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt470to600_Mu_ext1'  : '/QCD_Pt-470to600_MuEnrichedPt5_TuneCP5_13TeV_pythia8/'+MCType_ext1+'/NANOAODSIM',
'QCD_Pt600to800_Mu'       : '/QCD_Pt-600to800_MuEnrichedPt5_TuneCP5_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt800to1000_Mu'      : '/QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5_13TeV_pythia8/'+MCType_ext3+'/NANOAODSIM',
'QCD_Pt1000toInf_Mu'      : '/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5_13TeV_pythia8/'+MCType+'/NANOAODSIM',

'QCD_Pt20to30_Ele'        : '/QCD_Pt-20to30_EMEnriched_TuneCP5_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt30to50_Ele'        : '/QCD_Pt-30to50_EMEnriched_TuneCP5_13TeV_pythia8/'+MCType_ext1+'/NANOAODSIM',
'QCD_Pt50to80_Ele'        : '/QCD_Pt-50to80_EMEnriched_TuneCP5_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt80to120_Ele'       : '/QCD_Pt-80to120_EMEnriched_TuneCP5_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt120to170_Ele'      : '/QCD_Pt-120to170_EMEnriched_TuneCP5_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt170to300_Ele'      : '/QCD_Pt-170to300_EMEnriched_TuneCP5_13TeV_pythia8/'+MCType+'/NANOAODSIM',
'QCD_Pt300toInf_Ele'      : '/QCD_Pt-300toInf_EMEnriched_TuneCP5_13TeV_pythia8/'+MCType+'/NANOAODSIM',


}
