#!/usr/bin/perl

#
# generate index.html for a list of directory
#
#    fileIndex.pl title htmlfile dir1 dir2 ... dirn
#
#
# list file/dir sort by time(-t),no owner(-g),no group(-G),no backup(~,-B),
#      reverse sorting(-r)x, 
#      time-style: full-iso, long-iso, iso q
my $cmd="ls -lBgGt --time-style long-iso --group-directories-first";

sub generateHtml {
	my ($title,$htmlfile,$dir)=@_;
	my $fullfname = $dir =~ /\/$/ ? "${dir}${htmlfile}" : "$dir/$htmlfile";
	
	if ( ! -d $dir ) { print "directory $dir not exists\n"; return;}
	
	print "create $fullfname\n";
	
	open(OUTFILE, "> ${fullfname}") || die "ERROR: Cannot write output file ${fullfname}\n";
	print OUTFILE "<html><head><title>${title}</title></head><body><H1>${title}</H1><hr><pre>";
	print OUTFILE "<A HREF=\"../\">[To Parent Directory]</A><br><br>";
	
	my $files=system("cd $dir && $cmd > tmp.txt");
    open(INFILE, "$dir/tmp.txt") || die "ERROR: Cannot read output from $dir/tmp.txt\n";
    system("cd $dir && rm tmp.txt");
    my @lines=<INFILE>; close INFILE;
    foreach(@lines) {
        my @items = split(/\s+/,$_);
        my $size= $items[0] =~ /^d/ ? '     &lt;dir&gt;' : $items[2]; #10chars
        my $date=$items[3]; $date =~ s/-/\//g;
        my $info=sprintf("%s %s %10s  ",$date,$items[4],$size);
        #  1/13/2020  8:21 AM      1885117 <A HREF="/ftp/Specs/latest/Rel-15/38_series/38101-1-f81.zip">38101-1-f81.zip</A><br>
        print OUTFILE "$info<A HREF=\"./$items[5]\">$items[5]</A><br>";
    }
	print OUTFILE "</pre><hr></body></html>";
	close OUTFILE;
}

my $title="index";
my $dir=".";
my $htmlfile="index.html";

if (@ARGV==1) {
    if ($ARGV[0] =~ /-h/ || $ARGV[0] =~ /help/ || $ARGV[0] =~ /--help/) {
       print "Usage: $0 [title [htmlfile|index.xml] [directories|.]\n";
       exit 0;
    } else {
       $title=shift @ARGV;
    }
} elsif (@ARGV>=2) {
    $title=shift @ARGV;
    $htmlfile=shift @ARGV;
}

if (@ARGV>1) {
	foreach (@ARGV) {
	    generateHtml($title,$htmlfile,$_);
	}
} else {
	generateHtml($title,$htmlfile,$dir);
}
