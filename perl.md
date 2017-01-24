# perl

##[XML DOM](http://www.cgi101.com/modules/XML.dom.html)

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
```
