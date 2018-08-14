# [SIGTRAN protocols](https://en.wikipedia.org/wiki/SIGTRAN)
## [TCAP](https://www.itu.int/ITU-T/recommendations/index.aspx?ser=Q): 771-775
- Q.771: Functional description of transaction capabilities
-	Q.772: Transaction capabilities information element definitions
-	Q.773: Transaction capabilities formats and encoding: ASN1
-	Q.774: Transaction capabilities procedures
-	Q.775: Guidelines for using transaction capabilities

## Signalling connection control part (SCCP): 711-715
-	Q.711: Functional description of the signalling connection control part
-	Q.712: Definition and function of Signalling connection control part messages
-	Q.713: Signalling connection control part formats and codes: ASN1
-	Q.714: Signalling connection control part procedures
-	Q.715: Signalling connection control part user guide
-	Q.716: Signalling System No. 7 – Signalling connection control part (SCCP) performance

## M3UA
- [RFC 4666](https://tools.ietf.org/rfc/rfc4666.txt) Signaling System 7 (SS7) Message Transfer Part 3 (MTP3) - User Adaptation Layer (M3UA)
- [RFC 3332](https://tools.ietf.org/rfc/rfc3332.txt): Obsolted by 4666
- [M2UA RFC 3331](https://tools.ietf.org/rfc/rfc3331.txt))
- [M2PA RFC 4165](https://tools.ietf.org/rfc/rfc4165.txt))

## SCCP Address

## [PC (PointCode)](https://en.wikipedia.org/wiki/Point_code)
An SS7 point code is similar to an IP address in an IP network. It is a unique address for a node (Signaling Point, or SP), used in MTP layer 3 to identify the destination of a message signal unit (MSU):
- OPC (Originating Point Code) 
- DPC (Destination Point Code)
- ISPC International Signaling Point Code

Depending on the network, a point code can be 24 bits (North America, China), 16 bits (Japan), or 14 bits (ITU standard, International SS7 network and most countries) in length:
- ANSI point codes use 24 bits, mostly in 8-8-8 format
- ITU point codes use 14 bits and are written in 3-8-3 format
