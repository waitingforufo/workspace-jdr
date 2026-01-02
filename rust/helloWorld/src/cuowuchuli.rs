
// Rust有一套 独特的处理异常情况的机制， 它并不像其他语言中的 try机制那样简单。
// 首先，程序中一般会出现两种错误： 可恢复错误 和 不可恢复错误。

// 可恢复错误
//   典型案例是 文件访问错误。 可以用等待来解决。
// 不可恢复错误
//   无法解决的逻辑错误导致，例如访问数组末尾以外的位置 - 程序bug。
//
// 大多数编程语言不区分这两种错误，并用 Exception（异常）类 来表示错误。
// 在 Rust中 没有 Exception。
// 对于可恢复错误 用 Result<T,E>类来处理， 对于不可恢复错误 使用 panic! 宏来处理。

// 不可恢复错误 : panic!宏

use std::fs::File;

// 可恢复的错误
// Rust中，通过 Result<T,E>枚举类 作返回值 来进行异常表达:
enum Result2<T,E>{
    Ok(T),
    Err(E)
}

// 自己写的函数传递错误 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
fn func2(i:i32) -> Result2<i32, bool>{
    if i >= 0 { Result2::Ok(i)}
    else { Result2::Err(false)}
}

// ? 符号 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 实际作用： 
//   将Result类非异常的值 直接取出，
//   如果有异常 将 异常Result返回出去。
// 所以， ？符号 仅用于 返回值类型为 Result<T,E>的函数， 其中 E类型 必须和 ？ 所处理的Result的E类型一致。

// kind方法 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 可以把try块在独立函数中实现，将所有的异常都传递出去解决。
// 实际上这才是一个分化良好的程序应当遵循的编程方法。
// 这就需要判断 result的 Err类型， 获取 Err类型的函数是 kind()。
use std::io;
use std::io::Read;
//use std::fs::File;

// fn read_text_from_file(path: &str) -> Result<String, io::Error>{
//     let mut f = File::open(path)?;
//     let mut s = String::new();
//     
//     f.read_to_string(&mut s)?;
//     Ok(s);
// }

pub fn cuowuchuli(){
    println!("错误处理 练习");

    // 不可恢复错误
    //panic!("error occured");  // OK 抛出异常
    println!("Hello, JDR");

    // 可恢复错误
    let f = File::open("hello.txt");
    match f {
        Ok(file) => {
            println!("File opened successfully.");
        },
        Err(err) => {
            println!("Faild to open the file.");
        }
    }
    // 显示：Faild to open the file.

    // 自己写的函数错误
    let r = func2(10000);
    if let Result2::Ok(v) = r{
        println!("OK: f(-1) = {}", v);
    }else{
        println!("Err");
    }
}