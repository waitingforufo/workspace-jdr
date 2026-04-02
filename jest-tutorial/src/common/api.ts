import axios from "axios";

/***
 * 下記APIからデータを取得
 * https://jsonplaceholder.typicode.com/users/<id>
 * 
 * @param id: number 取得するID
 * @returns
 *     APIから取得したデータ部分
 * @throws
 *     Error 例外発生した場合
 */
export const getUser = async (id: number): Promise<any> => {

  try{
      //const res = await axios.get(`https://jsonplaceholder.typicode.com/users/${id}AB`);
      const res = await axios.get(`https://jsonplaceholder.typicode.com/users/${id}`);

      console.log("APIからの返却値：", res);
      return res.data;
  }catch(ex: any){
    console.error("API例外発生。ex:", ex);

    throw ex;
  }//end try
};