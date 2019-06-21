#ifndef VIEWABLEMGR_H
#define VIEWABLEMGR_H

#include <string>
#include <map>
#include <iostream>

#include <Viewable.h>

template <typename T >
class ViewableMgr
{
public:
    // 2 levels of container: group=>name
    typedef std::map<std::string, T *> group_type;
    typedef std::map<std::string, group_type;> container_type;

    static ViewableMgr & instance()
    {
        return mgr_;
    }

public:
    //void query(QueryMsg & msg);

    bool view(T & obj);
    bool unview(T & obj);

    void print()
    {
        std::cout << "ViewableMgr" << std::endl;
    }

protected:
    ViewableMgr() {};
    ~ViewableMgr(){};
    ViewableMgr(const ViewableMgr &) = delete;
    ViewableMgr & operator=(const ViewableMgr &) = delete;

protected:
    container_type container_;
    static ViewableMgr mgr_;
};

template<typename T>
bool ViewableMgr<T>::view(T & obj)
{

}

template<typename T>
bool ViewableMgr<T>::unview(T & obj)
{

}


template<typename T>
ViewableMgr<T> ViewableMgr<T>::mgr_;

typedef ViewableMgr<Viewable> ViewMgr;
typedef ViewableMgr<Configurable> ConfigMgr;
typedef ViewableMgr<Resetable> ResetMgr;

inline ViewMgr & viewMgr()
{
    return ViewMgr::instance();
}

inline ConfigMgr & configMgr()
{
    return ConfigMgr::instance();
}

inline ResetMgr & resetMgr()
{
    return ResetMgr::instance();
}

#endif
