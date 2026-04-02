import {fetchData} from "../../src/common/asyncUtils";

// 非同期処理関数のテスト
test("fetchData() returns correct data", async()=>{
  const data = await fetchData();

  expect(data).toBe("Hello, Jest!");
})