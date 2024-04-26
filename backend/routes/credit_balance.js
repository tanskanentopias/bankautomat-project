const express=require('express');
const router=express.Router();
const credit_balance=require('../models/credit_balance_model');

router.get('/:id',function(request,response){
    credit_balance.getAccountCredit(request.params.id, function(err,result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result[0]);
        }
    })
});


module.exports=router;