#include <Lockable.h>

const LockingTraits<DEFER_LOCKING>::locking_type & LockingTraits<DEFER_LOCKING>::locking_(std::defer_lock);

const LockingTraits<TRY_LOCKING>::locking_type & LockingTraits<TRY_LOCKING>::locking_(std::try_to_lock);

const LockingTraits<ADOPT_LOCKING>::locking_type & LockingTraits<ADOPT_LOCKING>::locking_(std::adopt_lock);

#ifdef TEST
#include <iostream>
using namespace std;

int main()
{
	DefaultLockable obj1;
	obj1.mutex();
	LOCKER(DefaultLockable, obj1);

}

#endif
