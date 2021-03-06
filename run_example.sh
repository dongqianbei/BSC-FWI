#!/bin/bash
#.........................................
# define configuration
OPTION_DEBUG_VALUE=OFF
OPTION_IO_VALUE=ON
OPTION_NVME_VALUE=ON
OPTION_STATS_VALUE=OFF
OPTION_ARCH_VALUE=generic  # values are: generic,KNL

# env. variables required by the FWI code
export FWIDIR=$PWD

# script internal variables
color_green=`tput setaf 2`
color_cyan=`tput setaf 6`
color_reset=`tput sgr0`

# compile the schedule and model generator utilities
echo "${color_green}------------- Compiling scheduler and model generator binaries${color_reset}"
cd utils
source environment_$2.sh
mkdir -p build
cd build
rm -rf *
cmake -DCMAKE_C_COMPILER=gcc -Ddebug=$OPTION_DEBUG_VALUE -Dperform-io=$OPTION_IO_VALUE -Duse-nvme=$OPTION_NVME_VALUE ..
make install

# create the schedule and model by running the binaries
cd ..
echo "${color_green}------------- Running scheduler and model generator utilities${color_reset}"

echo "${color_cyan}"
rm fwi.log
./generateSchedule.bin fwi_params.txt fwi_frequencies.txt
echo "${color_reset}"
./generateModel.bin fwi_schedule.txt

# compile an run one FWI flavour
echo "${color_green}------------- Compiling $1 FWI version code${color_reset}"
cd ../$1
source environment_$2.sh
mkdir -p build
cd build
rm -rf *
echo "cmake -Darchitecture=$OPTION_ARCH_VALUE -Ddebug=$OPTION_DEBUG_VALUE -Dperform-io=$OPTION_IO_VALUE -Duse-nvme=$OPTION_NVME_VALUE -Dcollect-stats=$OPTION_STATS_VALUE .."
cmake -Darchitecture=$OPTION_ARCH_VALUE -Ddebug=$OPTION_DEBUG_VALUE -Dperform-io=$OPTION_IO_VALUE -Duse-nvme=$OPTION_NVME_VALUE -Dcollect-stats=$OPTION_STATS_VALUE ..
make install

# script ends here
echo ""
echo "${color_cyan}In order to launch the job youll need to modify the proper jobscript under $1 according to the information presented in this log${color_reset}"
echo ""
