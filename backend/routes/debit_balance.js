const express=require('express');
const router=express.Router();
const debit_balance=require('../models/debit_balance_model');


router.get('/:id',function(request,response){
    debit_balance.getAccountDebit(request.params.id, function(err,result){
        if(err){
            response.json(err.errno);
        }
        else{
            console.log(result);
            response.json(result[0]);
        }
    })
});


module.exports=router;