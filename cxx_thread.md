
std::thread th;

// in TaskMgr with method run()
th = std::thread(&TaskMgr::run, this);
th = std::thread( [ this ] { run(); } );

th.join();
