import os

f = open("FileRetrieve.txt")
list = f.readlines()

for line in list:
    line=line.replace("\n","")
    command = "xrdcp root://xrootd-cms.infn.it/"+ str(line) + " /afs/cern.ch/work/w/wmcbraye/private/CMSSW_7_5_7_patch1/src/PbPb2015_PromptReco_MinBias2/"
    print command
    os.system(command)

print "DONE"
