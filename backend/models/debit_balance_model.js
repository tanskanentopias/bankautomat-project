const db=require('../database');



const debit_balance={
    getAccountDebit(id, callback){
    return db.query("SELECT debit_balance FROM account WHERE id_account=?",[id], callback);
    }
}


module.exports=debit_balance;
