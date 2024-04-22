const db=require('../database');



const credit_withdraw={
credit_withdraw(param, callback){
    return db.query("CALL credit_withdraw(?,?)", [param.eventAmount, param.accountId],callback);
}}


module.exports=credit_withdraw;