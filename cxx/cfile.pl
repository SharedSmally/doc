#!/bin/perl

my $total = $#ARGV + 1;

if ($total==1) {
   createHFile("",$ARGV[0]);
   createCXXFile("",$ARGV[0]);
} elsif ($total > 1) {
	my $ns=$ARGV[0];
	shift;
	
	foreach my $a(@ARGV) {
       createHFile($ns,$a);
       createCXXFile($ns,$a);
   }
}


sub createHFile {
	my ($ns,$name)=@_;

	my $hns=$ns;
	$hns =~ s/\./_/g;
	$hns = uc($hns);
	$hns .= '_' if (length($hns)>0);
	$hns .= uc($name);
	$hns .= "_H";
	
	my @nss=split('\.',$ns);
	
	my $clsname=ucfirst($name);
	
	print " generat head file: ${clsname}.h\n";
	
	open(my $fh, '>', "$clsname.h");
	print $fh "#ifndef $hns\n";
	print $fh "#define $hns\n\n";
	
	foreach my $myns (@nss) {
		print $fh "namespace $myns {\n";
	}
	
	print $fh "\n" if (length($ns)>0);
	
	print $fh "class $clsname {\n\n";
	print $fh "public:\n";
	print $fh "    $clsname();\n";
	print $fh "    virtual ~$clsname();\n\n";
	print $fh "protected:\n\n";
	print $fh "private:\n\n";
	print $fh "};\n\n";

	foreach my $myns (@nss) {
		print $fh "}\n";
	}
	print $fh "\n" if (length($ns)>0);

	print $fh "#endif /* end of $hns */\n";
	
	close $fh;
}

sub createCXXFile {
	my ($ns,$name)=@_;
	my $clsname=ucfirst($name);
	my @nss=split('\.',$ns);
	
	print " generat  cxx file: ${clsname}.cc\n";	
	open(my $fh, '>', "${clsname}.cc");
	print $fh "#include <${clsname}.h>\n\n";

	foreach my $myns (@nss) {
		print $fh "namespace $myns {\n";
	}
	
	print $fh "\n" if (length($ns)>0);
	
	print $fh "${clsname}::${clsname}()\n";
	print $fh "{}\n\n";

	print $fh "${clsname}::~${clsname}()\n";
	print $fh "{}\n\n";
	
	foreach my $myns (@nss) {
		print $fh "}\n";
	}
	print $fh "\n" if (length($ns)>0);
	
	close $fh;	
}
