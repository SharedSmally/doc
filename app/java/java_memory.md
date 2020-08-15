# Java Memory
- Heap memory:

The Java heap is the memory area that JVM allocated from native memory for java applications. -Xmx(max) and -Xms(min) will specify the heap size allocation.

- Direct memory

NIO added support for direct [ByteBuffers](https://docs.oracle.com/javase/7/docs/api/java/nio/ByteBuffer.html) to perform I/O based on channels and buffer, which can be passed directly to native memory rather than Java heap: allocation memory via native calls.
It is faster in some scenarios because they can avoid copying data between Java heap and native heap.

A non-direct ByteBuffer holds its data in a byte[] array on the Java heap.

A byte buffer is either direct or non-direct. Given a direct byte buffer, the Java virtual machine will make a best effort 
to perform native I/O operations directly upon it. That is, it will attempt to avoid copying the buffer's content to (or from) 
an intermediate buffer before (or after) each invocation of one of the underlying operating system's native I/O operations.

However, the application still uses an object on the Java heap to orchestrate I/O operations, but the buffer that holds the 
data is held in native memory, the Java heap object only contains a reference to the native heap buffer. 

- [Buffer](https://docs.oracle.com/javase/7/docs/api/java/nio/Buffer.html): 

NIO Buffer is a container for data of a specific primitive type. It is a linear, finite sequence of elements of a specific primitive type.

Direct Known Subclasses:  ByteBuffer, CharBuffer, DoubleBuffer, FloatBuffer, IntBuffer, LongBuffer, ShortBuffer 

 The following invariant holds for the mark, position, limit, and capacity values:
```
    0 <= mark <= position <= limit <= capacity 
```    
     - A buffer's capacity is the number of elements it contains. The capacity of a buffer is never negative and never changes.
     - A buffer's limit is the index of the first element that should not be read or written. A buffer's limit is never negative and is never greater than its capacity.
     - A buffer's position is the index of the next element to be read or written. A buffer's position is never negative and is never greater than its limit.

