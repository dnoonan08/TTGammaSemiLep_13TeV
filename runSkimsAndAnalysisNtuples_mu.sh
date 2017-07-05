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
"Data_SingleMu_b_" \
"Data_SingleMu_c_" \
"Data_SingleMu_d_" \
"Data_SingleMu_e_" \
"Data_SingleMu_f_" \
"Data_SingleMu_g_" \
"Data_SingleMu_h_")


inputfiles=("root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/ttgamma_SingleLeptFromTbar.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/ttgamma_semileptfromT.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/ttgamma_dilept.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/ttgamma_hadronic.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/TTbar.root" \
"root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/W1jets.root" \
"root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/W2jets.root" \
"root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/W3jets.root" \
"root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/W4jets.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/ntuple_DYjets.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/ST_s.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/ST_t_top.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/ST_t_bar.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/ST_tW_top.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/ST_t_tWbar.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/TTWJets.root" \
"root://cmseos.fnal.gov//store/user/troy2012/ntuples_2016/TTZ.root" \
"root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/job_SingleMu_Run2016B_FebReminiAOD.root" \
"root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/job_SingleMu_Run2016C_FebReminiAOD.root" \
"root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/job_SingleMu_Run2016D_FebReminiAOD.root" \
"root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/job_SingleMu_Run2016E_FebReminiAOD.root" \
"root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/job_SingleMu_Run2016F_FebReminiAOD1.root root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/job_SingleMu_Run2016F_FebReminiAOD2.root" \
"root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/job_SingleMu_Run2016G_FebReminiAOD.root" \
"root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/job_SingleMu_Run2016H_FebReminiAODv2.root root://cmseos.fnal.gov//store/user/dnoonan/13TeV_ggNTuples/job_SingleMu_Run2016H_FebReminiAODv3.root")

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



echo "AnalysisNtuple/makeSkim ele ${files[job]}skim.root ${inputfiles[job]}"
AnalysisNtuple/makeSkim ele ${files[job]}skim.root ${inputfiles[job]}

echo "AnalysisNtuple/makeAnalysisNtuple ${sampleType[job]} ${files[job]}AnalysisNtuple.root ${files[job]}skim.root"
AnalysisNtuple/makeAnalysisNtuple ${sampleType[job]} ${files[job]}AnalysisNtuple.root ${files[job]}skim.root


echo "xrdcp -f ${files[job]}skim.root ${outputdir}skims/electrons/"
xrdcp -f ${files[job]}skim.root ${outputdir}skims/electrons/

echo "xrdcp -f ${files[job]}AnalysisNtuple.root ${outputdir}AnalysisNtuples/electrons/"
xrdcp -f ${files[job]}AnalysisNtuple.root ${outputdir}AnalysisNtuples/electrons/


