from AllSamples_2016 import sampleList_2016
from AllSamples_2017 import sampleList_2017
from AllSamples_2018 import sampleList_2018

from getFiles import getFileList_DAS, getFileList_EOS

for year in [2016,2017,2018]:
    line = ""
    sampleList = eval("sampleList_%i"%year)
    for sampleName, sample in sampleList.items():
        print(sampleName)
        line += '%s_FileList_%i="'%(sampleName,year)
        if '/store/user/' in sample:
            line += getFileList_EOS(sample)
            line += '"\n\n'
        else:
            line += "xrootd "
            line += getFileList_DAS(sample)
            line += '"\n\n'
    with open('fileList_%i.sh'%year,'wb') as _file:
        _file.write(line.encode('ascii'))
