#[derive(Debug)]
struct Rectangle{
    width: u32,
    height: u32
}

impl Rectangle{  // impl块可以写多次， 效果相当于它们内容的拼接
    fn area(&self) -> u32{
        self.width * self.height
    }

    fn wider(&self, rect: &Rectangle) -> bool{
        self.width > rect.width
    }

    ///结构体关联函数（静态方法） 没有&self参数，不依赖实例
    fn create(width: u32, height: u32) -> Rectangle{
        Rectangle { width, height }
    }
}

pub fn jiegouti_lianxi(){
    // Rust结构体
    // Rust中的结构体（Struct）与元祖（Tuple）都可以将若干个类型不一定相同的数据捆绑在一起形成整体，
    //   但结构体的每个成员和其本身都有一个名字，这样访问它成员的时候就不用记住下标了。
    // 元祖 常用于 非定义的多值传递，
    // 结构体用于 规范常用的数据结构。 结构体的每个成员叫做“字段”。

    // 结构体定义
    #[derive(Debug)]  // {:?}需要
    struct Site{
        domain: String,
        name:   String,
        nation: String,
        found:  u32
    }
    // Rust里结构体仅用来定义，不能声明实例，结尾不需要分号，而且每个字段定义之后用逗号分隔（跟 C语言不一样）。

    // 结构体实例
    // Rust很多地方受 JavaScript影响，在实例化结构体的时候用JSON对象的 key:vale禹发来实现定义：
    let baidu = Site{
        domain: String::from("www.baidu.com"),
        name:   String::from("baidu"),
        nation: String::from("China"),
        found:  2025
    };
    // 如果正在实例化的结构体有字段名称和现存变量名称一样的，可以简化书写(与 javaScript相同)。

    //println!("baidu: {:?}", baidu);  // OK
    println!("baidu: {:#?}", baidu);
    // 导入调试库 #[derive(Debug)]，之后再println, print宏中就可以用 {:?}, {:#?}占位符输出整个结构体。
    // 属性较多，就用竖向显示的 {:#?}

    // 结构体更新语法 （仅需更改其中几个字段的值）
    let site = Site{
        domain: String::from("www.yahoo.com.cn"),
        name:   String::from("YAHOO CHINA"),
        ..baidu                                       // 其他的值都跟 baidu结构体一样
    };

    // 元祖结构体
    // 有一种更简单的定义和使用结构体的方式： 元祖结构体
    // 与 元祖 的区别是， 它 有名字 和 固定的 类型格式。
    //   它存在的意义是： 为了处理那些需要定义类型（经常使用）又不想太复杂的简单数据：

    struct Color(u8, u8, u8);
    struct Point(f64, f64);

    let black = Color(0, 0, 0);
    let origin = Point(0.0, 0.0);
    // 颜色 和 坐标点 是常用的两种数据类型， 但如果实例化时写个大括号再写上两个名字就为了可读性牺牲了便捷性，
    //   Rust不会遗留这个问题。
    //   元祖结构体 对象的使用方式和元祖一样， 通过 . 和下标来进行访问：

    println!("black = ({}, {}, {})", black.0, black.1, black.2);
    println!("origin = ({}, {})", origin.0, origin.1);

    // 结构体方法 （method 必须实例化后才能调用的函数）
    // 第一个参数必须是 &self， 不需要声明类型，因为 self 不是一种风格 而是关键字。
    // 计算一个矩形的面积：

    let rect1 = Rectangle{width: 30, height: 50};
    println!("rect1's area is {}", rect1.area());

    // 结构体关联函数（静态函数 不依赖实例，故没有 &self参数）
    let rect2 = Rectangle::create(30, 50);
    println!("rect2 : {:?}", rect2);

    // 单元结构体
    //   结构体可以只作为一种象征而无需任何成员：
    struct UnitStruct;
    // 这样的结构体 称之为 单元结构体（Unit Struct）
}