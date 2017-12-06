
## ASN1

### PDU (Protocol Data Unit): [wiki](https://en.wikipedia.org/wiki/Protocol_data_unit)
The global top level message unit that contains all of the data that can be sent as an independent unit.


### Online Decoder
- [Marben] ( http://www.marben-products.com/asn.1/services/decoder-asn1-add.html)

### Tools:
- Open Source [asn1c](https://github.com/vlm/asn1c) 
- [DMT:Data Modelling Tools](http://download.tuxfamily.org/taste/DMT/DMT-latest.tgz): contains open source [asn1c] (https://github.com/ttsiodras/asn1scc) compiler (Download from http://download.tuxfamily.org/taste/DMT/DMT-latest.tgz)

### [ASN1 Wiki](https://en.wikipedia.org/wiki/Abstract_Syntax_Notation_One)

### ObjSys Asn1 Compiler
-  ASN1T_xxx: Contains Data
-  ASN1C_xxx: Manipulate the ASN1T_xxx data object, such as for add/remove ops for List/Array
-  XXXEncode/DecodeBuffer: Buffer to encode/decode asn1 message

### Encoder/Decoders:

#### BER, DER, CER

The oldest encoding rules, the Basic Encoding Rules (BER), use a Tag-Length-Value (TLV) format for encoding all information. BER always sends a tag to indicate what kind of data follows, then a length indicating the length of the data that follows, then the value which is the actual data. Two related encoding rules, the Distinguished Encoding Rules (DER) and the Canonical Encoding Rules (CER) are subsets of BER which eliminate some of the extra flexibility provided by BER. Note that DER is commonly used in security-related applications such as X.509 digital certificates.

#### OER

The fastest ASN.1 encoding rules are the Octet Encoding Rules (OER). The Octet Encoding Rules (OER), like the Packed Encoding Rules (PER), produce compact encodings by taking advantage of information present in the ASN.1 schema to limit the amount of information included in each encoded message. However, in contrast to PER, OER favors encoding/decoding speed and ease of implementation over compactness of the encodings. Unlike PER Aligned, OER is completely octet-oriented. Whereas in PER Aligned a fixed-size encoding occupying less than 8 bits may begin at any bit position within an octet and may end at any bit position within the same or another octet, in OER the encoding of every possible value of every ASN.1 type occupies a whole number of octets, and all the fields of the encoding are octet-aligned. OER is used in Intelligent Transportation protocols and is highly suited for any protocol for which the speed of encoding/decoding is essential.

#### PER (most are unaligned PER)

The unaligned PER data is essentially an ordered stream of bits, and not an ordered stream of bytes like with aligned PER. In aligned OER, each octet is padded individually with null bits on their unused most significant bits.

The most compact encoding rules are the Packed Encoding Rules (PER). PER differs from BER in that PER does not send the Tag of the TLV since the order in which components of the message occur is known. PER also does not send the Length of the TLV if the Value has a fixed length. PER also uses additional information from the ASN.1 message description to eliminate redundant information from the Value portion of the TLV, thus making PER messages quite compact and suitable for environments in which bandwidth conservation is important. There are two ways to encode messages in PER-Aligned and Unaligned. With the Aligned PER, a field can be aligned to 8-bit octet boundaries by inserting padding bits. With the Unaligned PER, pad bits are never inserted between fields. Unaligned PER is commonly used in 3GPP cellular technologies such as UMTS (3G) or LTE (4G) for protocols like RANAP, NBAP or RRC.

#### XER, E-XER

The least compact of the encoding rules, the XML Encoding Rules (XER), uses a textual XML format for its encodings of the form <start-tag> value <end-tag>. The XER and E-XER (Extended XER) differ in that the default encodings produced by E-XER are more suitable for exchanging information with XML Schema Definition (XSD) engines. Note that the same ASN.1 specification can be used with multiple encoding rules, which means that a PER message from a cell phone could be converted to E-XER for display and manipulation in a web browser.

#### JER

The JSON encoding rules (JER), compared to XER or E-XER, provide a more compact and easy-to-use encoding method. The encoding of ASN.1 types using JER is based on the JSON specification (RFC-7159). JER combines the advantages of the popular JSON data format and the benefits of ASN.1: ASN.1 schemas are easier to read and can be used to validate regular JSON messages, ASN.1 endpoints can communicate with JSON endpoints (the encoding of primitive types matches the encoding of JSON messages), etc. JER enables ASN.1 users to easily debug and troubleshoot ASN.1 protocols. The following example shows a JSON message with two variants of an ASN.1 schema:

### Samples:
```
length:0x0034: (52bytes) 

lpp payload (10bytes): 0x92FC1023204010000440 0          

0034020000C000005000000003FFFFFC0000004085102B0E9E5A0000000000000000000021001A8000992FC10232040100004400
ULP {
   length = 52
   version {
      maj = 2
      min = 0
      servind = 0
   }
   sessionID {
      setSessionID {
         sessionId = 0
         setId {
            msisdn = 0x1400000000ffffff
         }
      }
      slpSessionID {
         sessionID = 0x00000010
         slpId {
            iPAddress {
               ipv6Address = 0x0a20561d3cb400000000000000000000
            }
         }
      }
   }
   message {
      msSUPLPOS {
         posPayLoad {
            ver2-PosPayLoad-extension {
               lPPPayload[0] = 0x92fc1023204010000440
            }
         }
      }
   }
}
```

