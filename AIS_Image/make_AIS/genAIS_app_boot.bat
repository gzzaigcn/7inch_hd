copy E:\CCS5.4.0\Sample_SPI_secondary_Boot\Sample_SPI_secondary_Boot\SPI_secondary_boot\build\boot\SPI_secondary_boot.out SPI_secondary_boot.out

C:\Perl\bin\perl.exe genAIS.pl -otype bin -i SPI_secondary_boot.out -o SPI_secondary_boot.bin -bootmode spimaster -memwidth 8 -datawidth 8 -addrsz 24 -cfg dm6437_hd_dsp.cfg

C:\Perl\bin\perl.exe genAIS.pl -otype bin -i hd_dsp.out -o hd_dsp.bin -bootmode raw

C:\Perl\bin\perl.exe combineAIS.pl SPI_secondary_boot.bin hd_dsp.bin hd_dsp_ais.bin 10

pause;