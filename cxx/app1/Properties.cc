#include "Properties.h"
#include "Utils.h"

#include <fstream>

const String Properties::EMPTY_STRING("");

bool Properties::hasProperty(const String & key) const
{
	return properties_.find(key) != properties_.end();
}

const String & Properties::getProperty(const String & key) const
{
	return getProperty(key, EMPTY_STRING);
}

const String & Properties::getProperty(const String & key, const String & defaultValue) const
{
	auto iter = properties_.find(key);
	return properties_.find(key) == properties_.end() ? defaultValue : iter->second;
}

void Properties::setProperty(const String & key, const String & value)
{
	auto iter = properties_.insert(std::make_pair(key, value));
	if (iter.second) { // new one
		names_.push_back(key);
	} else {  // exist one
		properties_[key] = value;
	}
}

void Properties::output(std::ostream & out) const
{
	out << "[ " << name_ << " ]\n";
	for (auto & name : names_) {
		out << name << " = " << getProperty(name) << "\n";
	}
	out << "\n";
}

PropertiesGroup::~PropertiesGroup()
{
	for (auto iter : groups_) {
		delete iter.second;
		iter.second = nullptr;
	}
	groups_.clear();
	names_.clear();
}

bool PropertiesGroup::hasProperties(const String & name) const
{
	return groups_.find(name) != groups_.end();
}
const Properties * PropertiesGroup::getProperties(const String & name) const
{
	auto iter = groups_.find(name);
	return groups_.find(name) == groups_.end() ? nullptr : iter->second;
}
Properties * PropertiesGroup::getProperties(const String & name)
{
	auto iter = groups_.find(name);
	if (iter != groups_.end() ) return iter->second;

	Properties * group = new Properties(name);
	names_.push_back(name);
	groups_.insert(std::make_pair(name, group));
	return group;
}

void PropertiesGroup::removeProperties(const String & name)
{
	auto iter = groups_.find(name);
	if (iter == groups_.end() ) return;

	groups_.erase(iter);
	delete iter->second;
	names_.remove(name);
}

bool PropertiesGroup::load(const String & cfgfile)
{
    std::ifstream input( cfgfile.c_str());
    if (!input)
       return false;

    String gname;
    Properties * props;

    for( std::string line; getline( input, line ); )
    {
        trim(line);

        if (line.empty()) continue;

        if (line[0]=='[')  // group
        {
            gname=::group_name(line);
            props = getProperties(gname);
        }
        else if (props != nullptr)
        {
            auto ind = line.find_first_of('=');
            String name=line.substr(0,ind);
            String value=line.substr(ind+1);
            props->setProperty(trim(name), trim(value) );
        }
        /*else {
            std::cout << "Properties if null for name=" << gname << std::endl;
        }
        std::cout << "read: {" << line << "}" << std::endl;
        */
    }

    return true;
}

bool PropertiesGroup::store(const String & cfgfile) const
{
    std::ofstream fout( cfgfile.c_str());
    if (!fout)
       return false;

    output(fout);

    return fout.good();
}

void PropertiesGroup::output(std::ostream & out) const
{
    for (auto & name : names_)
    {
        const Properties * props = getProperties(name);
        if (props != nullptr)
            props->output(out);
    }
}
