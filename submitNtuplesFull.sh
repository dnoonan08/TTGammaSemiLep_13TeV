source RequiredScaleFactors.sh

xrdcp -f RequiredScaleFactors.tgz root://cmseos.fnal.gov//store/user/lpctop/TTGamma_FullRun2

condor_submit submitNtuples.jdl
condor_submit submitNtuples_Syst.jdl
condor_submit submitNtuples_Dilep.jdl
condor_submit submitNtuples_SystDilep.jdl
condor_submit submitNtuples_QCD.jdl
