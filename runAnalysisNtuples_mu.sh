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



inputdir="root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_skim_Temp/dimuons/V08_00_26_07/"
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



echo "AnalysisNtuple/makeAnalysisNtuple ${sampleType[job]}__Dilep . ${inputdir}${files[job]}skim.root"
AnalysisNtuple/makeAnalysisNtuple ${sampleType[job]}__Dilep . ${inputdir}${files[job]}skim.root

echo "xrdcp -f Dilep_${files[job]}AnalysisNtuple.root ${outputdir}AnalysisNtuples/BtagDeepCSV/dimuons/"
xrdcp -f Dilep_${files[job]}AnalysisNtuple.root ${outputdir}AnalysisNtuples/BtagDeepCSV/dimuons/


