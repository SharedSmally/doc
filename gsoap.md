== [gSOAP](https://www.cs.fsu.edu/~engelen/soap.html):  

SOAP and REST XML Web services and generic C/C++ XML data bindings. It is compliant with WS-I Basic Profile 1.0a, 1.1, and 1.2, passed W3C Databinding interoperability testing, and interoperates with other SOAP/REST stacks such as WCF, .NET, and Axis.


== Quick How-to
- Run wsdl2h to obtain a header file from a WSDL document or a Web location of the WSDL:
```
wsdl2h -o outfile.h infile.wsdl
wsdl2h -o XMethodsQuery.h http://www.xmethods.net/wsdl/query.wsdl
```
- Run gSOAP compiler 'soapcpp2' on the gSOAP header file to produce the source code to implement the client application.

The gSOAP runtime library provides a transport layer with an HTTP stack on top of TCP/IP as well as secure SSL and DIME/MIME attachment support.

- Run the gSOAP 'wsdl2h' parser on a WSDL to create a gSOAP header file to develop a service application
