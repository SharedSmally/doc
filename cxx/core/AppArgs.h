#ifndef APPARGS_H
#define APPARGS_H

#include <string>

class AppArgs
{
public:
	static std::string getEnv( std::string const & key );
	AppArgs(int argc, char **argv);
	AppArgs(int argc, char **argv, char ** env);
	~AppArgs();

	const char * name() const;
	void print() const;


private:
	AppArgs() = delete;
	AppArgs(const AppArgs &) = delete;
	AppArgs & operator=(const AppArgs &) = delete;

protected:
        int argc_;
        char ** argv_;
        int envc_;
        char ** env_;
};

#endif
