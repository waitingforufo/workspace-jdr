let hello1 = "Hello World!";
console.log(hello1);
let name = "Alice";
let age = 25;
let name1 = "Alice";
class Student {
    name;
    age;
    constructor(name, age) {
        this.name = name;
        this.age = age;
    }
    greet() {
        console.log(`Hello, my name is ${this.name}`);
    }
}
let value = 42;
// 枚举
var Direction;
(function (Direction) {
    Direction[Direction["Up"] = 0] = "Up";
    Direction[Direction["Down"] = 1] = "Down";
    Direction[Direction["Left"] = 2] = "Left";
    Direction[Direction["Right"] = 3] = "Right";
})(Direction || (Direction = {}));
let dir = Direction.Up;
// 元组（Tuple）
let point = [10, 20];
// 访问控制修饰符(Access Modifiers)
class Person1 {
    name;
    age;
    constructor(name, age) {
        this.name = name;
        this.age = age;
    }
}
// 抽象类(Abstract Classes)
// 抽象类不能直接实例化，需要由子类实现。抽象类适用于定义通用行为和抽象方法的类层次结构
class Animal {
}
class Dog extends Animal {
    makeSound() {
        console.log("Woof!");
    }
}
// 泛型(Generics)
//允许在类，接口和函数中使用参数化类型，是的代码可以适应不同的类型需求，同时保持类型安全。
function identity(value) {
    return value;
}
let num = identity(42);
export function add(a, b) {
    return a + b;
}
// 类型守卫
function printId(id) {
    if (typeof id === "string") {
        console.log(id.toUpperCase());
    }
    else {
        console.log(id.toFixed(2));
    }
}
// 可选链和控制合并运算符
// ts增加了js的可选链(?.)和空值合并运算符(??)，简化了代码中对可能为null或undefined值的处理。
let user = { name: "Alice", address: { city: "Wonderland" } };
console.log(user?.address?.city); // 如果address存在则输出city,否则返回undefined
let value2 = null;
console.log(value2 ?? "default"); // 如果value2为null或undefined，则返回 "default"
let PartialTodo = { title: "Learn TypeScript" }; // 可选属性
// 编译期错误检查
// ts提供的编译期错误检查可以捕获js中不易发现的错误，如拼写错误，类型不匹配等，帮助提升代码质量。
// ES新特性支持
// ts提前支持了一些还未在所有环境中普及的ES特性，如装饰器(Decorators)，异步迭代器等，且能够将其编译成兼容js版本。
// 通过这些特性，ts提供了更安全，更结构化的代码能力，在大型项目和多人协作中尤其具有优势。
class Site {
    name() {
        console.log("Runoob");
    }
}
let obj = new Site();
obj.name();
