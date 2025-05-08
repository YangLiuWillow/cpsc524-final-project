# cpsc520-final-project

Repo directory structure:
- `BFS/Unpartitioned`: simple implementation of BFS using Vitis_HLS to generate RTL and Vivado Design Suite to generate bitstream
- `GraFlex-U280-sw-vitis-hls`: Our attempt to generate RTL using `cpsc520-final-project/GraFlex/applications/bfs_bf/PE_2/src/sw/bfs_host.cpp` as the source file. You can refer to the original GraFLex paper here: https://dl.acm.org/doi/10.1145/3626202.3637573. Right now, we are stuck due to the different characteristics of ZCU106 and U280. This is a potential research direction and we would like to pursue further.


## Guide to generate HLS implementation (Vitis_HLS)
Make sure to source the `settings64.sh` into your path. You can launch Vitis_HLS using `vitis_hls &`


Input to Vitis HLS:
1. We have the kernel code written in C++ (`BFS/Unpartitioned/bfs_kernel.cpp`), select `shortest` as the top function
2. When being prompted for testbench, choose `BFS/Unpartitined/bfs_test.cpp` and `edge_list.txt`
3. Use the default clock period (10), or you customize the clock period.
4. For the target FPGA board, click to `board` interface and choose `ZCU106`
5. Click `Finish`
6. Now, you will see the `source` folder, the `testbench` folder, and the `solution` folder on the panel on the left.
7. You can run `C Simulation` which will compile your source code (C++) and run with the test bench
8. You can run `C Synthesis` that will generate estimation of the hardware acceleration report, such as latency.
9. Now, right click the `solution` folder and export IP.


## Vivado Design Suite
Just now, we exported the IP package from the Vitis HLS with RTL implementation of our C++ algorithm. Now we need to integrate the exported IP and generate bitstream for validating the design on the hardware.


1. Open Vivado Design Suite and click on `Create Project` on the homepage. You will see a dialog box that will guide you through the process.
2. Name your project and set its directory.
3. Next, in the `Project Type`, choose `RTL Project` and check the box under it that says `Do not specify sources at this time` and click `Next`
4. In `Default Part`, select the Board/Part that you created your HLS design for and click `Next`, then `Finish`.
5. You will now see your project created and opens with a `Project Manager` pane and a `Flow Mavigator` pane.
6. Click on `Create Block Design` under `IP Integrator` in the Flow Navigator pane and click `ok`.
7. Add `Zynq UltraScale+ MPSoCs` IP to in the "Diagram" window. Click on "Run Block Automation" and click on "OK" in the dialog box that appears.
6. Go to settings and navigate to `IP Repository`. Add the exported IP you just created and click `Apply` and click `ok`.
7. Add the exported IP to the Block Design and click on `Run Connection Automation`. Set the clock source to be `zynq_ultra_ps_e_0`.
8. For now, we hardcode the `shortest/sp_start` to 1. To do this, right click in the "Diagram" window, click `Add IP`, and add the `Constant` IP. By default, this is set to 1. Connect this to the `shortest/sp_start`.
9. Navigate to the Sources and right click on the design file. Click on "Create HDL Wrapper" and select auto-update then click "OK"
10. Click "Generate bitsteam" under "Program and Debug" in Flow Navigator pane. Click "yes" then "ok"
11. The bitsteam is now succesfully generated.



