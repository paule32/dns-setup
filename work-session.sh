#!/bin/sh
#-------------------------------------------------------------------------------
# THIS FILE IS PART OF THE DVE INTERNET CAFE PROJECT.
# PLEASE DON'T EDIT THIS FILE.
#
# (c) 2017 Jens Kallp * non-profit Software
# http://kallup.net
#
# e-mail: jkallup@web.de
#-------------------------------------------------------------------------------
display=:$(expr 10 + $1)
current_dir=$(dirname $0)
pass1="30392322035981a638056b282b870ba5"
pass2=$(echo -n "$2" | md5sum | awk '{ print $1; }')
home=$HOME
xsess=$(expr length "$2")
if [ $xsess > 0 ];
then
  if [ $pass1 != $pass2 ]; then
    echo "password wrong, access denied."
    exit 1
  fi
fi
pass3=$2
xsess=$(expr length "$2")
echo $display
export DISPLAY=:0 # could be to fix
Xephyr -ac -br -screen 1024x728 -retro -dpi 96 -keybd \
ephyr,,,,xkblayout=de $display &

echo $$ > work.pid
echo $current_dir >> work.pid
xpid=$(awk "NR==1{print;exit}" work.pid)

#--------------------------------------------
# we are on the X session:
# then, run the cafe software application ...
#--------------------------------------------
if [ "$xsess" -gt 0 ]
then
  #exec $(pwd)/server
  exec /home/jens/Projekte/dns-setup/server --display $display
fi

#------------------------------------------
# delete unecassary suff  after session ...
#------------------------------------------
kill -9 $xpid
rm -rf work.pid

