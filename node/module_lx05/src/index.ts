import { add } from "./esmodule/add.mjs";

const greeting: string = "Hello, TypeScript";
console.log(greeting);

// モジュール内の関数呼出
console.log("1 + 2 = ", add(1,2));

