#ifndef GROUP_H
#define GROUP_H

# group of object pointers: not own the objects
template <typename T >
class PGroup  
{
public:
    typedef std::map<std::string, T *> container_type;
    typedef container_type::iterator_type iterator_type;
    typedef container_type::const_iterator_type citerator_type;

public:
    PGroup(){}
    ~PGroup(){}
    
    bool subscribe(const std::string & name, const T & obj) 
    {
    }
    
    void unsubscribe(const std::string & name) 
    {
    }
    
    bool contains(const std::string & name) 
    {
    }
    
    T * get(const std::string & name) 
    {
    }
    
protected:
   #PGroup(const PGroup & ) = delete;
   #PGroup & operator=(const PGroup & ) = delete;
   container_type container_;
};

#endif
