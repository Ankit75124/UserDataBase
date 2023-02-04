const  express = require('express');
const dotenv = require('dotenv');
const morgan = require('morgan');
const bodyparser = require("body-parser")
const path=require('path');
const connectDB = require('./server/database/connection');

const app=express();

dotenv.config({path:'config.env'})
const PORT=process.env.PORT  ||8080

// log request
app.use(morgan('tiny'));

// MongoDb connection
connectDB();

// parser request
app.use(bodyparser.urlencoded({extended:true}))

// set view engine
app.set("view engine","ejs")
// app.set("view",path.resolve(__dirname,"view/ejs"))     this line is for setting the path of ejs if all the ejs in not present in view folder

// load assets
app.use('/css',express.static(path.resolve(__dirname,"assets/css" )))
app.use('/img',express.static(path.resolve(__dirname,"assets/img" )))
app.use('/js',express.static(path.resolve(__dirname,"assets/js" )))

//load routers
app.use('/',require('./server/routes/router'))

app.listen(PORT,()=>{console.log(`server is running on http://localhost:${PORT}`)});
