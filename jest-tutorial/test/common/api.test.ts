import {getUser} from "../../src/common/api";

/***
 * getUser()内で下記のAPIを呼出ている。
 * const res = await axios.get(`https://jsonplaceholder.typicode.com/users/${id}`)
 * 
 * 上記APIの呼出をモックし、テストする。
 */

// 1. libインポート
import axios from "axios";

// 2. MOCK axios -> mockedAxios
jest.mock("axios");
const mockedAxios = axios as jest.Mocked<typeof axios>;  // axiosのMOCK版obj

// /* MOCK版
test("call getUser() using MOCK", async ()=>{

  // 3. 返却データを指定(APIからの返却値を真似る)
  const mockUser = {id: 1, name: "JDR"};

  // 4. 仮返却値mockUserを axios.getの返却値に書き込む {data: 返却したい値}
  mockedAxios.get.mockResolvedValueOnce({data: mockUser});

  try{
    const user1 = await getUser(1);

    console.log("user1:", JSON.stringify(user1));

    expect(user1).toEqual(mockUser);
    expect(mockedAxios.get).toHaveBeenCalledWith("https://jsonplaceholder.typicode.com/users/1");
  }catch(ex){
    console.error("例外発生。ex:", ex);
  };

});
// */

// /* API例外模拟
test("发送GET请求并处理例外", async ()=>{

  /* const tmpObj = {
    message: "Request failed with status code 404 ----AAAAA!",
    name: "JDRError",
    response:{
      status: 400,
      statusText: "BAD REQUEST",
      data:{
        message: "User-id must be specified."
      }
    }
  }; */

  // 模拟错误相应
  const mockException = new Error("Request failed with status code 404 ----AAAAA!");

  // 模拟GET方法并抛出错误
  mockedAxios.get.mockRejectedValue(mockException);

  try{
    //const user2 = await getUser(1);

    await getUser(1);
    expect(1).toBe(2);
  }catch(ex: any){
    console.log("api.test.ts TEST: 捕捉例外。status:", ex);
 
    //console.log("api.test.ts TEST: 捕捉例外。status:", ex.response.status);

    console.log("api.test.ts TEST: 捕捉例外。ex:", ex);
  }
})
// */

/* 普通の getUser()呼出テスト　　OK
test("call getUser()", async ()=>{

  try{
    const user1 = await getUser(1);
    console.log("user1:", JSON.stringify(user1));
  }catch(ex){
    console.error("例外発生。ex:", ex);
  };

});
*/