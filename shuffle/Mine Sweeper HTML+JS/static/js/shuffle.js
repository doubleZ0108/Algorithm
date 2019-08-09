//生成从minNum到maxNum的随机数
function randomNum(minNum,maxNum){
    switch(arguments.length){
        case 1:
            return parseInt(Math.random()*minNum+1,10);
            break;
        case 2:
            return parseInt(Math.random()*(maxNum-minNum+1)+minNum,10);
            break;
        default:
            return 0;
            break;
    }
}

//洗牌算法
function shuffle() {
    console.log('shuffle...');
    for(let i=board.length-1;i>0;--i){
        let pos = randomNum(0,i);
        let buf = board[i];
        board[i] = board[pos];
        board[pos] = buf;
    }
}
