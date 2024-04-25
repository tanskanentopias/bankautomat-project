const express=require('express');
const router=express.Router();
const account=require('../models/account_model');

router.get('/',function(request, response){
    account.getAccountInfo(function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

router.get('/',function(request,response){
    account.getOneAccount(request.params.usern, function(err,result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result[0]);
        }
    })
});

router.post('/',function(request, response){
    account.addAccount(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
            //response.json(result.affectedRows);
        }
    });
});




module.exports=router;