# Eclipse Application
https://eclipsesource.com/blogs/tutorials/your-first-application-based-on-eclipse-faq/amp/
- Development Environment: OSGi + IDE + Extension Point + SDKs
- Application Environment: 
![OSGi Application](https://eclipsesource.com/wp-content/uploads/2016/04/image05.png)

## Application Architecture
- Product: Product Definition; Target Platform
    - Project: Feature
        - Package: Plugin (OSGi bundle/MANIFEST.MF + plugin.xml/extension point/extension)
            - Module (api; module; ui; database; json; xml; ...)
            
