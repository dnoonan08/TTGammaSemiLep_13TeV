#!/bin/bash

job=$1
jobType=$2

if [ -z ${_CONDOR_SCRATCH_DIR} ] ; then 
	echo "Running Interactively" ; 
else
	echo "Running In Batch"
	cd ${_CONDOR_SCRATCH_DIR}
	echo ${_CONDOR_SCRATCH_DIR}
	echo "xrdcp root://cmseos.fnal.gov//store/user/"${USER}"/CMSSW_8_0_26_patch1.tgz ."
	xrdcp root://cmseos.fnal.gov//store/user/${USER}/CMSSW_8_0_26_patch1.tgz .
	echo "tar -xvf CMSSW_8_0_26_patch1.tgz"
	tar -xzf CMSSW_8_0_26_patch1.tgz
	cd CMSSW_8_0_26_patch1/src/
	source /cvmfs/cms.cern.ch/cmsset_default.sh
	cd  TTGammaSemiLep_13TeV/
	echo "xrdcp -r root://cmseos.fnal.gov//store/user/dnoonan/DataPUfiles_2016.tgz ."
	xrdcp -r root://cmseos.fnal.gov//store/user/dnoonan/Data_Pileup.tgz .
	tar -xvf Data_Pileup.tgz
	sleep 5
fi

eval `scramv1 runtime -sh`
channel="mu"
channelDir="muons"
tupleExtraName1=""
tupleExtraName2=""
if [ "$jobType" == "mu" ] ;	then
	channel="mu"
	channelDir="muons"
fi
if [ "$jobType" == "ele" ] ;	then
	channel="ele"
	channelDir="electrons"
fi


outputdir="root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_"

DannyEOS="root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/V08_00_26_07/"
GGNtupleGroupEOSMC="root://cmseos.fnal.gov//store/user/lpcggntuples/ggNtuples/13TeV/mc/V08_00_26_07/"
TitasEOS="root://cmseos.fnal.gov//store/user/troy2012/13TeV_ggNTuples/V08_00_26_07/"
GGNtupleGroupEOSData="root://cmseos.fnal.gov//store/user/lpcggntuples/ggNtuples/13TeV/data/V08_00_26_07/"
LPCtop="root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_ggNTuples/V08_00_26_07/"

inputfiles=($LPCtop"TTGamma_Dilept_TuneCUETP8M2T4_13TeV-madgraph-fsrdown-pythia8.root" \
$LPCtop"TTGamma_Dilept_TuneCUETP8M2T4_13TeV-madgraph-fsrup-pythia8.root" \
$LPCtop"TTGamma_Dilept_TuneCUETP8M2T4_13TeV-madgraph-isrdown-pythia8.root" \
$LPCtop"TTGamma_Dilept_TuneCUETP8M2T4_13TeV-madgraph-isrup-pythia8.root" \
$LPCtop"TTGamma_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnlo-fsrdown-pythia8-pythia8.root" \
$LPCtop"TTGamma_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnlo-fsrup-pythia8-pythia8.root" \
$LPCtop"TTGamma_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnlo-isrdown-pythia8-pythia8.root" \
$LPCtop"TTGamma_SingleLeptFromT_TuneCUETP8M2T4_13TeV-amcatnlo-isrup-pythia8-pythia8.root" \
$LPCtop"TTGamma_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnlo-fsrdown-pythia8-pythia8.root" \
$LPCtop"TTGamma_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnlo-fsrup-pythia8-pythia8.root" \
$LPCtop"TTGamma_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnlo-isrdown-pythia8-pythia8.root" \
$LPCtop"TTGamma_SingleLeptFromTbar_TuneCUETP8M2T4_13TeV-amcatnlo-isrup-pythia8-pythia8.root")


sampleType=("TTGamma_Dilepton_fsrDown" \
"TTGamma_Dilepton_fsrUp" \
"TTGamma_Dilepton_isrDown" \
"TTGamma_Dilepton_isrUp" \
"TTGamma_SingleLeptFromT_fsrDown" \
"TTGamma_SingleLeptFromT_fsrUp" \
"TTGamma_SingleLeptFromT_isrDown" \
"TTGamma_SingleLeptFromT_isrUp" \
"TTGamma_SingleLeptFromTbar_fsrDown" \
"TTGamma_SingleLeptFromTbar_fsrUp" \
"TTGamma_SingleLeptFromTbar_isrDown" \
"TTGamma_SingleLeptFromTbar_isrUp")


echo "AnalysisNtuple/makeSkim ${channel} ${sampleType[job]}_skim.root ${inputfiles[job]}"
AnalysisNtuple/makeSkim ${channel} ${sampleType[job]}_skim.root ${inputfiles[job]}

echo "AnalysisNtuple/makeAnalysisNtuple ${sampleType[job]}${tupleExtraName2} . ${sampleType[job]}_skim.root"
AnalysisNtuple/makeAnalysisNtuple ${sampleType[job]}${tupleExtraName2} . ${sampleType[job]}_skim.root


echo "xrdcp -f ${sampleType[job]}_skim.root ${outputdir}skims/${channelDir}/V08_00_26_07/"
xrdcp -f ${sampleType[job]}_skim.root ${outputdir}skims/${channelDir}/V08_00_26_07/

echo "xrdcp -f ${tupleExtraName1}${sampleType[job]}_AnalysisNtuple.root ${outputdir}AnalysisNtuples/${channelDir}/V08_00_26_07/"
xrdcp -f ${tupleExtraName1}${sampleType[job]}_AnalysisNtuple.root ${outputdir}AnalysisNtuples/${channelDir}/V08_00_26_07/


