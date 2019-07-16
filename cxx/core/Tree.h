#ifndef TREE_H
#define TREE_H

#include <string>
#include <memory>
#include <mutex>
#include <unordered_map>

#include <iostream>

template <typename NODE>
class Tree : public NODE
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
	~Tree()
	{}

	Tree * parent() { return parent_; }
    const container_type & children() const { return container_; }

	bool root() const { return parent_ == nullptr; }

	element_type get(const std::string & name)
    {
        auto it = container_.find(name);
        if (it!= container_.end()) return it->second;

        Guarder guarder(mtx_);
        it = container_.find( name);
        if (it!= container_.end()) return it->second;

        return nullptr;
    }

    template <class ...Args>
    element_type put(const std::string &name, Args... args)
    {
    	element_type ptr = std::make_shared<Tree>(this, args...);
        Guarder guarder(mtx_);
        container_[name] = ptr;
        return ptr;
    }

    template <class ...Args>
    bool insert(const std::string &name, Args... args)
    {
        auto it = container_.find(name);
        if (it!= container_.end()) return false;

        Guarder guarder(mtx_);
        it = container_.find( name);
        if (it!= container_.end()) return false;

        element_type ptr = std::make_shared<Tree>(this, args...);
        container_.insert(std::make_shared(name, ptr));
        return true;
    }

    size_type erase( const std::string & name)
    {
    	Guarder guarder(mtx_);
    	return container_.erase(name);
    }
    void clear()
    {
    	Guarder guarder(mtx_);
    	return container_.clear();
    }

//protected:
	template <class ...Args>
	Tree(Tree * parent, Args... args)
	: parent_(parent), NODE(args...)
	{}

	void print(std::ostream & out) const
	{
		output(out, "");
	}

	void output(std::ostream & out, const std::string & prefix) const
	{
		std::string s0(prefix+"    ");
		for ( auto it = container_.begin(); it !=  container_.end(); ++it)
		{
			out << prefix << it->first << ":\n";
			it->second->output(out, s0);
		}
	}

protected:
	Tree * parent_;
	mutex_type mtx_;
	container_type container_;
};

#endif
