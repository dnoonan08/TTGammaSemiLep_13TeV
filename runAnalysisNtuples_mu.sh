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
if [ "$jobType" == "QCD" ] ;	then
	channel="qcdmu"
	channelDir="qcdmuons"
	tupleExtraName1="QCDcr_"
	tupleExtraName2=""
fi
if [ "$jobType" == "Dilep" ] ;	then
	channel="dimu"
	channelDir="dimuons"
	tupleExtraName1="Dilep_"
	tupleExtraName2="__Dilep"
fi


inputdir="root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_skims/${channelDir}/V08_00_26_07/"
outputdir="root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/${channelDir}/V08_00_26_07/."


sampleType=("TTGamma_SingleLeptFromTbar" \
"TTGamma_SingleLeptFromT" \
"TTGamma_Dilepton" \
"TTGamma_Hadronic" \
"TTbarPowheg" \
"TTbarMadgraph_SingleLeptFromT" \
"TTbarMadgraph_SingleLeptFromTbar" \
"TTbarMadgraph_Dilepton" \
"TGJets" \
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
"WW" \
"WZ" \
"ZZ" \
"QCD_Pt20to30_Mu" \
"QCD_Pt30to50_Mu" \
"QCD_Pt50to80_Mu" \
"QCD_Pt80to120_Mu" \
"QCD_Pt120to170_Mu" \
"QCD_Pt170to300_Mu" \
"QCD_Pt300to470_Mu" \
"QCD_Pt470to600_Mu" \
"QCD_Pt600to800_Mu" \
"QCD_Pt800to1000_Mu" \
"QCD_Pt1000toInf_Mu" \
"Data_SingleEle_b" \
"Data_SingleEle_c" \
"Data_SingleEle_d" \
"Data_SingleEle_e" \
"Data_SingleEle_f" \
"Data_SingleEle_g" \
"Data_SingleEle_h")



echo "AnalysisNtuple/makeAnalysisNtuple ${sampleType[job]}${tupleExtraName2} . ${inputdir}${sampleType[job]}_skim.root"
#AnalysisNtuple/makeAnalysisNtuple ${sampleType[job]}${tupleExtraName2} . ${inputdir}${sampleType[job]}_skim.root

echo "xrdcp -f ${tupleExtraName1}${sampleType[job]}_AnalysisNtuple.root ${outputdir}"
#xrdcp -f ${tupleExtraName1}${sampleType[job]}_AnalysisNtuple.root ${outputdir}
