// TypeScript模块
// 模块的设计理念是可以更换的组织代码
// 模块是在其自身的作用域里执行，并不是在全局作用域，这意味着定义在模块里的变量，函数和类在模块外部是不可见的，除非明确的使用export导出它们。
// 类似的，必须通过import导入其他模块导出的变量，函数，类等。

// 两个模块之间的关系是通过在文件级别上使用import和export建立的。

// 模块使用模块加载器去导入其他的模块。
// 在运行时，模块加载器的作用是在执行此模块代码前去查找并执行这个模块的所有依赖。
// 最熟知的js模块加载器：
//     服务于Node.js的 CommonJS
//     服务于Web应用的  Require.js
//     此外还有        SystemJS , Webpack

// 模块导入
// import someInterfaceRef = require("./SomeInterface");  // CommonJS
import {SomeInterface} from "./SomeInterface"; // Module(ES6)
