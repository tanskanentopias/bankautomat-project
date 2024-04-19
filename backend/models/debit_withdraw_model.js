const db=require('../database');



const debit_withdraw={
debit_withdraw(param, callback){
        return db.query("CALL debit_withdraw(?,?)", [param.eventAmount, param.accountId],callback);
    }}

    
module.exports=debit_withdraw;

