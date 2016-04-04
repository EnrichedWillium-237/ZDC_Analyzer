import os

f = open("MASTER.txt")
list = f.readlines()

for line in list:
    line=line.replace("\n","")
    command = "lcg-del -D srmv2 -b -l srm://se1.accre.vanderbilt.edu:6288/srm/v2/server?SFN="+ str(line)
#    command = "lcg-del -D srmv2 -d -b -l srm://se1.accre.vanderbilt.edu:6288/srm/v2/server?SFN="+ str(line)
    print command
    os.system(command)

print "DONE"
