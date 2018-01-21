
	find ./ -name pom.xml | xargs sed -i 's/1.0-SNAPSHOT/1.0.0/g'
	find ./ -name pom.xml | xargs sed -i 's/<groupId>junit/<groupId>org.springframework/g'
	find ./ -name pom.xml | xargs sed -i 's/junit/spring-context/g'
	find ./ -name pom.xml | xargs sed -i "s/3.8.1/\x24{spring.version}/g"   => \x24 = $
  
