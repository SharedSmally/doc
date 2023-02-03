# std::shared_ptr vs weak_ptr vs unique_ptr
- unique_ptr: only one ownes the object (replaced auto_ptr)
- shared_ptr: owned by multiple owners (based on reference counter)
- weak_ptr: now owned the object, needs to convert to shared_ptr to get the object

https://stackoverflow.com/questions/12030650/when-is-stdweak-ptr-useful

Suppose you have Team and Member objects.

Obviously it's a relationship : the Team object will have pointers to its Members. And it's likely that the members will also have a 
back pointer to their Team object.

Then you have a dependency cycle. If you use shared_ptr, objects will no longer be automatically freed when you abandon reference on them, 
because they reference each other in a cyclic way. This is a memory leak.

You break this by using weak_ptr. The "owner" typically use shared_ptr and the "owned" use a weak_ptr to its parent, and convert it 
temporarily to shared_ptr when it needs access to its parent.

Store a weak ptr :
```
weak_ptr<Parent> parentWeakPtr_ = parentSharedPtr; // automatic conversion to weak from shared
```
then use it when needed
```
shared_ptr<Parent> tempParentSharedPtr = parentWeakPtr_.lock(); // on the stack, from the weak ptr
if( !tempParentSharedPtr ) {
  // yes, it may fail if the parent was freed since we stored weak_ptr
} else {
  // do stuff
}
// tempParentSharedPtr is released when it goes out of scope
```
  
![Example](https://i.stack.imgur.com/iKXVO.png)
