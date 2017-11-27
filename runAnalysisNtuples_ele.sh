#!/bin/bash
job=$1

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
#	echo "xrdcp -r root://cmseos.fnal.gov//store/user/dnoonan/DataPUfiles_2016 ."
#	xrdcp -r root://cmseos.fnal.gov//store/user/dnoonan/DataPUfiles_2016 .
	xrdcp -r root://cmseos.fnal.gov//store/user/dnoonan/Data_Pileup.tgz .
	tar -xvf Data_Pileup.tgz
	sleep 5
	ls
fi

eval `scramv1 runtime -sh`

inputdir="root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_skims/electrons/V08_00_26_07/"
outputdir="root://cmseos.fnal.gov//store/user/lpctop/TTGamma/13TeV_AnalysisNtuples/electrons/V08_00_26_07/"



files=("TTGamma_SingleLeptFromTbar_" \
"TTGamma_SingleLeptFromT_" \
"TTGamma_Dilepton_" \
"TTGamma_Hadronic_" \
"TTbarPowheg_" \
"TTbarMadgraph_SingleLeptFromT_" \
"TTbarMadgraph_SingleLeptFromTbar_" \
"TTbarMadgraph_Dilepton_" \
"TGJets_" \
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
"QCD_Pt20to30_Ele_" \
"QCD_Pt30to50_Ele_" \
"QCD_Pt50to80_Ele_" \
"QCD_Pt80to120_Ele_" \
"QCD_Pt120to170_Ele_" \
"QCD_Pt170to300_Ele_" \
"QCD_Pt300toInf_Ele_" \
"Data_SingleEle_b_" \
"Data_SingleEle_c_" \
"Data_SingleEle_d_" \
"Data_SingleEle_e_" \
"Data_SingleEle_f_" \
"Data_SingleEle_g_" \
"Data_SingleEle_h_")




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
"QCD_Pt20to30_Ele" \
"QCD_Pt30to50_Ele" \
"QCD_Pt50to80_Ele" \
"QCD_Pt80to120_Ele" \
"QCD_Pt120to170_Ele" \
"QCD_Pt170to300_Ele" \
"QCD_Pt300toInf_Ele" \
"Data_SingleEle_b" \
"Data_SingleEle_c" \
"Data_SingleEle_d" \
"Data_SingleEle_e" \
"Data_SingleEle_f" \
"Data_SingleEle_g" \
"Data_SingleEle_h")



echo "AnalysisNtuple/makeAnalysisNtuple ${sampleType[job]} . ${inputdir}${files[job]}skim.root"
AnalysisNtuple/makeAnalysisNtuple ${sampleType[job]} . ${inputdir}${files[job]}skim.root

echo "xrdcp -f ${files[job]}AnalysisNtuple.root ${outputdir}/."
xrdcp -f ${files[job]}AnalysisNtuple.root ${outputdir}/.
