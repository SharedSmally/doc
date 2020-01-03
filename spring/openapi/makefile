# https://itnext.io/creating-a-java-spring-rest-service-from-an-openapi-3-0-definition-94fbd5b8aa9e
main: openapi

download:
        wget http://central.maven.org/maven2/io/swagger/codegen/v3/swagger-codegen-cli/3.0.11/swagger-codegen-cli-3.0.11.jar -O swagger-codegen-cli.jar

openapi_download:
        wget https://www.3gpp.org/ftp/specs/archive/OpenAPI/Rel-15/TS29571_CommonData.yaml
        wget https://www.3gpp.org/ftp/specs/archive/OpenAPI/Rel-15/TS29503_Nudm_EE.yaml
        wget codegen/swagger-codegen-spring-options.json

openapi:
        java -jar swagger-codegen-cli.jar generate \
    -i TS29503_Nudm_EE.yaml \
    -l spring \
    -o app \
    -c spring-options.json \
    -DhideGenerationTimestamp=true


# more spring-options.json
{
    "basePackage":"org.piweather.app",
    "configPackage":"org.piweather.app.config"
}
#
#
#
