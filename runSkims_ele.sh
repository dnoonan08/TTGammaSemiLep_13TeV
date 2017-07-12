#!/bin/bash

job=17+$1

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




outputdir="root://cmseos.fnal.gov//store/user/dnoonan/13TeV_skims/electrons/"
#outputdir="/uscmst1b_scratch/lpc1/3DayLifetime/dnoonan/13TeV_skims/electrons/"

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
"ZGamma_skim.root                     " \
"QCD_20to30EM_skim.root               " \
"QCD_30to50EM_skim.root               " \
"QCD_50to80EM_skim.root               " \
"QCD_80to120EM_skim.root              " \
"QCD_120to170EM_skim.root             " \
"QCD_170to300EM_skim.root             " \
"QCD_300toInfEM_skim.root             " \
"Data_SingleEle_b_skim.root           " \
"Data_SingleEle_c_skim.root           " \
"Data_SingleEle_d_skim.root           " \
"Data_SingleEle_e_skim.root           " \
"Data_SingleEle_f_skim.root           " \
"Data_SingleEle_g_skim.root           " \
"Data_SingleEle_h_skim.root           ")





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
"/uscmst1b_scratch/lpc1/3DayLifetime/dnoonan/Ntuples/job_summer16_Zg_aMCatNLO.root" \
"/uscmst1b_scratch/lpc1/3DayLifetime/troy2012/ntuples_temp/QCD_20to30EM.root" \
"/uscmst1b_scratch/lpc1/3DayLifetime/troy2012/ntuples_temp/QCD_30to50EM.root" \
"/uscmst1b_scratch/lpc1/3DayLifetime/troy2012/ntuples_temp/QCD_50to80EM.root" \
"/uscmst1b_scratch/lpc1/3DayLifetime/troy2012/ntuples_temp/QCD_80to120EM.root" \
"/uscmst1b_scratch/lpc1/3DayLifetime/troy2012/ntuples_temp/QCD_120to170EM.root" \
"/uscmst1b_scratch/lpc1/3DayLifetime/troy2012/ntuples_temp/QCD_170to300EM.root" \
"/uscmst1b_scratch/lpc1/3DayLifetime/troy2012/ntuples_temp/QCD_300toInfEM.root" \
"/uscmst1b_scratch/lpc1/3DayLifetime/dnoonan/Ntuples/job_SingleEle_Run2016B_FebReminiAOD.root" \
"/uscmst1b_scratch/lpc1/3DayLifetime/dnoonan/Ntuples/job_SingleEle_Run2016C_FebReminiAOD.root" \
"/uscmst1b_scratch/lpc1/3DayLifetime/dnoonan/Ntuples/job_SingleEle_Run2016D_FebReminiAOD.root" \
"/uscmst1b_scratch/lpc1/3DayLifetime/dnoonan/Ntuples/job_SingleEle_Run2016E_FebReminiAOD.root" \
"/uscmst1b_scratch/lpc1/3DayLifetime/dnoonan/Ntuples/job_SingleEle_Run2016F_FebReminiAOD1.root /uscmst1b_scratch/lpc1/3DayLifetime/dnoonan/Ntuples/job_SingleEle_Run2016F_FebReminiAOD2.root" \
"/uscmst1b_scratch/lpc1/3DayLifetime/dnoonan/Ntuples/job_SingleEle_Run2016G_FebReminiAOD.root" \
"/uscmst1b_scratch/lpc1/3DayLifetime/dnoonan/Ntuples/job_SingleEle_Run2016H_FebReminiAODv2.root /uscmst1b_scratch/lpc1/3DayLifetime/dnoonan/Ntuples/job_SingleEle_Run2016H_FebReminiAODv3.root")

echo "AnalysisNtuple/makeSkim ele ${outputfiles[job]} ${inputfiles[job]}"
AnalysisNtuple/makeSkim ele ${outputfiles[job]} ${inputfiles[job]}

echo "xrdcp -f ${outputfiles[job]} ${outputdir}"
xrdcp -f ${outputfiles[job]} ${outputdir}