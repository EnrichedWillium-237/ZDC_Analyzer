import os

f = open("FileList.txt")
list = f.readlines()

for line in list:
    line=line.replace("\n","")
    command = "lcg-ls -b -D srmv2 'srm://se1.accre.vanderbilt.edu:6288/srm/v2/server?SFN='"+ str(line)
    print command
    os.system(command)

print "DONE"
