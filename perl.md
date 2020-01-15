# perl

## Install Missing Module:
- Linux: cpan install  module
- Windows: ppm install module

## Tips
- sed
```
#!/usr/bin/perl
if (@ARGV == 1) {
    open(INFILE, "$ARGV[0]") || die "ERROR: Cannot read input file $ARGV[1]\n";
    @lines=<INFILE>; close INFILE;
} else { die "Not input file !\n"; }

open(OUTFILE, "> $ARGV[0]") || die "ERROR: Cannot write output file $ARGV[0]\n";
foreach(@lines) {
    s|tag \"[^\"]*\"|tag \"$ENV{TAG}\"|g;
    s|JAVAHOME \"[^\"]*\"|JAVAHOME \"$ENV{JAVA_HOME}\"|g;
    s|\"[^\"]*app.ent|\"$ENV{APP_HOME}/meta/app.ent|g;
    s|app.&css;adm0|$ENV{HOSTNAME}|g;
    s|%USER%|$ENV{USER}|g;   
    s|\"DSN=[^\"]*\"|\"DSN=PostgresDSN"|g unless /FLRDB/;
    s|hostname|$ENV{HOSTNAME}|g;
    s|(<EnvVar name=\"LD_LIBRARY_PATH\" value=\"&CORE;/lib.*true\"/>)|$1 \n$ld_library_path|g;
    s|ADMCluster|Cloud|g;
    s|\"tag.value\" value=\"[^\"]*\"|\"tag.value\" value=\"{{ ansible.tag.value \|e}}\"|g;
    s|\"tag.jdbc\" value=\"[^\"]*\"|\"tag.jdbc\" value=\"jdbc:postgresql:\/\/{{ host \|e}}:{{ port \|e}}\/{{ db_name \|e}}?user={{ db_user \|e}}&amp;password={{ db_passwd \|e}}\"|g;
    
    print OUTFILE $_;
}
close OUTFILE;
```

## [XML DOM](http://www.cgi101.com/modules/XML.dom.html)
## [XML LibXML](http://search.cpan.org/~shlomif/XML-LibXML/LibXML.pod)
### [Document](http://search.cpan.org/dist/XML-LibXML/lib/XML/LibXML/Document.pod)
 - XML document with version, encoding, createElement/Attribute; PI, ...

```
my $parser = new XML::DOM::Parser;
my $dom = $parser->parsefile ($fname); 
my $root = $dom->getDocumentElement();
my $body = $dom->createElement('body');
$root->appendChild($body);
print $root->toString;
```

```
my $dom = XML::DOM::Document->new;
my $xml_pi = $dom->createXMLDecl ('1.0');
my $root = $dom->createElement('html');
my $body = $dom->createElement('body');
$root->appendChild($body);
$root->setOwnerDocument ($dom);
print $dom->toString;

#dom document has only one child:
# use dom->appendChild() if no root element
# or dom->replaceChild() if root element exists
```
