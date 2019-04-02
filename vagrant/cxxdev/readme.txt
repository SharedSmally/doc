Vagrant file to setup cxx dev env.

redis:  key/value as string/string
CRUD: create/read/update/delete
   create/insert(string & key, Object &object): insert key and value (object serialized to string)
   update(string & key, Object & object): update object by key (object serialized to string)
   Object read(string & key): get object from key (value deserialize to Object)
   delete(string & key): delete object by key 
   
OR
   put:  create or update
   get:  query
   remove: delete

   
   
