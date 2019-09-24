#ifndef CPW_APPCONFIG_H
#define CPW_APPCONFIG_H

#include <string>

class NamedObject
{
public:
	NamedObject(const std::string & name)
	: name_(name)
	{}
	virtual ~NamedObject()
	{};
	const std::string & name() const
	{
		return name_;
	}

protected:
	std::string name_;
};

/**
 * SNMP get operations
 */
class Configable : public NamedObject
{
public:
	enum ConfigType
	{
		QUERYABLE,
		CONFIGABLE,
		UPDATEABLE,
		RESETABLE
	};

	Configable(const std::string & name, const std::string & desc, ConfigType type)
	: NamedObject(name), desc_(desc), type_(type)
	{}
	virtual ~Configable(){};

	const std::string & desc() const { return desc_; }
	ConfigType type() const { return type_; }

	virtual std::string query() const = 0;

	virtual bool config(const std::string & value)
	{
		return (type_ == ConfigType::CONFIGABLE || type_ == ConfigType::UPDATEABLE) ?
			_config(value) : false;
	}
	virtual bool update(const std::string & value)
	{
		return (type_ == ConfigType::UPDATEABLE) ?
			_config(value) : false;
	}
	virtual bool reset()
	{
		return (type_ == ConfigType::RESETABLE) ?
			_reset() : false;
	}

protected:
	virtual bool _config(const std::string & value) { return false; }
	virtual bool _reset() { return false; }

protected:
	std::string desc_;
	ConfigType type_;
};

#endif
