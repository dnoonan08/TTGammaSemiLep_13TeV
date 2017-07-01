#!/bin/bash

job=$1

if [ -z ${_CONDOR_SCRATCH_DIR} ] ; then 
	echo "Running Interactively"
else
	echo "Running In Batch"
	cd ${_CONDOR_SCRATCH_DIR}
	echo ${_CONDOR_SCRATCH_DIR}
	echo "tar -xvf CMSSW_8_0_26_patch1.tgz"
	tar -xzf CMSSW_8_0_26_patch1.tgz
	cd CMSSW_8_0_26_patch1/src/
	source /cvmfs/cms.cern.ch/cmsset_default.sh
	cd  TTGammaSemiLep_13TeV/
fi

eval `scramv1 runtime -sh`




inputdir="root://cmseos.fnal.gov//store/user/dnoonan/13TeV_skims/muons/"
outputdir="../../../Ntuples/muons/"
#outputdir="/uscmst1b_scratch/lpc1/3DayLifetime/dnoonan/13TeV_skims/muons/"

files=("TTGamma_SingleLeptFromTbar_" \
"TTGamma_SingleLeptFromT_" \
"TTGamma_Dilepton_" \
"TTGamma_Hadronic_" \
"TTbar_" \
"W1jets_" \
"W2jets_" \
"W3jets_" \
"W4jets_" \
"DYjets_" \
"ST_s-channel_" \
"ST_t-channel_" \
"ST_tbar-channel_" \
"ST_tW-channel_" \
"ST_tbarW-channel_" \
"TTW_" \
"TTZ_" \
"Data_SingleMu_b_" \
"Data_SingleMu_c_" \
"Data_SingleMu_d_" \
"Data_SingleMu_e_" \
"Data_SingleMu_f_" \
"Data_SingleMu_g_" \
"Data_SingleMu_h_")


sampleType=("TTGamma_SingleLeptFromTbar " \
"TTGamma_SingleLeptFromT    " \
"TTGamma_Dilepton           " \
"TTGamma_Hadronic           " \
"TTbarPowheg                " \
"W1jets                     " \
"W2jets                     " \
"W3jets                     " \
"W4jets                     " \
"DYjets                     " \
"ST_s-channel               " \
"ST_t-channel               " \
"ST_tbar-channel            " \
"ST_tW-channel              " \
"ST_tbarW-channel           " \
"TTW                        " \
"TTZ                        " \
"Data                       " \
"Data                       " \
"Data                       " \
"Data                       " \
"Data                       " \
"Data                       " \
"Data                       ")



echo "AnalysisNtuple/makeAnalysisNtuple ${sampleType[job]} ${outputdir}${files[job]}AnalysisNtuple.root ${inputdir}${files[job]}skim.root"

AnalysisNtuple/makeAnalysisNtuple ${sampleType[job]} ${outputdir}${files[job]}AnalysisNtuple.root ${inputdir}${files[job]}skim.root

#echo "xrdcp -f ${outputfiles[job]} ${outputdir}"