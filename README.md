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

Additionally, for btagging scale factors, the appropriate scale factor files can be copied from Danny's area.  These have been taken from the twiki, and placed on cmslpc for easier access.

```
cp /uscms/homes/d/dnoonan/TTGammaFiles/CSVv2_Moriond17_B_H.csv .
cp /uscms/homes/d/dnoonan/TTGammaFiles/DeepCSV_Moriond17_B_H.csv .
```

Then, simply compile the code with `make`
