#ifndef CPW_CACHEABLE_H
#define CPW_CACHEABLE_H

#include <string>
#include <memory>
#include <exception>

// Interface of Caching Object based on string:string map.
// key is string, and object is serialized/deserialized to string.
// The object will be removed when TTL(time-to-live) expires.
// Support sync/async CRUD operations

typedef uint32_t Duration;

// Callback interface
class Callback
{
public:
	Callback(const Duration & timeout)
	: timeout_(timeout)	{}
	virtual ~Callback() {}
	virtual void onTimeout() = 0;
	virtual void onError(const std::string & errmsg) = 0;
	virtual void onSuccess() = 0; // onCompleted()

	void setTimeout(const Duration & timeout) { timeout_ = timeout; }
	const Duration & getTimeout() const { return timeout_; }

private:
	Duration timeout_;
};

// Callback for Get operation
class GetCallback : public Callback
{
public:
	GetCallback(const Duration & timeout) : Callback(timeout){}
	virtual ~GetCallback() {}
	virtual void onCompleted(const std::string & key, const std::string & value) = 0;

	const std::string getValue() const { return value_; }
	void setValue(const std::string & value) { value_=value; }

protected:
	std::string value_;
};
typedef std::shared_ptr<GetCallback> GetCallbackPtr;

// Callback for Put operation
class PutCallback : public Callback
{
public:

	PutCallback(const std::string & value, const Duration & timeout)
	: Callback(timeout), value_(value)
	{}
	virtual ~PutCallback() {}

	const std::string getValue() const { return value_; }

protected:
	std::string value_;
};
typedef std::shared_ptr<PutCallback> PutCallbackPtr;

//Put operation:
//create: if not existing, create one, if existing, do nothing
//update: if not existing, do nothing, if existing, update
//append: if not existing, create, if existing, append
enum class PutOperation {
	CREATE = 0,   //create-only not existing
	UPDATE = 1,   //update-only existing
	OVERRIDE = 2, //create if not existing, update if existing
	APPEND = 2    //create if not existing; then append
};


// Callback for Remove operation
class RemoveCallback : public Callback
{
public:
	RemoveCallback(const Duration & timeout) : Callback(timeout){}
	virtual ~RemoveCallback() {}
};
typedef std::shared_ptr<RemoveCallback> RemoveCallbackPtr;

///////////////////////////////////////////////////////////////////////////////
class StorageException : public std::runtime_error
{
public:
	StorageException(const std::string& message)
        : std::runtime_error(message)
    {}
};

class Storageable
{
public:
    virtual ~Storageable() {}

    // sync interfaces(return bool for success/fail) and async interfaces (with callback which contains the data object to put/update/get)
    // Get operation: value returned in GetCallback object
    virtual bool get(std::string &value, const std::string &key, const Duration &timeout) throw (StorageException) = 0;
    virtual void get(GetCallbackPtr &cb, const std::string &key) throw (StorageException) = 0;

    // Put operation: If not existing, same as Create options
    //if exist, override it or not. value is stored in PutCallback object
    virtual bool put(const std::string &key, const std::string &value, PutOperation op, const Duration &timeout) throw (StorageException) = 0;
    virtual void put(PutCallbackPtr &cb, const std::string &key, PutOperation op) throw (StorageException) = 0;

    // Delete operation:
    virtual bool remove(const std::string &key, const Duration &timeout) throw (StorageException) = 0;
    virtual void remove(RemoveCallbackPtr &cb, const std::string &key) throw (StorageException) = 0;
};


///////////////////////////////////////////////////////////////////////////////
// Callback for TTL operation
class UpdateTTLCallback : public Callback
{
public:
	UpdateTTLCallback(const Duration & ttl, const Duration & timeout)
	: Callback(timeout), ttl_(ttl) {}
	virtual ~UpdateTTLCallback() {}

	void setTTL(const Duration & ttl) { ttl_ = ttl; }
	const Duration & getTTL() const { return ttl_; }

protected:
	Duration ttl_;
};
typedef std::shared_ptr<UpdateTTLCallback> UpdateTTLCallbackPtr;


class CacheException : public std::runtime_error
{
public:
    CacheException(const std::string& message)
        : std::runtime_error(message)
    {}
};

// Similar to Storageable, but the object with TTLT(Time-To-Live), and be automatically removed if ttl expired.
class Cacheable
{
public:
    virtual ~Cacheable() {}

    // sync interfaces(return bool for success/fail) and async interfaces (with callback which contains the data object to put/update/get)
    // Get operation: value returned in GetCallback object
    virtual bool get(std::string &value, const std::string &key, const Duration &timeout) throw (CacheException) = 0;
    virtual void get(GetCallbackPtr &cb, const std::string &key, const Duration &timeou) throw (CacheException) = 0;

    // Put operation: If not existing, same as Create options
    //if exist, override it or not. value is stored in PutCallback object
    virtual bool put(const std::string &key, const std::string &value, const Duration &ttl, const Duration &timeout, PutOperation op) throw (CacheException) = 0;
    virtual void put(PutCallbackPtr &cb, const std::string &key, const Duration &ttl, const Duration &timeout, PutOperation op) throw (CacheException) = 0;

    // Delete operation:
    virtual bool remove(const std::string &key, const Duration &timeout) throw (CacheException) = 0;
    virtual void remove(RemoveCallbackPtr &cb, const std::string &key, const Duration &timeout) throw (CacheException) = 0;

    // update TTL
    virtual uint64_t updateTTL(const std::string &key, const Duration &ttl, const Duration &timeout) throw (CacheException) = 0;
    virtual void updateTTL(UpdateTTLCallbackPtr &cb, const std::string &key) throw (CacheException) = 0;
};

#endif
