# JNI :  Java <-> C/C++

## Swig
 Generate Java, xxx from C/C++ impl. Command:
 ```
 swig -java|xxx [-cxx] interface.i
 ```
 
## JNI:
The JNI does not enforce class, field, and method access control restrictions that can be expressed at the Java programming language level through the use of modifiers such as private and final. It is possible to write native code to access or modify fields of an object even though doing so at the Java programming language level would lead to an IllegalAccessException. *This means JNI can call JAVA any methods/fiels, including protected and private methods/fields*.

#### interface
- Can use c/c++ comments: /* */ and  //
- %{  ... %} will go to the wrapper code

```
%module moduleName

%{
/* Includes the headers in the wrapper code */
#include <string>
#include <TestException.h>
%}

/* Define name space for Message */
namespace com {
    namespace jpw {
       class Message;
   }
}

// The functions (goto modelName.java) and classes that should be wrapped
/* Include standard swig interfaces or some other interfaces */
%include <std_vector.i>
%include <std_map.i>
%include <std_string.i>
%include <various.i>
%include <stdint.i>

SWIG_JAVABODY_METHODS(public, public, SWIGTYPE)
#SWIG_JAVABODY_TYPEWRAPPER(public, public, public, SWIGTYPE)

# template classes need to be instantiated
namespace std {
    %template(StringArray) vector< string >;
    %template(IntegerArray) vector< int >;
    %template(UnsignedIntegerArray) vector< unsigned int >;
    %template(AddressArray) vector<com::cpw::Address>;
    %template(FailedAVPArray) vector<com::cpw::FailedAVP>;
    %template(AVPArray) vector<com::cpw::AVP * >;
}

#%javamethodmodifiers com::CPW::MsgJNI %{
#%javamethodmodifiers MsgJNI %{
#    public static %}

#%pragma(java) modulemethodmodifiers="protected final static synchronized"
#%pragma(java) javamethodmodifiers="public static"
#%javamethodmodifiers "public static synchronized";

%typemap(in, numinputs=0) std::string & data (std::string temp) "$1=&temp;"
%typemap(argout) std::string & data {
  $result = JCALL1(NewByteArray, jenv, $1->size());
  JCALL4(SetByteArrayRegion, jenv, $result, 0, $1->size(), (const jbyte*)$1->c_str());
}
%typemap(jtype) bool getRawData "byte[]"
%typemap(jstype) bool getRawData "byte[]"
%typemap(jni) bool getRawData "jbyteArray"
%typemap(javaout) bool getRawData { return $jnicall; }
%typemap(out) bool getRawData {
  if (!$1) {
    return NULL;
  }
}

%typemap(in, numinputs=0) std::string& out (std::string temp) "$1=&temp;"
%typemap(argout) std::string& out {
  $result = JCALL1(NewByteArray, jenv, $1->size());
  JCALL4(SetByteArrayRegion, jenv, $result, 0, $1->size(), (const jbyte*)$1->c_str());
}
%typemap(jtype) bool getAddress "byte[]"
%typemap(jstype) bool getAddress "byte[]"
%typemap(jni) bool getAddress "jbyteArray"
%typemap(javaout) bool getAddress { return $jnicall; }
%typemap(out) bool getAddress {
  if (!$1) {
    return NULL;
  }
}

%typemap(jtype) (const signed char *data, int sz) "byte[]"
%typemap(jstype) (const signed char *data, int sz) "byte[]"
%typemap(jni) (const signed char *data, int sz) "jbyteArray"
%typemap(javain) (const signed char *data, int sz) "$javainput"
%typemap(in,numinputs=1) (const signed char* data, int sz) {
  $1 = JCALL2(GetByteArrayElements, jenv, $input, NULL);
  $2 = JCALL1(GetArrayLength, jenv, $input);
}
%typemap(freearg) (const signed char *data, int sz) {
  JCALL3(ReleaseByteArrayElements, jenv, $input, $1, 0);
}

// map C++ classes to java class: first:
// Answer, Answer *, Answer &  => com.jpw.message.Answer;
%typemap("javapackage") Answer, Answer *, Answer & "com.jpw.message.Answer";
%typemap("javapackage") Request, Request *, Request & "com.jpw.message.Request";

#import for all java classes
%pragma(java) jniclassimports=%{
import com.jpw.message.Answer;
import com.jpw.message.Request;
import com.jpw.message.AVPArray;
%}

namespace com {
namespace jpw {
namespace base {

#import for individual java classe
%typemap(javaimports) CpaRequest   %{
import com.jpw.message.Request;
import com.jpw.message.AVPArray;
%}

SWIG_JAVABODY_METHODS(public, public, SWIGTYPE)

// map C++ methods that return std::string to Java return byte[]
SWIG_JAVABODY_METHODS(public, public, SWIGTYPE)

%typemap(in, numinputs=0) std::string& out (std::string temp) "$1=&temp;"
%typemap(argout) std::string& out {
  $result = JCALL1(NewByteArray, jenv, $1->size());
  JCALL4(SetByteArrayRegion, jenv, $result, 0, $1->size(), (const jbyte*)$1->c_str());
}

%typemap(jtype) bool foo "byte[]"
%typemap(jstype) bool foo "byte[]"
%typemap(jni) bool foo "jbyteArray"
%typemap(javaout) bool foo { return $jnicall; }
%typemap(out) bool foo {
  if (!$1) {
    return NULL;
  }
}

%typemap(jtype) bool getMSISDN "byte[]"
%typemap(jstype) bool getMSISDN "byte[]"
%typemap(jni) bool getMSISDN "jbyteArray"
%typemap(javaout) bool getMSISDN { return $jnicall; }
%typemap(out) bool getMSISDN {
  if (!$1) {
    return NULL;
  }
}

%typemap(jtype) (const signed char *data, int sz) "byte[]"
%typemap(jstype) (const signed char *data, int sz) "byte[]"
%typemap(jni) (const signed char *data, int sz) "jbyteArray"
%typemap(javain) (const signed char *data, int sz) "$javainput"
%typemap(in,numinputs=1) (const signed char* data, int sz) {
  $1 = JCALL2(GetByteArrayElements, jenv, $input, NULL);
  $2 = JCALL1(GetArrayLength, jenv, $input);
}
%typemap(freearg) (const signed char *data, int sz) {
  JCALL3(ReleaseByteArrayElements, jenv, $input, $1, 0);
}

#if defined(SWIGJAVA)
%typemap(in)     (char * BYTE, int LENGTH) {
$1 = (char *) JCALL2(GetByteArrayElements, jenv, $input, 0);
$2 = (int)    JCALL1(GetArrayLength,       jenv, $input);
}
%typemap(jni)    (char * BYTE, int LENGTH) "jbyteArray"
%typemap(jtype)  (char * BYTE, int LENGTH) "byte[]"
%typemap(jstype) (char * BYTE, int LENGTH) "byte[]"
%typemap(javain) (char * BYTE, int LENGTH) "$javainput"

%apply (char * BYTE, int LENGTH)   { (char * byteArray, long len) };
#else
%apply (char * STRING, int LENGTH) { (char *  byteArray, long len) };
#endif

#if defined(SWIGJAVA)
%typemap(in)     (char * BYTE, int LENGTH) {
$1 = (char *) JCALL2(GetByteArrayElements, jenv, $input, 0);
$2 = (int)    JCALL1(GetArrayLength,       jenv, $input);
}
%typemap(jni)    (char * BYTE, int LENGTH) "jbyteArray"
%typemap(jtype)  (char * BYTE, int LENGTH) "byte[]"
%typemap(jstype) (char * BYTE, int LENGTH) "byte[]"
%typemap(javain) (char * BYTE, int LENGTH) "$javainput"

%apply (char * BYTE, int LENGTH)   { (char * byteArray, long len) };
#else
%apply (char * STRING, int LENGTH) { (char *  byteArray, long len) };
#endif

// handle exception
%include <exception.i>

// Modify the code generation
/* Any std::exception not handled throw SWIG_RuntimeError */
%exception {
  try {
    $action
  } catch (const std::exception& e) {
    SWIG_exception(SWIG_RuntimeError, e.what());
  }
}

/* Translate TestException C++ exceptions to JavaTestException java exception */
%typemap(throws, throws="com.jpw.exception.JavaTestException") TestException{
  jclass excep = jenv->FindClass("com/jpw/exception/JavaTestException");
  if (excep)
    jenv->ThrowNew(excep, $1.what());
  return $null;
}

/* Force TestException Java class to extend java.lang.Exception */
%typemap(javabase) TestException "java.lang.Exception";
/* Override getMessage() */
%typemap(javacode) TestException %{
  public String getMessage() {
    return what();
  }
%}

%include <TestException.h> # The classes to be wrapped

```
#### C++ string to Java byte array
See https://stackoverflow.com/questions/12192624/swig-convert-return-type-stdstringbinary-to-java-byte

#### Pass C++ object to Java Directly
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
    - memory management:
```
    jclass tmpcls = env->FindClass(clsName.c_str());

    if (tmpcls != NULL)
    {
        cls = (jclass)env->NewGlobalRef(tmpcls);

        constructor = env->GetMethodID(cls, "<init>", "()V");
        getCPtr = env->GetStaticMethodID(cls, "getCPtr", sigName.c_str());

        env->DeleteLocalRef(tmpcls);
    }
```
