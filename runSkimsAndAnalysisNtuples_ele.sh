#!/bin/bash

job=$1

if [ -z ${_CONDOR_SCRATCH_DIR} ] ; then 
	echo "Running Interactively" ; 
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




outputdir="root://cmseos.fnal.gov//store/user/dnoonan/13TeV_"


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
"Data_SingleEle_b_" \
"Data_SingleEle_c_" \
"Data_SingleEle_d_" \
"Data_SingleEle_e_" \
"Data_SingleEle_f_" \
"Data_SingleEle_g_" \
"Data_SingleEle_h_")


inputfiles=("root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/ttgamma_SingleLeptFromTbar.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/ttgamma_semileptfromT.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/ttgamma_dilept.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/ttgamma_hadronic.root" \
"root://cmseos.fnal.gov//store/user/yumiceva/ntuples_2016/TTbar.root" \
"root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/W1jets.root" \
"root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/W2jets.root" \
"root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/W3jets.root" \
"root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/W4jets.root" \
"root://cmseos.fnal.gov//store/user/yumiceva/ntuples_2016/ntuple_DYjets.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/ST_s.root" \
"root://cmseos.fnal.gov//store/user/yumiceva/ntuples_2016/ST_t_top.root" \
"root://cmseos.fnal.gov//store/user/yumiceva/ntuples_2016/ST_t_bar.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/ST_tW_top.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/ST_t_tWbar.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/TTWJets.root" \
"root://cmseos.fnal.gov//store/user/yumiceva/ntuples_2016/TTZ.root" \
"/uscmst1b_scratch/lpc1/3DayLifetime/dnoonan/Ntuples/job_summer16_Zg_aMCatNLO.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/QCD_20to30EM.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/QCD_30to50EM.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/QCD_50to80EM.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/QCD_80to120EM.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/QCD_120to170EM.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/QCD_170to300EM.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/QCD_300toInfEM.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/QCD_20to30Mu.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/QCD_30to50Mu.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/QCD_50to80Mu.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/QCD_80to120Mu.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/QCD_120to170Mu.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/QCD_170to300Mu.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/QCD_300to470Mu.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/QCD_470to600Mu.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/QCD_600to800Mu.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/QCD_800to1000Mu.root" \
"root://eoscms.cern.ch//store/caf/user/dnoonan/job_SingleEle_Run2016B_FebReminiAOD.root" \
"root://eoscms.cern.ch//store/caf/user/dnoonan/job_SingleEle_Run2016C_FebReminiAOD.root" \
"root://eoscms.cern.ch//store/caf/user/dnoonan/job_SingleEle_Run2016D_FebReminiAOD.root" \
"root://eoscms.cern.ch//store/caf/user/dnoonan/job_SingleEle_Run2016E_FebReminiAOD.root" \
"root://eoscms.cern.ch//store/caf/user/dnoonan/job_SingleEle_Run2016F_FebReminiAOD1.root root://eoscms.cern.ch//store/caf/user/dnoonan/job_SingleEle_Run2016F_FebReminiAOD2.root" \
"root://eoscms.cern.ch//store/caf/user/dnoonan/job_SingleEle_Run2016G_FebReminiAOD.root" \
"root://eoscms.cern.ch//store/caf/user/dnoonan/job_SingleEle_Run2016H_FebReminiAODv2.root root://eoscms.cern.ch//store/caf/user/dnoonan/job_SingleEle_Run2016H_FebReminiAODv3.root")

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
"Data                       " \
"Data                       " \
"Data                       " \
"Data                       " \
"Data                       " \
"Data                       " \
"Data                       ")



echo "AnalysisNtuple/makeSkim ele ${files[job]}skim.root ${inputfiles[job]}"
AnalysisNtuple/makeSkim ele ${files[job]}skim.root ${inputfiles[job]}

echo "AnalysisNtuple/makeAnalysisNtuple ${sampleType[job]} ${files[job]}AnalysisNtuple.root ${files[job]}skim.root"
AnalysisNtuple/makeAnalysisNtuple ${sampleType[job]} ${files[job]}AnalysisNtuple.root ${files[job]}skim.root


echo "xrdcp -f ${files[job]}skim.root ${outputdir}skims/electrons/"
xrdcp -f ${files[job]}skim.root ${outputdir}skims/electrons/

echo "xrdcp -f ${files[job]}AnalysisNtuple.root ${outputdir}AnalysisNtuples/electrons/"
xrdcp -f ${files[job]}AnalysisNtuple.root ${outputdir}AnalysisNtuples/electrons/


