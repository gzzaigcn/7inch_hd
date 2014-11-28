#!/usr/local/bin/perl5.8.0 -w
###############################################################################################
# Copyright 2004, All Rights Reserved, Texas Instruments Incorporated
#
# genAIS.pl
#
# Generates AIS command sctream for bootloading DM64xLC.
#
# 2005-04-01 v1.00
# - Created
# 2005-10-10 v1.01.00
# - Re-introduced using AIS BOOT TABLE commands for PLL/SDRAM/ASYNC RAM configuration
# - Fixed bug that required cfg.c file to be included
# 2005-10-25 v1.01.01
# - Fixed bug with odd byte sized sections that caused bad array reference to
#   section data when calculating CRC
# - Fixed async ram configuration problem when using boot table commands.
# 2005-Oct-27 v1.01.02
# - Fixed potential problem with creating default output file name (if none is specified
#   on command line) that specifically looks for .out extension. Changed this to use
#   generic fileparse utility to find basename of file.
# 2005-Nov-03 v1.01.03
# - Added error checking to detect sections that may overload internal ram that
#   on-chip bootloader uses for stack/data. Primarily, this affects SPI/I2C boot modes
# 2005-Nov-10 v1.01.04
# - Fixed internal ram overload detect warning
# - Fixed section type checking to stop load of COPY sections and make sure we get
#   sections created by linker "fill".
# - Added test for I2C/SPI master mode to give warning when AIS file exceeeds 64KB
# 2005-Nov-15 v1.02.00
# - Added -eepromsz and -slaveaddrs options to support booting application from
#   multiple EEPROMS for I2C Master mode. Added CreateMultiEeprom function that
#   divides the ASI stream among the EEPROMS and creates separate AIS file for
#   each device in the chain.
# 2005-Nov-16 V1.03.00
# - Modified multi-eeprom boot to use small self-modifying code to set slave
#   address and reset internal addres counter for multi-eeprom boot.
# 2006-July-27
#   Moved total number section to load and total number of bytes to load
#   to end of AIS stream after JUMP_CLOSE command
# 2007-Jan-18 V1.04.00
#   Incoroporated functions defined in AISFile.pm library to remove this
#   dependency from the utlity. The utility will then be stand-alone with
#   exception of use of the ofd6x.exe, Object File Display utility that
#   comes with the C6000 Code Gen Tools.
# 2007-Jan-25 V1.05.00
#   Added search for .xml file given as input to routine. If it is found
#   then "system" is not called to invoke the utility. XML is parsed
#   directly from input file.
# 2007-May-16 V1.06.00
#   1. Fixed problm with odd byte sized sections not being managed correctly. Adjusted
#   byte count to match total number of words for section as loaded thru AIS. 
#   2. Fixed problem with CRC generation and calculation when global CRC for entire
#   load is requested ( -crc 2 option)
# 2007-May-18 V1.07.00
#    Fixed problem with reading physical ("run") address rather than virtual ("load") address
# 2007-June-13 V1.08.00
#    Added additional debug information to trace invalid section count from XML
#    and added warning to customers that there is mismatch in ofd6x output.
###############################################################################################
use strict qw(subs refs);
use warnings qw(all);
use FindBin;
use FindBin;
use lib "$FindBin::Bin/../lib";
use File::Basename;
use XML::Simple;
use MIME::Base64;
use File::Temp qw(tempfile tempdir);

my ($CFG);
my ($COFF);
my ($VERSION) = "1.08.00";
my ($dotOutFile) = "";
my ($aisOutFile) = "";
my ($xmlFile)    = "";
my ($useTISecondaryBoot) = 0;
my ($oType) = "ASM";
my ($cfgFile) = "";
my ($cf);
my ($entryPoint);
my ($pkgType);
my ($bootmode);
my ($pinTable) = {};
my ($sdramCfg) = {};
my ($pllCfg) = {};
my ($asyncRamcCfg) = {};
my ($pllConfigured) = 0;
my ($sdramConfigured) = 0;
my ($asyncRamConfigured) = 0;
my ($useAddressLatch) = 0;
my ($addressShift) = 13;
my ($debug) = 0;
my ($secRawData) = [];
my ($memwidth) = '8';
my ($byteCount) = 0;
my ($dataWidth) = 8;
my ($swap) = 0;
my ($endian) = 'little';

#----------------------------------------------------------------------------------------------
# helpText - Displayed when user uses the -h or -hh command line options
#----------------------------------------------------------------------------------------------
my $helpText = qq{
  genAis v$VERSION:  AIS Generation Tool
    -i filename[.out] => Input COFF (.out) File (REQUIRED)
    
    -o filename[.cfg] => AIS Ouput File
                         Default ===> inputFileName.asm
                     
    -x filename[.xml] => Optional XML ouput from call to ofd6x
                         NOTE: If your operating system/Perl version does not
                         support use of system(), then inclusion of
                         this file is a requirement.
                   
    -cfg filename => Configuration file containing initialization for EMIF, GPIO
                   pins, PLL, or other startup conditions for boot.
                   
    -cfgtype    => type of configuration to use "ais" or "c"
                   if == ais, then AIS BOOT TABLE command will be used to effect
                   the configuration.
                   if == c, then too lassumes that cfg.c file was compiled/linked
                   with application code and will search for .TIBOOT section for
                   configuration.               
                   
    -otype      => Output file type , one of ascii, asm, bin, txt
                   Default ===> asm
                   
    -bootmode   => spimaster  => DM640 is SPI Master
                   i2cmaster  => DM640 is I2C Master
                   emifa      => EMIFA Fast Boot
                   nand       => NAND Flash Boot
                   emac       => EMAC Boot
                   uart       => UART Boot
                   pci        => PCI Boot
                   hpi        => HPI boot
                   vlynq      => VLYNQ boot
                   raw        => RAW AIS stream
                   Default ===> uart
                  
    -addrsz     => Address width in bits for serial EEPROM one of 8, 16, 24, 32
                   Default ===> 16
                   
    -datawidth  => EMIF Data BUs Width, one of 8 or 16
    
    -crc        => 0, 1, 2
                   0 ===> No CRC Generated/Enabled
                   1 ===> CRC Enabled and Generated for Each Section Load/Fill
                   2 ===> CRC Enabled, Single CRC Generated For Entire Load 
                   
    -debug      => Invokes genAIS in debug mode which produces additional information in
                   output file to allow tracking of data/addresses in flash
  Example(s)...
    genAis -i myApplication.out -o myAIStable.asm -pkg BGA -pf 8 -boomode tisecboot -cfg myApplication.cfg
    
    genAis -i myApplication.out -o myApplication.ais -otype ASCII -bootmode spimaster
};



my (%MEMTYPE) = (
	'8' => 1,
	'16' => 2,
	'24' => 3,
	'32' => 4
);

my (@month) = ('Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep',
                'Oct', 'Nov', 'Dec');

#----------------------------------------------------------------------------------------------
# AIS Commands - HASH Table of AIS Commands
#----------------------------------------------------------------------------------------------

my (%AISCOMMAND_LE) = (
    aisMagic          => 0x41504954,
    spiI2cMasterMagic => 0x41504954,
    i2cSlaveXmtStart  => 0x00000058,    
    spiSlaveXmtStart  => 0x00005853,
    spiI2cXmitSync    => 0x58535900,
    spiI2cPingDevice  => 0x5853590B,
	sectionLoad       => 0x58535901,
	requestCRC        => 0x58535902,
	enableCRC         => 0x58535903,
	disableCRC        => 0x58535904,
	jump              => 0x58535905,
	jumpAndClose      => 0x58535906,
	bootTable         => 0x58535907,
	startOver         => 0x58535908,
	reserved          => 0x58535909,
	sectionFill       => 0x5853590A,
	ping              => 0x5853590B,
	deviceCfgCommand  => 0x585359F0,	
	pageSwapCommand   => 0x585359F1,
	latchAddress      => 0x585359F2
);

my (%AISCOMMAND_BE) = (
    aisMagic          => 0x54495041,
    spiI2cMasterMagic => 0x54495041,
    i2cSlaveXmtStart  => 0x58000000,    
    spiSlaveXmtStart  => 0x53580000,
    spiI2cXmitSync    => 0x00595358,
    spiI2cPingDevice  => 0x0B595358,
	sectionLoad       => 0x01595358,
	requestCRC        => 0x02595358,
	enableCRC         => 0x03595358,
	disableCRC        => 0x04595358,
	jump              => 0x05595358,
	jumpAndClose      => 0x06595358,
	bootTable         => 0x07595358,
	startOver         => 0x08595358,
	reserved          => 0x09595358,
	sectionFill       => 0x0A595358,
	ping              => 0x0B595358,
	deviceCfgCommand  => 0x0F595358,	
	pageSwapCommand   => 0xF1595358,
	latchAddress      => 0xF2595358
);

#----------------------------------------------------------------------------------------------
# COFF Section Types
#----------------------------------------------------------------------------------------------

my (%SECTYPE) = (
    STYP_REG	  => 0x00000000,
    STYP_DSECT	  => 0x00000001,
    STYP_NOLOAD	  => 0x00000002,
    STYP_GROUP	  => 0x00000004,
    STYP_PAD	  => 0x00000008,
    STYP_COPY	  => 0x00000010,
    STYP_TEXT	  => 0x00000020,
    STYP_DATA	  => 0x00000040,
    STYP_BSS	  => 0x00000080,
    STYP_CLINK	  => 0x00004000,
    STYP_LOADABLE => 0x00000060
);

#----------------------------------------------------------------------------------------------
# CALL Main Application
#----------------------------------------------------------------------------------------------

main();
exit(0);

#----------------------------------------------------------------------------------------------
# Main Application
#----------------------------------------------------------------------------------------------
sub main {
	use XML::Simple;
	use Data::Dumper;	
	
	my ($args);
	$args = parseArguments (\@ARGV,
	   -i     => "",
	   -o     => "",
	   -cfg   => "",
	   -otype => "asm",
	   -crc   => '1',
	   -sec   => 0,
	   -pf    => 8,
	   -cfgtype => 'c',
	   -bootmode => 'spimaster',
	   -pgsize => 'default',
	   -ping   => 10,
	   -datawidth => 8,
	   -addrsz => '16',
	   -eepromsz => '',
	   -swap => 0
	 );
	 
	$numSlaves = 0;
	$dotOutFile = $args->{"-i"};
	$aisOutFile = $args->{"-o"};
	$cfgFile = $args->{"-cfg"};
    $genCrc  = ($args->{"-crc"});
	$oType = uc($args->{"-otype"});	
	$bootmode = lc($args->{"-bootmode"});
	$memwidth  = ($args->{"-memwidth"}) ? ($args->{"-memwidth"}) : $memwidth;
	$addrsz  = ($args->{"-addrsz"}) ? ($args->{"-addrsz"}) : $addrsz;
	$dataWidth = ($args->{"-datawidth"}) ? ($args->{"-datawidth"}) : $dataWidth;
	$debug   = ($args->{"-debug"}) ? 1 : 0; 
	$ping    = ($args->{"-ping"}) ? ($args->{'-ping'}) : 10;
	$swap    = ($args->{"-swap"}) ? ($args->{'-swap'}) : $swap;	
	$eepromSize = ($args->{"-eepromsz"}) ? ($args->{"-eepromsz"}) : 64;
	$eepromSize = $eepromSize * 1024;
	@slaveAddr = split (/,/, ($args->{"-slaveaddrs"})) if ($args->{"-slaveaddrs"});
	$numSlaves = @slaveAddr;
	$sectionCountErr = 0;
	
	
	for($i = 0 ; $i < $numSlaves ; ++$i) {
		$slaveAddr[$i] = oct($slaveAddr[$i]);
	}
	
	
#	$addressShift = 12 if ($pkgType eq 'TQFP');
	$addressShift += 2 if ($memwidth eq '16');
	
	$useTISecondaryBoot = 1 if ($bootmode eq 'tisecboot');
	
	if (($bootmode eq 'tisecboot') && ($genCrc eq '2')) {
		printf (STDERR "Error - global CRC (- crc 2) Not Supported for this mode\n");
		printf (STDERR "      Using -crc 1\n");
		$genCrc = '1';
	}
	 
	if ($dotOutFile eq "") {
		printf (STDERR "Error - no input file specified\n");
		doHelp($helpText);
    }
    
	if (-e $dotOutFile) {
	   my($sec,$min,$hour,$mday,$mon,$year)=localtime(time);
	   my($login) = getlogin();
	   
	   ###########################################################################
	   # Check for XML file as input to the script. If not found ,then
	   # call system to invoke ofd6x to create the file
	   ###########################################################################
	   if (defined($args->{'-x'})) {
		   $xmlFile = $args->{'-x'};
	   } else {
		  printf "Invoking OFD6X, file\n" if $debug;
	      $xmlFile = sprintf("genAIStmp_%s_%s_%02d_%04d_%02d_%02d_%02d.xml",$login,$month[$mon],$mday,$year+1900,$hour,$min,$sec);	   
	      system("ofd6x -x --obj_display=none,header,optheader,sections,symbols $dotOutFile > $xmlFile");
       }
	   
       $cf = XMLin($xmlFile);
	   open($COFF, "<$dotOutFile");
	   binmode($COFF);    	   
# 	   if ($debug) {
# 		   $Data::Dumper::Indent   = 1;
# 	       $Data::Dumper::Sortkeys = 1;
# 	       print Dumper($cf);
# 	       print "\n";
#        }   
    } else {
	   printf (STDERR "Specified input file, $dotOutFile, does not exist\n");
	   exit(1);
    }
        
     $aisExtension = ($oType eq "ASM")? "asm" : "ais";
     
     if ($aisOutFile eq "") {
	     $aisOutFile = $dotOutFile;
	     ($aisOutFile, $tmpPath) = fileparse($dotOutFile, ('\.\S*'));
	     $aisOutFile = $tmpPath."/".$aisOutFile.".".$aisExtension;
     }
 
        
    CreateAISStream();
    
    printf "\tAIS File Generation Complete\n";
    close($CFG) if ($cfgFile ne "");
    if ($sectionCountErr == 1) {
	    printf "!!! Warning, potential error detected in XML translation of .out file\n";
	    printf "!!! the number of sections in XML file generated from ofd6x.exe does \n";
	    printf "!!! not match the number of sections input thru Perl XML parser.\n";
	    printf "!!! Most likely this mismatch is due to duplicate section entry in\n";
	    printf "!!! the XML file created by ofd6x.\n";
	    printf "!!! The XML file , $xmlFile, has been retained to allow further debug.\n";
	    printf "!!! Please check .XML output of ofd6x for list of section names.\n";
	    printf "!!! and check for duplicate entries. \n";
	    printf "!!! Please note, that if duplicate entries are present in the .xml file\n";
	    printf "!!! ouput from ofd6x, this will not affect the AIS gneration. The AIS\n";
	    printf "!!! file created should be correct\n";
    } else {    
       unlink($xmlFile);
    }
}

#--------------------------------------------------------------------------------------------
sub CreateCFGTable {
	my ($AIS) = shift(@_);
	my ($CFG) = shift(@_);
	my ($args) = @_;
	my ($lineCnt);
	my ($address);
	my ($dataType);
	my ($val);
	my ($doze);

	my ($i);
	my ($tlArgs);
	my ($linesPerEntry) = 9;
	my ($pincount) = 0;
	my ($iline) = "";
	my ($j);
	my ($numSets) = 0;

	
    $fh = $AIS->{'fh'};
    $writeFn = $AIS->{'write'};
    
    $lineCnt = 0;
    
	while ($iline = <$CFG>) {
	    # skip line if it begins with a comment
	    next if ($iline =~ m/^\s*\#/);
	    
	    # skip if blank line
	    $tmpLine = $iline;
	    $tmpLine =~ s/[\n\r\f]//g;
	    
	    next if ($tmpLine eq '');
	    
	    # Remove any trailing comments
	    $iline =~ s/\#.*//;
	    
	    # 	    
	    next if ($iline !~ m/^(\s*\-\s*\w*)*/);
	    printf $fh "Parsing line :%s:\n",$iline if ($debug);
	    chomp($iline);
	    $iline =~ s/\s*//g;  # remove any blanks spaces
	    $tlOptions = $iline;
	    printf $fh "value :%s:\n",$tlOptions if ($debug);
	    $val = oct($tlOptions);
	    &$writeFn($AIS,$val,\$byteCount);
    }
    

    
   return;
}

#--------------------------------------------------------------------------------------------
sub CreateAISStream {
	use XML::Simple;
	
	my ($args) = shift(@_);
	my ($runAddr);
	my ($secName);
	my ($secSize);
	my ($entryPoint);
	my ($count);
	my ($sizeOfRequestCrc) = 4 * 3;
	my ($sizeOfSectionLoad) = 4 * 3;
	my ($globalSeek) = 0;
	my ($seek) = 0;
	my ($crcVal) = 0;
	my ($fh);
	my ($writeFn);
	my ($i,$j,$x);
	my ($TIBoot) = 0;
	my ($TIBootSetupAddr) = 0;
	my ($TIBootSecSize) = 0;
	my ($TIBootSetupSym) = {};
	my ($totalDataSize) = 0;
    my ($numSections) = 0;
    my ($numWords) = 0;
    my ($remainder) = 0;
    my ($numLoadableSections) = 0;
    my ($loadableSections) = [];
    my ($symbol);
    my ($symTab);
    my ($BIG_ENDIAN) = 'big';
    my ($LITTLE_ENDIAN) = 'little';
    my ($rawDataPtr) = 0;
	
	
	

    
    $AIS = AISFile->new($aisOutFile, $oType, ">", $debug, $bootmode);
    $fh = $AIS->{'fh'};
    $writeFn = $AIS->{'write'};

 
    ###########################################################################################
    # Get Object Entry Point Address
    ###########################################################################################
    $entryPoint = ($cf->{'object_file'}{'ti_coff'}{'optional_file_header'}{'entry_point'});
    $endian = ($cf->{'object_file'}{'ti_coff'}{'file_header'}{'endian'});
  
    printf "# File Endianness is %s\n", $endian if $debug;
      
     $TIBootSetupAddr = 0;
    
       
    printf $fh "# Found entry point, entry point %s\n",$entryPoint if ($debug);
    
    
    $entryPoint = oct($entryPoint);
    
    
    ############################################################################################
    # Get section data from XML file
    ############################################################################################
    $sections = $cf->{'object_file'}->{'ti_coff'}->{'section'};
    $numSections = oct($cf->{'object_file'}->{'ti_coff'}->{'file_header'}->{'section_count'});
  
    printf $fh "; Number of Sections in Out file, %d\n", $numSections  if ($debug);
   
     
    @secNames = keys %$sections;
        	
    

    ############################################################################################
    # Make sure .TIBoot section is loaded first if it exists and make
    # sure the loadable sections list contains only those sections that 
    # are non-zero in size and can/should be loaded
    ############################################################################################
  
    printf $fh "; Section Names\n"  if ($debug);
    $firstSection = $secNames[0];
    $numXmlSections = @secNames;
    printf $fh "; Number of Sections From XML file, %d\n",$numXmlSections if ($debug);
    
    ++$sectionCountErr if ($numSections != $numXmlSections);
    

   	for($i = 0; $i < $numXmlSections; ++$i) {
	   	printf $fh "; \t%s\n",$secNames[$i] if ($debug);
		if ($secNames[$i] eq '.TIBoot') {
			$secNames[$i] = $firstSection;
			$secNames[0] = '.TIBoot';
			last;
		}
	}
 
	#############################################################################################
	# Search for TIBootSetup function and set address if it is present.
	#############################################################################################
	$symTab = $cf->{'object_file'}->{'ti_coff'}->{'symbol_table'}->{'symbol'};
	printf $fh "; Processing symbol table \n" if ($debug);
	
	foreach $symbol (keys %$symTab) {
		if ($symbol eq '_TIBootSetup'){	
		   printf $fh "; Symbol :%s:\n",$symbol if ($debug);
		   $TIBootSetupAddr = oct($symTab->{$symbol}->{'value'});
	    }
	}
	
	for($i = 0; $i < $numXmlSections; ++$i) {
	    $secDescriptor = $sections->{$secNames[$i]};
	    $secSize = oct($secDescriptor->{'raw_data_size'});
	    $rawDataPtr = oct($secDescriptor->{'file_offsets'}{'raw_data_ptr'});
	  
	    printf $fh "; Section Number :%d: Section Name :%s:, Section Size :%d:\n", $i,
	      $secNames[$i], $secSize if ($debug);
	        	        
	    if ((($secSize != 0) && ($rawDataPtr != 0)) &&
	        (not defined $secDescriptor->{'bss'})   &&
             #----------------------------------------------------------------------
             # and it is not a copy section ...
             # (copy sections are information of some kind that is not to be
             # loaded to the target.  Best example is .cinit when linked under
             # -cr.  Dwarf debug sections are also copy sections.)
             #----------------------------------------------------------------------
	         (not defined $secDescriptor->{'copy'})  &&
             #----------------------------------------------------------------------
             # and not a dummy section ...
             # (dummy is a legacy section type typically not used)
             #----------------------------------------------------------------------
	         (not defined $secDescriptor->{'dummy'}) &&
             #----------------------------------------------------------------------
             # and not a noload section.
             # (noload sections come up when you are doing particularly complicated
             # partial linking tricks.  As the name implies, the section is not to
             # loaded.)
             #----------------------------------------------------------------------
	         (not defined $secDescriptor->{'noload'})) {
		      $loadableSections[$numLoadableSections] = $secNames[$i];
		      printf $fh "; Found loadable section,:%s:\n",$secNames[$i] if ($debug);
		      ++$numLoadableSections;
		      $totalDataSize += $secSize;
	    }
	}	   
	
	printf $fh "; Number of loadable sections = %d\n",$numLoadableSections if ($debug);
	printf $fh "; Bootmode :%s:\n",$bootmode if ($debug);
	
    if (($bootmode eq 'i2cslave')) {
	    &$writeFn($AIS,swapBytes($AISCOMMAND_LE{"i2cSlaveXmtStart"},1) ,\$byteCount);
    }

    if (($bootmode eq 'spislave')) {
	   &$writeFn($AIS,swapBytes($AISCOMMAND_LE{"spiSlaveXmtStart"},1),\$byteCount);
    }            
    
    if (($bootmode eq 'i2cslave') || ($bootmode eq 'spislave')) {
	   &$writeFn($AIS,swapBytes($AISCOMMAND_LE{"spiI2cPingDevice"},1),\$byteCount);
	   &$writeFn($AIS,$ping,\$byteCount);
	   for($i = 1; $i <= $ping; ++$i) {
	     &$writeFn($AIS,$i,\$byteCount);
       }
    }   
    
    if (($bootmode eq 'spimaster') || ($bootmode eq 'i2cmaster')) {
		&$writeFn($AIS,$MEMTYPE{$addrsz},\$byteCount);
	}
	
	if ($bootmode eq 'emif') {
		&$writeFn($AIS,($dataWidth == 8) ? 0 : 1,\$byteCount);
	}
    
	&$writeFn($AIS,swapBytes($AISCOMMAND_LE{"aisMagic"},1),\$byteCount);
	
	    

     
    ### Reserve space for block start, page start and num pages
    if ($bootmode eq 'nand') {
	    &$writeFn($AIS,0x00000000,\$byteCount);
		&$writeFn($AIS,0x00000000,\$byteCount);
		&$writeFn($AIS,0x00000000,\$byteCount);
	}
   
    ############################################################################################
    # Load Boot Configuration First - these are the AIS "SET" commans which may
    # setup, PLL, EMIF, DDR settings needed to load the application.
    ############################################################################################     
    if ($cfgFile ne "") {
       open($CFG,"<$cfgFile") || die "Couldn't open '$cfgFile' for reading";
       CreateCFGTable($AIS,$CFG, $args); 
     }
	
    if ($genCrc ne '0'){
	    &$writeFn($AIS,swapBytes($AISCOMMAND_LE{"enableCRC"},1),\$byteCount);
    }
     
    for ($i = 0; $i < $numLoadableSections ; ++$i) {
	    $secDescriptor = $sections->{$loadableSections[$i]};
	    $secSize = oct($secDescriptor->{'raw_data_size'});
	    $rawDataPtr = oct($secDescriptor->{'file_offsets'}{'raw_data_ptr'});
    
	       $secName = $loadableSections[$i];
	       $runAddr = oct($secDescriptor->{'virtual_addr'});
           $secSize = oct($secDescriptor->{'raw_data_size'});
           $numWords = int(($secSize+3)>>2);
           $secSize = int($numWords << 2);
                                
           ####################################################################
           # Position pointer in COFF file to start of Raw Data for the 
           # section. Then read the number of 32 bit words required for
           # section.
           ####################################################################
		    seek($COFF,$rawDataPtr,0);

            for ($x=0; $x<$numWords; $x++) {
                 $secRawData[$x] = read32($COFF, $endian);    
            }		        

	        
	        
           if (($oType eq 'ASM') || ($debug)) {
	           printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	           printf $fh ";;; Section Size = %d,  NumWords = %d\n",$secSize, $numWords;
	           printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
           }
           	        	        
           if (($oType eq 'ASM') || ($debug)) {
              printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
              printf $fh ";;;   Loading Section: %s\n", $secName;
              printf $fh ";;;   Current FLASH Address: 0x%08X\n",$byteCount;
              printf $fh ";;;   Section Size in Bytes: 0x%08X\n",$secSize;
              printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"; 
           }  
                                 
           &$writeFn($AIS,swapBytes($AISCOMMAND_LE{"sectionLoad"},1),\$byteCount);
	       &$writeFn($AIS,swapBytes($runAddr,1),\$byteCount);
	       &$writeFn($AIS,swapBytes($secSize,1),\$byteCount);
	       
	       #######################################################################
	       # IF Code was compiled/linked in BIG Endian Mode then data has been
	       # stored in BIG Endian format. If requested, swap the data to conform to
	       # Little Endian format.
	       #######################################################################  
            
	       if (($bootmode ne 'nand') && ($endian eq 'big')) {	       
	          for($j=0; $j < $numWords; $j++) {
		          $tmp = $secRawData[$j];
		          $secRawData[$j] = swapBytes($tmp,0);
	          }
           }          
                 
	        for($j=0; $j < $numWords; $j++) {
		        &$writeFn($AIS,$secRawData[$j],\$byteCount);
	        }
           
           

       
           
           $seek = int ($secSize + $sizeOfSectionLoad + $sizeOfRequestCrc); 

           $crcVal = 0 if ($genCrc eq '1');
	       $crcVal = calcCrcWord($runAddr,$crcVal);
	       $crcVal = calcCrcWord($secSize,$crcVal);	  
	       if ($debug) {
		       printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
		       printf $fh ";;; Calling calcCrc for Section :%s:\n",$secName;
		       printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"; 
		       
		       printf ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
		       printf ";;; Calling calcCrc for Section :%s:\n",$secName;
		       printf ";;;     Section Size :0x%08x\n",$secSize;
		       printf ";;;     Run Address  :0x%08x\n",$runAddr;
		       printf ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n"; 		       
	       }
	       
	
	       if (($bootmode eq 'nand') && ($endian eq 'big')) {	       
	          for($j=0; $j < $numWords; $j++) {
		          $tmp = $secRawData[$j];
		          $secRawData[$j] = swapBytes($tmp,0);
	          }
           }
           
	       $crcVal = calcCrcSection($secSize,$crcVal,0, $fh);
				
	       if ($genCrc eq '1') {
	           if (($oType eq "ASM") || ($debug)) {
	              printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	              printf $fh ";;; Requesting CRC\n";
	              printf $fh ";;;   Current CRC For This Section: 0x%08X\n",$crcVal;
	              printf $fh ";;;   Number bytes to copy: 0x%08X\n",$secSize;
	              printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	           }
		            
	           &$writeFn($AIS,swapBytes($AISCOMMAND_LE{"requestCRC"},1),\$byteCount);
# 	           if (($endian eq 'big') && ($swap eq 1)) {
# 		           $byte0 = $crcVal & 0xFF;
# 		           $byte1 = (($crcVal >> 8) & 0xFF);
# 		           $byte2 = (($crcVal >> 16) & 0xFF);
# 		           $byte3 = (($crcVal >> 24) & 0xFF);
# 		           $crcVal =   $byte3
# 		                     | (($byte2 << 8) & 0xFF00)
# 		                     | (($byte1 << 16) & 0xFF0000)
# 		                     | (($byte0 << 24) & 0xFF000000);
# 	          }
		                     
              if (($bootmode ne 'nand') && ($endian eq 'big')) {
	             &$writeFn($AIS,swapBytes($crcVal,0),\$byteCount);
	             &$writeFn($AIS,swapBytes(0-($seek),1),\$byteCount);
              } else {	             
	             &$writeFn($AIS,swapBytes($crcVal,1),\$byteCount);
	             &$writeFn($AIS,swapBytes(0-($seek),1),\$byteCount);
	          }
           }
           
	       if ($i == 0) {
	 	      if ($TIBootSetupAddr != 0) {
	 	          if (($oType eq 'ASM') || ($debug)) {
	 	              printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	 	              printf $fh ";;;   Placing Jump Command\n";
	 	              printf $fh ";;;   Current FLASH Address: 0x%08X\n", $byteCount;
	 	              printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
	 	          } 
	 	      
	 		   &$writeFn($AIS,swapBytes($AISCOMMAND_LE{"jump"},1),\$byteCount);
	 		   &$writeFn($AIS,$TIBootSetupAddr,\$byteCount);
	 	      }
 	      }
 	      
 	      if ($genCrc eq '2') {
 	          if (($oType eq 'ASM') || ($debug)) {
 	              printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
 	              printf $fh ";;;   Calculating global seek \n";
 	              printf $fh ";;;   Current Seek: 0x%08X\n", $seek;
 	              printf $fh ";;;   New Global Seek: 0x%08X + 0x%08X = 0x%08X\n", 
 	                               $globalSeek, $seek, $globalSeek + $seek;
 	              printf $fh ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;\n";
 	              $globalSeek += $seek;
 	          } 
	 	  } 
     	          
       
    }
    ############################################################################################
    # If Generating Single CRC , place REQUEST CRC as last command before JUMP_CLOSE
    ############################################################################################
    
    if ($genCrc eq '2') {
	           &$writeFn($AIS,swapBytes($AISCOMMAND_LE{"requestCRC"},1),\$byteCount);
	           &$writeFn($AIS,swapBytes($crcVal,1),\$byteCount);
	           &$writeFn($AIS,swapBytes(0-($globalSeek),1),\$byteCount);	
    }    
    
    #############################################################################################
    # ALL Code should be loaded, place JUMP_CLOSE command to branch to application
    #############################################################################################
  	
    &$writeFn($AIS,swapBytes($AISCOMMAND_LE{"jumpAndClose"},1),\$byteCount);
	&$writeFn($AIS,swapBytes($entryPoint,1),\$byteCount);
 	&$writeFn($AIS,swapBytes($numLoadableSections,1),\$byteCount);
	&$writeFn($AIS,swapBytes($totalDataSize,1),\$byteCount);
	   
    $AIS->DESTROY();
    
	return;

}

#--------------------------------------------------------------------------------------------
sub calcCrcSection {
	my($section_size) = shift(@_);
	my($crc) = shift(@_);
	my($dataNdx) = shift(@_);
	my($fh) = shift(@_);
	my($n);
	my($residue_value) = 0;
	my($msb_bit) = 0;
	my($bits) = 0;
	my($nwords);
	my($temp);
	my($crc_poly) = 0x04C11DB7; # CRC - 32
	

	
	for( $n = 0; $n < ($section_size>>2); $n++ )
	{
		$bits = 32;
        while( --$bits >= 0 )
		{
			$msb_bit = $crc & 0x80000000;
			$crc = ($crc << 1) ^ ((($secRawData[$n + $dataNdx]) >> $bits) & 1 );
			if ( $msb_bit ){
       		  $crc = ($crc ^ $crc_poly);
   		    }
		}
	}
			
	if (($section_size & 3) == 1) {
	   $residue_value = (($secRawData[$n + $dataNdx]) && 0xFF);
	   $bits = 8;	   
    }
    if (($section_size & 3) == 2) {
	    $residue_value = (($secRawData[$n + $dataNdx]) && 0xFFFF);
	    $bits = 16;	    
    }
    if (($section_size & 3) == 3) {
	    $residue_value = (($secRawData[$n + $dataNdx]) && 0xFFFFFF);
	    $bits = 24;
    }
	
	if($section_size & 3)
	{

		while( --$bits >= 0 )
		{
			$msb_bit = $crc & 0x80000000;
			$crc = ($crc << 1) ^ (($residue_value >> $bits) & 1 );
			if ( $msb_bit ) {
			   $crc = ($crc ^ $crc_poly);
			}
		}
	}	  	

	return  $crc;
}


#--------------------------------------------------------------------------------------------
sub calcCrcWord {
	my($dataWord) = shift(@_);
	my($crc) = shift(@_);
	my($msb_bit) = 0;
	my($bits) = 0;
	my($crc_poly) = 0x04C11DB7; # CRC - 32
	


	$bits = 32;
	while( --$bits >= 0 )
	{
		$msb_bit = $crc & 0x80000000;
		$crc = ($crc << 1) ^ (($dataWord >> $bits) & 1 );
		if ( $msb_bit ){
    		  $crc = $crc ^ $crc_poly;
 	    }
	}
		

	return  $crc;
}
#--------------------------------------------------------------------------------------------
sub swapBytes {
	my($val) = shift(@_);
	my($ais) = shift(@_);
	my($byte0, $byte1, $byte2, $byte3);
	
	my($tmp) = 0;
	
	$byte0 = $val & 0xFF;
	$byte1 = (($val >> 8) & 0xFF);
	$byte2 = (($val >> 16) & 0xFF);
	$byte3 = (($val >> 24) & 0xFF);
		
	$tmp = $byte3 
	     | (($byte2 << 8) & 0xFF00)
	     | (($byte1 << 16) & 0xFF0000)
	     | (($byte0 << 24) & 0xFF000000);
	     	     
	if ($ais == 1) {
		$tmp = (($bootmode eq 'nand') && ($endian eq 'big')) ? $tmp : $val;
	} else {
		$tmp = ($endian eq 'big')? $tmp : $val;
	}       	     
   return $tmp;
}
	
	

#--------------------------------------------------------------------------------------------
sub parseArguments {

  my ($argv)           = shift(@_);
  my ($inputDefaults)  = {@_};
  my ($status)         = 0;
  my ($args)           = {};
  my ($argStr)         = "";
  my ($rcStr)          = "";
  my ($strArgs);
  my ($key);
  my ($arg);

  # Baseline defaults for librray specific arguments
  my ($defaults) = {
	   -i     => "",
	   -o     => "",
	   -cfg   => "",
	   -otype => "asm",
	   -crc   => 1,
	   -sec   => 0,
	   -pf    => 8,
	   -bootmode => 'spislave',
  };

  # Assign base defaults to args
  foreach $key (keys %$defaults) {
    $args->{$key} = $defaults->{$key};
  }

  # Assign input defaults to args
  foreach $key (keys %$inputDefaults) {
    $args->{$key} = $inputDefaults->{$key};
  }

  # Need to double quote all entries in @argv that have white-space
  foreach $arg (@$argv) {
    if ($arg =~ m/\s+/) {
      $arg = "\"$arg\"";
    }
  }

  # Combine command line arguments into a string
  $argStr = join(' ',@$argv);

  # Assign the argument string to the return hash
  $args->{_argument_str_} = $argStr;

  # Parse the argument string into a hash
  $strArgs = parseCommandString($argStr);

  # Assign the string arguments to the arguments hash
  foreach $key (keys %$strArgs) {
    $args->{$key} = $strArgs->{$key};
  }

  # Set help level
  $args->{-h} = 2 if ($args->{-hh});

  # This is used by the setupLog() subroutine to get original command line arguments
  $args->{_original_args_} = $args;

  return $args;
}

#------------------------------------------------------------------------------
#  The following files are a set of utilities used to parse option strings, etc.
#------------------------------------------------------------------------------
sub parseOptionsString {

  my ($inputStr)  = shift(@_);
  my ($inputArgs) = {@_};
  my ($args);
  my ($arg);
  my ($strArgs);

  %$args = %$inputArgs;
  
  $strArgs = parseCommandString($inputStr);
  
  %$args = (%$args, %$strArgs);

  return $args;
}


#------------------------------------------------------------------------------
sub parseCommandString {

  my ($inputStr) = shift(@_);
  my ($args);
  my ($state);
  my (@chars);
  my ($ch);
  my (@tokens);
  my ($token);
  my ($string);
  my ($switch);
  my (@nonSwitches);

  #*******************************************************
  # Tokenizing state machine, turn string into array of
  # strings and tokens.
  #*******************************************************

  # Initialize state information
  @chars  = split(//,$inputStr);
  $ch     = shift(@chars);
  $state  = 'base';
  $token  = "";
  $string = "";
  @tokens = ();

  # Enter the state machine
  while (1) {

    #=== base state =======================================
    if ($state eq 'base') {

      if (! defined $ch) {
        $state = 'done';
        next;
      }
      elsif ($ch eq '#') {
        $state = 'done';
        next;
      }
      elsif ($ch =~ m/\s/) {
        $ch = shift(@chars);
        next;
      }
      elsif ($ch eq '"') {
        $ch = shift(@chars);
        $state = 'string';
        next;
      }
      else {
        $token = $ch;
        $ch = shift(@chars);
        $state = 'token';
        next;
      }
    }

    #=== token state ======================================
    elsif ($state eq 'token') {

      if (! defined $ch) {
        push(@tokens,$token);
        $token = "";
        $state = 'base';
        next;
      }
      if ($ch eq '#') {
        push(@tokens,$token);
        $token = "";
        $state = 'base';
        next;
      }
      elsif ($ch =~ m/\s/) {
        push(@tokens,$token);
        $token = "";
        $state = 'base';
        next;
      }
      else {
        $token .= $ch;
        $ch = shift(@chars);
        next;
      }
    }

    #=== string state =====================================
    elsif ($state eq 'string') {

      if (! defined $ch) {
        push(@tokens, $token);
        $token = "";
        $state = 'base';
        next;
      }
      elsif ($ch eq '"') {
        push(@tokens, $token);
        $token = "";
        $ch = shift(@chars);
        $state = 'base';
        next;
      }
      else {
        $token .= $ch;
        $ch = shift(@chars);
        next;
      }
    }

    #=== done state =======================================
    elsif ($state eq 'done') {
      last;
    }

  }


  #*******************************************************
  # Switch parsing state machine, turn tokens and strings
  # into switch hash values.
  #*******************************************************

  # Initialize state information
  $args = {};
  @nonSwitches = ();
  $token = shift(@tokens);
  $state = 'base';
  $switch = "";

  # Enter the state machine
  while (1) {

    #=== base state =======================================
    if ($state eq 'base') {

      if (! defined $token) {
        $state = 'done';
        next;
      }

      elsif ($token =~ m/^-/) {
        $switch = $token;
        $token = shift(@tokens);
        $state = 'switch';
        next;
      }

      else {
        push(@nonSwitches,$token);
        $token = shift(@tokens);
        next;
      }
    }

    #=== switch state =====================================
    elsif ($state eq 'switch') {

      if (! defined $token) {
        $args->{$switch} = '1';
        $switch = "";
        $state = 'done';
        next;
      }

      elsif ($token =~ m/^-/) {
        $args->{$switch} = '1';
        $switch = "";
        $state = 'base';
        next;
      }

      else {
        $args->{$switch} = $token;
        $token = shift(@tokens);
        $state = 'base';
        next;
      }
    }

    #=== done state =======================================
    elsif ($state eq 'done') {
      last;
    }
  }

  #*******************************************************
  # Done with state machine parsing
  #*******************************************************

  return $args;
}

#******************************************************************************
sub read32 {
  my ($fh) = shift(@_);
  my ($endianMode) = shift(@_);
  my ($val0,$val1,$val2,$val3,$val);

  read($fh, $val0, 1);
  read($fh, $val1, 1);
  read($fh, $val2, 1);
  read($fh, $val3, 1);
  $val0 = ord($val0);
  $val1 = ord($val1);
  $val2 = ord($val2);
  $val3 = ord($val3);

  $val = ($val3 << 24) | ($val2 << 16) | ($val1 << 8) | $val0;


  return $val;
}

#--------------------------------------------------------------------------------------------
sub doHelp {

  my ($helpText)  = shift(@_);


    print $helpText;


  exit();
}   
#----------------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------------

###############################################################################################
#    P A C K A G E    P A C K A G E    P A C K A G E    P A C K A G E    P A C K A G E
#
# DeviceCfg - Package implementing the configuration object.
#
###############################################################################################
package AISFile;
require 5.000;
use FileHandle;
use Symbol;
use File::Basename;

#******************************************************************************
sub AISFile::new {
  my ($class) = shift(@_);
  my ($name)  = shift(@_);
  my ($fileType) = shift(@_);
  my ($openMode) = shift(@_);
  my ($debugMode) = shift(@_);
  my ($bootMode) = shift(@_);
  
  my ($this)  = {};
  bless($this,$class);

  $this->{'fh'} = gensym;
  $this->{'endianMode'} = "little";
  $this->{'name'} = $name;
  $this->{'debugMode'} = $debugMode;
  $this->{'bootMode'} = $bootMode;
  

  open($this->{'fh'}, "$openMode $name") || die "Can't open $name!";
  binmode($this->{'fh'}) if ($fileType eq 'BIN');
  $this->{'write'} = \&writeASM if ($fileType eq 'ASM');
  $this->{'write'} = \&writeASCII if ($fileType eq 'ASCII');
  $this->{'write'} = \&writeBIN if ($fileType eq 'BIN');
  $this->{'write'} = \&writeTXT if ($fileType eq 'TXT');

  return $this;
}

#******************************************************************************
sub AISFile::DESTROY {
  my ($this) = shift(@_);
  close($this->{"fh"});
}

#******************************************************************************
sub AISFile::eof {
  my ($this) = shift(@_);
  return eof($this->{"fh"});
}

#******************************************************************************
sub AISFile::seek {
  my ($this) = shift(@_);
  my ($position) = shift(@_);
  seek($this->{"fh"}, $position, 0);
}

#******************************************************************************
sub AISFile::tell {
  my ($this) = shift(@_);
  return tell($this->{"fh"});
}



#

#--------------------------------------------------------------------------------------------
sub AISFile::writeASM {
	
	my($OUT) = shift(@_);
	my($data) = shift(@_);
	my($addrPtr) = shift(@_);
	my($fh) = $OUT->{'fh'};
	my($addr);
	
	$addr = $$addrPtr;
	
	if ($OUT->{'debugMode'}) {
        printf $fh "\t.word 0x%08X\t\t;Flash Address 0x%08X\n",$data,$addr;
    } else {
        printf $fh "\t.word 0x%08X\n",$data;
    }
    	    
    $addr += 4;
    $$addrPtr = $addr;
    
    return;
}

#--------------------------------------------------------------------------------------------
sub AISFile::writeASCII {
	
	my($OUT) = shift(@_);
	my($data) = shift(@_);
	my($addrPtr) = shift(@_);
	my($fh) = $OUT->{'fh'};
	my($addr);
	
	$addr = $$addrPtr;
	
	if ($OUT->{'debugMode'}) {
        printf $fh "\t0x%08X\t\t;Flash Address 0x%08X\n",$data,$addr;
    } else {
          printf $fh "\t0x%08X\n",$data;
    }  
    
    $addr += 4;
    
    $$addrPtr = $addr;
    
    return;
}


#--------------------------------------------------------------------------------------------
sub AISFile::writeTXT {
	
	my($OUT) = shift(@_);
	my($data) = shift(@_);
	my($addrPtr) = shift(@_);
	my($fh) = $OUT->{'fh'};
	my($addr);
	
	$addr = $$addrPtr;
	
	if ($OUT->{'debugMode'}) {
        printf $fh "\t0x%08X\t\t;Flash Address 0x%08X\n",$data,$addr;
    } else {
		    printf $fh "%08X",$data;
    } 
    $addr += 4;
    
    $$addrPtr = $addr;
    
    return;
}


#--------------------------------------------------------------------------------------------
sub AISFile::writeBIN {
	
	my($OUT) = shift(@_);
	my($data) = shift(@_);
	my($addrPtr) = shift(@_);
	my($fh) = $OUT->{'fh'};
	my ($packedData);
	
	binmode($fh);
    $packedData = pack("V",$data);
     syswrite($fh, $packedData, length($packedData));

    $$addrPtr += 4;
    
    return;
}

__END__
###############################################################################################
# End of File
###############################################################################################
  