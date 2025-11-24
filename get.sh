#!/usr/bin/bash

# extracts the year from CmakeLists.txt
year=$(grep "set(year" CMakeLists.txt | sed "s/.*year //" | sed "s/)//")
prev_day=$(grep "set(day" CMakeLists.txt | sed "s/.*day //" | sed "s/)//")


if [ $# -eq 1 ] && [ "$1" = "-h" ]; then
  echo "On year ${year}"
  echo "usage: -y [YEAR] to modify year"
  echo "day change will be prompted"
  exit
fi

if [ $# -eq 2 ]; then
  if [ "$1" = "-y" ] && [ $2 != "${year}" ]; then
    sed -i "s/year ${year}/year $2/" CMakeLists.txt
    echo "Year changed: run setup.sh"
    exit
  elif [ $2 = "${year}" ]; then
    echo "Year already set"
    exit
  fi
fi



echo "On year ${year}.  usage: -h for info"
if [ $# -eq 0 ]; then
  echo "Which day?"
  read day_num
fi

day=$(printf %02d ${day_num})
if [ ${day} != ${prev_day} ]; then
  sed -i "s/day ${prev_day}/day ${day}/" CMakeLists.txt
fi


dir="src/${year}/${day}" 
src=${dir}/main.cpp

mkdir -p ${dir} 
touch ${src}


input_dir="inputs/${year}/${day}"
mkdir -p "${input_dir}"
touch "${input_dir}/input.txt"

echo "reading problem input into input.txt"
curl --cookie ~/cookies.txt https://adventofcode.com/${year}/day/${day_num}/input > "${input_dir}/input.txt"
