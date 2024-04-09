var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const jwt=require('jsonwebtoken');

var indexRouter = require('./routes/index');
var cardRouter = require('./routes/card');


var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

//suojaamattomat reitit
app.use('/', indexRouter);
app.use('/login', loginRouter);

//app.use(authenticateToken);
//suojatut reitit
app.use('/card', cardRouter);
app.use('/course', courseRouter);
app.use('/studentgrade', studentgradeRouter);



function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, function(err, user) {
  
      if (err) return res.sendStatus(403)

      req.user = user
  
      next()
    })
  }

module.exports = app;
