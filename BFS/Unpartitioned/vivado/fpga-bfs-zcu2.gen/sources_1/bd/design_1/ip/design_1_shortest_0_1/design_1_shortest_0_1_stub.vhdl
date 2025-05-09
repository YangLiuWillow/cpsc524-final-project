-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2022.1 (lin64) Build 3526262 Mon Apr 18 15:47:01 MDT 2022
-- Date        : Wed May  7 20:47:24 2025
-- Host        : wuyue-i9-9820X running 64-bit Ubuntu 20.04.6 LTS
-- Command     : write_vhdl -force -mode synth_stub -rename_top design_1_shortest_0_1 -prefix
--               design_1_shortest_0_1_ design_1_shortest_0_0_stub.vhdl
-- Design      : design_1_shortest_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xczu7ev-ffvc1156-2-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity design_1_shortest_0_1 is
  Port ( 
    s_axi_control_AWADDR : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s_axi_control_AWVALID : in STD_LOGIC;
    s_axi_control_AWREADY : out STD_LOGIC;
    s_axi_control_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_control_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_control_WVALID : in STD_LOGIC;
    s_axi_control_WREADY : out STD_LOGIC;
    s_axi_control_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_control_BVALID : out STD_LOGIC;
    s_axi_control_BREADY : in STD_LOGIC;
    s_axi_control_ARADDR : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s_axi_control_ARVALID : in STD_LOGIC;
    s_axi_control_ARREADY : out STD_LOGIC;
    s_axi_control_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_control_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_control_RVALID : out STD_LOGIC;
    s_axi_control_RREADY : in STD_LOGIC;
    s_axi_sqrt_AWADDR : in STD_LOGIC_VECTOR ( 4 downto 0 );
    s_axi_sqrt_AWVALID : in STD_LOGIC;
    s_axi_sqrt_AWREADY : out STD_LOGIC;
    s_axi_sqrt_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_sqrt_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_sqrt_WVALID : in STD_LOGIC;
    s_axi_sqrt_WREADY : out STD_LOGIC;
    s_axi_sqrt_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_sqrt_BVALID : out STD_LOGIC;
    s_axi_sqrt_BREADY : in STD_LOGIC;
    s_axi_sqrt_ARADDR : in STD_LOGIC_VECTOR ( 4 downto 0 );
    s_axi_sqrt_ARVALID : in STD_LOGIC;
    s_axi_sqrt_ARREADY : out STD_LOGIC;
    s_axi_sqrt_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_sqrt_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_sqrt_RVALID : out STD_LOGIC;
    s_axi_sqrt_RREADY : in STD_LOGIC;
    ap_clk : in STD_LOGIC;
    ap_rst_n : in STD_LOGIC;
    ap_start : in STD_LOGIC;
    ap_done : out STD_LOGIC;
    ap_idle : out STD_LOGIC;
    ap_ready : out STD_LOGIC;
    m_axi_input_r_AWADDR : out STD_LOGIC_VECTOR ( 63 downto 0 );
    m_axi_input_r_AWLEN : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axi_input_r_AWSIZE : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_input_r_AWBURST : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_input_r_AWLOCK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_input_r_AWREGION : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_input_r_AWCACHE : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_input_r_AWPROT : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_input_r_AWQOS : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_input_r_AWVALID : out STD_LOGIC;
    m_axi_input_r_AWREADY : in STD_LOGIC;
    m_axi_input_r_WDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_input_r_WSTRB : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_input_r_WLAST : out STD_LOGIC;
    m_axi_input_r_WVALID : out STD_LOGIC;
    m_axi_input_r_WREADY : in STD_LOGIC;
    m_axi_input_r_BRESP : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_input_r_BVALID : in STD_LOGIC;
    m_axi_input_r_BREADY : out STD_LOGIC;
    m_axi_input_r_ARADDR : out STD_LOGIC_VECTOR ( 63 downto 0 );
    m_axi_input_r_ARLEN : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axi_input_r_ARSIZE : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_input_r_ARBURST : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_input_r_ARLOCK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_input_r_ARREGION : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_input_r_ARCACHE : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_input_r_ARPROT : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_input_r_ARQOS : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_input_r_ARVALID : out STD_LOGIC;
    m_axi_input_r_ARREADY : in STD_LOGIC;
    m_axi_input_r_RDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_input_r_RRESP : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_input_r_RLAST : in STD_LOGIC;
    m_axi_input_r_RVALID : in STD_LOGIC;
    m_axi_input_r_RREADY : out STD_LOGIC;
    m_axi_output_r_AWADDR : out STD_LOGIC_VECTOR ( 63 downto 0 );
    m_axi_output_r_AWLEN : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axi_output_r_AWSIZE : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_output_r_AWBURST : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_output_r_AWLOCK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_output_r_AWREGION : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_output_r_AWCACHE : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_output_r_AWPROT : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_output_r_AWQOS : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_output_r_AWVALID : out STD_LOGIC;
    m_axi_output_r_AWREADY : in STD_LOGIC;
    m_axi_output_r_WDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_output_r_WSTRB : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_output_r_WLAST : out STD_LOGIC;
    m_axi_output_r_WVALID : out STD_LOGIC;
    m_axi_output_r_WREADY : in STD_LOGIC;
    m_axi_output_r_BRESP : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_output_r_BVALID : in STD_LOGIC;
    m_axi_output_r_BREADY : out STD_LOGIC;
    m_axi_output_r_ARADDR : out STD_LOGIC_VECTOR ( 63 downto 0 );
    m_axi_output_r_ARLEN : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axi_output_r_ARSIZE : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_output_r_ARBURST : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_output_r_ARLOCK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_output_r_ARREGION : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_output_r_ARCACHE : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_output_r_ARPROT : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_output_r_ARQOS : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_output_r_ARVALID : out STD_LOGIC;
    m_axi_output_r_ARREADY : in STD_LOGIC;
    m_axi_output_r_RDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_output_r_RRESP : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_output_r_RLAST : in STD_LOGIC;
    m_axi_output_r_RVALID : in STD_LOGIC;
    m_axi_output_r_RREADY : out STD_LOGIC
  );

end design_1_shortest_0_1;

architecture stub of design_1_shortest_0_1 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "s_axi_control_AWADDR[5:0],s_axi_control_AWVALID,s_axi_control_AWREADY,s_axi_control_WDATA[31:0],s_axi_control_WSTRB[3:0],s_axi_control_WVALID,s_axi_control_WREADY,s_axi_control_BRESP[1:0],s_axi_control_BVALID,s_axi_control_BREADY,s_axi_control_ARADDR[5:0],s_axi_control_ARVALID,s_axi_control_ARREADY,s_axi_control_RDATA[31:0],s_axi_control_RRESP[1:0],s_axi_control_RVALID,s_axi_control_RREADY,s_axi_sqrt_AWADDR[4:0],s_axi_sqrt_AWVALID,s_axi_sqrt_AWREADY,s_axi_sqrt_WDATA[31:0],s_axi_sqrt_WSTRB[3:0],s_axi_sqrt_WVALID,s_axi_sqrt_WREADY,s_axi_sqrt_BRESP[1:0],s_axi_sqrt_BVALID,s_axi_sqrt_BREADY,s_axi_sqrt_ARADDR[4:0],s_axi_sqrt_ARVALID,s_axi_sqrt_ARREADY,s_axi_sqrt_RDATA[31:0],s_axi_sqrt_RRESP[1:0],s_axi_sqrt_RVALID,s_axi_sqrt_RREADY,ap_clk,ap_rst_n,ap_start,ap_done,ap_idle,ap_ready,m_axi_input_r_AWADDR[63:0],m_axi_input_r_AWLEN[7:0],m_axi_input_r_AWSIZE[2:0],m_axi_input_r_AWBURST[1:0],m_axi_input_r_AWLOCK[1:0],m_axi_input_r_AWREGION[3:0],m_axi_input_r_AWCACHE[3:0],m_axi_input_r_AWPROT[2:0],m_axi_input_r_AWQOS[3:0],m_axi_input_r_AWVALID,m_axi_input_r_AWREADY,m_axi_input_r_WDATA[31:0],m_axi_input_r_WSTRB[3:0],m_axi_input_r_WLAST,m_axi_input_r_WVALID,m_axi_input_r_WREADY,m_axi_input_r_BRESP[1:0],m_axi_input_r_BVALID,m_axi_input_r_BREADY,m_axi_input_r_ARADDR[63:0],m_axi_input_r_ARLEN[7:0],m_axi_input_r_ARSIZE[2:0],m_axi_input_r_ARBURST[1:0],m_axi_input_r_ARLOCK[1:0],m_axi_input_r_ARREGION[3:0],m_axi_input_r_ARCACHE[3:0],m_axi_input_r_ARPROT[2:0],m_axi_input_r_ARQOS[3:0],m_axi_input_r_ARVALID,m_axi_input_r_ARREADY,m_axi_input_r_RDATA[31:0],m_axi_input_r_RRESP[1:0],m_axi_input_r_RLAST,m_axi_input_r_RVALID,m_axi_input_r_RREADY,m_axi_output_r_AWADDR[63:0],m_axi_output_r_AWLEN[7:0],m_axi_output_r_AWSIZE[2:0],m_axi_output_r_AWBURST[1:0],m_axi_output_r_AWLOCK[1:0],m_axi_output_r_AWREGION[3:0],m_axi_output_r_AWCACHE[3:0],m_axi_output_r_AWPROT[2:0],m_axi_output_r_AWQOS[3:0],m_axi_output_r_AWVALID,m_axi_output_r_AWREADY,m_axi_output_r_WDATA[31:0],m_axi_output_r_WSTRB[3:0],m_axi_output_r_WLAST,m_axi_output_r_WVALID,m_axi_output_r_WREADY,m_axi_output_r_BRESP[1:0],m_axi_output_r_BVALID,m_axi_output_r_BREADY,m_axi_output_r_ARADDR[63:0],m_axi_output_r_ARLEN[7:0],m_axi_output_r_ARSIZE[2:0],m_axi_output_r_ARBURST[1:0],m_axi_output_r_ARLOCK[1:0],m_axi_output_r_ARREGION[3:0],m_axi_output_r_ARCACHE[3:0],m_axi_output_r_ARPROT[2:0],m_axi_output_r_ARQOS[3:0],m_axi_output_r_ARVALID,m_axi_output_r_ARREADY,m_axi_output_r_RDATA[31:0],m_axi_output_r_RRESP[1:0],m_axi_output_r_RLAST,m_axi_output_r_RVALID,m_axi_output_r_RREADY";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "shortest,Vivado 2022.1";
begin
end;
