URL=http://www.springframework.org/schema/

#NAMES=beans context oxm aop batch cache cloud  data jdbc jee jms ldap mvc rabbit redis task tool tx util web-services webflow websocket
NAMES=beans context oxm jdbc jee jms ldap mvc task tool tx util 
SPRING_NAMES=$(addprefix spring-,${NAMES})
 
main: ${SPRING_NAMES}

spring-%: spring-%.xsd
	
spring-%.xsd:	
	wget ${URL}/$*/$@ -O ./$@

.PRECIOUS: spring-%.xsd
