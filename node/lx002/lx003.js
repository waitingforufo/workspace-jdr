"use strict";
var Role;
(function (Role) {
    Role[Role["Admin"] = 0] = "Admin";
    Role[Role["User"] = 1] = "User";
    Role[Role["Guest"] = 2] = "Guest";
})(Role || (Role = {}));
// 创建用户对象，符合User接口的结构
const user = {
    id: 1,
    userName: "Alice",
    isActive: true,
    role: Role.User,
    hobbies: ["Reading", "Gaming"],
    contactInfo: ["+1", 123456789],
};
/**
 * 获取用户信息
 * @param user
 */
function getUserInfo(user) {
    return `User ${user.userName} is ${user.isActive ? "active" : "inactive"} with role %{Role[user.role]}`;
}
/**
 * 打印用户信息
 * @param user
 */
function printUserInfo(user) {
    console.log(getUserInfo(user));
}
/**
 *
 * @param query
 */
function findUser(query) {
    // 判断query类型
    if (typeof query === "number") {
        return user.id ? user : undefined;
    }
    else if (typeof query === "string") {
        return user.userName ? user : undefined;
    }
    return undefined;
}
function throwException(message) {
    throw new Error(message);
}
// 处理未知类型数据
let unknownData = "This is a string";
unknownData = 42; // 重新赋值为数字，类型为any
// 使用unknow类型处理不确定的数据，更加安全
let someData = "Possible data";
if (typeof someData === "string") {
    console.log(`Length of data:${someData.length}`);
}
// 调用各个函数
printUserInfo(user);
console.log(findUser(1));
console.log(findUser("Alice"));
// 使用null和undefined类型的变量
let emptyValue = null;
let unInitializedValue = undefined;
var str = "1";
var str2 = str;
console.log(str2);
var a = 10;
var result = a < 10 && a > 5;
var result2 = a > 5 || a < 10;
function buildName(firstName, lastName) {
    if (lastName) {
        return firstName + " " + lastName;
    }
    return firstName;
}
let rst111 = buildName("Bob");
let rst222 = buildName("Bob", "adams"); //可选参数
//let rst223: string = buildName("Bob", "adams", "aaa");
//默认参数
function calculate_discount(price, rate = 0.5) {
    var discount = price * rate;
    console.log("计算结果：", discount);
}
calculate_discount(1000);
calculate_discount(1000, 0.3);
//剩余参数
function addNumbers(...nums) {
    var i;
    var sum = 0;
    for (i = 0; i < nums.length; i++) {
        sum += nums[i];
    }
    console.log("和：", sum);
}
addNumbers(1, 2, 3);
addNumbers(10, 10, 10, 10, 10);
// 匿名函数
// var res = function([arguments]){...}
let msg = function () {
    return "hello world";
};
console.log(msg());
let res = function (a, b) {
    return a + b;
};
console.log(res(1, 2));
//匿名函数自调用
(function (name) {
    var x = "Hello! from 匿名函数自调用 name: " + name;
    console.log(x);
})("JDR");
// js内置构造函数Function()定义函数
// var res = new Function([arg1[,arg2[, ...argN]],] functionBody)
let myFunction = new Function("a", "b", "return a*b");
let valkk = myFunction(4, 3);
console.log("valkk: ", valkk);
//递归函数
function factorial(number) {
    if (number <= 0) {
        return 1;
    }
    else {
        return number * factorial(number - 1);
    }
} //end func
console.log("6*5*4*3*2*1 = ", factorial(6));
// Lambda函数
//也称之为箭头函数
//比函数表达式更短
// ([param1,param2,...paramn]) => statement;
const foo = (x) => 10 + x;
console.log(foo(100));
//函数是一个语句块：
// ([param1, param2, ...paramn]) => {
//     // 代码块
// }
// 函数返回两个数的和
const foo2 = (x) => {
    x = 10 + x;
    console.log(x);
};
foo2(200);
// 可以不指定参数类型，通过函数内来推断参数类型
const func1 = (x) => {
    if (typeof x == "number") {
        console.log(x + "是一个数字");
    }
    else if (typeof x === "string") {
        console.log(x + "是一个字符串");
    }
};
func1(12);
func1("Tom");
// 单个参数的时候，（）是可选的
const display = (x) => {
    console.log("输出为" + x);
};
display(12);
function disp(x, y) {
    console.log(x);
    console.log(y);
}
disp("abc");
disp(1, "xyz");
const val99 = new Number(10);
console.log(val99.valueOf());
// 数组
const numArr = [2, 4, 6, 8];
const numArr2 = new Array(4);
for (let i = 0; i < numArr2.length; i++) {
    numArr2[i] = i * 2;
    console.log(numArr2[i]);
}
// 直接初始化数组元素
let sites = new Array("Google", "Runoob");
//数组结构 - 可以把数组元素赋值给变量
let arr88 = [12, 13];
let [x, y] = arr88; // 将数组的两个元素赋值给变量x和y
console.log(x);
console.log(y);
//数组迭代
const arr89 = [1001, 1002, 1003, 1004];
for (let j in arr89) {
    // j 得到的是下标值 0, 1, 2, 3
    console.log(j);
    console.log(arr89[j]);
}
console.log(" --------------- j of arr89 ");
for (let j of arr89) {
    console.log(arr89[j]); // undefined
}
//多维数组
const multi = [
    [1, 2, 3],
    [23, 24, 25],
];
console.log(multi[0][0]);
console.log(multi[1][2]);
let myMap = new Map([
    ["key1", "value1"],
    ["key2", "value2"],
]);
for (const key of myMap.keys()) {
    console.log(key);
}
for (const value of myMap.values()) {
    console.log(value);
}
for (const [key, value] of myMap.entries()) {
    console.log(key, value);
}
myMap.forEach((value, key) => {
    console.log(key, value);
});
// 元组
let tuple = [1, "John"];
console.log(tuple);
// 通过 as const断言，ts会将改元组视为一个不可变的常量元组
let tuple2 = [42, "Hello"];
function printArray(arr) {
    arr.forEach((item) => console.log(item));
}
function getResult(value) {
    return value;
}
function combine(first, second) {
    return `${first} ${second}`;
}
// 泛型类
class Box {
    value;
    constructor(value) {
        this.value = value;
    }
    getValue() {
        return this.value;
    }
}
let stringBox = new Box("TypeScript");
console.log(stringBox.getValue());
function logLength(arg) {
    console.log(arg.length);
}
logLength("hello");
//logLength(42); // ERROR 数字没有length属性
// 泛型的默认值
function defaultValue(arg) {
    return arg;
}
let rst33 = defaultValue("hello"); // 推断为string类型
let rst34 = defaultValue(42); // 推断为number类型
