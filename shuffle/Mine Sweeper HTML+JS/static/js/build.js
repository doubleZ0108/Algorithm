const boardSize = 20;   //棋盘大小默认为20 * 20
const mineNum = 50;     //雷总数默认为50个
let board = new Array(boardSize*boardSize);     //用一维数组模拟二维棋盘

window.onload = function () {
    //初始化棋盘数组
    let i=0;
    for(;i<mineNum;++i){
        board[i] = 1;
    }
    for(;i<board.length;++i){
        board[i] = 0;
    }

    //根据棋盘数组构建表格
    buildTable()
}

//监听鼠标双击事件
document.ondblclick = function () {
    console.log('double click...');

    shuffle()       //进行一次洗牌
    buildTable()    //更新棋盘
}

function buildTable() {
    let mine_table = document.getElementById('mine-table');
    mine_table.innerHTML = '';      //清空table内容

    for(let i=0;i<boardSize;++i){
        let row = document.createElement('tr');     //创建一个行元素
        for(let j=0;j<boardSize;++j){
            let elem = document.createElement('td');    //在行中创建boardSize个表格项

            let value = board[i*boardSize + j];
            elem.innerText = String(value);         //表格项的值为棋盘上对应的值
            if (value===1){     //如果该处为雷，则将表格项的类设置为mine
                elem.className = 'mine';
            }else{
                elem.className = 'no-mine';
            }

            row.appendChild(elem);
        }
        mine_table.appendChild(row);
    }

}


