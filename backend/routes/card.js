const express=require('express');
const router=express.Router();
const card=require('../models/card_model');

router.get('/',function(request, response){
    card.getCardInfo(function(err, result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result);
        }
    });
});

router.get('/:usern',function(request,response){
    student.getOneStudent(request.params.usern, function(err,result){
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
    card.addCard(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            response.json(result);
            //response.json(result.affectedRows);
        }
    });
});

router.put('/:usern', function(request, response){
    student.updateStudent(request.params.usern, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            //response.json(result);
            console.log(result.affectedRows);
            response.json(result.affectedRows);
        }
    });
});

router.delete('/:usern',function(request, response){
    card.deleteCard(request.params.usern, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            //response.json(result);
            console.log(result.affectedRows);
            response.json(result.affectedRows);
        }
    });
});


module.exports=router;