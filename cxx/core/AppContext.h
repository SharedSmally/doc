#ifndef APPCONTEXT_H
#define APPCONTEXT_H

template <typename APP, typename ARGS>
class AppContext
{
public:
	typedef APP app_type;
	typedef ARGS appargs_type;

	AppContext(app_type & app, appargs_type & args)
	: args_(args), app_(app_)
	{
	}
	~AppContext()
	{};

	app_type & app() { return app_; }
	appargs_type & args() { return args_; }

private:
	AppContext() = delete;
	AppContext(const AppContext &) = delete;
	AppContext & operator=(const AppContext &) = delete;

protected:
	app_type & app_;
	appargs_type & args_;
};

#endif
