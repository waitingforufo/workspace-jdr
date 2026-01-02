mod suoyouquan;
mod qiepian;
mod jiegouti;
mod meijulei;
mod rust_zuzhiguanli;
mod cuowuchuli;
mod fanxing;
// 输出平方后的数组
// println!("Squared numbers: {:?}", squared_numbers);  // OK rst: [2,4,9]

// 闭包 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 特性        闭包                       函数
// 匿名性      是匿名的，可存储为变量         有固定名称
// 环境捕获    可以捕获外部变量              不能捕获外部变量
// 定义方式    、                          参数
// 类型推导    参数和返回值类型可以推导        必须显示指定
// 存储与传递   可以作为变量，参数，返回值      同样支持

// 闭包声明
// let closure_name = |参数列表| 表达式或语句块;
// e.g.:
//     let calculate = |a, b, c| a * b + c;
//     let rst = calculate(1, 2, 3);  // 像函数一样被调用

// 匿名函数
// 闭包在rust中类似于匿名函数，可以在代码中以 {} 语法块的形式定义，使用 || 符号来表示参数列表；
// let add = |a,b| a+b;
// println!("{}", add(2,3));  // 输出5

// 捕获外部变量
// 闭包可以捕获周围环境中的变量，可以访问定义闭包的所在作用域中的变量；
// e.g.:
//    lex x =５；

//    let square = |num| num *　ｘ；
//    println!("{}", square(3));  // 输出： 15

// 闭包可以通过三种方式捕获外部变量：
//     - 按引用捕获(默认，类似 &T)
//     - 按值捕获(类似 T)
//     - 可变借用捕获(类似 &mut T)

// 闭包默认按引用捕获外部变量
// 使用 move 关键字可以强制按值捕获， 将外部变量的所有权转移到闭包内。
// 如果闭包需要修改外部变量，需显示声明为 mut 闭包。

// 闭包的特性
// 1.闭包可以作为函数参数
//   闭包经常作为参数传递给函数，例如迭代器的.map(), .filter()方法；
//   e.g.:
//   fn apply_to_value<F>(val: i32, f: F) -> i32
//   where
//       F: Fn(i32) -> i32,  // Fn是闭包的一个特性(trait)，表示闭包可以被调用
//   {
//        f(val)
//   }
//
//   fn main() {
//       let double = |x| x *２；
//       let result = apply_to_value(5, double);
//       println!("Result: {}", result);  // 输出： Result: 10
//   }
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/// Adds one to the number given.
///
/// # Examples
///
/// ```
/// let x = add(1, 2);
/// ```
fn add(a: i32, b: i32) -> i32 {
    a + b
}

fn add2(a: i32, b: i32) -> i32 {
    // 随时都可以以return关键字结束函数运行并返回一个类型合适的值
    return a + b;

    // 但是rust不支持自动返回值类型判断！
    // 如果没有声明函数返回值的类型，函数将被认为是“纯过程”，不允许产生返回值，return后面不能有返回值表达式。
    // 这样做的目的是为了让公开的函数能够形成可见的公报。
    // 注意： 函数体表达式不能等同于函数体， 它不能使用return关键字。
}

/// while循环练习
///
/// Example:
/// ```
/// whileLoop();
/// ```
fn while_loop(){
    println!("while循环练习");

    let mut number = 1;
    while number != 4{
        println!("{}", number);
        number += 1;
    }
    println!("EXIT");
}

/// for循环练习
///
/// Example:
/// ```
/// for_loop();
/// ```
fn for_loop(){
    println!("for循环练习");

    let a = [10, 20, 30, 40, 50];

    // 完成对数组的遍历。 a.iter()代表a的迭代器(iterator)
    for i in a.iter(){
        println!("值为：{}", i);
    }

    // 也可以使用数组下标来访问
    println!("使用下标来访问数组：");

    for i in 0..5{  // 不包括5 项包括5就用 0..=5
        println!("a[{}] = {}", i, a[i]);
    }
}

/// loop循环练习
///
/// Example:
/// ```
/// loop_loop();
/// ```
fn loop_loop(){
    let s = ['H', 'e', 'l', 'l', 'o', ',', 'W', 'o', 'r', 'l', 'd'];

    let mut i = 0;
    loop{
        let ch = s[i];

        if ch == 'd' {
            println!("碰到了d字符，loop循环结束");
            break;
        }

        println!("\'{}\'", ch);
        i += 1;
    }// end loop

    println!("loop结束。 i的值：{}", i);
}

// Rust迭代器
// Rust中的迭代器(Iterator)强大灵活。用于对集合（数组，向量，链表等）进行逐步访问和操作。
// 迭代器是惰性求值的，迭代器本身不会立即执行操作，而是在需要时才会产生值。
// 迭代器允许以一种声明式的方式来遍历序列，如数组，切片，链表等集合类型的元素。
// 迭代器的核心思想： 将数据处理过程与数据本身分离，使代码更清晰，更易读，更易维护。
// 在Rust中，迭代器通过实现Iterator trait来定义。
// 最基本的trait方法是next，用于逐一返回迭代器中的下一个元素，直到返回 None 表示结束。
// 示例
pub trait Iterator{
    type Item;

    fn next(&mut self) -> Option<Self::Item>;

    // 其他默认实现的方法，如map, filter等。
}

/// rust程序入口点 - main函数
/// 学习rust的联系用代码
/// 学习一门编程语言就需要亲自动手编写代码，不能只是停留在用眼睛看的层面上
/// 敲代码敲多了自然就熟悉各种语法了，也就熟练掌握了一门语言。。。
fn main() {

    let a = true;
    let b = false;

    println!("a && b = {}", a && b);
    println!(" a || b = {}", a || b);

    println!("\n\n --- \nHello, world! This is my first RUST program.");

    let num1 = 50;
    let num2 = 20;

    println!("\nadd() The value of num1+num2 is {}", add(num1,num2));
    println!("\nadd2() The value of num1+num2 is {}", add2(num1,num2));

    let sum = 5 + 10;
    let difference = 95.5 - 4.3;
    let product = 4 * 30;
    let quotient = 56.7 / 32.2;
    let remainder = 43 % 5;

    println!("{}, {}, {}, {}, {}", sum, difference, product, quotient, remainder);

    // 元祖 用（）包括的不同类型的数据
    let tup: (i32, f64, u8) = (500, 6.4, 1);
    // tup.0 , tup.1, tup.2
    println!("tup {}, {}, {}", tup.0, tup.1, tup.2);

    let (x, y, z) = tup;
    println!("The value of y is: {}", y);

    // 数组  用[]包括的同类型的数据
    let a = [1, 2, 3, 4, 5, 6];
    let b = ["January", "February", "March", "April", "May"];
    let c:[i32; 5] = [1, 2, 3, 4, 5];

    let d = [3; 5];

    let first = a[0];
    let second = b[1];

    println!("first: {}, second: {}", first, second);

    //a[0] = 123;  // NG 数组a不可变
    let mut a = [1, 2, 3];
    a[0] = 4;  // OK

    /*
    多行注释
    */

    // rust可以在一个用{}包括的块里编写一个较为复杂的表达式：
    let x = 5;

    let y = {
        let x = 3;
        x + 1           // 最后一个步骤是表达式，此表达式的结果是整个表达式块所代表的值。
                        // 这种表达式块叫做函数体表达式
                        // 注意： x + 1 后面没有分号， 否则它将变成一条语句！
    };
    // 这种表达式块是一个合法的函数体，而且rust中函数定义可以嵌套

    println!("x 的值为 : {}", x);
    println!("y 的值为 : {}", y);

    fn five()->i32{
        5
    }

    println!("five()的值为：{}",five());

    let number = 3;
    if (number <5){
        println!("condition was true");
    }else{
        println!("condition was false");
    }

    //println!("2222\n\n\n{}", 5);  // 5222 ???
    println!(" == 22222 == ");

    if number < 5{
        println!("condition was true");
    }else{
        println!("condition was false");
    }

    println!(" ---------------------- ");

    let mut tmpStr: String;
    if number > 0 {
        tmpStr = String::from("大于0");
    }else if number < 2 {
        tmpStr = String::from("小于2");
    }else{
        tmpStr = String::from("else");
    }
    println!("结果：{}", tmpStr);

    // rust中的条件表达式必须是bool类型， 例如下面的程序是错误的:
    // let number = 3;
    // if number {              // NG expected 'bool'
    //     println!("Yes");
    // }

    // 虽然C/C++语言中的条件表达式用整数表示，非0即真， 但这个规则在很多注重代码安全性的语言中是禁止的。
    // 在rust中可以只用if - else结构实现类似于三元条件运算表达式 (A?B:C)的效果：
    let a = 3;
    //let number = if a>0 {1} else {-1};  // OK
    //let number = a>0? 1 : -1;           // NG
    println!("number: {}", number);

    while_loop();

    for_loop();

    loop_loop();

    println!("loop的break <retVal>练习");
    // loop循环可以通过 break结束循环，并给予外部一个返回值。
    let s = ['J', 'D', 'R'];
    let mut idx = 0;

    let location = loop{
        let ch = s[idx];
        if ch == 'D'{
            break idx;         // break可以指定返回值， 类似return
        }
        idx += 1;
    };
    println!("'D'的索引为 {}", location);

    println!("迭代器练习");
    let vec = vec![1,2,3,4,5];
    let filtered_vec: Vec<i32> = vec.into_iter().filter(|x| x % 2 == 0).collect();
    for &itm in filtered_vec.iter(){
        println!("{}", itm);
    }
    // vec.iter()返回一个迭代器，for循环遍历这个迭代器，并将每个元素赋值给itm变量，然后执行循环体中的代码。

    println!("迭代器适配器练习");
    // 迭代器适配器
    // 允许通过方法链来改变或过滤迭代器的内容，而不会立刻消耗它。
    let v = vec![1,2,3,4,5];
    let doubled: Vec<i32> = v.iter().map(|x| x*2).collect();
    for &itm in doubled.iter(){
        println!("{}", itm);
    }

    println!("迭代器链 练习");
    // 迭代器链
    use std::iter::Peekable;

    let arr = [1,2,3,4,5];
    let mut iter = arr.into_iter().peekable();
    while let Some(val) = iter.next(){
        if val % 2 == 0 {
            continue;
        }
        println!("{}", val);
    }

    let numbers = vec![1,2,3,4,5];

    // 使用迭代器对数组进行遍历，并输出每个元素
    println!("Iterating through the array:");
    for num in numbers.iter(){
        println!("{}", num);
    }

    // 使用迭代器的map方法对数组的每个元素进行平方运算，并收集结果到一个新的数组中
    let squared_numbers: Vec<i32> = numbers.iter().map(|x| x*x).collect();

    // 输出平方后的数组
    println!("Squared numbers: {:?}", squared_numbers);

    // 过滤练习
    let tmpVec = vec![1,2,3,4,5,6,7,8,9,10];

    // 使用迭代器的filter方法对数组进行过滤，筛选出偶数
    let even_numbers: Vec<i32> = tmpVec.iter().filter(|&x| x % 2 == 0).cloned().collect();
    println!("orgin numbers: {:?}", tmpVec);
    println!("Even numbers: {:?}", even_numbers);

    // 闭包练习
    println!("闭包练习");
    let mut num = 5;

    // 按引用捕获
    let print_num = || println!("num = {}", num);  // 无参数，使用环境中的 num
    print_num();  // num =５

    // 按值捕获
    // move关键字，闭包会获取它捕获的环境变量的所有权，这些变量的所有权会从外部作用域转移到闭包内部，
    //     外部作用域将无法再使用这些变量。
    let take_num = move || println!("num taken = {}", num);
    take_num();  // num taken = 5
    println!("{}", num);  // 5    * 按理说要出错（没有所有权了）， 但是仍然正常运行。。。

    // 可变借用捕获
    let mut change_num = || num += 1;
    change_num();
    println!("num after closure = {}", num);  // num after closure = 6

    // 获取所有权
    let s = String::from("hello");
    let print_s = move || println!("{}", s);
    print_s();  // 输出： hello
    //println!("{}", s);  // 出错。 因为s的所有权已经被转移给了闭包

    suoyouquan::suoyouquan_lianxi();
    qiepian::qiepian_lianxi();
    jiegouti::jiegouti_lianxi();
    meijulei::meijulei_lianxi();

    rust_zuzhiguanli::zuzhiguanli_lianxi();
    
    cuowuchuli::cuowuchuli();
    
    fanxing::fanxing_lianxi();
}