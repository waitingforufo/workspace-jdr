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
    name() {
        console.log("Runoob");
    }
}
const obj = new Site();
obj.name();
const person1 = new Person("KKK");
console.log("Person name is ", person1.name);
let val = "hello";
let strLength = val.length;
function identity(arg) {
    return arg;
}
let num = 10;
// 类型守卫
function isString(value) {
    return typeof value === "string";
}
async function fetchData() {
    const res = await fetch("http://baidu.com");
    const data = await res.text();
    return data;
}
try {
    throw new Error("Something went wrong");
}
catch (e) {
    if (e instanceof Error) {
        console.log(e.message);
    }
}
let name22 = "Alice";
let age = 30;
let isDone = true;
let list = [1, 2, 3];
let person22 = ["Alice", 30];
let value22 = 42;
function log() { }
let empty = null;
let undef = undefined;
function error() {
    throw new Error("error");
}
let obj22 = { name: "Alice" };
let value222 = "Hello";
if (typeof value222 === "string") {
    let value222 = "aaaa";
    //value222 = "aaa";
}
let id;
id = "123";
id = 456;
let direction;
direction = "up";
//direction = "aaa";
