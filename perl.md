# perl

##[XML DOM](http://www.cgi101.com/modules/XML.dom.html)
##[XML LibXML](http://search.cpan.org/~shlomif/XML-LibXML/LibXML.pod)
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
