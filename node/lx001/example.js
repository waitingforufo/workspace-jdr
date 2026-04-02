"use strict";
function isAdult(user) {
    return user.age >= 18;
}
const justine = {
    name: 'Justine',
    age: 23
};
const isJustineAnAdult = isAdult(justine);
console.log("-------\n\n rst:", isJustineAnAdult);
