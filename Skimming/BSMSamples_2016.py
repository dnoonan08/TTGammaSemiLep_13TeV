#MCType='RunIISummer16NanoAODv5-PUMoriond17_Nano1June2019_102X_mcRun2_asymptotic_v7-v1'
#MCType='RunIISummer16NanoAODv6-PUMoriond17_Nano25Oct2019_102X_mcRun2_asymptotic_v7-v1'
MCType='RunIISummer16NanoAODv7-PUMoriond17_Nano02Apr2020_102X_mcRun2_asymptotic_v8-v1'
MCType_ext1=MCType.replace('-v1','_ext1-v1')
MCType_ext2=MCType.replace('-v1','_ext2-v1')
MCType_ext3=MCType.replace('-v1','_ext3-v1')
MCType_noPULabel = MCType.replace('PUMoriond17_','')

MCType_v2 = MCType.replace('-v1','-v2')

DataType='Nano1June2019-v1'
DataType_ver2='_ver2-Nano1June2019_ver2-v1'

sampleList_2016 = {
'TstarTstarToTgammaTgluon_M800'  : '/TstarTstarToTgammaTgluon_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M900'  : '/TstarTstarToTgammaTgluon_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M1000' : '/TstarTstarToTgammaTgluon_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M1100' : '/TstarTstarToTgammaTgluon_M-1100_TuneCUETP8M1_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M1200' : '/TstarTstarToTgammaTgluon_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M1300' : '/TstarTstarToTgammaTgluon_M-1300_TuneCUETP8M1_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M1400' : '/TstarTstarToTgammaTgluon_M-1400_TuneCUETP8M1_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M1500' : '/TstarTstarToTgammaTgluon_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
'TstarTstarToTgammaTgluon_M1600' : '/TstarTstarToTgammaTgluon_M-1600_TuneCUETP8M1_13TeV-madgraph-pythia8/'+MCType+'/NANOAODSIM',
}
