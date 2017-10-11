#!/bin/bash

job=$1

if [ -z ${_CONDOR_SCRATCH_DIR} ] ; then 
	echo "Running Interactively" ; 
else
	echo "Running In Batch"
	cd ${_CONDOR_SCRATCH_DIR}
	echo ${_CONDOR_SCRATCH_DIR}

	echo "xrdcp root://cmseos.fnal.gov//store/user/troy2012/CMSSW_8_0_26_patch1.tgz ."
	xrdcp root://cmseos.fnal.gov//store/user/troy2012/CMSSW_8_0_26_patch1.tgz .
	echo "tar -xvf CMSSW_8_0_26_patch1.tgz"
	tar -xzf CMSSW_8_0_26_patch1.tgz
	cd CMSSW_8_0_26_patch1/src/
	source /cvmfs/cms.cern.ch/cmsset_default.sh
	cd  TTGammaSemiLep_13TeV/
fi

eval `scramv1 runtime -sh`




outputdir="root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_"


files=("TTGamma_SingleLeptFromTbar_" \
"TTGamma_SingleLeptFromT_" \
"TTGamma_Dilepton_" \
"TTGamma_Hadronic_" \
"TTbarPowheg_" \
"TTbarMadgraph_SingleLeptFromT_" \
"TTbarMadgraph_SingleLeptFromTbar_" \
"TTbarMadgraph_Dilepton_" \
"W1jets_" \
"W2jets_" \
"W3jets_" \
"W4jets_" \
"DYjetsM10to50_" \
"DYjetsM50_" \
"ST_s-channel_" \
"ST_t-channel_" \
"ST_tbar-channel_" \
"ST_tW-channel_" \
"ST_tbarW-channel_" \
"TTWtoQQ_" \
"TTWtoLNu_" \
"TTZtoLL_" \
"WGamma_" \
"ZGamma_" \
"Data_SingleMu_b_" \
"Data_SingleMu_c_" \
"Data_SingleMu_d_" \
"Data_SingleMu_e_" \
"Data_SingleMu_f_" \
"Data_SingleMu_g_" \
"Data_SingleMu_h_")

DannyEOS="root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/V08_00_26_07/"
GGNtupleGroupEOSMC="root://cmseos.fnal.gov//store/user/lpcggntuples/ggNtuples/13TeV/mc/V08_00_26_07/"
TitasEOS="root://cmseos.fnal.gov//store/user/troy2012/13TeV_ggNTuples/V08_00_26_07/"
GGNtupleGroupEOSData="root://cmseos.fnal.gov//store/user/lpcggntuples/ggNtuples/13TeV/data/V08_00_26_07/"

inputfiles=($DannyEOS"TTGamma_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root" \
$DannyEOS"TTGamma_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root" \
$DannyEOS"TTGamma_Dilept_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root" \
$DannyEOS"TTGamma_Hadronic_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root" \
$GGNtupleGroupEOSMC"TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_1of4.root "$GGNtupleGroupEOSMC"TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_2of4.root "$GGNtupleGroupEOSMC"TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_3of4.root "$GGNtupleGroupEOSMC"TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_4of4.root" \
$DannyEOS"TTJets_SingleLeptFromT_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root" \
$DannyEOS"TTJets_SingleLeptFromTbar_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root" \
$DannyEOS"TTJets_DiLept_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root" \
$GGNtupleGroupEOSMC"W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root" \
$GGNtupleGroupEOSMC"W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root" \
$GGNtupleGroupEOSMC"W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root" \
$GGNtupleGroupEOSMC"W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root" \
$GGNtupleGroupEOSMC"DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_1.root "$GGNtupleGroupEOSMC"DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_2.root" \
$TitasEOS"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_2_1of2.root "$TitasEOS"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_2_1of2.root"
$DannyEOS"ST_s-channel_4f_InclusiveDecays_13TeV-amcatnlo-pythia8.root" \
$DannyEOS"ST_t-channel_top_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1.root" \
$DannyEOS"ST_t-channel_antitop_4f_inclusiveDecays_13TeV-powhegV2-madspin-pythia8_TuneCUETP8M1.root" \
$DannyEOS"ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1.root" \
$DannyEOS"ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1.root" \
$GGNtupleGroupEOSMC"TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root" \
$GGNtupleGroupEOSMC"TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8.root" \
$GGNtupleGroupEOSMC"TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8.root" \
$DannyEOS"WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root" \
$DannyEOS"ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root" \
$GGNtupleGroupEOSData"job_SingleMu_Run2016B_FebReminiAOD.root" \
$GGNtupleGroupEOSData"job_SingleMu_Run2016C_FebReminiAOD.root" \
$GGNtupleGroupEOSData"job_SingleMu_Run2016D_FebReminiAOD.root" \
$GGNtupleGroupEOSData"job_SingleMu_Run2016E_FebReminiAOD.root" \
$GGNtupleGroupEOSData"job_SingleMu_Run2016F_FebReminiAOD.root" \
$GGNtupleGroupEOSData"job_SingleMu_Run2016G_FebReminiAOD.root" \
$GGNtupleGroupEOSData"job_SingleMu_Run2016H_FebReminiAODv2.root "$GGNtupleGroupEOSData"job_SingleMu_Run2016H_FebReminiAODv3.root")





sampleType=("TTGamma_SingleLeptFromTbar" \
"TTGamma_SingleLeptFromT" \
"TTGamma_Dilepton" \
"TTGamma_Hadronic" \
"TTbarPowheg" \
"TTbarMadgraph_SingleLeptFromT" \
"TTbarMadgraph_SingleLeptFromTbar" \
"TTbarMadgraph_Dilepton" \
"W1jets" \
"W2jets" \
"W3jets" \
"W4jets" \
"DYjetsM10to50" \
"DYjetsM50" \
"ST_s-channel" \
"ST_t-channel" \
"ST_tbar-channel" \
"ST_tW-channel" \
"ST_tbarW-channel" \
"TTWtoQQ" \
"TTWtoLNu" \
"TTZtoLL" \
"WGamma" \
"ZGamma" \
"Data_SingleMu_b" \
"Data_SingleMu_c" \
"Data_SingleMu_d" \
"Data_SingleMu_e" \
"Data_SingleMu_f" \
"Data_SingleMu_g" \
"Data_SingleMu_h")



echo "AnalysisNtuple/makeSkim dimu ${files[job]}skim.root ${inputfiles[job]}"
AnalysisNtuple/makeSkim dimu ${files[job]}skim.root ${inputfiles[job]}

echo "AnalysisNtuple/makeAnalysisNtuple ${sampleType[job]}__Dilep . ${files[job]}skim.root"
AnalysisNtuple/makeAnalysisNtuple ${sampleType[job]}__Dilep . ${files[job]}skim.root


echo "xrdcp -f ${files[job]}skim.root ${outputdir}skim_Temp/dimuons/V08_00_26_07/"
xrdcp -f ${files[job]}skim.root ${outputdir}skim_Temp/dimuons/V08_00_26_07/

echo "xrdcp -f Dilep_${files[job]}AnalysisNtuple.root ${outputdir}AnalysisNtuples/BtagDeepCSV/dimuons/"
xrdcp -f Dilep_${files[job]}AnalysisNtuple.root ${outputdir}AnalysisNtuples/BtagDeepCSV/dimuons/


