const axios=require("axios");


exports.homeRoutes=(req,res)=>{
    // make a get request to api/users
    axios.get('http://localhost:3000/api/users')
        .then(function(response){
            console.log(response.data)   //this line will print all the response data in the console log
            res.render('index', { users : response.data });
        })
        .catch(err =>{
            res.send(err);
        })
    
}

exports.add_user=(req,res)=>{
    res.render('add_user');
}

exports.update_user = (req, res) =>{
    axios.get('http://localhost:3000/api/users', { params : { id : req.query.id }})  // i have used params and id get a specific user from the database otherwise i will get all the users from the database
        .then(function(userdata){
            res.render("update_user", { user : userdata.data})  // we are getting a secific user record so we can use it in update page
        })
    // res.render('update_user');
        .catch(err =>{
            res.send(err);
        })
}