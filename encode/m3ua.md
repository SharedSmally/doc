## M3UA - SCCP - TCAP - MAP

G [0x7f8fd764b700]           M3UAParser.cc -   23 : (1582726797:453) Received 0x010001010000002C021000210000107D0000107E03020000090003050702C20102C2010502917D1001000000
G [0x7f8fd764b700]             M3UALink.cc -  220 : link 0 stream 1 received DATA length=44 protocolData={opc=4221, dpc=4222, si=3, ni=2, mp=0, sls=0, dataLen=17}
G [0x7f8fd764b700]           M3UAParser.cc -   23 : (1582726797:453) Received 0x010001010000002C021000210000107D0000107E03020000090003050702C20102C2010501917D1001000000
G [0x7f8fd764b700]             M3UALink.cc -  220 : link 0 stream 1 received DATA length=44 protocolData={opc=4221, dpc=4222, si=3, ni=2, mp=0, sls=0, dataLen=17}
G [0x7f8fd7596700]        SCCPSubsystem.cc -  192 : received UnitData mhandling=0, pclass=0, clg={ssn-routed ssn 1}, cld={ssn-routed ssn 1}, datalen=5
G [0x7f8fd7596700]        SCMGSubsystem.cc -   56 : received SCMG SSP affectedSSN=145 affectedPC=4221 multiplicity=1
G [0x7f8fd75b7700]        SCCPSubsystem.cc -  192 : received UnitData mhandling=0, pclass=0, clg={ssn-routed ssn 1}, cld={ssn-routed ssn 1}, datalen=5
G [0x7f8fd75b7700]        SCMGSubsystem.cc -   56 : received SCMG SSA affectedSSN=145 affectedPC=4221 multiplicity=1

        <SendMessage name="Send SLR CO" packageType="0x62" timeout="20000" acName="0.1.2.3.4.5.6.7" calledssn="145">
            <Component type="0xa1">
                <Opcode value="0x56"/>
                <ComponentID value="0x00"/>
                <Parameters tag="0x30" value="0x30700A0100302A800101A10880069021435344F58207902160972216F2A412800163820A53617479614B756D6172830101300B0409940100000000000110800
69144871132008107022287113200F0820821436500896745F08508100C0C0C0C0C0C0C860204D2AD09800723636803F20193"/>
            </Component>
        </SendMessage>
		
T [0x7f8fd750c700]         StateMachine.cc -   92 : executing next state 2 type SendMessage name Send SLR CO
G [0x7f8fd750c700]        ITUTCAPParser.cc -  501 : (1582726798:354)
dialogue {
   dialogueRequest {
      protocol_version = { 0,  }
      application_context_name = { 0 1 2 3 4 5 6 7 }
   }
}

		
G [0x7f8fd750c700]        ITUTCAPParser.cc -  612 : (1582726798:355)
outbound {
   begin {
      otid = 0x00000000
      dialoguePortion {
         direct_reference = { 0 0 17 773 1 1 1 }
         encoding {
            single-ASN1-type = 0x600ba109060701020304050607
         }
      }
      components[0] {
         invoke {
            invokeID = 0
            operationCode = 86
            parameter =
30 70 0a 01 00 30 2a 80 01 01 a1 08 80 06 90 21  0p...0*........!
43 53 44 f5 82 07 90 21 60 97 22 16 f2 a4 12 80  CSD....!`.".....
01 63 82 0a 53 61 74 79 61 4b 75 6d 61 72 83 01  .c..SatyaKumar..
01 30 0b 04 09 94 01 00 00 00 00 00 01 10 80 06  .0..............
91 44 87 11 32 00 81 07 02 22 87 11 32 00 f0 82  .D..2...."..2...
08 21 43 65 00 89 67 45 f0 85 08 10 0c 0c 0c 0c  .!Ce..gE........
0c 0c 0c 86 02 04 d2 ad 09 80 07 23 63 68 03 f2  ...........#ch..
01 93                                            ..
         }
      }
   }
}

G [0x7f8fd750c700]        SCCPSubsystem.cc -  382 : encoded SCCP UnitData mhandling=0, pclass=0, clg={ssn-routed ssn 8}, cld={ssn-routed ssn 145}, datalen=161
G [0x7f8fd750c700]             M3UALink.cc -  207 : link 0 stream 1 sending m3ua DATA length=200 protocolData={opc=4222, dpc=4221, si=3, ni=2, mp=0, sls=0, dataLen=173}
G [0x7f8fd750c700]             M3UALink.cc -  212 : (1582726798:355) Sending 0x01000101000000C8021000BD0000107E0000107D030200000900030507024291024208A162819E4804000000006B1A28
18060700118605010101A00D600BA1090607010203040506076C7AA17802010002015630700A0100302A800101A10880069021435344F58207902160972216F2A412800163820A53617479614B756D6172830101300B040
994010000000000011080069144871132008107022287113200F0820821436500896745F08508100C0C0C0C0C0C0C860204D2AD09800723636803F20193000000
G [0x7f8fd750c700]        M3UASubsystem.cc -  199 : sent M3UA message through the Link 0


        <ReceiveMessage name="Receive SLR CO RRL" packageType="0x64" grade="true" timeout="20000">
            <Component type="0xa2">
                <ComponentID value="0x00"/>
                <Parameters tag="0x30">
                </Parameters>
            </Component>
        </ReceiveMessage>
T [0x7f8fd750c700]         StateMachine.cc -   92 : executing next state 3 type ReceiveMessage name Receive SLR CO RRL
T [0x7f8fd750c700]        SigtranTester.cc -  403 : haven't received a message yet.  waiting 20000
G [0x7f8fd764b700]           M3UAParser.cc -   23 : (1582726798:383) Received 0x01000101000000640210005A0000107D0000107E0302000009000305070242080242913E643C4904000000006B26282
4060700118605010101A0196117A109060701020304050607A203020100A305A1030201006C0CA20A020100300502015630000000
G [0x7f8fd764b700]             M3UALink.cc -  220 : link 0 stream 1 received DATA length=100 protocolData={opc=4221, dpc=4222, si=3, ni=2, mp=0, sls=0, dataLen=74}
G [0x7f8fd7596700]        SCCPSubsystem.cc -  192 : received UnitData mhandling=0, pclass=0, clg={ssn-routed ssn 145}, cld={ssn-routed ssn 8}, datalen=62
G [0x7f8fd7596700]    TCAPSCCPSubsystem.cc -   79 : application TCAP message
G [0x7f8fd7596700]        ITUTCAPParser.cc -   65 : (1582726798:384)
inbound {
   end {
      dtid = 0x00000000
      dialoguePortion {
         direct_reference = { 0 0 17 773 1 1 1 }
         encoding {
            single-ASN1-type = 0x6117a109060701020304050607a203020100a305a103020100
         }
      }
      components[0] {
         returnResultLast {
            invokeID = 0
            result {
               operationCode = 86
               parameter = 0x3000
            }
         }
      }
   }
}

G [0x7f8fd7596700]        ITUTCAPParser.cc -  276 : (1582726798:384)
dialogue {
   dialogueResponse {
      protocol_version = { 1, 1xxxxxxx }
      application_context_name = { 0 1 2 3 4 5 6 7 }
      result = accepted
      result_source_diagnostic {
         dialogue-service-user = null_
      }
   }
}

T [0x7f8fd7596700]    TCAPSCCPSubsystem.cc -  101 : received response with tid=0
D [0x7f8fd750c700]     GradeableMessage.cc -   88 : packageType matches
D [0x7f8fd750c700]     GradeableMessage.cc -  101 : component type matches
D [0x7f8fd750c700]     GradeableMessage.cc -  156 : component ID matches
D [0x7f8fd750c700]      GradeableParams.cc -   80 : parameter with tag 0x30 matches expected


        <SendMessage name="Send SLR CallOrigination" packageType="0x62" timeout="20000" acName="0.1.2.3.4.5.6.7" calledssn="145">
            <Component type="0xa1">
                <Opcode value="0x56"/>
                <ComponentID value="0x00"/>
                <Parameters tag="0x30" value="0x305C0A0101302A800101A10880069021435344F58207902160972216F2A412800163820A53617479614B756D6172830101300A0408A1068044878188F880069
144871132008508100C0C0C0C0C0C0C860204D2AD09800723636803F20193"/>
            </Component>
        </SendMessage>

T [0x7f8fd750c700]         StateMachine.cc -   91 : state succeeded
T [0x7f8fd750c700]         StateMachine.cc -   92 : executing next state 5 type SendMessage name Send SLR CallOrigination
T [0x7f8fd750c700]    TCAPSCCPSubsystem.cc -  142 : new AI transaction started with timeout 20
G [0x7f8fd750c700]        ITUTCAPParser.cc -  501 : (1582726818:353)
dialogue {
   dialogueRequest {
      protocol_version = { 0,  }
      application_context_name = { 0 1 2 3 4 5 6 7 }
   }
}

G [0x7f8fd750c700]        ITUTCAPParser.cc -  612 : (1582726818:353)
outbound {
   begin {
      otid = 0x01000000
      dialoguePortion {
         direct_reference = { 0 0 17 773 1 1 1 }
         encoding {
            single-ASN1-type = 0x600ba109060701020304050607
         }
      }
      components[0] {
         invoke {
            invokeID = 0
            operationCode = 86
            parameter =
30 5c 0a 01 01 30 2a 80 01 01 a1 08 80 06 90 21  0\...0*........!
43 53 44 f5 82 07 90 21 60 97 22 16 f2 a4 12 80  CSD....!`.".....
01 63 82 0a 53 61 74 79 61 4b 75 6d 61 72 83 01  .c..SatyaKumar..
01 30 0a 04 08 a1 06 80 44 87 81 88 f8 80 06 91  .0......D.......
44 87 11 32 00 85 08 10 0c 0c 0c 0c 0c 0c 0c 86  D..2............
02 04 d2 ad 09 80 07 23 63 68 03 f2 01 93        .......#ch....
         }
      }
   }
}

G [0x7f8fd750c700]        SCCPSubsystem.cc -  382 : encoded SCCP UnitData mhandling=0, pclass=0, clg={ssn-routed ssn 8}, cld={ssn-routed ssn 145}, datalen=141
G [0x7f8fd750c700]             M3UALink.cc -  207 : link 0 stream 2 sending m3ua DATA length=180 protocolData={opc=4222, dpc=4221, si=3, ni=2, mp=0, sls=0, dataLen=153}
G [0x7f8fd750c700]             M3UALink.cc -  212 : (1582726818:354) Sending 0x01000101000000B4021000A90000107E0000107D0302000009000305070242910242088D62818A4804010000006B1A28
18060700118605010101A00D600BA1090607010203040506076C66A164020100020156305C0A0101302A800101A10880069021435344F58207902160972216F2A412800163820A53617479614B756D6172830101300A040
8A1068044878188F880069144871132008508100C0C0C0C0C0C0C860204D2AD09800723636803F20193000000
G [0x7f8fd750c700]        M3UASubsystem.cc -  199 : sent M3UA message through the Link 0


        <ReceiveMessage name="Receive SLR CallRelease RRL" packageType="0x64" grade="true" timeout="20000">
            <Component type="0xa2">
                <ComponentID value="0x00"/>
                <Parameters tag="0x30">
                </Parameters>
            </Component>
        </ReceiveMessage>

T [0x7f8fd750c700]         StateMachine.cc -   92 : executing next state 6 type ReceiveMessage name Receive SLR CallRelease RRL
T [0x7f8fd750c700]        SigtranTester.cc -  403 : haven't received a message yet.  waiting 20000
G [0x7f8fd764b700]           M3UAParser.cc -   23 : (1582726818:363) Received 0x01000101000000640210005A0000107D0000107E0302000009000305070242080242913E643C4904010000006B26282
4060700118605010101A0196117A109060701020304050607A203020100A305A1030201006C0CA20A020100300502015630000000
G [0x7f8fd764b700]             M3UALink.cc -  220 : link 0 stream 1 received DATA length=100 protocolData={opc=4221, dpc=4222, si=3, ni=2, mp=0, sls=0, dataLen=74}
G [0x7f8fd7575700]        SCCPSubsystem.cc -  192 : received UnitData mhandling=0, pclass=0, clg={ssn-routed ssn 145}, cld={ssn-routed ssn 8}, datalen=62
G [0x7f8fd7575700]    TCAPSCCPSubsystem.cc -   79 : application TCAP message
G [0x7f8fd7575700]        ITUTCAPParser.cc -   65 : (1582726818:363)
inbound {
   end {
      dtid = 0x01000000
      dialoguePortion {
         direct_reference = { 0 0 17 773 1 1 1 }
         encoding {
            single-ASN1-type = 0x6117a109060701020304050607a203020100a305a103020100
         }
      }
      components[0] {
         returnResultLast {
            invokeID = 0
            result {
               operationCode = 86
               parameter = 0x3000
            }
         }
      }
   }
}

G [0x7f8fd7575700]        ITUTCAPParser.cc -  276 : (1582726818:363)
dialogue {
   dialogueResponse {
      protocol_version = { 1, 1xxxxxxx }
      application_context_name = { 0 1 2 3 4 5 6 7 }
      result = accepted
      result_source_diagnostic {
         dialogue-service-user = null_
      }
   }
}

T [0x7f8fd7575700]    TCAPSCCPSubsystem.cc -  101 : received response with tid=1
