library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity clean is Port ( 
	 ARDUINO_RESET : out  STD_LOGIC;
	 A12, SD_CS, SD_MOSI, SD_SCK : out  STD_LOGIC;
	 A10, A11, A13, SD_MISO : in STD_LOGIC);
end clean;

architecture Behavioral of clean is
begin
	ARDUINO_RESET <='1';
	
	SD_CS <=	A10;
	SD_MOSI <= A11;
	SD_SCK <= A13;
	A12 <= SD_MISO;
	
end Behavioral;

