#!/bin/bash

channel=$1
year=$2
job=$3
nJobTotal=$4

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

fi


if [ -z $job ] ; then
    jobNum=""
else
    jobNum=" ${job}of${nJobTotal}"
fi

outputdir="root://cmseos.fnal.gov//store/user/lpctop/TTGamma_FullRun2/Skims_v6/"

source fileLists_${year}.sh
varname=${channel}_FileList_${year}

echo "./makeSkim ${year}${jobNum} ${channel}_${year}_skim.root ${!varname}"
./makeSkim ${year}${jobNum} ${channel}_${year}_skim.root ${!varname}

if [ -z ${_CONDOR_SCRATCH_DIR} ] ; then
    echo "Running Interactively" ;
else
    echo "xrdcp -f ${channel}_${year}_skim*.root ${outputdir}/${year}"
    xrdcp -f ${channel}_${year}_skim*.root ${outputdir}/${year}

    echo "Cleanup"
    rm -rf CMSSW_10_2_10
    rm *root
    rm makeSkim    
fi
