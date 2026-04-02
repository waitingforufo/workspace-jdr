let hello1: string = "Hello World!";
console.log(hello1);

let name: string = "Alice";
let age: number = 25;

let name1 = "Alice";

interface Person {
  name: string;
  age: number;
  greet(): void;
}

class Student implements Person {
  public name: string;
  public age: number;

  constructor(name: string, age: number) {
    this.name = name;
    this.age = age;
  }

  greet() {
    console.log(`Hello, my name is ${this.name}`);
  }
}

type StringOrNumber = string | number;
let value: StringOrNumber = 42;

// 枚举
enum Direction {
  Up,
  Down,
  Left,
  Right,
}

let dir: Direction = Direction.Up;

// 元组（Tuple）
let point: [number, number] = [10, 20];

// 访问控制修饰符(Access Modifiers)
class Person1 {
  private name: string;
  protected age: number;
  public constructor(name: string, age: number) {
    this.name = name;
    this.age = age;
  }
}

// 抽象类(Abstract Classes)
// 抽象类不能直接实例化，需要由子类实现。抽象类适用于定义通用行为和抽象方法的类层次结构
abstract class Animal {
  abstract makeSound(): void;
}

class Dog extends Animal {
  makeSound(): void {
    console.log("Woof!");
  }
}

// 泛型(Generics)
//允许在类，接口和函数中使用参数化类型，是的代码可以适应不同的类型需求，同时保持类型安全。
function identity<T>(value: T): T {
  return value;
}

let num = identity<number>(42);

export function add(a: number, b: number): number {
  return a + b;
}

// 类型守卫
function printId(id: string | number) {
  if (typeof id === "string") {
    console.log(id.toUpperCase());
  } else {
    console.log(id.toFixed(2));
  }
}

// 可选链和控制合并运算符
// ts增加了js的可选链(?.)和空值合并运算符(??)，简化了代码中对可能为null或undefined值的处理。
let user = { name: "Alice", address: { city: "Wonderland" } };
console.log(user?.address?.city); // 如果address存在则输出city,否则返回undefined

let value2 = null;
console.log(value2 ?? "default"); // 如果value2为null或undefined，则返回 "default"

// 类型兼容性和工具类型
// ts提供了一些工具类型，如Partial, Pick, Readonly, Record等，这些类型可以帮助生成新的类型，简化类型定义。
interface Todo {
  title: string;
  description: string;
}

let PartialTodo: Partial<Todo> = { title: "Learn TypeScript" }; // 可选属性

// 编译期错误检查
// ts提供的编译期错误检查可以捕获js中不易发现的错误，如拼写错误，类型不匹配等，帮助提升代码质量。

// ES新特性支持
// ts提前支持了一些还未在所有环境中普及的ES特性，如装饰器(Decorators)，异步迭代器等，且能够将其编译成兼容js版本。
// 通过这些特性，ts提供了更安全，更结构化的代码能力，在大型项目和多人协作中尤其具有优势。

class Site {
  name(): void {
    console.log("Runoob");
  }
}
let obj = new Site();
obj.name();
