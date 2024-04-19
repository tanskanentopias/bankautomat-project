const express=require('express');
const router=express.Router();
const event=require('../models/event_model');



router.post('/:id',function(request,response){
    event.getEvents(request.params.id, function(err,result){
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