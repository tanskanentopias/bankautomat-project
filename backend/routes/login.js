const express=require('express');
const router=express.Router();
const card=require('../models/card_model');
const bcrypt=require('bcryptjs');
const jwt=require('jsonwebtoken');
const dotenv=require('dotenv');
dotenv.config();

router.post('/',function(request, response){
    if(request.body.username && request.body.password){
        card.login(request.body.username, function(err,result){
            if(err){
                console.log(err.errno);
                response.json(err.errno);
            }
            else{
                if(result.length >0){
                    bcrypt.compare(request.body.password, result[0].password, function(err, compareResult){
                        if(compareResult){
                            console.log('Kirjautuminen ok');
                            const token=genToken({username: request.body.username});
                            response.send(token);
                        }
                        else {
                            console.log("Väärä salasana");
                            response.send(false);
                        }
                    })
                }
                else {
                    console.log("tunnusta ei ole");
                    response.send(false);
                }

            }
        });
    }
    else {
        console.log("Tunnus tai salasana puuttuu")
        response.send(false);
    }
});

function genToken(value){
    return jwt.sign(value, process.env.MY_TOKEN, {expiresIn: '200s'});
}

module.exports=router;