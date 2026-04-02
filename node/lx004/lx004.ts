// TypeScript声明文件
// TS作为JS的超集，在开发过程中不可避免要引用其他第三方的javascript库。
// 虽然通过直接引用可以调用库的类和方法，但是却无法使用typescript诸如类型检查等特性功能。
// 为了解决这个问题，需要将这些库里的函数和方法去掉后  只保留导出类型声明， 而产生了一个描述javascript库和模块信息的声明文件。
// 通过引用这个声明文件，就可以借用typescript的各种特性来使用库文件了。

// 假如我们想使用第三方库 ， jQuery，我们通常这样获取一个id是foo的元素：
//
// $('#foo');
// 或
// jQuery('#foo');

// 但是在TS中，我们并不知道 $ 或 jQuery是什么东西。
// 这时，我们需要使用 declare关键字来定义它的类型，帮助TS判断我们传入的参数类型对不对：

// declare var jQuery: (selector: string) => any;
//
// jQuery('#foo');

// declare定义的类型只会用于编译时的检查，编译结果中会被删除。
// 上例编译结果是：
//
// jQuery('#foo');

// ============================================================
// 声明文件
// 声明文件以 .d.ts 为后缀，例如：

// runoob.d.ts

// 声明文件或模块的语法格式如下：
// declare module Module_Name {
// }

// TypeScript引入声明文件语法格式：

// /// <reference path = "runoob.d.ts" />

// 当然，很多流行的第三方库的声明文件不需要我们定义了，比如jQuery已经有人帮我们定义好了：
//   https://github.com/DefinitelyTyped/DefinitelyTyped/blob/master/types/jquery/index.d.ts
//====================================
// /// <reference path="JQueryStatic.d.ts" />
// /// <reference path="JQuery.d.ts" />
// /// <reference path="misc.d.ts" />
// /// <reference path="legacy.d.ts" />

// export = jQuery;
//=====================================
