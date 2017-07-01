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




outputdir="root://cmseos.fnal.gov//store/user/dnoonan/13TeV_skims/muons/"     
#outputdir="/uscmst1b_scratch/lpc1/3DayLifetime/dnoonan/13TeV_skims/muons/"   

outputfiles=("TTGamma_SingleLeptFromTbar_skim.root " \
"TTGamma_SingleLeptFromT_skim.root    " \
"TTGamma_Dilepton_skim.root           " \
"TTGamma_Hadronic_skim.root           " \
"TTbar_skim.root                      " \
"W1jets_skim.root                     " \
"W2jets_skim.root                     " \
"W3jets_skim.root                     " \
"W4jets_skim.root                     " \
"DYjets_skim.root                     " \
"ST_s-channel_skim.root               " \
"ST_t-channel_skim.root               " \
"ST_tbar-channel_skim.root            " \
"ST_tW-channel_skim.root              " \
"ST_tbarW-channel_skim.root           " \
"TTW_skim.root                        " \
"TTZ_skim.root                        " \
"Data_SingleMu_b_skim.root            " \
"Data_SingleMu_c_skim.root            " \
"Data_SingleMu_d_skim.root            " \
"Data_SingleMu_e_skim.root            " \
"Data_SingleMu_f_skim.root            " \
"Data_SingleMu_g_skim.root            " \
"Data_SingleMu_h_skim.root            ")





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
"/uscmst1b_scratch/lpc1/3DayLifetime/troy2012/ntuples_temp/ST_s.root" \
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



echo "AnalysisNtuple/makeSkim mu ${outputfiles[job]} ${inputfiles[job]}"
AnalysisNtuple/makeSkim mu ${outputfiles[job]} ${inputfiles[job]}

echo "xrdcp -f ${outputfiles[job]} ${outputdir}"
xrdcp -f ${outputfiles[job]} ${outputdir}