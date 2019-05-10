#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <map>

#include <App.h>

typedef std::map<std::string, std::string> Properties;
typedef std::map<std::string, Properties> PropertiesGroup;

class Manageable
{
public:
	virtual ~Manageable() {}
	virtual bool config(const Properties & props) = 0;
};

typedef std::shared_ptr<Manageable> ManageablePtr;
typedef std::map<std::string, ManageablePtr> manageable_container;

class AppContext
{
public:
	AppContext(App & app, int argc, char **argv, char **env = nullptr)
	: app_(app)
	{}
	~AppContext() {};

	App & app() { return app_; }

	virtual void start();
	virtual void stop();

	bool hasProperties(const std::string & group) const;
	const Properties & getProperties(const std::string & group) const;

	bool hasProperty(const std::string & group, const std::string & name) const;
	const std::string & getProperty(const std::string & group, const std::string & name) const;

	ManageablePtr get(const std::string & name);

	template<typename T>
	std::shared_ptr<T> get(const std::string & name);

	template<typename T, typename... Args>
	bool put(const std::string & name, Args & ... args);

	template<typename T, typename... Args>
	bool put(const std::string & name, Args && ... args);

private:
	void loadProperties(const std::string & filename);
	void saveProperties(const std::string & filename);

private:
	AppContext() = delete;
	AppContext(const AppContext &) = delete;
	AppContext & operator=(const AppContext &) = delete;

protected:
	App & app_;
	PropertiesGroup propsgroup_;
	manageable_container container_;
};


template <typename ARGS>
class TAppContext : public AppContext
{
public:
	typedef App app_type;
	typedef ARGS appargs_type;

	TAppContext(App & app, int argc, char **argv, char ** env = nullptr)
	: AppContext(app), args_(argc, argv, env)
	{}
	~TAppContext() {};

	ARGS & args() { return args_; }

protected:
	ARGS & args_;
};


////////////////////////////////////////////impl
template<typename T>
std::shared_ptr<T> AppContext::get(const std::string & name)
{
	auto it = container_.find(name);
	return ( it == container_.end() ) ?
			std::shared_ptr<T>(nullptr) :
			std::dynamic_pointer_cast<T>(it->second);
}

template<typename T, typename... Args>
bool AppContext::put(const std::string & name, Args & ... args)
{
	const Properties & props = getProperties(name);

	ManageablePtr ptr = std::static_pointer_cast<Manageable>(std::make_shared<T> (args...));

	if (ptr && !props.empty())
	{
		if (!ptr->config(props))
			return false;
	}

	auto ret = container_.insert(std::make_pair(name, ptr));

	return ret.second;
}

template<typename T, typename... Args>
bool AppContext::put(const std::string & name, Args && ... args)
{
	const Properties & props = getProperties(name);

	ManageablePtr ptr = std::static_pointer_cast<Manageable>(std::make_shared<T> (args...));

	if (ptr && !props.empty())
	{
		if (!ptr->config(props))
			return false;
	}
	auto ret = container_.insert(std::make_pair(name, ptr));

	return ret.second;
}

#endif

