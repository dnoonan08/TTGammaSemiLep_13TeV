from BSMSamples_2016 import sampleList_2016

from getFiles import getFileList_DAS, getFileList_EOS

for year in [2016]:
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
