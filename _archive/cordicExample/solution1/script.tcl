############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project cordicExample
add_files reference/class_examples/cordicExample.cpp
add_files reference/class_examples/cordicExample.h
add_files reference/class_examples/cordicExampleTop.cpp
add_files -tb reference/class_examples/cordicExampleTB.cpp
open_solution "solution1" -flow_target vivado
set_part {xc7z014sclg484-1}
create_clock -period 10 -name default
#source "./cordicExample/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
