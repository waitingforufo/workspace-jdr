import {isZero} from "../../src/common/jdr-util";  // OK
//import * as jdrUtil from "../../src/common/jdr-util";  // OK

test("0を渡したらtrueになること", () => {
  const rst = isZero(0);            // OK
  //const rst = jdrUtil.isZero(0);  // OK

  expect(rst).toBe(true);
});

test("1を渡したらfalseになること", ()=>{
  const rst = isZero(1);

  expect(rst).toBe(false);
})