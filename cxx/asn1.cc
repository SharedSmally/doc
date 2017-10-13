#objsys asn1 decode
ASN1T_ULP_PDU pdu;
ASN1C_ULP_PDU pduc(pdu);
unsigned char buffer_[MAX_BUFFER_SIZE];
uint32_t len_;

ASN1PERDecodeBuffer perBuffer(buffer, len, FALSE); //unaligned
asn1Init_ULP_PDU(&pdu);
int16_t status = pduc_.DecodeFrom(perBuffer);

if(status == 0) { //successful
     printASNtoString(perBuffer);
} else { //error
     printASNErrorInfo(jsonBuf);
}

OSJSONEncodeBuffer jsonBuf(0, 0);
jsonBuf.setIndent(0);
ASN1C_PDU jsonC(jsonBuf, pdu);
int status = jsonC.Encode();
if(status == RT_OK) {
    printASN1(jsonBuf);
} else {
    printASNErrorInfo(jsonBuf);
}

template< class BUFFER >
void printASNtoString(BUFFER & buffer, const char *title) {
     char mybufr[ASN1_BUFFER_SIZE];
     size_t len(sizeof(mybuf));
     memset(mybuf, 0, len) ;
     buffer.toString(title, mybuf, len);
     std::cout << mybuf << std::endl;
}
template< class BUFFER >
void printASN1(BUFFER & buffer, const char *title) {
    std::ostringstream oss;
    oss.write( (const char*)buffer.getMsgPtr(), buffer.getByteIndex());
    std::cout << oss.str() << std::endl;
}
template< typename BUFFER >
inline void printASNErrorInfo(BUFFER &buffer) {
     char mybuf[ASN1_ERROR_SIZE];
     size_t len(sizeof(mybuf));  memset(mybuf, 0, len);

     buffer.getErrorInfo(mybuf, len);
     std::cout << mybuf << std::endl;
}

ASN1C_ULP_PDU pdu;
unsigned char buf[MAX_BUFFER_SIZE];
ASN1PEREncodeBuffer encodeBuffer(buf, MAX_BUFFER_SIZE, FALSE);
ASN1C_ULP_PDU pduc(encodeBuffer, pdu);

int16_t status = pduc_.EncodeTo(encodeBuffer);
if (status==RT_OK) { //success
   printASNToString(buf);
   const unsigned char *ptr(encodeBuffer.getMsgPtr());
   uint16_t size(encodeBuffer.getMsgLen());
   ::be_val2mem(size,buf);
   pdu.length = size;
} else {
   printASNErrorInfo(encodeBuffer);
}

SUPLPOSINIT: 52=0x0034; 
0034010000C000005000000003FFFFFC0000000485102B0EA74F000000000000000000001A04093FF000000000CE80C000104D22
{
   length = 52
   version {
      maj = 1
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
         sessionID = 0x00000001
         slpId {
            iPAddress {
               ipv6Address = 0x0a20561d4e9e00000000000000000000
            }
         }
      }
   }
   message {
      msSUPLPOSINIT {
         sETCapabilities {
            posTechnology {
               agpsSETassisted = FALSE
               agpsSETBased = TRUE
               autonomousGPS = FALSE
               aflt = FALSE
               ecid = FALSE
               eotd = FALSE
               otdoa = FALSE
            }
            prefMethod = agpsSETBasedPreferred
            posProtocol {
               tia801 = FALSE
               rrlp = TRUE
               rrc = FALSE
            }
         }
         requestedAssistData {
            almanacRequested = TRUE
            utcModelRequested = TRUE
            ionosphericModelRequested = TRUE
            dgpsCorrectionsRequested = TRUE
            referenceLocationRequested = TRUE
            referenceTimeRequested = TRUE
            acquisitionAssistanceRequested = TRUE
            realTimeIntegrityRequested = TRUE
            navigationModelRequested = TRUE
            navigationModelData {
               gpsWeek = 0
               gpsToe = 0
               nsat = 0
               toeLimit = 0
            }
         }
         locationId {
            cellInfo {
               gsmCell {
                  refMCC = 826
                  refMNC = 12
                  refLAC = 1
                  refCI = 1234
               }
            }
            status = current
         }
      }
   }
}

#objsys asn1 encode
