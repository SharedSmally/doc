URL_SPEC=http://openmobilealliance.org/wp/index.html
#URL_API=http://openmobilealliance.org/wp/API_Inventory.html
#NGSI: OMA Next Generation Services Interface: http://www.openmobilealliance.org/release/NGSI/(V1_0-20120529-A)
#SOAP: SOAP binding for NGSI: http://www.openmobilealliance.org/release/NGSI_S/(V1_0-20120529-A)
#ParlayX: Parlay Service Access 1.0: PSA(V1_0-20100427-A)
#REST: RESTful Network API for xxx
#Schema: http://openmobilealliance.org/wp/supporting_data.html: DTD/XSD/WSDL/JSD/IDL
URL_DTD=http://openmobilealliance.org/tech/dtd/
URL_XSD=http://openmobilealliance.org/tech/profiles/
URL_WSDL=http://openmobilealliance.org/tech/wsdl/
URL_JSD=http://openmobilealliance.org/tech/JSD/
#URL_OMNA:http://openmobilealliance.org/tech/omna/ *.ddf
#   

main:

spec:
	cp oma_$@.html tmp.xml
	sed -i '/^<!doctype\s/d' tmp.xml
	sed -i '/^<link\s/d' tmp.xml
	sed -i '/^<meta\s/d' tmp.xml
	sed -i '/^<img\s/d' tmp.xml
	sed -i 's/<br>/<br\/>/g' tmp.xml
	xsl xsl/oma_$@.xsl tmp.xml oma_$@.xml
#	
xsd dtd wsdl omna:
	cp oma_$@.html tmp.xml
	sed -i 's/<br>/<br\/>/g' tmp.xml
	sed -i 's/<hr>/<hr\/>/g' tmp.xml
	xsl xsl/oma_$@.xsl tmp.xml oma_$@.xml

update:
	wget ${URL_SPEC} -O oma_spec.html
	wget ${URL_DTD}  -O oma_dtd.html
	wget ${URL_XSD}  -O oma_xsd.html
	wget ${URL_WSDL} -O oma_wsdl.html
	wget ${URL_JSD}  -O oma_omna.html
