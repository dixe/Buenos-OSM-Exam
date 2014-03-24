# ~/bin/bash
# commandline arg should be filename, and the file should
# be placed inside tests/

#delete old file from fyams hdd
util/tfstool delete fyams.harddisk $1

#write new file
util/tfstool write fyams.harddisk tests/$1 $1
