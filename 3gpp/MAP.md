# MAP
App: HLR|VLR|MSC|EIR
L7:      M A P 
L4-6:   T C A P
L3:    S C C P

## [Packets](https://wiki.wireshark.org/GSMMAP)

## TCAP Messages
Types:
- TCAP-Begin
- TCAP-Continue
- TCAP-End
- TCAP-Abort

Dialog Portion:
- Request
- Response
- Abort

Component Portion
- Invoke: Start an operation on the receive side
- Return Result: Result of a dialog opened by an Invoke
- Return Error: Answer to a Invoke if an operation cannot be completed
- Reject: An application is unable to process a component because of error
