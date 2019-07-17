#ifndef TREE_H
#define TREE_H

#include <string>
#include <memory>
#include <mutex>
#include <vector>
#include <sstream>
#include <iterator>
#include <unordered_map>

#include <iostream>

#include <algorithm>
#include <cctype>
#include <locale>

typedef std::string String;
typedef std::vector<std::string> Strings;

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

inline bool beginsWith(const std::string& s, const std::string& prefix)
{
    return s.size() >= prefix.size() &&
           s.substr(0, prefix.size()) == prefix;
}
inline bool endsWith(const std::string& s, const std::string& suffix)
{
    return s.size() >= suffix.size() &&
           s.substr(s.size() - suffix.size()) == suffix;
}

inline void split (std::vector<std::string> & result, const std::string & s, char delim)
{
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim))
    {
        if (!item.empty())
           result.push_back (item);
    }
}
inline std::vector<std::string> split (const std::string & s, char delim)
{
    std::vector<std::string> result;
    split(result, s, delim);
    return result;
}

// for string delimiter
inline void split (std::vector<std::string> & res, const std::string & s, const std::string & delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        if (!token.empty())
            res.push_back (token);
    }

    res.push_back (s.substr (pos_start));

}
inline std::vector<std::string> split (const std::string & s, const std::string & delimiter)
{
    std::vector<std::string> res;
    split(res, s, delimiter);
    return res;
}

inline std::string join(const std::vector<std::string>& vec, const char* delim)
{
    std::stringstream res;
    copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(res, delim));
    return res.str();
}

inline std::string join(const std::vector<std::string> &elements, const std::string &separator)
{
    switch (elements.size())
    {
        case 0: return "";
        case 1: return elements[0];
        default:
            std::ostringstream os;
            std::copy(elements.begin(), elements.end()-1,
                std::ostream_iterator<std::string>(os, separator.c_str()));
            os << *elements.rbegin();
            return os.str();
    }
}

template <typename NODE>
class Tree : public NODE //,  public std::enable_shared_from_this< Tree<NODE> >
{
    friend std::ostream & operator<<(std::ostream & out, const Tree & tree)
    {
        tree.print(out);
        return out;
    }

public:
    typedef NODE node_type;
    typedef std::shared_ptr<Tree > element_type;
    typedef std::unordered_map<std::string, element_type > container_type;
    typedef typename container_type::size_type size_type;

    typedef std::mutex mutex_type;
    typedef std::lock_guard<mutex_type> Guarder;

    template <class ...Args>
    Tree( Args... args)
    : parent_(nullptr), NODE(args...)
    {}
    //protected:
    template <class ...Args>
    Tree(Tree *  parent, Args... args)
    : parent_(parent), NODE(args...)
    {}
    ~Tree()
    {
    	clearNode();
    }

    Tree * parent() { return parent_; }
    const container_type & children() const { return container_; }

    bool isRoot() const { return parent_ == nullptr; }

    element_type getNode(const std::string & name)
    {
        auto it = container_.find(name);
        if (it!= container_.end()) return it->second;

        Guarder guarder(mtx_);
        it = container_.find( name);
        if (it!= container_.end()) return it->second;

        return nullptr;
    }

    element_type getNode(const std::vector<std::string> & names, uint32_t index = 0)
    {
        if (index >= names.size())  return nullptr;

        element_type child = getNode(names[index]);

        if (!child) return nullptr;

        ++index;
        return index == names.size() ? child : child->getNode(names, index );
    }

    template <class ...Args>
    element_type putNode(const std::string &name, Args... args)
    {
        element_type ptr = std::make_shared<Tree>(this, args...);
        Guarder guarder(mtx_);
        container_[name] = ptr;
        return ptr;
    }

    template <class ...Args>
    element_type insertNode(const std::string &name, Args... args)
    {
        auto it = container_.find(name);
        if (it!= container_.end()) return nullptr;

        Guarder guarder(mtx_);
        it = container_.find( name);
        if (it!= container_.end()) return nullptr;

        element_type ptr = std::make_shared<Tree>(this, args...);
        container_.insert(std::make_pair(name, ptr));
        return ptr;
    }

    bool eraseNode( const std::string & name)
    {
        Guarder guarder(mtx_);
        return container_.erase(name) != 0;
    }
    void clearNode()
    {
        Guarder guarder(mtx_);
        return container_.clear();
    }

    virtual void print(std::ostream & out = std::cout) const
    {
        output(out, "");
    }

    virtual void output(std::ostream & out, const std::string & prefix) const
    {
        std::string s0(prefix+"    ");
        for ( auto it = container_.begin(); it !=  container_.end(); ++it)
        {
            out << prefix << it->first << ":\n";
            it->second->output(out, s0);
        }
    }
/*
protected:
    element_type getptr()
    {
        return std::enable_shared_from_this< Tree<NODE> >::shared_from_this();
    }
*/
protected:
    //element_type parent_;
    Tree * parent_;
    mutex_type mtx_;
    container_type container_;
};

#endif

/*
struct Good: std::enable_shared_from_this<Good> // note: public inheritance
{
    std::shared_ptr<Good> getptr() {
        return shared_from_this();
    }
};
     // Good: the two shared_ptr's share the same object
    std::shared_ptr<Good> gp1 = std::make_shared<Good>();
    std::shared_ptr<Good> gp2 = gp1->getptr();

    // Bad: shared_from_this is called without having std::shared_ptr owning the caller
    try {
        Good not_so_good;
        std::shared_ptr<Good> gp1 = not_so_good.getptr();
    } catch(std::bad_weak_ptr& e) {
        // undefined behavior (until C++17) and std::bad_weak_ptr thrown (since C++17)
        std::cout << e.what() << '\n';
    }
 */
