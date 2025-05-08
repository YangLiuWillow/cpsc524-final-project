############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project cpsc520-bfs-unpartitioned-hls
set_top shortest
add_files ../bfs.h
add_files ../bfs_kernel.cpp
add_files -tb ../bfs.h
add_files -tb ../bfs_test.cpp
add_files -tb ../edge_list.txt
open_solution "solution1" -flow_target vivado
set_part {xczu7ev-ffvc1156-2-e}
create_clock -period 10 -name default
#source "./cpsc520-bfs-unpartitioned-hls/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -rtl verilog -format ip_catalog
