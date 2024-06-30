import "fmt"

type FooBar struct {
    n   intanA 
    chanA   chan    bool
    chanB   chan    bool
}
func NewFooBar(n int) *FooBar {
    return &FooBar{n:n, chanA: make(chan bool, 1), chanB: make(chan bool)}
}

func (fb *FooBar) Foo(printFoo func()) {
    for i := 0; i < fb.n; i++ {
        fb.chanA <- true 
        printFoo()
        fb.chanB <- true 
    }
}

func (fb *Foobar) Bar(printBar func()) {
    for i := 0; i < fb.n; i ++ {
        <- fb.chanB
        printBar()
        <- fb.ChanA 
    }
}

func printFoo() {fmt.Println("foo")}
func printBar() {fmt.Println("bar")}
func main() {
    fmt.Println("hi")
    FooBar f = NewFooBar(100)
    go f.Foo()
    go f.Bar()
}