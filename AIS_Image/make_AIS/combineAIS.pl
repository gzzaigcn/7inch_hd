################################################################################
#
#   File:   package_il2.pl
#   Author: Sadanand Sheorey
#
#   Description: This perl script combines the AIS images of the secondary boot
#   loader and the application. The current boot-loader size is about 6 KB. To
#   accomodate any further changes to the boot-loader 10 KB is allocated. The
#   application image starts from this 10 KB offset.
#
#   Revision History:
#   0.1 - 18-sep-2009 - Sadanand Sheorey
#     - Initial revision
#   0.2 - 22-sep-2009 - Sadanand Sheorey
#     - Modified to eliminate cygwin/linux commands.
#
################################################################################

use strict;
use IO::File;
use File::Copy;
use Time::localtime;
use Time::Local;
#use POSIX qw(strftime);

if (@ARGV < 3)
{
    usage($0);
    exit (1);
}

my $sec_BL_img = shift;
my $app_img = shift;
my $combine_img = shift;

my $num_1kb_blk = 10;

# check if Secondary boot loader block-size is provided. 
if (@ARGV)
{
	$num_1kb_blk = shift;
}

#-----------------------------------------------------------------
# get the date.
#-----------------------------------------------------------------

my @months = qw(Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec); 
my $tm = localtime;
my ($day, $month, $year) = ($tm->mday, $tm->mon, $tm->year);
$year = $year+1900;

my $date = "$day-$months[$month]-$year";
print "Date: $date \n";

#-----------------------------------------------------------------

print "\nBL img : $sec_BL_img, App img : $app_img, combined img : $combine_img, Secondary BL block size : $num_1kb_blk KB\n";

#-----------------------------------------------------------------
# Combine the files.
#-----------------------------------------------------------------

# Limit size of the sec boot-loader image.
my $SB_limit_size = ($num_1kb_blk * 1024);

copy($sec_BL_img, $combine_img) or die "Cannot copy $sec_BL_img to $combine_img.\n";

#-----------------------------------------------------------------
# Add "0" padding till 10KB
#-----------------------------------------------------------------

my $sec_BL_size = -s $sec_BL_img;
my $patch_len = $SB_limit_size - $sec_BL_size;

print "\n    Sec BL size = $sec_BL_size, zero patch required = $patch_len\n";

if($patch_len < 0) {
	die "Error: Boot loader image greater than $SB_limit_size.\n";
}

# Using cat and system commands. For use with cygwin.
#system("cat /dev/zero | head -c $patch_len > TI_fill.dat");
#
#system("cat TI_fill.dat >> $combine_img");
#unlink("TI_fill.dat");
#
#system("cat $app_img >> $combine_img");


# Copy using perl only. For active perl / windows installations.

my $srcFileFH = new IO::File();
my $dstFileFH = new IO::File();

$dstFileFH->open(">>$combine_img");
$dstFileFH->binmode;

my $i;

# Add the "0" padding till 10KB.
for ($i = 0; $i < $patch_len; $i++) {
	printf $dstFileFH "\0";
}

# Append the application AIS image, starting from 10KB.

my $app_size = -s $app_img;
printf "Application image size = $app_size bytes. \n";

$srcFileFH->open("<$app_img");
$srcFileFH->binmode();

my $data;	# to store application image.
$srcFileFH->read($data, $app_size, 0);

print $dstFileFH $data;

$srcFileFH->close();
$dstFileFH->close();

print "Combined image $combine_img created.\n";

#--------------------------------------------------------------------
#--------------------------------------------------------------------

sub usage
{
    my  ($prog) = @_;

    $prog =~ s{.*/}{};

    print STDERR "\nUSAGE:\n\$> $prog <secondary BL AIS image> <application AIS image> <Final AIS image name> [secondary BL block size in KB (default 10)]\n\n";
}

sub trim
{
  my ($String) = @_;

  $String =~ s/^\s+//;
  $String =~ s/\s+$//;

  return ($String);
}

