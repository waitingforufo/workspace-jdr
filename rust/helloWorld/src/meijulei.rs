
#[derive(Debug)]
enum Book{
    Papery, Electronic
}

#[derive(Debug)]
enum Book2{
    Papery(u32),
    Electronic(String)
}

#[derive(Debug)]
enum Book3{
    Papery {index: u32},
    Electronic { url: String }
}
// 虽然可以如此命名，但是注意：并不能像访问结构体字段一样访问枚举类绑定的属性。
// 访问方法在 match 语法中。

#[derive(Debug)]
enum Book4{
    Papery(u32),
    Electronic { url: String }
}

// Option枚举类 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Option是Rust标准库中的枚举类，这个类用于填补Rust不支持 null 引用的空白。
// 许多语言支持 null 的存在（C，java），这样很方便，但也制造了极大的问题， null的发明者也承认这一点，”一个方便的想法造成累计10亿美元的损失”。
// null 经常在开发者把一切都当做不是null的时候给予程序致命一击：NPE
// 为了解决这个问题，很多语言默认不允许 null， 但在语言层面支持null的出现（常在类型前面用？符号修饰）
// java默认支持null，但可以通过 @NotNull注释限制出现null， 这是一种应付的办法。
// Rust在语言层面彻底不允许空值null的存在，但无奈null可以高效地解决少量的问题，
// 所以Rust引入了Option枚举类
enum Option<T>{
    Some(T),
    None
}
// 如果想定义一个可以为空值的类，可以这样：
// let opt = Option::Some("Hello");

// 如果想针对 opt 执行某些操作，必须先判断它是否是 Option::None:
// match opt {
//     Option::Some(something) => {
//         println!("{}", something);
//     },
//     Option::None => {
//         println!("opt is nothing");
//     }
// }
//
// 如果变量刚开始是空值，那么要体量一下编译器，它怎么知道值不为空的时候变量是什么类型的呢？
// 所以初始值为空的 Option 必须明确类型：
// let opt: Option<&str> = Option::None;
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

// if let语法 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// let i = 0;
// match i {
//     0 => println!("zero"),
//     _ => {}
// }
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

pub fn meijulei_lianxi(){
    let book = Book::Papery;

    println!("book: {:?}", book);  // book: Papery

    let book2 = Book2::Papery(1001);
    let ebook = Book2::Electronic(String::from("url://..."));
    println!("book2: {:?}, ebook: {:?}", book2, ebook);

    // 如果想为属性命名，可以用结构体语法：
    let book3 = Book3::Papery { index: 1001 };
    println!("book3: {:?}", book3);

    // match语法
    // 枚举的目的是对某一类事物的分类，分类的目的是为了对不同的情况进行描述。
    // 基于这个原理，往往枚举类型最终都会被分支结构处理（许多语言中的switch）。
    // switch语法很经典，但在Rust中并不支持，很多语言摒弃switch的原因都是因为switch容易存在因忘记添加break而产生的串接运行问题。
    //   java和C#这类语言通过安全检查杜绝这种情况出现。
    // Rust 通过 match 语句来实现分支结构。

    match book3 {                          // 类似 switch
        Book3::Papery { index } => {  // 类似 catch
            println!("it is Papery book: {}", index);
        },
        Book3::Electronic { url } => {
            println!("E0book: {}", url);
        }
    }

    // match块也可以当做函数表达式来对待，它也是可以有返回值的：
    // match 枚举类实例 {
    //     分类1 => 返回值表达式,
    //     分类2 => 返回值表达式,
    //     ...
    // }

    // 但是 所有返回值表达式 的类型必须一样！
    // 如果把 枚举类附加属性 定义成 元祖， 在 match块中需要临时指定一个名字：
    println!("book4: ");
    let book4 = Book4::Papery(1001);
    match &book4 {
        Book4::Papery(i) => {
            println!("{}", i);
            println!("{:?}", &book4);
        },
        Book4::Electronic { url } => {
            println!("{}", url);
            println!("{:?}", &book4);
        }
    }

    println!("Option枚举类 练习");
    // Option枚举类 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    let opt = Option::Some("Hello");
    match opt {
        Option::None =>{
            println!("opt is nothing");
        },
        Option::Some(something)=>{
            println!("{}", something);
        }
    }
    
    // 初始值为null的时候，必须明确类型
    let opt: Option<&str> = Option::None;
    match opt {
        Option::None => {
            println!("opt is nothing");
        },
        Option::Some(something) => {
            println!("{}", something);
        }
    }
    
    println!("Option枚举类 值分支选择练习");
    // Option是一种特殊的枚举类，他可以含值分支选择：
    let t = Some(64);
    match t {
        None => {
            println!(" t is nothing");
        },
        Some( 64 ) => println!("Yes"),
        _ => println!("No")
    }
    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    
    // if let语法
    let i = 0;
    match i {
        0 => println!("zero"),
        _ => {}
    }
}