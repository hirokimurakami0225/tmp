const express = require('express')
const path = require('path')
const multer = require('multer')

const app = express()
const port = 80

const storage = multer.diskStorage({
  destination: function (req, file, cb) {
    cb(null, 'public/uploads/')
  },
  filename: function (req, file, cb) {
    cb(null, file.originalname)
  }
})
//const upload = multer({ dest: 'public/uploads/' })
const upload = multer({ storage: storage })

app.use(express.static(path.join(__dirname, 'public')))

app.get('/', (request, response) => response.send('Hello World!'))

app.get('/upload', (req, res) => res.sendFile(path.join(__dirname, 'public/upload.html')))

app.post('/upload', upload.single('file'), function (req, res, next) {
  console.log(req.file);
  res.send('ファイルのアップロードが完了しました。');
});

app.listen(port,function(){
	console.log(`Example app listening on port ${port}!`)
})	