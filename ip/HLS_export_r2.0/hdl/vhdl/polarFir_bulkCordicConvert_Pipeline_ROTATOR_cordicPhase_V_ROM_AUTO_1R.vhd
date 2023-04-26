-- ==============================================================
-- Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
-- Version: 2022.2
-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
library ieee; 
use ieee.std_logic_1164.all; 
use ieee.std_logic_unsigned.all;

entity polarFir_bulkCordicConvert_Pipeline_ROTATOR_cordicPhase_V_ROM_AUTO_1R is 
    generic(
             DataWidth     : integer := 12; 
             AddressWidth     : integer := 6; 
             AddressRange    : integer := 64
    ); 
    port (
 
          address0        : in std_logic_vector(AddressWidth-1 downto 0); 
          ce0             : in std_logic; 
          q0              : out std_logic_vector(DataWidth-1 downto 0);

          reset               : in std_logic;
          clk                 : in std_logic
    ); 
end entity; 


architecture rtl of polarFir_bulkCordicConvert_Pipeline_ROTATOR_cordicPhase_V_ROM_AUTO_1R is 
 
signal address0_tmp : std_logic_vector(AddressWidth-1 downto 0); 

type mem_array is array (0 to AddressRange-1) of std_logic_vector (DataWidth-1 downto 0); 

signal mem0 : mem_array := (
    0 => "110010010000", 1 => "011101101011", 2 => "001111101011", 3 => "000111111101", 
    4 => "000011111111", 5 => "000001111111", 6 => "000000111111", 7 => "000000011111", 
    8 => "000000001111", 9 => "000000000111", 10 => "000000000011", 11 => "000000000001", 
    12 => "000000000000", 13 => "000000000000", 14 => "000000000000", 15 => "000000000000", 
    16 => "000000000000", 17 => "000000000000", 18 => "000000000000", 19 => "000000000000", 
    20 => "000000000000", 21 => "000000000000", 22 => "000000000000", 23 => "000000000000", 
    24 => "000000000000", 25 => "000000000000", 26 => "000000000000", 27 => "000000000000", 
    28 => "000000000000", 29 => "000000000000", 30 => "000000000000", 31 => "000000000000", 
    32 => "000000000000", 33 => "000000000000", 34 => "000000000000", 35 => "000000000000", 
    36 => "000000000000", 37 => "000000000000", 38 => "000000000000", 39 => "000000000000", 
    40 => "000000000000", 41 => "000000000000", 42 => "000000000000", 43 => "000000000000", 
    44 => "000000000000", 45 => "000000000000", 46 => "000000000000", 47 => "000000000000", 
    48 => "000000000000", 49 => "000000000000", 50 => "000000000000", 51 => "000000000000", 
    52 => "000000000000", 53 => "000000000000", 54 => "000000000000", 55 => "000000000000", 
    56 => "000000000000", 57 => "000000000000", 58 => "000000000000", 59 => "000000000000", 
    60 => "000000000000", 61 => "000000000000", 62 => "000000000000", 63 => "000000000000");



begin 

 
memory_access_guard_0: process (address0) 
begin
      address0_tmp <= address0;
--synthesis translate_off
      if (CONV_INTEGER(address0) > AddressRange-1) then
           address0_tmp <= (others => '0');
      else 
           address0_tmp <= address0;
      end if;
--synthesis translate_on
end process;

p_rom_access: process (clk)  
begin 
    if (clk'event and clk = '1') then
 
        if (ce0 = '1') then  
            q0 <= mem0(CONV_INTEGER(address0_tmp)); 
        end if;

end if;
end process;

end rtl;

