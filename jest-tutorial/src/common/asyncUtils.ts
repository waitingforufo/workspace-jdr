/***
 * 非同期処理
 */
export const fetchData = async (): Promise<string> =>{

  return new Promise((resolve)=>{
    setTimeout(()=>resolve("Hello, Jest!"), 1000);
  });
};