// TypeScript基本结构
// 声明部分： 包括类声明，接口声明等。
// 变量部分： 包括let，const和var的使用
// 函数声明： 普通函数和箭头函数
// 类声明： 定义类及其成员
// 接口与类型别名： 描述类型的结构
// 模块化： 通过import和export组织代码
// 类型断言： 强制类型转换
// 泛型： 是代码具备更多的复用性
// 注释： 增加代码的可读性
// 类型推断： 自动推断类型
// 类型守卫： 缩小类型范围
// 异步编程： 支持async/await
// 错误处理： 通过try/catch进行错误捕捉

import { Person } from "./person.js";

class Site {
  name(): void {
    console.log("Runoob");
  }
}

const obj = new Site();
obj.name();

// 接口语类型别名
interface Animal {
  name: string;
  sound: string;
  makeSound(): void;
}

// 类型别名（Type Alias）：允许为对象类型，联合类型，交叉类型等定义别名
type ID = string | number;

const person1 = new Person("KKK");

console.log("Person name is ", person1.name);

let val: any = "hello";
let strLength: number = (val as string).length;

function identity<T>(arg: T): T {
  return arg;
}

let num = 10;

// 类型守卫
function isString(value: any): value is string {
  return typeof value === "string";
}

async function fetchData(): Promise<string> {
  const res = await fetch("http://baidu.com");
  const data = await res.text();
  return data;
}

try {
  throw new Error("Something went wrong");
} catch (e) {
  if (e instanceof Error) {
    console.log(e.message);
  }
}

let name22: string = "Alice";
let age: number = 30;
let isDone: boolean = true;
let list: number[] = [1, 2, 3];
let person22: [string, number] = ["Alice", 30];

let value22: any = 42;

function log(): void {}

let empty: null = null;
let undef: undefined = undefined;

function error(): never {
  throw new Error("error");
}

let obj22: object = { name: "Alice" };

let value222: unknown = "Hello";
if (typeof value222 === "string") {
  let value222: string = "aaaa";
  //value222 = "aaa";
}

let id: string | number;
id = "123";
id = 456;

let direction: "up" | "down" | "left" | "right";
direction = "up";
//direction = "aaa";
