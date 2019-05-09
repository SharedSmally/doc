#include <string.h>

#include <iostream>
using namespace std;

std::string AppArgs::getEnv( std::string const & key )
{
    char * val = getenv( key.c_str() );
    return val == NULL ? std::string("") : std::string(val);
}

AppArgs::AppArgs(int argc, char ** argv)
    : argc_(argc), argv_(argv),
	  envc_(0), env_(nullptr)
{
}

AppArgs::AppArgs(int argc, char ** argv, char ** env)
: argc_(argc), argv_(argv), envc_(0), env_(env)
{
    if (env_ != nullptr)
    {
    	char ** ptr = env_;
    	while ( *ptr != nullptr ) {
    		++ptr; ++ envc_;
    	}
    }
}

AppArgs::~AppArgs()
{}

const char * AppArgs::name() const
{
	return argv_[0];
}

void AppArgs::print() const
{
	if (argc_==0) return;

	cout << "AppArgs name: " << argv_[0];
	for(int i=0; i<argc_; i++)
		cout << "\nargv[" << i << "]:" << argv_[i];
	cout << endl;

	for(int i=0; i<envc_; i++)
		cout << "\nenv[" << i << "]:" << env_[i];
	cout << endl;
}
