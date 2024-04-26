const express=require('express');
const router=express.Router();
const debit_withdraw=require('../models/debit_withdraw_model');




router.post('/',function(request, response){
    debit_withdraw.debit_withdraw(request.body, function(err, result){
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