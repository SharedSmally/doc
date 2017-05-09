Eclipse:
=======

## Eclipse + Web Service
- Install Server: Apache Tomcat or other Application Server

    - For Tomcat: need to download Extra-> Web Service jar, and save it in lib/
    
    - Config Eclipse to use Server: Windows ->Preference -> Server -> Runtune Environment -> Add [include name and installation home dir]

- Install Web Service runtime: Either Apache CXF or Apache Axis 2

    - Config Web Service: Windows->Preference->Web Services:
    
         - CXF 2.0 Preferences->Add [installation home dir]
         
         - Scenario Defaults: Select default behavoirs for Server and Client src generation 
         
         - Server and Runtime: Select server and Web service runtime
    
- Create a new Web Dynamic Project / Spring Boot project
 
    - Right click on the project => Properties => Project Facets:  Select CXF 2.0 Web Service; Dynamic Web Module; Java; xxx
    
    - Project Facet: Define characteristics and requirements for **Java EE** projects and are used as part of the runtime configuration
    
    - Create folder meta\/wsdl; added \*.wsdl files (will be copied to WebContent/wsdl).
    
    - Generate server skeleton:   Right Click \*.wsdl file => Web Services => Generate Java Bean skeleton =>  Top Down Javabean Web Service -> Specify WSDL nnamespace to Package Name Mappings(Check and update: source folde) => Finish
    
    - Start Server: Right Click on Project => RunAs => Sprint Boot App

    - Test with SoapUI:
     
       - File -> New Soap Project -> Project Name; Initial WSDL (define endpoint, such as: http://localhost:9080/ThirdPartyCallService/services/ThirdPartyCall: (soap:address/location in \*.wsdl) PortTypes defines Operations)
       
       - For each operation; Add new Request -> Update Request Contents -> Submit Request to the specific endpoint
       
       
       
## Style
- Show whitespaces: Window>Preferences>General>Editors>Text Editors
