// 导出数组
export let months = ['Jan', 'Feb', 'Mar','Apr', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'];

export const MODULES_BECAME_STANDARD_YEAR = 2026;

export class User{
    constructor(name) {
        this.name = name;
    }
}

// export function sayHi(user){
//     alert(`Hello, ${user}!`);
// } // no ; at the end

function sayHi(user){
    //alert(`Hello, ${user}!`);
    console.log(`Hello, ${user}!`);
}

function sayBye(user){
    //alert(`Bye, ${user}!`);
    console.log(`Bye, ${user}!`);
}

export {sayHi, sayBye};  // 导出变量列表
