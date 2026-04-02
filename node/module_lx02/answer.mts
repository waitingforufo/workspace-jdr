import { calculation } from './function.mjs';  // ファイルは .mts でもコンパイル後のファイルを指定するので　.mjs

const answer : number[] = calculation(100,10);

console.log(answer);

/**
 * 先に必ずコンパイルしてから　node answer.mts   or    node answer.mjsで実行OK
 *   npx tsc
 *
 * PS D:\workspace-jdr\node\module_lx02> node answer.mts
 * [ 110, 90, 1000, 10 ]
 */

