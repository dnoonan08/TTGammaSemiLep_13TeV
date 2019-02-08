# AnalysisNtuple Framework
This framework uses as a starting point the NanoAODv4 ntuples.  It is setup to not make use of CMSSW, but typically is run with CMSSW_10_2_X environment to get consistant versions of compilers and root libraries.

## Compiling code
To compile, first a couple of files must be checked out (for use in JES systematics). The JEC files needing to be checked out can obtained through the following:
```
mkdir jecFiles
cd jecFiles
wget https://github.com/cms-jet/JECDatabase/raw/master/tarballs/Summer16_23Sep2016V4_MC.tar.gz
tar -zxf Summer16_23Sep2016V4_MC.tar.gz
cd -
```

Additionally, for btagging scale factors, the appropriate scale factor files can be copied from Danny's area.  These have been taken from the twiki, and placed on cmslpc for easier access.

```
cp /uscms/homes/d/dnoonan/TTGammaFiles/CSVv2_Moriond17_B_H.csv .
cp /uscms/homes/d/dnoonan/TTGammaFiles/DeepCSV_Moriond17_B_H.csv .
cp /uscms/homes/d/dnoonan/TTGammaFiles/DeepCSV_94XSF_V3_B_F.csv .
```



Then, simply compile the code with `make`
