== JNI ==
JVM:

== JNI implementing difference in C and C++ :

- C variants:
```
(*env)->FindClass(env, ...)
```
- C++ variants:
```
env->FindClass(...)
```
