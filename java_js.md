Use Javascript Engine in Java
========

```Java
import javax.script.*;

class Jtest
{
 public static void main(String[] args)
 {
     ScriptEngine engine = new ScriptEngineManager().getEngineByName("nashorn");
     try {
          engine.eval("print('Hello World!');");
     }
     catch (ScriptException ex)
     {
     }
 }
}

```
