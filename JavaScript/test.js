var myFunction = function (a, b) {return a * b};

var x = myFunction(4, 3);


//自调用
(function (x) {
    alert(x);
})("参数");

//函数
function selfCall(){

}


//箭头函数
const arrow = (x, y) => x * y;

var z = arrow(1,2);


alert(arrow.toString());
alert(z)