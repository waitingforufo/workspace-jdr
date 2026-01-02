
// C++语言中使用 “模板” 来实现泛型， 而C语言中没有泛型机制，这也导致C语言难以构建类型复杂的工程。
// 泛型机制
//   用于表达类型抽象的机制，一般用于功能确定，数据类型待定的类，如链表，映射表等。

// 在函数中定义泛型
// e.g.: 对整型数字选择排序的方法

fn max(array: &[i32]) -> i32{
    let mut max_index = 0;
    let mut i = 1;

    while i < array.len() {
        if array[i] > array[max_index] {
            max_index = i;
        }
        i += 1;
    }

    array[max_index]
}
// 这是一个简单的取最大值程序，可以用于处理 i32类型的数据，但无法用于 f64类型的数据。
// 通过泛型，可以使用这个函数 利用到各个类型中去。
// 但实际上并不是所有的数据类型都可以比大小，所以接下来一段代码并不是用来运行的，而是用来描述一下函数泛型的语法格式：
// e.g.:
// fn max<T>(array: &[T]) -> T {
//     let mut max_index = 0;
//     let mut i = 1;
//
//     while i < array.len() {
//         if array[i] > array[max_index] {
//             max_index = i;
//         }
//         i += 1;
//     }
//     array[max_index]
// }

// 结构体与枚举类中的泛型 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// Option和Result枚举类 就是泛型的。
// Rust中的结构体和枚举类都可以实现泛型机制。

#[derive(Debug)]
struct Point<T>{
    x: T,
    y: T
}
// 使用方法
// let p1 = Point{x:1, y:2};
// let p2 = Point{x: 1.0, y: 2.0};

// 如果想让 x与y用不同的数据类型，可以使用两个泛型标识符：
struct Point2<T1, T2>{
    x: T1,
    y: T2
}

// 枚举类型中表示泛型的方法，如 Option和Result：
enum Option<T>{
    Some(T),
    None
}

enum Result<T,E>{
    Ok(T),
    Err(E)
}

// 结构体与枚举类都可以定义方法，那么方法也应该实现泛型的机制，否则泛型的类将无法被有效地方法操作：
impl<T> Point<T>{  // impl关键字后面 必须有 <T>，因为它后面的T是以之为榜样的。
    fn x2(&self) -> &T {
        &self.x
    }
}
// let p = Point{x:1, y:2};
// println!("p.x = {}", p.x());

// 也可以为其中的 一种泛型 添加方法：
impl Point<f64>{  // 给 f64类型添加方法
    fn x(&self) -> f64{
        self.x
    }
}

// impl块本身的泛型 并没有阻碍其内部方法具有泛型的能力：
impl<T,U> Point2<T,U>{
    fn mixup<V,W>(self, other: Point2<V,W>) -> Point2<T,W>{  // self是Point<T,U>
        Point2{
            x: self.x,
            y: other.y
        }
    }
}
// 方法 mixup 将一个 Point2<T, U> 点的 x 与 Point2<V, W> 点的 y 融合成一个类型为 Point2<T, W> 的新点。

// 特性（trait） >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 概念接近于Java中的接口（interface），但两者完全不同。
// 特性 与 接口 相同的地方： 它们都是一种行为规范， 可以用于标识哪些类有哪些方法。
// 特性 在 Rust中用 trait表示：
trait Descriptive {
    fn describe(&self) -> String;  // 函数定义
}
// 以上 Descriptive 规定了实现者必需有 describe(&self) -> String 方法。
struct Person{
    name: String,
    age:  u8
}

impl Descriptive for Person{
    fn describe(&self) -> String{
        format!("{} {}", self.name, self.age)
    }
}
// 格式： impl <特性名> for <所实现的类型名>
// Rust 同一个类可以实现多个特性，每个impl块只能实现一个。

// 默认特性 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//   这是 特性 与 接口的不同点：
//     接口 只能规范方法而不能定义方法，
//     特性 可以定义方法作为默认方法， 因为是“默认”，所以对象既可以重新定义方法，也可以不重新定义方法使用默认的方法：
// e.g.:
// trait Descriptive {
//     fn describe(&self) -> String {  // 特性指定的 默认方法
//         String::from("[Object]")
//     }
// }
//
// struct Person {
//     name: String,
//     age: u8
// }
//
// impl Descriptive for Person {
//     fn describe(&self) -> String {  // 覆盖特性里的 默认方法。 如果没有这个，那么就使用特性里的默认方法
//         format!("{} {}", self.name, self.age)
//     }
// }
//
// fn main() {
//     let cali = Person {
//         name: String::from("Cali"),
//         age: 24
//     };
//     println!("{}", cali.describe());  // 结果： Cali 24  如果默认方法，结果： [Object]
// }

// 特性做参数 (类似接口定义) >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 很多情况下我们需要传递一个函数做参数，例如回调函数、设置按钮事件等。在 Java 中函数必须以接口实现的类实例来传递，在 Rust 中可以通过传递特性参数来实现：
// 
// fn output(object: impl Descriptive) {
//     println!("{}", object.describe());
// }
// 任何实现了 Descriptive 特性的对象都可以作为这个函数的参数，这个函数没必要了解传入对象有没有其他属性或方法，只需要了解它一定有 Descriptive 特性规范的方法就可以了。当然，此函数内也无法使用其他的属性与方法。
// 
// 特性参数还可以用这种等效语法实现：
// 
// fn output<T: Descriptive>(object: T) {
//     println!("{}", object.describe());
// }
// 这是一种风格类似泛型的语法糖，这种语法糖在有多个参数类型均是特性的情况下十分实用：
// 
// fn output_two<T: Descriptive>(arg1: T, arg2: T) {
//     println!("{}", arg1.describe());
//     println!("{}", arg2.describe());
// }
// 特性作类型表示时如果涉及多个特性，可以用 + 符号表示，例如：
// 
// fn notify(item: impl Summary + Display)
// fn notify<T: Summary + Display>(item: T)
// 注意：仅用于表示类型的时候，并不意味着可以在 impl 块中使用。
// 
// 复杂的实现关系可以使用 where 关键字简化，例如：
// 
// fn some_function<T: Display + Clone, U: Clone + Debug>(t: T, u: U)
// 可以简化成：
// 
// fn some_function<T, U>(t: T, u: U) -> i32
// where T: Display + Clone,
//       U: Clone + Debug
// 在了解这个语法之后，泛型章节中的"取最大值"案例就可以真正实现了：
// 
// 实例
// trait Comparable {
//     fn compare(&self, object: &Self) -> i8;
// }
// 
// fn max<T: Comparable>(array: &[T]) -> &T {
//     let mut max_index = 0;
//     let mut i = 1;
//     while i < array.len() {
//         if array[i].compare(&array[max_index]) > 0 {
//             max_index = i;
//         }
//         i += 1;
//     }
//     &array[max_index]
// }
// 
// impl Comparable for f64 {
//     fn compare(&self, object: &f64) -> i8 {
//         if &self > &object { 1 }
//         else if &self == &object { 0 }
//         else { -1 }
//     }
// }
// 
// fn main() {
//     let arr = [1.0, 3.0, 5.0, 4.0, 2.0];
//     println!("maximum of arr is {}", max(&arr));
// }
// 运行结果：
// 
// maximum of arr is 5
// Tip: 由于需要声明 compare 函数的第二参数必须与实现该特性的类型相同，所以 Self （注意大小写）关键字就代表了当前类型（不是实例）本身。

// 特性做返回值 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// 特性做返回值格式如下：
// 
// 实例
// fn person() -> impl Descriptive {
//     Person {
//         name: String::from("Cali"),
//         age: 24
//     }
// }
// 但是有一点，特性做返回值只接受实现了该特性的对象做返回值且在同一个函数中所有可能的返回值类型必须完全一样。比如结构体 A 与结构体 B 都实现了特性 Trait，下面这个函数就是错误的：
// 
// 实例
// fn some_function(bool bl) -> impl Descriptive {
//     if bl {
//         return A {};
//     } else {
//         return B {};
//     }
// }
// 有条件实现方法
// impl 功能十分强大，我们可以用它实现类的方法。但对于泛型类来说，有时我们需要区分一下它所属的泛型已经实现的方法来决定它接下来该实现的方法：
// 
// struct A<T> {}
// 
// impl<T: B + C> A<T> {
//     fn d(&self) {}
// }
// 这段代码声明了 A<T> 类型必须在 T 已经实现 B 和 C 特性的前提下才能有效实现此 impl 块。

pub fn fanxing_lianxi(){
    println!("泛型练习");

    let a = [2, 4, 6, 3, 1];
    println!("org array: {:?}, max = {}", a, max(&a));

    let p1 = Point{x:1, y:2};
    let p2 = Point{x: 1.0, y: 2.0};
    println!("p1: {:?}, p2: {:?}", p1, p2);

    let p = Point{x:1, y:2};
    println!("p.x = {}", p.x2());
}