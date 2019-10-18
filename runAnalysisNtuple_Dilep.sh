#!/bin/bash

sample=$1
year=$2

if [ -z ${_CONDOR_SCRATCH_DIR} ] ; then 
    echo "Running Interactively" ; 
else
    echo "Running In Batch"
    cd ${_CONDOR_SCRATCH_DIR}
    echo ${_CONDOR_SCRATCH_DIR}
    source /cvmfs/cms.cern.ch/cmsset_default.sh

    eval `scramv1 project CMSSW CMSSW_10_2_10`
    cd CMSSW_10_2_10
    eval `scramv1 runtime -sh`
    cd -
    echo 'Untarring Scale Factors'
    tar -zxf RequiredScaleFactors.tgz
    mkdir AnalysisNtuple
    mv makeAnalysisNtuple AnalysisNtuple/makeAnalysisNtuple
fi


outputdir="root://cmseos.fnal.gov//store/user/lpctop/TTGamma_FullRun2/AnalysisNtuples/Dilepton"

source sampleList_${year}.sh
varname=${sample}_${year}

echo "./AnalysisNtuple/makeAnalysisNtuple ${year} ${sample}__Dilep . ${!varname}"
./AnalysisNtuple/makeAnalysisNtuple ${year} ${sample}__Dilep . ${!varname}

xrdcp -f Dilep_${sample}_${year}_AnalysisNtuple.root ${outputdir}/${year}

if [ -z ${_CONDOR_SCRATCH_DIR} ] ; then
    echo "Finished" ;
else
    echo "Finished, Cleaning up"
    rm *
fi
