# JNI :  Java <-> C/C++

## Swig
 Generate Java, xxx from C/C++ impl. Command:
 ```
 swig -java|xxx [-cxx] interface.i
 ```
 
## JNI:
The JNI does not enforce class, field, and method access control restrictions that can be expressed at the Java programming language level through the use of modifiers such as private and final. It is possible to write native code to access or modify fields of an object even though doing so at the Java programming language level would lead to an IllegalAccessException. *This means JNI can call JAVA any methods/fiels, including protected and private methods/fields*.

### Pass C++ object to Java Directly
C++ code:
```
    CxxCallback cb;  # c++ object
    jclass cbcls = env->FindClass( "CxxCallback");
    jmethodID cbconstructor = env->GetMethodID(cbcls, "<init>", "(JZ)V" );
    jobject cbobject = env->NewObject(cbcls,cbconstructor, (long) &cb, false);  # create swig generated proxy Java Object
```

### JNIEnv
JNI interface pointer (JNIEnv \*) is only valid in the current thread. Within synchronous calls using JNI from Java to C++ the "environment" has already been setup by the JVM, but it may not have been from an arbitrary C++ thread.

To call Java method from C++:
- get hold of the JVM environment context using GetEnv
- attach the context if necessary using AttachCurrentThread
- call the method as normal using CallVoidMethod
- detach using DetachCurrentThread
```
void callback(int val) {
    JNIEnv * g_env;
    // double check it's all ok
    int getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        std::cout << "GetEnv: not attached" << std::endl;
        if (g_vm->AttachCurrentThread((void **) &g_env, NULL) != 0) {
            std::cout << "Failed to attach" << std::endl;
        }
    } else if (getEnvStat == JNI_OK) {
        //
    } else if (getEnvStat == JNI_EVERSION) {
        std::cout << "GetEnv: version not supported" << std::endl;
    }

    g_env->CallVoidMethod(g_obj, g_mid, val);

    if (g_env->ExceptionCheck()) {
        g_env->ExceptionDescribe();
    }

    g_vm->DetachCurrentThread();
}
```
- JNI implementing difference in C and C++ :
    - C variants:
```
(*env)->FindClass(env, ...)
```
    - C++ variants:
```
env->FindClass(...)
```
