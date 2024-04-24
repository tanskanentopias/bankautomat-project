const express=require('express');
const router=express.Router();
const credit_withdraw=require('../models/credit_withdraw_model');




router.post('/',function(request, response){
    credit_withdraw.credit_withdraw(request.body, function(err, result){
        if(err){
            response.json(err.errno);
        }
        else{
            //response.json(result);
            response.json(result.affectedRows);
        }
    });
});

module.exports=router;