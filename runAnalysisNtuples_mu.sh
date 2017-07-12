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
outputdir="root://cmseos.fnal.gov//store/user/dnoonan/13TeV_AnalysisNtuples/muons/"

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
"WGamma_" \
"ZGamma_" \
"QCD_20to30EM_" \
"QCD_30to50EM_" \
"QCD_50to80EM_" \
"QCD_80to120EM_" \
"QCD_120to170EM_" \
"QCD_170to300EM_" \
"QCD_300toInfEM_" \
"QCD_20to30Mu_" \
"QCD_30to50Mu_" \
"QCD_50to80Mu_" \
"QCD_80to120Mu_" \
"QCD_120to170Mu_" \
"QCD_170to300Mu_" \
"QCD_300to470Mu_" \
"QCD_470to600Mu_" \
"QCD_600to800Mu_" \
"QCD_800to1000Mu_" \
"QCD_1000toInfMu_" \
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
"WGamma                     " \
"ZGamma                     " \
"QCD_Pt20to30_EM            " \
"QCD_Pt30to50_EM            " \
"QCD_Pt50to80_EM            " \
"QCD_Pt80to120_EM           " \
"QCD_Pt120to170_EM          " \
"QCD_Pt170to300_EM          " \
"QCD_Pt300toInf_EM          " \
"QCD_Pt20to30_Mu            " \
"QCD_Pt30to50_Mu            " \
"QCD_Pt50to80_Mu            " \
"QCD_Pt80to120_Mu           " \
"QCD_Pt120to170_Mu          " \
"QCD_Pt170to300_Mu          " \
"QCD_Pt300to470_Mu          " \
"QCD_Pt470to600_Mu          " \
"QCD_Pt600to800_Mu          " \
"QCD_Pt800to1000_Mu          " \
"QCD_Pt1000toInf_Mu          " \
"Data                       " \
"Data                       " \
"Data                       " \
"Data                       " \
"Data                       " \
"Data                       " \
"Data                       ")


echo "AnalysisNtuple/makeAnalysisNtuple ${sampleType[job]} ${files[job]}AnalysisNtuple.root ${inputdir}${files[job]}skim.root"

AnalysisNtuple/makeAnalysisNtuple ${sampleType[job]} ${files[job]}AnalysisNtuple.root ${inputdir}${files[job]}skim.root

echo "xrdcp -f ${files[job]}AnalysisNtuple.root ${outputdir}/."

xrdcp -f ${files[job]}AnalysisNtuple.root ${outputdir}/.