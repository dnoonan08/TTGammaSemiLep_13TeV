#!/bin/bash

sample=$1
year=$2
syst=$3
job=$4
nJobs=$5

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
    echo "Untarring Scale Factors"
    xrdcp root://cmseos.fnal.gov//store/user/lpctop/TTGamma_FullRun2/AnalysisNtuples/RequiredScaleFactors.tgz .
    tar -zxf RequiredScaleFactors.tgz
    mkdir AnalysisNtuple
    mv makeAnalysisNtuple AnalysisNtuple/makeAnalysisNtuple
    echo "Done With Setup" ;
fi


echo ${sample}
echo ${year}
echo ${job}
echo ${nJobs}

outputdir="root://cmseos.fnal.gov//store/user/lpctop/TTGamma_FullRun2/AnalysisNtuples_Dec2020/Systematics"

source sampleList_${year}.sh

if [ ${syst} = "CR1" ] || [ ${syst} = "CR2" ] || [ ${syst} = "erdOn" ]  || [ ${syst} = "TuneUp" ]  || [ ${syst} = "TuneDown" ] ;
then
    varname=${sample}_${syst}_${year}
else
    varname=${sample}_${year}
fi

if [ -z ${job} ] ; then
    echo "./AnalysisNtuple/makeAnalysisNtuple ${year} ${sample}__${syst} . ${!varname}"
    ./AnalysisNtuple/makeAnalysisNtuple ${year} ${sample}__${syst} . ${!varname};
else
    echo "./AnalysisNtuple/makeAnalysisNtuple ${year} ${sample}__${syst} ${job}of${nJobs} . ${!varname}"
    ./AnalysisNtuple/makeAnalysisNtuple ${year} ${sample}__${syst} ${job}of${nJobs} . ${!varname};
fi


if [ -z ${_CONDOR_SCRATCH_DIR} ] ; then
    echo "Finished" ;
else
    xrdcp -f ${syst}*${sample}_${year}_AnalysisNtuple*.root ${outputdir}/${year}
    echo "Finished, Cleaning up"
    rm *root
    rm *sh
    rm RequiredScaleFactors.tgz ;
fi
