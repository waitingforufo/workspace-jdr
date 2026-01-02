
// 任何一门编程语言如果不能组织代码都是难以深入的，几乎没有一个软件产品是由一个源文件编译而成的。
// 对于一个工程来讲，组织代码是十分重要的。
// Rust有三种重要的组织概念： 箱， 包， 模块。

// 箱（Crate） >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// “箱” 是二进制程序文件或者库文件，存在于“包”中。
// “箱”是 树状结构 的，它的 树根 是 编译器开始运行时 编译的 源文件 所编译的程序。
// 注意： “二进制程序文件” 不一定是 “二进制可执行文件”， 只能确定是 包含目标机器语言 的文件， 文件格式随编译环境不同而不同。

// 包（Package） >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 用 Cargo new 所创建rust工程时，工程目录下会建立一个 Cargo.toml文件。
// 工程 的实质就是一个 包， 包 必须由一个 Cargo.toml文件来管理，该文件描述了包的基本信息以及依赖项。
// 一个 包 最多包含 一个库“箱”， 可以包含任意数量的 二进制“箱”， 但是至少包含一个“箱”（不管是库还是二进制“箱”）。
// 当使用 Cargo new命令创建完包之后，src 目录下会生成一个 main.rs 源文件， Cargo默认这个文件为二进制箱的根，
//   编译之后的二进制箱将与包名相同。

// 模块（Module）
// 组织模块的主要结构往往是 树。
// java组织功能模块的主要单位是 类， 而JavaScript组织模块的主要方式是 function。
// 这些先进的语言的组织单位可以层层包含，就像文件系统的目录结构一样。
// Rust中的组织单位是 模块（Module）。

mod nation{
    mod government{
        fn govern(){
            ;
        }
    }// end mod

    mod congress{
        fn legislate(){
            ;
        }
    }// end mod

    mod court{
        fn judicial(){
            ;
        }
    }// end mod
}// end mod
// 这是一段描述法治国家的程序： 国家（nation）包括政府（government），议会（congress）和法院（court），
//   分别有行政，立法和司法的功能。
//   可以转换成树状结构表示：
//   nation
//     |_ government
//     |    |_ govern
//     |_ congress
//     |    |_ legislate
//     |_ court
//          |_ judicial
//
// 在文件系统中，目录结构往往以斜杠在路径字符串中表示对象的位置，rust中路径分隔符是 ::
// 路径分为 绝对路径 和 相对路径。
// 绝对路径 从 crate 关键字开始描述。
// 相对路径 从 self或super关键字 或一个标识符 开始描述。
// e.g.:
// crate::nation::government::govern();  // govern()函数的绝对路径
// nation::government::govern();         // 相对路径

// 访问权限 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Rust中有两种简单的访问权： 公共（public） 和 私有（private）。
// 默认情况下，如果不加修饰， 模块中的成员访问权限都是 私有 的。
// 如果想使用公共权限， 需要使用 pub 关键字。
// 对于私有的模块， 只有在与其 平级 的位置 或 下级 的位置才能访问，不能从其外部访问。
// e.g.:
mod nation2 {
    pub mod government{
        pub fn govern(){}
    }

    mod congress{
        pub fn legislate(){}
    }

    mod court{
        fn judicial(){
            super::congress::legislate();
        }
    }
}

// 如果模块中定义了 结构体，结构体除了 其本身是私有的 以外， 其字段默认也是私有的。
// 所以如果想使用 模块中的结构体 以及 其字段， 需要 pub 声明：
mod back_of_house{
    pub struct Breakfast {
        pub toast: String,
        seasonal_fruit: String
    }

    impl Breakfast {
        pub fn summer(toast: &str) -> Breakfast {
            Breakfast {
                toast: String::from(toast),
                seasonal_fruit: String::from("peaches")
            }
        }//end fn
    }//end impl
}// end mod

pub fn eat_at_restaurant() {
    let mut meal = back_of_house::Breakfast::summer("Rye");
    meal.toast = String::from("Wheat");
    println!("I'd like {} toast please", meal.toast);
}

// 难以发现的模块 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 每一个Rust文件的内容 都是一个 “难以发现”的 模块。
// 实例：
// second_module.rs --------------------------------
// pub fn message() -> String {
//     String::from("This is the 2nd module.");
// }
//
// main.rs -----------------------------------------
// mod second_module;  // 包含 second_module模块（即 second_module.rs文件的模块）
//
// fn main() {
//     println!("This is the main module.");
//     println!("{}", second_module::message());
// }

// use 关键字 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// use关键字 能够将模块标识符引入当前作用域：
// e.g.:
// mod nation{
//     pub mod government{
//         pub fn govern(){}
//     }
// }
//
// use crate::nation::government::govern;  // govern()引入到当前域里（当前模块里）
// 这样就解决了 局部模块 路径过长的问题。
//
// fn main(){
//     govern();  // govern()函数可以直接调用了
// }

// 有些情况下存在 两个 相同名称，且 同样需要导入， 就可以使用 as 关键字为标识符添加别名；
pub mod nation5 {
    pub mod government {
        pub fn govern(){}
    }//end mod

    pub fn govern(){}
}//end mod

use crate::rust_zuzhiguanli::nation5::government::govern;       // 1.
use crate::rust_zuzhiguanli::nation5::govern as nation_govern;  // 2. 与 govern()同名，所以用 as 取别名

// use关键字可以与 pub关键字配合使用：>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// mod nation {
//     pub mod government {
//         pub fn govern() {}
//     }//end mod
//
//     pub use government::govern;  // 引入 government::govern函数，同时pub类型抛出
// }//end mod
//
// fn main() {
//     nation::govern();
// }
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// 引用标准库 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Rust官方标准库字典：  https://doc.rust-lang.org/stable/std/all.html
// 导入系统库：
use std::f64::consts::PI;
// 所有的 系统库模块 都是被 默认导入 的， 所以在使用的时候只需要使用 use关键字 简化路径就可以方便地访问。

pub fn zuzhiguanli_lianxi(){
    nation2::government::govern();

    eat_at_restaurant();

    govern();         // 调用 1函数
    nation_govern();  // 调用 2函数

    println!("(PI / 2.0).sin() = {}", (PI / 2.0).sin());  // 1
}