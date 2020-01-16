#!/usr/bin/perl

open(INFILE, "$ARGV[0]") || die "ERROR: Cannot read input file $ARGV[1]\n";
@lines=<INFILE>; close INFILE;

open(OUTFILE, "> $ARGV[1]") || die "ERROR: Cannot write output file $ARGV[1]\n";

my $release=$ARGV[2];
my $series=$ARGV[3];

print OUTFILE "RELEASE=${release}\n";
print OUTFILE "SERIES=${series}\n\n";

print OUTFILE "DOC_DIR=/cygdrive/c/Users/$ENV{USER}/Documents/MyDoc/x3gpp/R${release}/S${series}\n";
print OUTFILE "URL_BASE=https://www.3gpp.org/ftp/specs/latest/Rel-${release}/${series}_series\n";

my $s0 = << 'END_MESSAGE';

main: init download doc
        ./fileIndex.pl "3GPP Release ${RELEASE} - Series ${SERIES}" index.html ${DOC_DIR} ${DOC_DIR}/zip

init: ${DOC_DIR}/zip

${DOC_DIR}/zip:
        mkdir -p $@

${DOC_DIR}/zip/%.zip:
        wget ${URL_BASE}/$*.zip -O $@

${DOC_DIR}/%.doc: ${DOC_DIR}/zip/%.zip
        unzip -o $< -d ${DOC_DIR}

download:  \
END_MESSAGE

print OUTFILE $s0;

foreach(@lines) {
    my @a0 = split(/\s+/, $_);
    print OUTFILE "     \${DOC_DIR}/zip/$a0[5]  \\\n" if ($a0[5] =~ /\.zip$/);
}
print OUTFILE "\n";
print OUTFILE "doc:  \\\n";
foreach(@lines) {
    my @a0 = split(/\s+/, $_);
    if ($a0[5] =~ /\.zip$/) {
       my $d0 = $a0[5];  $d0 =~ s/\.zip$/\.doc/g;
       print OUTFILE "  \${DOC_DIR}/$d0  \\\n" ;
    }
}

close OUTFILE;
