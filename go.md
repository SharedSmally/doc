# go

## env
```
echo 'export GOPATH=$HOME/code/go' >> $HOME/.profile    #GOPATH: go workspace
echo 'export PATH=$PATH:/usr/local/go/bin' >> $HOME/.profile
```

## start
The entry point to a program has to be a function called main within a package main.
```
# main.go
package main

func main() {
   println("it's over 9000!")
}
```
```
package main
import (
   "fmt"
   "os"
)
func main() {
   if len(os.Args) != 2 {
      os.Exit(1)
   }
   fmt.Println("It's over", os.Args[1])
}
```
```
go run main.go     # compile and run it, remove temp dir after running it
go run --work main.go   # compile and run it, keep temp dir
go build main.go   # compile
```
### Basic types:
- uint8/int8;uint16/int16;uint32/int32;uint64/int64;
- int/uint(32 or 64bits); string; boolean; byte(=uint8)
- float32/float64; complex32/complex64

### struct: can be associated with methods
```
type Saiyan struct {
   Name string
   Power int
}
```
```
goku := Saiyan{
   Name: "Goku",
   Power: 9000,
}

goku := Saiyan{}

goku := Saiyan{"Goku", 9000}

goku := Saiyan{Name: "Goku"}
goku.Power = 9000
```
Associate a method with a structure:
```
func (s *Saiyan) Super() {
   s.Power += 10000
}
Structures don’t have constructors. Instead create a function that returns an instance of the desired type (like a factory):
```
func NewSaiyan(name string, power int) *Saiyan {
   return &Saiyan {
     Name: name,
     Power: power,
   }
}
```
goku := &Saiyan{"Goku", 9001}
goku.Super()
fmt.Println(goku.Power) // will print 19001
```
- Go does have a built-in *new* function which is used to allocate the memory required by a type. The result of new(X) is the same as &X{}:
```
goku := new(Saiyan)
// same as
goku := &Saiyan{}

goku := new(Saiyan)
goku.name = "goku"
goku.power = 9001
//vs
goku := &Saiyan {
   name: "goku",
   power: 9000,
}
```

### map, array,slice
```
var scores [10]int
scores[0] = 339
scores := [4]int{9001, 9333, 212, 33} #with initialization
for index, value := range scores {  #iterate array

}
```

## difference to c++
- var decl: type is in the end, same for functions. Variable cannot be declared more than one time, and it must be used. All variables are initialized when declared.
```
var name1[, namen] type
name := initialValue   # declare and assign value to a var. type is from initial value, cannot use := for the same variable 2 times. Use = in the following assignments
name, power := "Goku", 1000
```
- No bracket for condition statements (if, for switch,...)
- switch/case can be anything
- Only struct; No classes, inheritance, polymorphism and overloading;
- Go passes arguments to a function as copies. Need to use pointer to update struct.
```
func main() {
   goku := &Saiyan{"Goku", 9000}
   Super(goku)
   fmt.Println(goku.Power)
}
func Super(s *Saiyan) {
   s = &Saiyan{"Gohan", 1000}
}

```
