const express=require('express');
const router=express.Router();
const withdraw=require('../models/withdraw_model');



router.post('/:type',function(request, response){
    withdraw.debit_withdraw(request.params.debit, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            //response.json(result);
            response.json(result.affectedRows);
        }
    });
});

router.post('/:type',function(request, response){
    withdraw.credit_withdraw(request.params.credit, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            //response.json(result);
            response.json(result.affectedRows);
        }
    });
});

module.exports=router;