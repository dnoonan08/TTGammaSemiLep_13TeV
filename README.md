# AnalysisNtuple Framework
This framework uses as a starting point the ggNtuples V08_00_26_07 (https://github.com/cmkuo/ggAnalysis/tree/V08_00_26_07)

## Compiling code
To compile, first a couple of files must be checked out (for use in JES systematics). The JEC files needing to be checked out can obtained through the following:
```
mkdir jecFiles
cd jecFiles
wget https://github.com/cms-jet/JECDatabase/raw/master/tarballs/Summer16_23Sep2016V4_MC.tar.gz
tar -zxf Summer16_23Sep2016V4_MC.tar.gz
cd -
```
Then, simply compile the code with `make`
