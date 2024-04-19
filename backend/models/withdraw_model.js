const db=require('../database');



const withdraw={
debit_withdraw(type, param, callback){
        return db.query("CALL debit_withdraw(?,?)", [param.eventAmount, param.accountId, type.debit],callback);
    },


credit_withdraw(type, param, callback){
        return db.query("CALL credit_withdraw(?,?)", [param.eventAmount, param.accountId, type.credit],callback);
    }}


    
module.exports=withdraw;

