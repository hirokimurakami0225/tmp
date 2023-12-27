// モジュールロード
var os = require('os');
var fs = require('fs');
var express = require("express");
const bodyParser = require("body-parser");  //  req.body.XXXXに使用

// 自分のIPアドレスを表示
var ip = os.networkInterfaces();
console.log(os.networkInterfaces()); 

/* 1.インスタンス化してappに代入。*/
var app = express();
/* 2. listen()メソッドを実行して80番ポートで待ち受け。*/
var server = app.listen(80, function(){
    console.log("Node.js is listening to PORT:" + server.address().port);
});

/* 3. 以後、アプリケーション固有の処理 */

// 写真のサンプルデータ
var photoList = [
    {
        id: "001",
        name: "photo001.jpg",
        type: "jpg",
        dataUrl: "http://localhost:80/data/photo001.jpg"
    },{
        id: "002",
        name: "photo002.jpg",
        type: "jpg",
        dataUrl: "http://localhost:80/data/photo002.jpg"
    }
]

// 写真リストを取得するAPI
app.get("/api/photo/list", function(req, res, next){
    res.json(photoList);
    console.log("OK");
});

// View EngineにEJSを指定。
app.set('view engine', 'ejs');

//middleware
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));


let todos = [];

/*
var mdata = {
    date: "2023/12/01",
    money: 100,
};
todos.push(mdata);
todos.push(mdata);
*/


todos =JSON.parse(fs.readFileSync('hoge.json'));

var total = 0;
total = 0;
for(let todo of todos)
{
    total = total + todo.money;
}

// "/"へのGETリクエストでindex.ejsを表示する。拡張子（.ejs）は省略されていることに注意。
app.get("/", function(req, res, next){
    res.render('index', {
        title: 'ToDo App',
        todos: todos,
        total: total,
    });
    console.log("GET");
});

app.post("/", function(req, res, next){

    if ( req.body.btnAdd)
    {
        var mdata = {
            date:  new Date().toLocaleDateString('sv-SE'),
            money: parseInt(req.body.txtAdd, 10),
        };
        todos.push(mdata);

        total = 0;
        for(let todo of todos)
        {
            total = total + todo.money;
        }

        fs.writeFileSync('hoge.json', JSON.stringify(todos, null, '    '));
        console.log("Add");
    }
    if ( req.body.btnDel)
    {
        var delno =parseInt(req.body.txtDel, 10);
        todos.splice(delno-1, 1);

        total = 0;
        for(let todo of todos)
        {
            total = total + todo.money;
        }

        fs.writeFileSync('hoge.json', JSON.stringify(todos, null, '    '));
        console.log("Del");
    }

    
    console.log("POST");

    res.render('index', {
        title: 'ToDo App',
        todos: todos,
        total: total,
    });
   
});