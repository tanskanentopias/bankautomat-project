const db=require('../database');



const credit_balance={
    getAccountCredit(id, callback){
    return db.query("SELECT credit_balance FROM account WHERE id_account=?",[id], callback);
    }
}


module.exports=credit_balance;
