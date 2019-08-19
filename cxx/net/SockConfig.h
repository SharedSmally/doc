#ifndef SOCKCONFIG_H
#define SOCKCONFIG_H

class FDObjectConfig : public ConfigGroup
{
public:
   FDObjectConfig(const std::string $ name)
      : ConfigGroup(name)
   {
   
   }
   ~FDObjectConfig()
   {}
   
protected: 
   Config<uint_t> x1;
};


#endif
