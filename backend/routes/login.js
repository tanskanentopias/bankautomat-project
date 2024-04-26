const express=require('express');
const router=express.Router();
const card=require('../models/card_model');
const bcrypt=require('bcryptjs');
const jwt=require('jsonwebtoken');
const dotenv=require('dotenv');
dotenv.config();

router.post('/',function(request, response){
    if(request.body.card_serial && request.body.card_pin){
        card.login(request.body.card_serial, function(err,result){
            if(err){
                console.log(err.errno);
                response.json(err.errno);
            }
            else{
                if(result.length >0){
                    bcrypt.compare(request.body.card_pin, result[0].card_pin, function(err, compareResult){
                        if(compareResult){
                            console.log('Kirjautuminen ok');
                            const token=genToken({card_serial: request.body.card_serial});
                            const id_account = result[0].account;
                            const card_type = result[0].card_type;
                            response.json({token, id_account, card_type});
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