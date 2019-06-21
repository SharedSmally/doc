#include <AppContext.h>

#define ENV

#ifdef ENV
int main(int argc, char ** argv, char **env)
#else
int main(int argc, char ** argv)
#endif
{
#ifdef ENV
    TApp<AppContext> app(argc, argv, env);
#else
    TApp<AppContext> app(argc, argv);
#endif
	app.run(); // blocked till return
	return app.getCode();
}
